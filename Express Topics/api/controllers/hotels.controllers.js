// hotels.controllers.js 

var mongoose = require('mongoose');
var Hotel = mongoose.model('Hotel');

/* without using mongoose
var dbconn = require('../data/dbConnection.js');
var ObjectId = require('mongodb').ObjectId;  // fixes the problem of findOne returning the first result of hotelId, but we need to have matching object ids..
var hotelData = require('../data/hotel-data.json'); */


var runGeoQuery = function(req, res) {
	var long = parseFloat(req.query.long);
	var lat = parseFloat(req.query.lat);

	if(isNaN(long) || isNaN(lat)) {
		res 
			.status(400)
			.json( {
				"message" : "If supplied in querystring, long and lat should be floating point numbers"
			});
		return;

	}
	// a geoJSON point
	var point = {
		type : "Point",
		coordinates : [long, lat]
	};
	var geoOptions = {   // helps limit the data returned back
		spherical : true,
		maxDistance : 2000,
		num : 5
	};

	Hotel 
		.geoNear(point, geoOptions, function(err, results, stats) {
			console.log('Geo results', results);
			console.log('Geo stats', stats);
			res
				.status(200)
				.json(results);
		});
};

module.exports.hotelsGetAll = function(req, res) {


	//var db = dbconn.get();
	//var collection = db.collection('hotels');

	var offset = 0;  // defaults
	var count = 5;
	var maxCount = 10;

	if (req.query && req.query.lat && req.query.long) {
		runGeoQuery(req, res);
		return;
	}

	if (req.query && req.query.offset) {
		offset = parseInt(req.query.offset, 10);
	}

	if (req.query && req.query.count) {
		count = parseInt(req.query.count, 10);
	}

	if (isNaN(offset) || isNaN(count)) {   // Dealing with errors
		res 
			.status(400)
			.json( {
				"message" : "If supplied in querystring, count and offset should be numbers"
			});
		return;
	}

	if (count > maxCount) {
		res 
			.status(400)
			.json({
				"message" : "Count limit of " + maxCount + " exceeded"
			});
		return;
	}

	Hotel
		.find()
		.skip(offset)
		.limit(count)
		.exec(function(err, hotels) { 
			if (err) {  // What other errors are there?
				console.log("Error finding hotels");
				res
					.status(500)
					.json(err);
				return;
			}
			else {  
				console.log("Found hotels", hotels.length);   
				res
					.status(200)
					.json(hotels);
			}
		});

	/*  How it works using the native driver
	collection
		.find()
		.skip(offset)
		.limit(count)
		.toArray(function(err, docs) {
			console.log("Found hotels", docs);
			res
				.status(200)
				.json(docs);
		});
 */

	


	//console.log("db", db);


	//console.log('GET the hotels');
	//console.log(req.query);
	

	/*var returnData = hotelData.slice(offset, offset+count); // slices data from hotelData

		res
			.status(200)
			.json(returnData); */
};

module.exports.hotelsGetOne = function(req, res) {

	
	
	var hotelId = req.params.hotelId;   // URL parameter
	
	console.log('GET hotelId', hotelId);

		Hotel
			.findById(hotelId)
			.exec(
				function(err, doc) {

					var response = {
						status : 200,
						message : doc
					};

					if (err) {  // What other errors are there?
						console.log("Error finding the hotel");
						response.status = 500;
						response.message = err;
					}
					// Here we need to consider if the err is false and doc object is empty, it really should not  return 200 status code....maybe 404?
					else if (!doc) {
						response.status = 404;
						response.message = { "message" : "HotelId not found" };
					}
					res
						.status(response.status)
						.json(response.message);
			});
					
};


// Helper Function to take care of photos, services in hotelsAddOne
var _splitArray = function(input) {
	var output;
	if (input && input.length > 0) {
		output = input.split(";");
	}
	else {
		output = [];
	}
	return output;
};

module.exports.hotelsAddOne = function(req, res) {

	Hotel
		.create({
			name : req.body.name,
			description : req.body.description,
			stars : parseInt(req.body.stars, 10),
			services : _splitArray(req.body.services),
			photos : _splitArray(req.body.photos),
			currency : req.body.currency,
			location : {
				address : req.body.address,
				coordinates : [parseFloat(req.body.long), parseFloat(req.body.lat)]
			}

		}, function(err, hotel) {
			if (err) {
				console.log("Error creating hotel entry");
				res
					.status(400)
					.json(err);
			}
			else {
				console.log("Hotel created", hotel);
				res
					.status(201)
					.json(hotel);
			}
		});


	
};


module.exports.hotelsUpdateOne = function(req, res) {
	var hotelId = req.params.hotelId;   // URL parameter
	
	console.log('GET hotelId', hotelId);

		Hotel
			.findById(hotelId)
			.select("-reviews -rooms")
			.exec(
				function(err, doc) {

					var response = {
						status : 200,
						message : doc
					};

					if (err) {  // What other errors are there?
						console.log("Error finding the hotel");
						response.status = 500;
						response.message = err;
					}
					// Here we need to consider if the err is false and doc object is empty, it really should not  return 200 status code....maybe 404?
					else if (!doc) {
						response.status = 404;
						response.message = { "message" : "HotelId not found" };
					}

					if (response.status !== 200) {
						res
							.status(response.status)
							.json(response.message);
					}
					else {
						doc.name = req.body.name;
						doc.description = req.body.description;
						doc.stars = parseInt(req.body.stars, 10);
						doc.services = _splitArray(req.body.services);
						doc.photos = _splitArray(req.body.photos);
						doc.currency = req.body.currency;
						doc.location = {
							address : req.body.address,
							coordinates : [
								parseFloat(req.body.long),
								parseFloat(req.body.lat)]
							};

						doc.save(function(err, updatedHotel) {
							if (err) {
								res
									.status(500)
									.json(err);
							}
							else {
								res
									.status(204)
									.json();  // for PUT return empty json 
							}
						});

						}
					
					
						
			});
};