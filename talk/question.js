// question.js

var answer = "Now that's a good question!";  // private variable

module.exports.ask = function(question) {
	console.log(question);
	return answer;	
};
