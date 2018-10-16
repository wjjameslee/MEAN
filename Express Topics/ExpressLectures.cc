Express is the web application framework in the MEAN stack
(ie.) Listens to incoming requests and responds

To run Express, start by typing the following code to run Express:
	var express = require('express');
	var app = express();


app.listen() is a asynchronous function, meaning when the console.log is executed in the index.js file, we do not know if the app is really listening..
Solution? Use a callback once again in app.listen()

Also app.listen() returns an object so we can do something like this:
	var express = require('express');
	var app = express();
	app.set('port', 3000);
	var server = app.listen(app.get('port'), function() {
		var port = server.address().port;
		console.log('Magic happens on port ' + port);
	});
	console.log('Me first!');


To change the method (get,post...etc) in terms of Express, we do:
	app.get('/', function(req, res) {
		console.log("GET the homepage");
	});

	The function inside app.get requires two parameters, the request object and the reponse object.
	We shall call them req and res.

	If we try running our app, we see that by visiting localhost:3000, 
	the website does not show anything and an output of "GET the homepage" is displayed on the terminal
	This is normal because we have not specified what the server should send back in the request
	Add "res.send("Express Yourself");" into app.get() ...

	We can also change the status of webpage load by adding in
	res 
		.status(404) // changes status to 404... NOTE there is no semicolon following 404...
		.send("Express Yourself!");


__dirname finds the current directory of the app file when used in path.find(...)


Sending static files over Express:
	A good practice in sending static files is to put them inside a folder called public!

.sendFile(path.join(__dirname, 'public', 'index.html'));  // instead of directly putting in public/index.html, 
		// avoids syntax errors in different OS

we can also app.use('/public', express.static(path.join(__dirname, 'public'))); which specifies 
the homepage to be accessed at the URL: localhost:3000/public/index.html



Using Middleware:
	the ".use" signals that we using some middleware.
	Any request that comes in will run through that functionality in the app.use() and keep repeating until all requests are processed.
	app.use(function(req, res, next) {
		console.log(req.method, req.url);
		next();
	});

	Order matters when you putting these inside your code. It runs sequentially, in the order that they appear in the code.


Using Express Router:
	express.Router();

	Code can get messy so it is wise to consider separation.  -> Create and use routes!
	Use a router, you can chain different methods to a single route.
	(Router -> Methods -> Controllers -> Manage Data)
	Adding controllers = better code architecture.



Adding dynamic routes:
 	Given our API, what if we want to pick only one hotel. Also what if we do not want to do it manually?
 	use .route('/hotels/:hotelId') where hotelId is a parameter which a controller can access...

 	URL parameters can be accessed using the request object.. like req.params.hotelId
 	Use this to query data as an index of an array...

req.query allows you to make querystrings such that 
by visiting localhost:3000/api/hotels?offset=2&count=2 you can return specific amount of data 
offset and count are two properties of the querystring 


if (req.query && req.query.offset) {
		offset = parseInt(req.query.offset, 10);
	}

offset value from req.query are strings so we need to parse it and send return it to the variable offset.
Querystrings are often used for forms with a GET method

Express cannot natively deal with a posted form. 
We need to install some middleware (ie. npm install --save body-parser)

Because the order of placing middleware is important, we should put it between the static path and the route...

var path = require('path'); // native module needed to send file
var bodyParser = require('body-parser');  //
var routes = require('./api/routes');
(Like above and below)

....
app.use(express.static(path.join(__dirname, 'public'))); 
app.use(bodyParser.urlencoded( {extended : false} )); 
app.use('/api', routes);

To test POST methods, make sure to use POSTMAN extension



Extension:

	npm install -g nodemon // installs globally (You'll get some errors due to administrative rights)
	so instead try : sudo npm install -g nodemon (or the alternative to running as administrator)

	nodemon (when it is run) will look at the package.json and look at the start script and run that
	when you make changes to the app and hit save, nodemon will update and restart immediately (you dont have to manually restart!)

	Nodemon restarts for any change made -> this gets a little annoying when we make changes to front end files (which do not have to be compiled)
	(eg. making changes to jquery doc)
	To get over this pesky situation, we create a nodemon.json file in our root folder that acts like a configuration file for nodemon.
	We simply write inside the file  
	{
			"ignore" : ["public/*"]
	}
	This will ignore changes made in public folder!

	We can also add other configurations to nodemon like the verbose property, which shows you a bit more information than default nodemon
	(good for debugging?)
	{
		...
		"verbose" : true
	}

	Great for development (not so great for production)