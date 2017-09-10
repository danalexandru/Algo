/*
Popup module
*/
//var rootFolderContainer = null;
var chromeBookmarksLink = 'chrome-extension://eemcgdkfndhakfknompkggombfjjjeno/main.html';
//depending on settings, chrome://bookmarks/ can redirect to the above


$(function() {

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
