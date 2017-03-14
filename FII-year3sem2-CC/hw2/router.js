var handlerFactory = require('./handler');
var fs = require('fs');
var parser = require('url');
var handlers = {};

exports.clear = function() {
  handlers = {};
}

exports.register = function(url, method) {
  handlers[url] = handlerFactory.createHandler(method);
}

exports.route = function(req) {
  url = parser.parse(req.url, true);
  var handler = handlers[url.pathname];
  if (!handler) handler = this.missing(req)
  return handler;
}

exports.missing = function(req) {
  // Try to read the file locally
  var url = parser.parse(req.url, true);

  var checkStr = url.pathname;
  console.log('url.pathname: ', checkStr);

  //this is a security hole, yo /../../etc/passwd
  var test = checkStr.includes('..');
  if(test){
    var path = __dirname + "/public";
  } else {
    var path = __dirname + "/public" + checkStr;
  }

  try {    
    data = fs.readFileSync(path);

    console.log('checkStr: ', checkStr);
    console.log('path: ', path);

    mime = req.headers.accepts || 'text/html'
    return handlerFactory.createHandler(function(req, res) {
      res.writeHead(200, {'Content-Type': 'text/html'}); //text/plain
      res.write(data);
      res.end();
    });        
  } catch (e) { 
    return handlerFactory.createHandler(function(req, res) {
      res.writeHead(404, {'Content-Type': 'text/plain'}); //text/plain
      res.write("No route registered for " + url.pathname);
      res.end();
    });      
  }  
}
