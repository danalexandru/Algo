var http = require('http');

var url = require('url');

var server = http.createServer(function (request, response) {

	request.on('error', function(err) {
	    console.error(err);
	    response.statusCode = 400;
	    response.end();
  	});

	response.on('error', function(err) {
    	console.error(err);
  	});

  console.log('Method used: ', request.method);

  if(request.method == 'GET'){
    var urlObject = url.parse(request.url);
    //console.log(urlObject);

    var method = request.method; //The request object is an instance of IncomingMessage
  	var urlUsed = request.url;
  	var headers = request.headers; //mai exista optiunea rawHeaders
  							//.headers returneaza obiect, rawHeaders returneaza txt
  							//rawHeaders include userAgent, deci daca il folosesti, userAgent va returna undefined
  	var userAgent = headers['user-agent'];

     // Send the HTTP header 
     // HTTP Status: 200 : OK
     // Content Type: text/plain
     response.writeHead(200, {'Content-Type': 'text/plain'});
     
     // Send the response body as 'Hello World'
     var methodChunk ='METHOD: ' + method + '\n';
     var urlChunk = 'URL: ' + urlUsed + '\n';
     var headersChunk = 'HEADERS: ' + headers + '\n';
     var userAgentChunk = 'USERAGENT: ' + userAgent + '\n';


     var respBody = methodChunk + urlChunk + headersChunk + userAgentChunk ;
     response.end(respBody);
  } else if (request.method == 'POST') {
    var urlObject = url.parse(request.url);
    //console.log(urlObject);

    var method = request.method;
    var urlUsed = request.url;
    var headers = request.headers;
    var userAgent = headers['user-agent'];

    var jsonObj = {}
    jsonObj['method'] = method;
    jsonObj['urlUsed'] = urlUsed;
    jsonObj['headers'] = headers;
    jsonObj['userAgent'] = userAgent;

    console.log(jsonObj);

    response.writeHead(200, {'Content-Type': 'application/json'});
    response.end( JSON.stringify(jsonObj) );
  }

  console.log('\n\n');
  response.end();
});

server.listen(8081);

exports.server = server;

// Console will print the message
console.log('Server running at http://127.0.0.1:8081/');
