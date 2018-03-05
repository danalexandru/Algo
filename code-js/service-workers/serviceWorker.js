
console.log('service worker loaded');

const cachePrefix = 'static-';
let currentCache = null;

self.addEventListener('install', event => {
	event.waitUntil(
		new Promise(function(resolve, reject) {
			fetch('resources-manifest.json')
				.then(resp => resp.json())
				.then(respJson => {
					console.log('haoleo');
					console.log(respJson['TO_PRECACHE']);
					
					let myCache = null;
					currentCache = cachePrefix + respJson['VERSION'];
					//debugger;

					if (currentCache in caches.keys()){
						console.log('cache exists');
						console.log('keys: ', caches.keys());
						resolve();
					} else {
						Promise.all(
							respJson['TO_PRECACHE'].map(function(item){
								console.log("cache doesn't exists, downloading");
								caches.open(currentCache)
									.then(cache => {
										myCache = cache;

										return cache.match(item);
									})
									.then(resp => {
										if (resp) {
											return resp;
										}
										return fetch(item);
									})
									.then(resp => {
										//wat ?
										const response = resp.clone();
										myCache.put(item, resp);

										return response;
									})
							})
						).then(resolve);
					}
				})
				.then(function(){
					console.log('service worker installed');
				})
				.catch(err => function(err){
					console.log(err);
					reject();
				});
		})
	);
});

self.addEventListener('fetch', function(event) {


	//waitUntil > promise > function run
	//function doesn't have to be defined in the same context
	function cacheServeHandler(){
		if (currentCache) {
			caches.open(currentCache)
				.then(cache => {
					//myCache = cache; ?
					//const response = resp.clone();
					console.log('Opened cache');

					event.respondWith(
					    cache.match(event.request).then(function(response) {
					      return response || fetch(event.request);
					    })
					  );
				})
		} else {
			console.log("Cache doesn't exist !");
		}
	}

	event.waitUntil(new Promise(function(resolve, reject) {
		cacheServeHandler();
	}));
});

// completeaza cu logica din branch day11
self.addEventListener('fetch', function(event) {
  event.respondWith(
    caches.match(event.request).then(function(response) {
      console.log('cache match found');
      return response || fetch(event.request);
    })
  );
});

//const cacheName = 'hamster';

// self.addEventListener('fetch', (event) => {
// 	console.log('din worker', event);
// 	if (event.request.url.indexOf('dog.ceo/api') !== -1){
// 		const bogusResp = {
// 			message: {
// 				gigi: [],
// 				vasile: [],
// 				filofteea: []
// 			}
// 		};

// 		let myCache = null;
// 		//event.respondWith(new Response(JSON.stringify(bogusResp)));
// 		event.respondWith(
// 			//new Response(JSON.stringify(bogusResp))
// 			caches.open(cacheName)
// 				.then(cache => {
// 					myCache = cache;

// 					return cache.match(event.request);
// 				})
// 				.then(resp => {
// 					if (resp) {
// 						return resp;
// 					}
// 					return fetch(event.request);
// 				})
// 				.then(resp => {
// 					//wat ?
// 					const response = resp.clone();
// 					myCache.put(event.request, resp);

// 					return response;
// 				})
// 		);
// 	}
// });

