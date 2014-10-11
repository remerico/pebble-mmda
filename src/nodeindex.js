var express = require('express')
var http = require('http');
var xml2js = require('xml2js');
var app = express();

var options = {
  host: 'mmdatraffic.interaksyon.com',
  port: 80,
  path: '/livefeed/'
};

app.set('port', (process.env.PORT || 5000))
app.use(express.static(__dirname + '/public'))

app.get('/', function(request, response) {

	var parser = new xml2js.Parser(); 

	http.get(options, function(res) {
	  
		var body = '';

		res.on('data', function(chunk) {
		    body += chunk;
		  });
		res.on('end', function() {
			parser.parseString(body, function(err, result) {
				response.send(parseItems(result));	
			});
		});

	}).on('error', function(e) {
	  response.send("Got error: " + e.message);
	});

})

app.listen(app.get('port'), function() {
  console.log("Node app is running at localhost:" + app.get('port'))
})


function parseItems(response) {

	var traffic = {};

	var items = response['rss']['channel'][0]['item'];

	for (var i in items) {
		var item = items[i];

		var title = item['title'][0];
		var description = item['description'][0];

		var firstDash = title.indexOf('-');
		var lastDash = title.lastIndexOf('-');

		var hwy = title.substring(0, firstDash);
		var seg = title.substring(firstDash + 1, lastDash);
		var dir = title.substring(lastDash + 1);

		if (!traffic[hwy]) traffic[hwy] = {};
		if (!traffic[hwy][seg]) traffic[hwy][seg] = {};

		traffic[hwy][seg][dir] = description;
		
	}

	return { 'traffic' : traffic };

}
