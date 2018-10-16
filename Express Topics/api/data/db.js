// db.js

var mongoose = require('mongoose');
var dburl = 'mongodb://localhost:27017/meanHotel';

mongoose.connect(dburl);

mongoose.connection.on('connected', function() {
	console.log('Mongoose connected to ' + dburl);
});

mongoose.connection.on('disconnected', function() {
	console.log('Mongoose disconnected');
});

mongoose.connection.on('error', function(err) {
	console.log('Mongoose connection error: ' + err);
});


process.on('SIGINT', function() {
	mongoose.connection.close(function() {
		console.log('Mongoose disconnected through app termination (SIGINT)');
		process.exit(0);
	});
}); 

process.on('SIGTERM', function() {    // Heroku uses the term SIGTERM
	mongoose.connection.close(function() {
		console.log('Mongoose disconnected through app termination (SIGTERM)');
		process.exit(0);
	});
}); 


process.once('SIGUSR2', function() {    // allow Nodemon to pick up event after restarting, which uses a different event
	mongoose.connection.close(function() {
		console.log('Mongoose disconnected through app termination (SIGUSR2)');
		process.kill(process.pid, 'SIGUSR2');
	});
}); 


// BRING IN SCHEMA AND MODELS

require('./hotels.model.js');