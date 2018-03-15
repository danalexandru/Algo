import json
import pandas as pd

with open('safe_bookmarks.json') as file:
	obj = json.loads(file.read())
	print(type(obj))
	print(obj.keys())

leafs = []
def paginate_obj(bookmarks):
	if 'children' in bookmarks:
		for child in bookmarks['children']:
			paginate_obj(child)
	else:
		leafs.append(bookmarks)

	return leafs

results = paginate_obj(obj)
print(len(results))

df = pd.DataFrame(results) #  columns=["colummn"]
df.to_csv('safe_bookmarks_leafs.csv', index=False)