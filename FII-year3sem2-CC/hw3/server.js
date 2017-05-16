var express = require('express');
var app = express();
var session = require('express-session')

var http = require('http').Server(app);
var io = require('socket.io')(http);

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
  
});

app.get('/webcam', function(req, res){
  res.sendFile(__dirname + '/public/webcam.html');
});


http.listen(port, function(){
  console.log('listening on *:' + port);
});