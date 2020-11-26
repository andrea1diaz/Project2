var express = require("express");
var app = express();

app.listen(3000, () => {
 console.log("Server running on port 3000");
});

app.get("/api", (req, res, next) => {
	var fs = require('fs');
	var obj;

	res.setHeader('Content-Type', 'application/json');
	fs.readFile('index/index.json', 'utf8', function (err, data) {
		obj = JSON.parse(JSON.stringify(data));

		res.end(obj);
	});

});
