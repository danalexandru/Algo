var express = require('express');
var app = express();
var session = require('express-session')

var http = require('http').Server(app);
var io = require('socket.io')(http);
var ss = require('socket.io-stream');

var path = require('path');
var port = process.env.PORT || 3000;

app.use('/public', express.static(path.join(__dirname, '/public')));
app.use(express.static('public'));

app.use(session({
  secret: 'keyboard cat',
  resave: false,
  saveUninitialized: true
}))


app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});


/**** main page ****/
app.get('/id', function(req, res){
  //console.log(req);
  res.send(req.sessionID);
});

io.on('connection', function(socket){
  socket.on('chat message', function(msg){
    io.emit('chat message', msg);
  });

  socket.on('new player', function(otherBunny){
    io.emit('new player', otherBunny);
  });

  socket.on('stream', function(img){
    io.emit('stream', img);
  });
 
  // var filename = 'profile.jpg';
  // ss(socket).on('stream-image', function(stream, data) {
  //   var filename = path.basename(data.name);
  //   stream.pipe(fs.createWriteStream(filename));
  // });
  
  // ss(socket).on('file', function(stream) {
  //   fs.createReadStream('/path/to/file').pipe(stream);
  // });
    
  // ss(socket).emit('file', stream);
  // stream.pipe(fs.createWriteStream('file.txt'));

  
});


/**** webcam page ****/
app.get('/webcam-stream', function(req, res){
  res.sendFile(__dirname + '/public/webcamStream.html');
});

app.get('/webcam-client', function(req, res){
  res.sendFile(__dirname + '/public/webcamClient.html');
});


http.listen(port, function(){
  console.log('listening on *:' + port);
});