//Utility functions to simplify 
//needed calls within route register

function isObject(obj) {
  return obj !== null && typeof obj === 'object';
}

exports.params = function(req){
  var query = req.url.split('?');
  var result = {};
  if(query.length >= 2){
      query[1].split('&').forEach((item)=>{
           try {
             result[item.split('=')[0]]=item.split('=')[1];
           } catch (e) {
             result[item.split('=')[0]]='';
           }
      })
  }
  return result;
}

exports.redirect = function (req, res, address){
  req.url += address;

  res.writeHead(302, {'Location': req.url});
  res.end();
}

exports.reflectMethod = function (req, res){
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.write('You just ' + req.method + 'ed');
  res.end();
}

exports.send = function(req, res, msg){
  //console.log('msg: ', msg);
  //res.setHeader('transfer-encoding', '');
  if(isObject(msg)){
  	res.writeHead(200, {'Content-Type': 'text/plain'}); //application/json
  	msg = JSON.stringify(msg);
  } else {
  	res.writeHead(200, {'Content-Type': 'text/plain'});
  }
  res.write( msg.toString() );
  res.end();
}

