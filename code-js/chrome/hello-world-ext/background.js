// chrome.app.runtime.onLaunched.addListener(function() {
// });
chrome.browserAction.onClicked.addListener(function(tab) { 
	chrome.tabs.create({url: "/page/page.html"});
});
