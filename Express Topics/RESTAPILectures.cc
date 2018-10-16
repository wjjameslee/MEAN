//RESTAPILectures.cc

Method:

	- GET
	- POST
	- GET
	- PUT
	- DELETE
	- GET
	- POST

	- GET
	- PUT
	- DELETE

URL (Base URLs):

	- /api/hotels
	- /api/hotels
	- /api/hotels/12345
	- /api/hotels/12345
	- /api/hotels/12345
	- /api/hotels/12345/reviews
	- /api/hotels/12345/reviews

	- /api/hotels/12345/reviews/54321
	- /api/hotels/12345/reviews/54321
	-/api/hotels/12345/reviews/54321

Action:

	- Get all/multiple hotels
	- Create a new hotels
	- Get a specific hotel
	- Update a specific hotel
	- Delete a specfic hotel
	- Get all reviews for a specific hotel
	- Add review for specific hotel

	- Get a specific review for a specific hotel
	- Update a specific review for a specific hotel
	- Delete a specific review 


Mongoose will help us write our REST APIs...
To install, we can call it: npm install --save Mongoose
Mongoose schemas for number values do not support double and long numbers by default (need Mongoose plugins)

default in your schemas may interfere with the compiler because default is a keyword
Solution: put quotes over it -> "default"

A model is a compiled version of the schema...

mongoose.model('Hotel', hotelSchema, 'hotels'); // if dbcollection is not specified (ie. 'hotels' was not in model method) it would look for pluralized 'Hotel' upper/lowercase
so we can rewrite this as from our comment: mongoose.model('Hotel', hotelSchema);

Nested schemas are used for sub documents...
Notice how in hotel-data.json the "reviews" section contains an array of objects, classified as a subdocument
that are nested inside the hotel document (in Mongoose)

So we create another schema for this particular instance...(reviewSchema)
and then reference this to the original hotel schema...

eg.
...
currency : String,
services : [String],
reviews : [reviewSchema]  // Updated

Also a small note: Make sure you define your nested schemas before your main schema
and also your model should come AFTER all your schemas have been defined.

Now, we consider data that stores geo-spatial coordinates.
Always store coordinates longitude (E/W), latitude (N/S) order



Golden Rules of API Design:
	- Always return a reponse
	- Return the correct HTTP status code 
	- Return contents or a message 


Status code 500 - internal server error
Status code 400 - bad request
Status code 404 - not found



