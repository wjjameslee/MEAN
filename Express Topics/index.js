//index.js

require('./api/data/db.js');
// As soon as the application starts, it will try to open the MongoDB connection; Edit: we now use Mongoose
var express = require('express');
var app = express();
var path = require('path'); // native module needed to send file
var bodyParser = require('body-parser');  //
var routes = require('./api/routes');

app.set('port', 3000); // Express variables  
// app.listen(3000);  // check on localhost:3000 in the browser. It is hardcoded and we do not want that.

app.use(function(req, res, next) {
	console.log(req.method, req.url);
	next();
});

app.use(express.static(path.join(__dirname, 'public'))); 
app.use(bodyParser.urlencoded( {extended : false} )); 
app.use('/api', routes);

/*
// returns json for use such as api
app.get('/json', function(req, res) {
	console.log('GET the json');
	res
		.status(200)
		.json({"jsonData" : true});
});

app.get('/file', function(req, res) {
	console.log('GET the file');
	res
		.status(200)
		.sendFile(path.join(__dirname, 'index.js'));
});
*/

var server = app.listen(app.get('port'), function() {
	var port = server.address().port;
	console.log('Magic happens on port ' + port);
});
// console.log('Magic happens on port ' + app.get('port'));
// The console.log above does not signal that the app is listening so.. we use a callback in app.listen

// We can verify that app.listen is asynchronous by adding another console.log to see that it does not interrupt flow:
// console.log('Me first!');

