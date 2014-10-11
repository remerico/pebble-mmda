var URL_TRAFFIC = 'http://mmdatraffic.interaksyon.com/livefeed/';
var URL_INCIDENTS = 'http://mmdainteraksyon.virusworldwide.com/mmdaalert.php';
var URL_TRAFFIC_JS 'http://vast-bayou-2822.herokuapp.com/';

var VOLUME = {
  L  : 0,
  ML : 1,
  M  : 2,
  MH : 3,
  H  : 4
}

var DIRECTIONS = [
  'NB', 'SB'
]

var HIGHWAY_DATA = [
  {
    id : 1,
    name : 'EDSA',
    segments : [
      'BALINTAWAK',
      'KAINGIN_ROAD',
      'MUñOZ',
      'BANSALANGIN',
      'NORTH_AVE.',
      'TRINOMA',
      'QUEZON_AVE.',
      'NIA_ROAD',
      'TIMOG',
      'KAMUNING',
      'NEW_YORK_-_NEPA_Q-MART',
      'MONTE_DE_PIEDAD',
      'AURORA_BLVD.',
      'MC_ARTHUR_-_FARMERS',
      'P._TUAZON',
      'MAIN_AVE.',
      'SANTOLAN',
      'WHITE_PLAINS_-_CONNECTICUT',
      'ORTIGAS_AVE.',
      'SM_MEGAMALL',
      'SHAW_BLVD.',
      'RELIANCE',
      'PIONEER_-_BONI',
      'GUADALUPE',
      'ORENSE',
      'KALAYAAN_-_ESTRELLA',
      'BUENDIA',
      'AYALA_AVE.',
      'ARNAIZ_-_PASAY_ROAD',
      'MAGALLANES',
      'MALIBAY',
      'TRAMO',
      'TAFT_AVE.',
      'F.B._HARRISON',
      'ROXAS_BOULEVARD',
      'MACAPAGAL_AVE.',
      'MALL_OF_ASIA'
    ]
  },
  {
    id : 2,
    name : 'C5',
    segments : [
      'TANDANG_SORA',
      'CAPITOL_HILLS',
      'UNIVERSITY_OF_THE_PHILIPPINES',
      'C.P._GARCIA',
      'MIRIAM_COLLEGE',
      'ATENEO_DE_MANILA_UNIVERSITY',
      'XAVIERVILLE',
      'AURORA_BOULEVARD',
      'P._TUAZON',
      'BONNY_SERRANO',
      'LIBIS_FLYOVER',
      'EASTWOOD',
      'GREEN_MEADOWS',
      'ORTIGAS_AVE.',
      'J._VARGAS',
      'LANUZA',
      'BAGONG_ILOG',
      'KALAYAAN',
      'MARKET!_MARKET!'
    ]
  },
  {
    id : 3,
    name : 'ORTIGAS',
    segments : [
        'SANTOLAN',
        'MADISON',
        'ROOSEVELT',
        'CLUB_FILIPINO',
        'WILSON',
        'CONNECTICUT',
        'LA_SALLE_GREENHILLS',
        'POEA',
        'EDSA_SHRINE',
        'SAN_MIGUEL_AVE',
        'MERALCO_AVE',
        'MEDICAL_CITY',
        'LANUZA_AVE',
        'GREENMEADOWS_AVE',
        'C5_FLYOVER'
    ]
  },
  {
    id : 4,
    name : 'COMMONWEALTH',
    segments : []
  },
  {
    id : 5,
    name : 'ESPAÑA',
    segments : []
  },
  {
    id : 6,
    name : 'ROXAS_BLVD.',
    segments : []
  },
  {
    id : 7,
    name : 'SLEX',
    segments : []
  },
  {
    id : 8,
    name : 'MARCOS_HIGHWAY',
    segments : []
  }
];


var HIGHWAY_IDS = {
  EDSA : 0,
  C5 : 1,
  ORTIGAS : 2,
  COMMONWEALTH : 3,
  QUEZONAVE : 4,
  ESPANA : 5,
  ROXAS : 6,
  SLEX : 7,
  MARCOSHWY : 8
}



function fetchTraffic() {
  
  fetchData(URL_TRAFFIC_JS, function(data) {
    
      var result = {};
    
      if (data != null) {
        result.traffic = parseTrafficData(data.traffic);
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


function parseTrafficData(data) {
  
  var result = [];
  
  for (var i in HIGHWAY_DATA) {
    
    var highway_data = HIGHWAY_DATA[i];
    var segment_names = highway_data.segments;
    
    for (var j in segment_names) {
      var segname = segment_names[j];
      
      for (var k in DIRECTIONS) {
        var dir = DIRECTIONS[k];
        result.push(VOLUME[data[highway_data.name][segname][dir]]);
      }
      
    }
    
  }
  
  return result;
  
}


Pebble.addEventListener("ready", function(e) {
  console.log('JS is ready!');
});

// Called when incoming message from the Pebble is received
Pebble.addEventListener("appmessage", function(e) {
  fetchTraffic();
});
