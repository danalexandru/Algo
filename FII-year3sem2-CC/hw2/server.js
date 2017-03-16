var http = require('http');
var router = require('./router');

var mongoose = require('mongoose');
var dbConfig = require('./server/config/db');

var utils = require('./server/utils');


//DB connection
db = mongoose.connect(dbConfig.url, function (err) {
  if (err) {
    console.log(err);
  }
  console.log('Connected to DB.');
});

var requestBody;
var requestParams;

// Main Route
router.register('/', function(req, res) {
  utils.redirect(req, res, 'index.html')
});

// res.writeHead(200, {'Content-Type': 'text/plain'});
// res.write('Hello World');
// res.end();

// API Route
var Message = require('./server/model/messageModel');

router.register('/api/messages', function(req, res){
  console.log(req.method, '/api/messages');

  if(req.method == 'GET'){
    var message = new Message();

    mongoose.connection.db.collection("messages", function (err, collection) {
      if(err){
        console.log(err);
        return utils.send(req, res, err);
      }

      collection.find({}).toArray(function(err,docs){
        if(err){
          console.log(err);
          return utils.send(req, res, err);
        }
        //console.log(docs);
        return utils.send(req, res, docs);
      });
    });
  } else if(req.method == 'POST') {
    console.log(req.body); //in express body-parser does it for you
    console.log(requestBody); //but at CC, you do it for you

    var message = new Message(JSON.parse(requestBody));
    
    message.save(function (err, message) {
      if (err) {
        console.log(err);
        return utils.send(req, res, req);
      }
        return utils.send(req, res, {message: "Successfully added new message.", data: message});
    });

  } else if(req.method == 'PUT') {
    console.log(requestBody);

    var reqObj = JSON.parse(requestBody);
    //var message = new Message();
    
    Message.findById(reqObj._id, function (err, message) {
      if (err) {
        console.log(err);
        return utils.send(req, res, req);
      } else {
        console.log('found message ! => reqObj._id: ', reqObj._id);
        //utils.send(req, res, {message: "Successfully updated message.", data: message});
        message.timestamp = Date.now(); //Date.now()
        message.content = reqObj.content;

        message.save(function(err){
          if(err){
            console.log(err);
            return utils.send(req, res, req);
          } else {
            return utils.send(req, res, {message: "Successfully updated message.", data: message});
          }
        });
      }
    });

  } else if(req.method == 'DELETE'){
    //console.log(req.params.id); 
    //console.log(requestParams); //same stuff
    console.log(requestBody);

    Message.remove({_id: requestBody}, function (err) {
      if (err) {
        return utils.send(req, res, err);
      }
      return utils.send(req, res, {message: 'Successfully removed message.'});
    });
  } else {
   utils.reflectMethod(req, res);
  }
});


// We need a server which relies on our router
var server = http.createServer(function (req, res) {
  requestBody = [];
  //requestParams = {};
 
  if(req.method == 'POST'|| req.method == 'PUT' || req.method == 'DELETE'){
    req.on('data', chunk => {
      console.log('A chunk of data has arrived: ', chunk);
      requestBody.push(chunk);
    });
    req.on('end', () => {
      console.log('No more data');
      requestBody = Buffer.concat(requestBody).toString();

      handler = router.route(req);
      handler.process(req, res);
    });
  } else {
    handler = router.route(req);
    handler.process(req, res);
  }

  //requestParams = utils.params(req);

  
});

// Start it up
server.listen(8081);
console.log('Server running on port 8081');