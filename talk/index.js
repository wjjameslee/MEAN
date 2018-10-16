// index.js

var filename = "index.js";  // private variable 
// files outside index.js do not have any idea that filename was a variable

var hello = function(name) {
	console.log("Hello " + name);
};

var intro = function() {
	console.log("I'm a node file called " + filename);
};

module.exports = {
	hello : hello,
	intro, intro
};