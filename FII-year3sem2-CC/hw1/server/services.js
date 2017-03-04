var fs = require('fs');

var express = require('express');
var request = require('request');
var router = express.Router();

var keysObject = JSON.parse(fs.readFileSync('server/api_keys/keys.json', 'utf8'));

/* GET API page. */
// router.get('/some_api', function (req, res) {
//     res.json('erm, not here');
// });

// router.get('/books', function (req, res) {
// 	res.setHeader('Content-Type', 'application/json');
// 	request.get({
// 	  url: 'https://www.googleapis.com/books/v1/volumes?q=' + 'neural',
// 	}, function(err, response, body) {
// 	  res.send(JSON.stringify(JSON.parse(body), null, 2) );
// 	})
// });

var weatherAPIkey = keysObject.weatherAPI;
console.log("[API] weather API key is: ", weatherAPIkey);

/* GET weather page */
router.get('/weather', function (req, res) { // /:city
	if(weatherAPIkey[0] == '<'){
		res.setHeader('Content-Type', 'application/json');
		res.send(JSON.stringify(
			{"Server response": "No API key present"},
			null, 2
		));
	} else {
		res.setHeader('Content-Type', 'application/json');
		request.get({
		  url: 'http://api.openweathermap.org/data/2.5/weather?' +
		  			'q=' + 'Iasi,RO' + // req.params.city?req.params.city:'Iasi,RO' +
		  			'&units=metric' + 
		  			'&appid=' + weatherAPIkey
		}, function(err, response, body) {
		  //full response
		  //res.send(JSON.stringify(JSON.parse(body), null, 2) );
		  var weatherObj = JSON.parse(body);
		  var displayObj = {};

		  displayObj.description = weatherObj.weather[0].description;
		  //console.log('description: ', displayObj.description);
		  
		  displayObj.icon = weatherObj.weather[0].icon;
		  //console.log('icon: ', displayObj.icon);

		  displayObj.temp = weatherObj.main.temp;
		  //console.log('temp: ', displayObj.temp);

		  displayObj.name = weatherObj.name;
		  //console.log('name: ', displayObj.name);

		  displayObj.country = weatherObj.sys.country;
		  //console.log('country: ', displayObj.country);

		  res.send(JSON.stringify(
		  	displayObj, 
		  	null, 2) 
		  );
		})
	}
});


var newsAPIkey = keysObject.newsAPI;
console.log("[API] news API key is: ", newsAPIkey);

/* GET NEWS page */
router.get('/news', function (req, res) {
	if(newsAPIkey[0] == '<'){
		res.setHeader('Content-Type', 'application/json');
		res.send(JSON.stringify(
			{"Server response": "No API key present"},
			null, 2
		));
	} else {
		res.setHeader('Content-Type', 'application/json');
		request.get({
		  url: 'https://newsapi.org/v1/articles?' + 
		  		'source=the-next-web' + 
		  		'&sortBy=latest' + 
		  		'&language=en' + 
		  		'&category=technology' + 
		  		'&apiKey=' + newsAPIkey
		}, function(err, response, body) {
		  //full response
		  res.send(JSON.stringify(JSON.parse(body), null, 2) );
		})
	}
});

module.exports = router;
// exports.router = router;
