NOSQL 

Types of NoSQL databases:	
	- Key-value store
	- Document store   <---  MongoDB
	- Graph databases



An example of no sql database (more specifically called a collection):

[
	{
		"PostId" : 1,
		"Title" : "My first post",
		"Content" : "Some content",
		"Comments" : [
				{
					"CommentId" : 1,
					"Content" : "Commenting on your first post"
				}
			]
	},
	{
		"PostId" : 2,
		"Title" : "My second post",
		"Content" : "Some content",
		"Comments" : [
				{
					"CommentId" : 2,
					"Content" : "Commenting on your second post"
				},
				{
					"CommentId" : 3,
					"Content" : "Also on your second post"
				}
			]
	},
	{
		"PostId" : 2,
		"Title" : "My third post",
		"Content" : "Some content"
	}  // here
]

for the section //here 
if the data does not exist for an attribute, that is fine in document databases
	Benefits: does not waste space keeping a container waiting to be populated  && data can be more flexible 


Updating a username can be expensive when dealing with relational databases - have to check all the user posts and comments and so on..
But compared to articles it may not be so... think about this when designing suitable databases


MongoDB Basics:

	Behind the scenes, MongoDB stores the data as binary json (performance)
	_id (unique) is recognized when you have a data for ids in general
	"_id" : ObjectId("53b01758fb7400d51faae284");


Commands - show dbs, show collections, use [name of db to use], exit (to exit MongoDB, simple enough)

To start using that database we write the following: db.createCollection("tech") (make sure you in the db you want to use (ie. use thisDB))
First parameter is the name of the collection to create 
and the second parameter is an optional parameter, just look it up since we will not be using it here right now...

To start adding a document into our collection within our database, the following method is invoked: db.tech.insert(insert_json_object)
eg. db.tech.insert( { name : "Mongo",
                      role : "Database"} )

Now how do we see our document in the database? 
Simple: db.tech.find()   (no parameters implies Mongo will find EVERY document it can find inside that collection)
Nice, we got ourselves the information of our document we initially created. But it does not really look like a readable json formatted file.
Can we format it to look better? Try db.tech.find().pretty()

Now we know how to insert and find a single document, but it would be able to insert and find multiple documents at once. How do we do this?
Instead of passing a single json object into db.tech.find(), we pass in an array of json objects

eg. 

db.tech.insert(
	[
		{ 
			name : "Express",
			role : "Web application server"
		},
		{
			name : "Angular",
			role : "Front-end framework"
		},
		{
			name : "Node.js",
			role : "Platform"
		}
	]
)

To query a specfic result: pass a parameter in like this:
db.tech.find({"_id" : ObjectId("5898c9d5d387411b70457bc")}).
This will return (with the previous instructions): {"_id" : ObjectId("5898c9d5d387411b70457bc"), "name" : "MongoDB", "role" : "Database" }
We can query with other keywords instead of searching by ids
db.tech.find({"name" : "Angular"})
db.tech.find().sort({"name" : 1}) sorts the results by ascending order by the name
db.tech.find().sort({"name" : -1}) will sort them by descending order

Now we return to the second parameter of the find() method. This parameter is a projection parameter that limits the results returned in some way, 
really useful for large databases.
So if we want to find ALL documents and return its name, but not its role, we can do: db.tech.find({}, {"name" : true})
We notice that _id column is returned as well. This is a default in MongoDB. If we do not want to specifically return these ids,
then we can use this command: db.tech.find({}, {"_id" : false, "name" : true}).
Alternatively, we can replace the boolean values with 0 and 1. db.tech.find({}, {"_id" : 0, "name" : 1})

**** An important sidenote, you cannot include and exclude some information in the projection parameter.
The only exception to this is demonstrated above, where we exclude the "_id" and include the "name"! *****

Suppose we want to update our current document where "Angular" needs to be updated to "Angular JS", we can do so like this:
db.tech.update({ "name" : "Angular" }, { $set : { "name" : "AngularJS" } } )
This update method will only work for a SINGLE DOCUMENT. So if the query run matches multiple documents, only the first one it finds
will be updated. You can pass in an optional third parameter like this:
db.tech.update({}, { $set : { "language" : "JavaScript" } }, { multi : true })  // Note updating, also inserts if there wasn't any existing data

To remove a single document use the following:
db.tech.remove( { "name" : "Express" } ). Be careful, when calling db.tech.remove({}), it REMOVES ALL!
Alternatively, db.tech.drop() removes the tech collection from our database.



Exporting and Importing BSON/JSON data:

Recall: Mongo stores data as BSON

One utility, Mongo has is called MongoDump and despite the name of "dump" being in it, it does not delete anything, but instead
MongoDump is what we use to export data into a dump folder so we can use it somewhere else

Command: mongodump 
(If you do not give specify a database to export in this command, it will dump all the databases...)
eg. mongodump --db [name of database, in this case meantest]
By default, MongoDump saves the exports in a folder called dump in the current working directory.
There are many other flags that can help customize mongodump, we consider only one of them, look the rest up online:

eg. mongodump --db meantest --gzip    --> zips the data for export 


To import bson data, we use MongoRestore

eg. mongorestore --db mean2 --gzip dump/meantest  

(Note: mongorestore will create mean2 if it cannot find it from the data)
**** mongorestore only "inserts" and does not "update" the database

mongodump, mongorestore -> use for binary json data
mongoexport, mongoimport  -> use for json data


eg. mongoexport --db meantest --collection tech // need to specify collection; this ouputs the data to be exported to standard output
In order to export and save to a file: mongoexport --db meantest --collection tech  --out api/data/tech.json 

Opening this tech.json file, we see that it is an invalid .json file...
// tech.json
{"_id":{"$oid":"5898f38acc78721d0fec4b70"},"name":"MongoDB","role":"Database"}
{"_id":{"$oid":"5898f38acc78721d0fec4b71"},"name":"Express","role":"Web application server"}
{"_id":{"$oid":"5898f38acc78721d0fec4b72"},"name":"Angular","role":"Front-end framework"}
{"_id":{"$oid":"5898f38acc78721d0fec4b73"},"name":"Node.js","role":"Platform"}

There are no commas, no outer brackets...we need to make it export as an array...
Solution: use the --jsonArray flag
eg. mongoexport --db meantest --collection tech --out api/data/tech.json --jsonArray
Much better!
It is computer readable, but not really human-readable because it is fairly compressed. We can do better.
mongoexport --db meantest --collection tech --out api/data/tech.json --jsonArray --pretty
Perfect!

eg. mongoimport --db mean3 --collection tech --jsonArray api/data/tech.json
(The last parameter, is the source of the data to import...)




Using Node.js to connect to MongoDB:

The command to start it up: npm install mongodb --save
To start a connection, you need this line of code inside your .js file:
var MongoClient = require('mongodb').MongoClient;

Connection string is required to open a connection to the database for MongoDB: var dburl = 'mongodb://localhost:27017/meanHotel';

To actually connect: 
MongoClient.connect(dburl, function(err, db) {
	if (err) {
		console.log("DB connection failed.");
		return;
	}
	else {
		_connection = db;
		console.log("DB connection open", db);
	}
});

The callback function above requires two parameters: an error object if the connection fails, and the connection object.
The idea of the callback function is to return an error message if there is an error, otherwise, save our connection to another variable for use...
Refer to code for further information...