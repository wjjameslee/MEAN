require('./instantHello');  // need to tell Node to look in the current directory 
var goodbye = require('./talk/goodbye');
var talk = require('./talk'); // index.js in talk folder
var question = require('./talk/question');

talk.intro();
talk.hello("James");

var answer = question.ask("What is the meaning of life?");
console.log(answer);

goodbye();