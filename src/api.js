var URL_TRAFFIC = 'http://mmdatraffic.interaksyon.com/livefeed/';
var URL_INCIDENTS = 'http://mmdainteraksyon.virusworldwide.com/mmdaalert.php';
var URL_TRAFFIC_JS = 'http://vast-bayou-2822.herokuapp.com/';

var COMMAND_READY = 1;
var COMMAND_DATA = 2;

var VOLUME = {
  NA : 0,    // no data
  L  : 1,
  ML : 2,
  M  : 3,
  MH : 4,
  H  : 5
}

var DIRECTIONS = [
  'NB', 'SB'
]

var HIGHWAY_DATA = [
  {
    id : 0,
    name : 'EDSA',
    segments : [
      'BALINTAWAK',
      'KAINGIN_ROAD',
      'MU\u00F1OZ',
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
    id : 1,
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
    id : 2,
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
    id : 3,
    name : 'COMMONWEALTH',
    segments : [
      'BATASAN',
      'ST._PETER\'S_CHURCH',
      'EVER_GOTESCO',
      'DILIMAN_PREPARATORY_SCHOOL',
      'ZUZUAREGI',
      'GENERAL_MALVAR_HOSPITAL',
      'TANDANG_SORA_EASTSIDE',
      'TANDANG_SORA_WESTSIDE',
      'CENTRAL_AVE',
      'MAGSAYSAY_AVE',
      'UNIVERSITY_AVE',
      'PHILCOA'
    ]
  },
  {
    id : 4,
    name : "QUEZON_AVE.",
    segments: [
      'ELLIPTICAL_ROAD',
      'AGHAM_ROAD',
      'BANTAYOG_ROAD',
      'EDSA',
      'SGT._ESGUERA',
      'SCOUT_ALBANO',
      'SCOUT_BORROMEO',
      'SCOUT_SANTIAGO',
      'TIMOG',
      'SCOUT_REYES',
      'SCOUT_MAGBANUA',
      'ROCES_AVENUE',
      'ROOSEVELT_AVENUE',
      'DR._GARCIA_SR.',
      'SCOUT_CHUATOCO',
      'G._ARANETA_AVE.',
      'STO._DOMINGO',
      'BIAK_NA_BATO',
      'BANAWE',
      'CORDILLERA',
      'D._TUAZON',
      'SPEAKER_PEREZ',
      'APO_AVENUE',
      'KANLAON',
      'MAYON'
    ]
  },
  {
    id : 5,
    name : 'ESPA\u00D1A',
    segments : [
      'LERMA',
      'P.NOVAL',
      'GOV._FORBES_-_LACSON',
      'VICENTE_CRUZ',
      'ANTIPOLO',
      'A._MACEDA',
      'BLUEMENTRITT',
      'WELCOME_ROTUNDA'
    ]
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
  console.log('fetchTraffic');
  
  fetchData(URL_TRAFFIC_JS, function(data) {
    
      var result = { command : COMMAND_DATA };
    
      if (data != null) {
        result.data = parseTrafficData(data.traffic);
        result.error = 0;
      }
      else {
        result.error = 1;
      }
    
      console.log('send app msg!');
    
      Pebble.sendAppMessage(result);
    
  });
  
}


function fetchData(url, callback) {
    
  var req = new XMLHttpRequest();
  
  req.open('GET', url, true);
  req.onload = function(e) {
    console.log('fetchData: onload()');
    if (req.readyState == 4 && req.status == 200) {
      callback(JSON.parse(req.responseText));
    }
    else {
      callback(null);
    }
  };
  req.onerror = function(e) {
    console.log('fetchData: onerror()');
    callback(null);
  };
  req.timeout = function(e) {
    console.log('fetchData: timeout()');
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
        
        //console.log('Push: ' + highway_data.name + " -> " + segname + " -> " + dir);
        
        if (data[highway_data.name] && 
            data[highway_data.name][segname] &&
            data[highway_data.name][segname][dir]) {

            result.push(VOLUME[data[highway_data.name][segname][dir]]);
            //console.log('  data found. pushing..')
        }
        else {     
          result.push(0);
          //console.log('  data NOT found. pushing no data..')
        }
        
      }
      
    }
    
  }
  
  return result;
  
}


Pebble.addEventListener("ready", function(e) {
  console.log('JS is ready!');
  Pebble.sendAppMessage({ command : COMMAND_READY });
});

// Called when incoming message from the Pebble is received
Pebble.addEventListener("appmessage", function(e) {
  console.log('App message received');
  fetchTraffic();
});
