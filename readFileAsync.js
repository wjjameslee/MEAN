// readFileAsync Asynchronous Code

var fs = require('fs'); // native node module 
console.log("Going to get a file.");

var onFileLoad = function(err, file) {
	console.log("Got the file!");
}  // named callback (USE THESE OFTEN, MORE READABLE)

var file = fs.readFile('readFileSync.js', onFileLoad);


console.log("App continues...");

