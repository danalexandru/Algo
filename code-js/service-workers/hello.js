// https://codepen.io/beaucarnes/pen/KmeRMx?editors=0011

(function () {
	console.log('hello.js initialized');


	/*
	 * Local storage is synchronous !
	 */
	function localStorageObjectExists(itemName) {
		var ls = localStorage;
		
		var retrievedItem = ls.getItem(itemName);
		return retrievedItem == null ? false:true;
	}
	
	function localStorageObjectExistsTest(itemName) {
		var ls = localStorage;
		
		var retrievedItem = ls.getItem(itemName);
		console.log(itemName + ': '
			, retrievedItem == null ? "Doesn't exist":'Exists');
	}

	// test function
	function localStorageTest() {
		console.log('--- localStorageTest started ---');

		var ls = localStorage;
		ls.setItem('lunch', 'cereal');

		console.log(localStorageObjectExists('lunch'));
		localStorageObjectExistsTest('breakfast');
		localStorageObjectExistsTest('lunch');

		console.log('--- localStorageTest finished ---');
	}

	// -------------------------------------------------
	// #################################################

	/*
	 * Web worker - generalize this code !
	 */

	 function handleWorker(){
		w.onmessage = function(event){
			document.getElementById("result").innerHTML = event.data;

			console.dir(event);
			//if(event.data == 20){
			//	stopWorker(); //stop worker on 20th iteration
			//}
		};
	  }

	  function startWorker(){
		//check for web worker support
		if(typeof(Worker) !== "undefined") {
			if (typeof(w) == "undefined") {
				w = new Worker("demo_workers.js");
				document.getElementById("status").innerHTML = 'Worker started';

				handleWorker();
			} else {
				document.getElementById("status").innerHTML = 'Worker variable already exists !';
			}
		} else {
			document.getElementById("status").innerHTML = "Sorry! No Web Worker support.";
		}
	  }

	  function stopWorker(){
		w.terminate();
		w = undefined;
		document.getElementById("status").innerHTML = 'Worker terminated !';
	  }

	// -------------------------------------------------
	// #################################################

	/*
	 * Service worker - generalize this code !
	 */
	
	function serviceWorkerSupportExists() {
		return 'serviceWorker' in navigator;
	}

	function serviceWorkerRegister(filename) {
		if (serviceWorkerSupportExists()) {
			window.addEventListener('load', function() {
				navigator.serviceWorker.register(filename).then(function(registration) {
				  // Registration was successful
				  console.log('ServiceWorker registration successful with scope: ', registration.scope);
				}, function(err) {
				  // Registration failed :(
				  console.log('ServiceWorker registration failed: ', err);
				});
			  });
		}
	}

	// test function
	function serviceWorkerTest() {

		serviceWorkerRegister('/sw.js');
	}

	// -------------------------------------------------
	// #################################################


	localStorageTest();
	//webWorkerTest();
	//serviceWorkerTest();

})();