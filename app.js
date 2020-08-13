const express = require("express");
const bodyParser = require("body-parser");

const app = express();
app.set("view engine", "ejs");
app.use(bodyParser.urlencoded({extended: true}));

var vals = [];
var timeRead = [];

app.get("/", function(req, res){
  res.render("index", {values: vals, times: timeRead});
});

app.post("/", function(req, res){
  console.log("Data received!");
  val = req.body.reading;
  var today = new Date();
  var time = today.toLocaleString('en-US', { hour: 'numeric', minute: 'numeric'});
  timeRead.push(time);
  vals.push(val);
  res.redirect("/");
});

app.listen(3000, function(){
  console.log("Server is running on port 3000...");
});
