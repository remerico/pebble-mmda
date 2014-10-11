var URL_TRAFFIC = 'http://mmdatraffic.interaksyon.com/livefeed/';
var URL_INCIDENTS = 'http://mmdainteraksyon.virusworldwide.com/mmdaalert.php';

var COMMANDS = {
  ERROR : 0,
  SEGMENT : 1
};

var FIELDS = {
  COMMAND : "command",
  HIGHWAY : "highway",
  SEGMENT : "segment",
  NORTH : "north",
  SOUTH : "south"
}

var HIGHWAYS = {
  EDSA : 1,
}


function fetchTraffic() {
  
  fetchData(URL_TRAFFIC, function(data) {
    
      var result = {};
    
      if (data != null) {
        result.traffic = data;
        result.error = 0;
      }
      else {
        result.error = 1;
      }
    
      Pebble.sendAppMessage(result);
    
  });
  
}


function fetchData(url, callback) {
    
  var req = new XMLHttpRequest();
  
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4 && req.status == 200) {
      callback(req.responseText);
    }
    else {
      callback(null);
    }
  };
  req.onerror = function(e) {
    callback(null);
  };
  req.timeout = function(e) {
    callback(null);
  };
  
  req.send(null);
  
}