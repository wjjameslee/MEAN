// hotels.model.js

var mongoose = require('mongoose');


var reviewSchema = new mongoose.Schema( {
	name : {
		type : String,
		required : true
	},
	rating : {
		type : Number,
		min : 0,
		max : 5,
		required : true
	},
	review : {
		type : String,
		required : true
	},
	createdOn : {
		type : Date,  //timestamps are data types in this case!
		"default" : Date.now
	}

});

// our rooms schema
var roomSchema = new mongoose.Schema({
	type : String,
	number : Number,
	description: String,
	photos : [String],
	price : Number
});

// our hotel schema defined
var hotelSchema = new mongoose.Schema( {
	name : {
		type : String,
		required : true     // a name is required for schema validation
	},
	stars : {
		type : Number, 
		min : 0,
		max : 5,
		"default" : 0  // if nothing is inputted, just give this value
	},   
	description : String,   // shorthand as opposed to "name"
	photos : [String],
	currency : String,
	services : [String],
	reviews : [reviewSchema],
	rooms : [roomSchema],
	location : {
		address : String,
		coordinates : {
			type : [Number],
			index : '2dsphere'  // coordinates for our world which is a sphere! 
		}
	}
});


mongoose.model('Hotel', hotelSchema);