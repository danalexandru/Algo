var express = require('express');
var path = require('path');
var logger = require('morgan');
var bodyParser = require('body-parser');

var services = require('./server/services')


var app = express();

app.use('/public', express.static(path.join(__dirname, '/public')));
app.use(logger('dev'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

// app.get('/', function(req, res) {
//   res.redirect('/public');
// });
app.use(express.static('public'));


// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
  app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
      message: err.message,
      error: err
    });
  });
}

// === Routes ===

// app.get('/internship', function(req, res) {
//   res.json('erm, not here');
// });

app.use('/', services);


module.exports = app;