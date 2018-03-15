/*
Popup module
*/
//var rootFolderContainer = null;
var chromeBookmarksLink = 'chrome-extension://eemcgdkfndhakfknompkggombfjjjeno/main.html';
//depending on settings, chrome://bookmarks/ can redirect to the above


$(function() {
	var bookmarkData = null;

	function loopFoldersRec(parentId, parentObject){
		//console.log('Looping through root folders');
		var container = $(parentId);

		for (var i = 0; i < parentObject.children.length; i++) {
			var parent1 = parentObject.children[i];

			if (parent1.children) {
				//console.log(parent1);
				var id = parent1.id;
				var nodeUrl = chromeBookmarksLink + '#' + id;

				//document.createElement('a')
				var anchor = $('<a>');
				anchor.attr('href', nodeUrl);
				anchor.text(parent1.title);//or append ?
		
				anchor.click(function() {
					console.log('Accessed:', $(this).attr('href'))
					chrome.tabs.create({url: $(this).attr('href')});
				});
				anchor.attr('id', 'bookmark-' + id + '-title');

				var li = $('<li>').append(anchor);
				var ul = $('<ul>').attr('id', 'bookmark-' + id);
				li.append(ul);

				container.append(li);

				loopFoldersRec('#bookmark-' + parent1.id, parent1);
			}
		}
	}

	function dumpBookmarks(){
		$('#bookmarkContainer').empty();

		var bookmarkTreeNodes = chrome.bookmarks.getTree(
			function(bookmarkTreeNodes) {
				// var list = $('<ul id="bookmarkContainer">');
				// $('#bookmarks').append(list);

				var parentObject = bookmarkTreeNodes[0];
				//rootFolderContainer = parent;
				console.log(parentObject);

				bookmarkData = parentObject;

				loopFoldersRec('#bookmarkContainer', parentObject);
				console.log('###################');
			}
		);
	}

	//$('#dump-folders').click(dumpBookmarks);
	$('#dump-folders').click(function(){
		console.log('Dumping folders');
		dumpBookmarks();
	});

	$('#clear-output').click(function(){
		console.log('Clearing output');
		$('#bookmarkContainer').empty();
	});

	// https://stackoverflow.com/questions/4845215/making-a-chrome-extension-download-a-file
	$('#download-bookmarks-json').click(function(){
		console.log('Download bookmarks');

		var exportObj = bookmarkData;
		var exportName = 'safe_bookmarks.json';

		var dataStr = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(exportObj));
		var node = document.createElement('a');

		node.download = exportName;
		node.href = dataStr;
		node.click();

		chrome.downloads.download({
		  url: dataStr,
		  filename: exportName// Optional
		});
	});

	//https://stackoverflow.com/questions/11257062/converting-json-object-to-csv-format-in-javascript
	$('#download-bookmarks-csv').click(function(){
		console.log('Download bookmarks');

		// var exportObj = bookmarkData;
		// var exportName = 'safe_bookmarks.csv';
	});

	function setBadge(){
		chrome.browserAction.setBadgeText({
			"text": "!"
		});
		chrome.browserAction.setBadgeBackgroundColor({
			"color": "#dc3545" //"#00cc00"
		});
	}

	console.log('Loaded');
	dumpBookmarks();
	setBadge();
});
