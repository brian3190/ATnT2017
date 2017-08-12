var express = require('express');
var path = require('path');
var serialport = require('serialport');
var portName = 'COM3';
var sp = new serialport.SerialPort(portName, {
    baudRate: 115200,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: serialport.parsers.readline("\r\n")
});

var app = express();

function setJSON() {
    sp.on('data', function(input) {
        var streamObject = JSON.parse({ x : input.substring(6, 12) });
	console.log(streamObject[0]);
    	return streamObject[0];
    });
    setInterval(setJSON(), 1000);
};

var json = setJSON();

app.get('/', function(req, res) {
    res.send(json);
});

app.listen(5000, () => {
    console.log('Serving at port 5000')
});    