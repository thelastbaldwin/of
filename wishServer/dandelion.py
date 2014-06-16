import requests
import pymongo
from flask import Flask, jsonify, render_template, request
import json

app = Flask(__name__)

#mongodb stuff
#Wrapped this in a function and init'd collection in every route or sometimes
# a weird pymongo.reconnect error happens if the connection goes stale.
# This way the connection is always fresh and I don't think uses anymore overhead.

def init_mongo_connection():
	connection = pymongo.Connection() #defaults to 'localhost:27017'
	db = connection.dandelion
	return db.dandelion #set the collection

#routing
@app.route('/<search_string>')
def index(search_string):
	#url_query = "http://search.twitter.com/search.json?q=%s&lang=en" % (search_string) # search for "I wish"
	#r = requests.get(url_query)

	#if(r.status_code == 200):
	#	for tweet in r.json["results"]:
	#		#save the record in the database if no result is returned
	#		if collection.find_one({'id' : tweet["id"]}) is None:
	#			tweet["granted"] = False; #add a wishGranted parameter
	#			collection.insert(tweet)
	#return everthing in the database where granted = false;

	collection = init_mongo_connection()

	wishes = collection.find({"granted" : False}, {'_id':False})
	wishes = [x for x in wishes] #still must iterate through cursor

	#Technically you should use jsonify(wishes) here unless it doesn't parse correctly
	# as it also sets the correct http headers.
	return json.dumps(wishes)

@app.route('/purge')
def purge():

	collection = init_mongo_connection()

	collection.remove() #kill everything in the database
	a = collection.count()

	return "There are now %d records in the database." % (a)

@app.route('/count')
def count():

	collection = init_mongo_connection()
	#All these Mongo queries can be changed to collection.count() which will return an integer.
	# you can then change everything in the string interpolation to just (a, granted, ungranted)
	# performance isn't an issue here but no need getting a cursor back

	a  = collection.find()
	ungranted = collection.find({"granted" : False}, {'_id':False})
	granted = collection.find({"granted" : True}, {'_id':False})
	return "There are %d records in the database.\n%d granted, %d ungranted" % (a.count(),granted.count(), ungranted.count())

@app.route('/manage', methods=['POST', 'GET'])
def manage():

	collection = init_mongo_connection()

	#get all the records from the database where granted has been marked false
	wishes = collection.find({"granted" : False}, {'_id':False})
	wishes = [x for x in wishes] #iterate through cursor

	if request.method=='POST':
		#remove the posted ids from the database

		#I think map is being removed from Python in v3+, this is equivalent just fyi
		# todelete = [int(x) for x in request.form.getlist("wish")]
		todelete = map(int,request.form.getlist("wish"))

		collection.update({'id': {'$in': todelete}},{'$set':{'granted': True}}, multi=True)
		return render_template('manage.html', widhes=wishes, todelete=todelete)
	else:
		return render_template('manage.html', wishes=wishes)


@app.route('/blacklist')
def blacklist():

	collection = init_mongo_connection()

	#see which items have been marked as granted, with the option to bring them back
	wishes = collection.find({"granted" : True}, {'_id':False})

#variable rule
@app.route('/granted/<int:tweet_id>')
def mark_as_granted(tweet_id):

	collection = init_mongo_connection()

	#mark the tweet as 'granted in the db'
	collection.update({'id':tweet_id},{'$set':{'granted': True}})
	#retweet to twitter with username + "your wish was granted!"
	return "tweet id: %d marked as granted!" % tweet_id

if __name__ == '__main__':
	app.debug = True
	app.run()