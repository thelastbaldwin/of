import json
import urllib2

#Get data from a url
#data = json.dumps([1, 2, 3])
#url = "http://search.twitter.com/search.json?q=%23cobra&src=typd" #test search
#req = urllib2.Request(url, data, {'Content-Type': 'application/json'})
#f = urllib2.urlopen(req)
#response = f.read()
#f.close()

data = [ { 'a':'A', 'b':(2, 4), 'c':3.0 } ]
print 'DATA:', repr(data)

data_string = json.dumps(data)
print 'JSON:', data_string