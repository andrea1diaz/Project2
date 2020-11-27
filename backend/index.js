var express = require("express");
const cors = require('cors');
var bodyParser = require('body-parser')
var fs = require('fs');
var spawn = require('child_process').spawn

var app = express();
var jsonParser = bodyParser.json()
var child = spawn('./a.out');

app.use(cors())
app.use(bodyParser.json({ type: 'application/*+json' }))

child.stdin.setEncoding('utf-8');
//child.stdout.pipe(process.stdout);
var blocks = [];

fs.readFile('index/0.json', 'utf8', function (err, data) {
	blocks.push({name: 0, value: JSON.parse(data)});
});

fs.readFile('index/144.json', 'utf8', function (err, data) {
	blocks.push({name: 0, value: JSON.parse(data)});
});
fs.readFile('index/288.json', 'utf8', function (err, data) {
	blocks.push({name: 288, value: JSON.parse(data)});
});
fs.readFile('index/432.json', 'utf8', function (err, data) {
	blocks.push({name: 432, value: JSON.parse(data)});
});
fs.readFile('index/576.json', 'utf8', function (err, data) {
	blocks.push({name: 576, value: JSON.parse(data)});
});
fs.readFile('index/720.json', 'utf8', function (err, data) {
	blocks.push({name: 720, value: JSON.parse(data)});
});
fs.readFile('index/864.json', 'utf8', function (err, data) {
	blocks.push({name: 864, value: JSON.parse(data)});
});

function getKeyByValue(object, value) {
  return Object.keys(object).find(key => object[key] === value);}


app.listen(3000, () => {
 console.log("Server running on port 3000");
});

app.get("/api", (req, res, next) => {
	res.json({
        message: 'Connected to server'
    });
});

app.get("/api/collection/words", (req, res, next) => {
	var obj;

	res.setHeader('Content-Type', 'application/json');
	
	fs.readFile('index/words.json', 'utf8', function (err, data) {
		obj = JSON.parse(data);
		res.json(obj)
	});

});

app.get("/api/collection/list", (req, res, next) => {
	var obj;

	res.setHeader('Content-Type', 'application/json');
	
	fs.readFile('index/test.txt', 'utf8', function (err, data) {
		obj = JSON.parse(data);
		res.json(obj)
	});

});

app.get("/api/find/:word", (req, res, next) => {
	res.setHeader('Content-Type', 'application/json');
	console.log("searching for " + req.params.word)
	var obj = req.params.word.replace(/_/g," ");

	
	var arr = obj.split(" ")
	child.stdin.write(obj);
	child.stdin.end();

	var result = []
	child.stdout.on('data', (data) => {
		var tmp = JSON.parse(data.toString())
		
		tmp.forEach(function (j) {
			blocks.forEach(function(i) {
				if (i.name == j) {
					arr.forEach(function(z) {
						if (i.value.words[z] !== 'undefined') { return result = [] }
						else {
							var file = i.value.words[z].tf
								Object.keys(file).forEach(function(w) {
								result.push(i.value.docs[w])
							})
						}
					})
				}
			})
			
		})
		//tmp.forEach(function(x) { console.log(block.words[obj]); });

		console.log("send")
		res.json(result);
	});


})
