#testing using requests and pymongo
import requests, pymongo

#search twitter for our hash tag (# = %23)
url_query = "http://search.twitter.com/search.json?q=%23gundam" # search for #gundam
r = requests.get(url_query)

#mongodb stuff
connection = pymongo.Connection() 
db = connection.dandelion
#db.collection_names() #this shows that dandelion is the collection that we want
collection = db.dandelion #set the collection

for tweet in r.json["results"]:
	#save the record in the database if no result is returned
	if collection.find_one({'id' : tweet["id"]}) is not None:
		tweet["granted"] = false; #add a wishGranted parameter
		collection.insert(tweet) #to be replaced with upsert
