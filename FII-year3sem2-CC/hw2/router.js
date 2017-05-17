var handlerFactory = require('./server/handler');
var fs = require('fs');
var parser = require('url');
var handlers = {};

var utils = require('./server/utils');

function mimeType(path){
  var data = fs.readFileSync('server/mime.json')
  var mimeObj = JSON.parse( data );

  var pathExt = path.substr( path.indexOf('.') + 1 );
  //console.log('pathExt: ', pathExt);

  var mimeType;
  Object.keys(mimeObj).forEach(function(key) {
    if (key == pathExt) {
      //console.log('mimeObj[key]: ', mimeObj[key]);
      mimeType = mimeObj[key];
    }
  });
  return mimeType || 'text/html';
}

exports.clear = function() {
  handlers = {};
}

exports.register = function(url, callback) {
  handlers[url] = handlerFactory.createHandler(callback);
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
  console.log(req.method, checkStr);

  //this is a security hole, yo /../../etc/passwd
  var test = checkStr.includes('..');
  if(test){
    var path = __dirname + "/public";
  } else {
    var path = __dirname + "/public" + checkStr;
  }

  try {    
    var data = fs.readFileSync(path);
    //console.log('checkStr: ', checkStr);
    //console.log('path: ', path);

    //mime = req.headers.accepts || mime_type(path);
    var mime = mimeType(path);
    console.log('  mime selected: ', mime);

    return handlerFactory.createHandler(function(req, res) {
      res.writeHead(200, {'Content-Type': mime});
      res.write(data);
      res.end();
    });        
  } catch (e) { 
    return handlerFactory.createHandler(function(req, res) {
      // hardcoded response
      // res.writeHead(404, {'Content-Type': 'text/plain'}); //text/plain
      // res.write("No route registered for " + url.pathname);
      // res.end();
      //or
      res.writeHead(404, {'Content-Type': 'text/plain'});
      utils.redirect(req, res, '404.html')
    });      
  }  
}
