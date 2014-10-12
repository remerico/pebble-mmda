#include <pebble.h>
#include "data.h"

static bool is_loaded = false;
  
uint8_t SEGMENT_DATA[LENGTH_SEGMENT_DATA] = {};

const char** SEGMENTS[NUM_HIGHWAY] = {
  SEGMENTS_EDSA,
  SEGMENTS_C5,
  SEGMENTS_ORTIGAS,
  SEGMENTS_COMMONWEALTH,
  SEGMENTS_QUEZONAVE,
  SEGMENTS_ESPANA,
  SEGMENTS_ROXAS,
  SEGMENTS_SLEX,
  SEGMENTS_MARCOSHWY
};
  
const int SEGMENT_COUNT[NUM_HIGHWAY] = {
  NUM_SEGMENT_EDSA,
  NUM_SEGMENT_C5,
  NUM_SEGMENT_ORTIGAS,
  NUM_SEGMENT_COMMONWEALTH,
  NUM_SEGMENT_QUEZONAVE,
  NUM_SEGMENT_ESPANA,
  NUM_SEGMENT_ROXAS,
  NUM_SEGMENT_SLEX,
  NUM_SEGMENT_MARCOSHWY
};

const char* VOLUMES[] = {
  "N/A",
  "Low",
  "L-M",
  "Med",
  "M-H",
  "Hi"
};

Segment get_segment_data(int highway, int segment) {
  
  int offset = 0;
  int i;
  for (i = 0; i < highway; ++i) {
    offset += SEGMENT_COUNT[i] * 2;
  }
  
  offset += (segment * 2);  // for north/south directions
  
  Segment seg = { SEGMENTS[highway][segment], 
                 segment, 
                 SEGMENT_DATA[offset], 
                 SEGMENT_DATA[offset+1] };
  return seg;
  
}
  
const Highway HIGHWAYS[] = { 
    {"EDSA", HIGHWAY_EDSA},
    {"C5", HIGHWAY_C5},
    {"Ortigas", HIGHWAY_ORTIGAS},
    {"Commonwealth", HIGHWAY_COMMONWEALTH},
    {"Quezon Ave.", HIGHWAY_QUEZONAVE},
    {"España", HIGHWAY_ESPANA},
    {"Roxas Blvd.", HIGHWAY_ROXAS},
    {"SLEX", HIGHWAY_SLEX},
    {"Marcos Hwy", HIGHWAY_MARCOSHWY},
}; 


const char* SEGMENTS_EDSA[] = {
  "Balintawak",
  "Kaingin Road",
  "Muñoz",
  "Bansalangin",
  "North Ave.",
  "Trinoma",
  "Quezon Ave.",
  "Nia Road",
  "Timog",
  "Kamuning",
  "New York - Nepa Q-Mart",
  "Monte De Piedad",
  "Aurora Blvd.",
  "Mc Arthur - Farmers",
  "P. Tuazon",
  "Main Ave.",
  "Santolan",
  "White Plains",
  "Ortigas Ave.",
  "SM Megamall",
  "Shaw Blvd.",
  "Reliance",
  "Pioneer - Boni",
  "Guadalupe",
  "Orense",
  "Kalayaan - Estrella",
  "Buendia",
  "Ayala Ave.",
  "Arnaiz - Pasay Road",
  "Magallanes",
  "Malibay",
  "Tramo",
  "Taft Ave",
  "F.B. Harrison",
  "Roxas Blvd.",
  "Macapagal Ave.",
  "Mall Of Asia"
};

const char* SEGMENTS_C5[] = {
  "Tandang Sora",
  "Capitol Hills",
  "University of the Philippines",
  "C.P. Garcia",
  "Miriam College",
  "Ateneo de Manila",
  "Xavierville",
  "Aurora Blvd.",
  "P. Tuazon",
  "Bonny Serrano",
  "Libis Flyover",
  "Eastwood",
  "Green Meadows",
  "Ortigas Ave.",
  "J. Vargas",
  "Lanuza",
  "Bagong Ilog",
  "Kalayaan",
  "Market! Market!"
};

const char* SEGMENTS_ORTIGAS[] = {
  "Santolan",
  "Madison",
  "Roosevelt",
  "Club Filipino",
  "Wilson",
  "Connecticut",
  "La Salle Greenhills",
  "Poea",
  "EDSA Shrine",
  "San Miguel Ave.",
  "Meralco Ave.",
  "Medical City",
  "Lanuza Ave.",
  "Greenmeadows Ave.",
  "C5 Flyover"
};

const char* SEGMENTS_COMMONWEALTH[] = {
  "Batasan",
  "St. Peter's Church",
  "Ever Gotesco",
  "Diliman Preparatory School",
  "Zuzuaregi",
  "General Malvar Hospital",
  "Tandang Sora Eastside",
  "Tandang Sora Westside",
  "Central Ave",
  "Magsaysay Ave",
  "University Ave",
  "Philcoa"
};

const char* SEGMENTS_QUEZONAVE[] = {
  "Elliptical Road",
  "Agham Road",
  "Bantayog Road",
  "EDSA",
  "Sgt. Esguerra",
  "Scout Albano",
  "Scout Borromeo",
  "Scout Santiago",
  "Timog",
  "Scout Reyes",
  "Scout Magbanua",
  "Roces Avenue",
  "Roosevelt Avenue",
  "Dr. Garcia Sr.",
  "Scout Chuatoco",
  "G. Araneta Ave.",
  "Sto. Domingo",
  "Biak na Bato",
  "Banawe",
  "Cordillera",
  "D. Tuazon",
  "Speaker Perez",
  "Apo Avenue",
  "Kanlaon",
  "Mayon"
};

const char* SEGMENTS_ESPANA[] = {
  "Lerma",
  "P. Noval",
  "Gov. Forbes - Lacson",
  "Vicente Cruz",
  "Antipolo",
  "A. Maceda",
  "Blumentritt",
  "Welcome Rotonda"
};

const char* SEGMENTS_ROXAS[] = {
  "Anda Circle",
  "Finance Road",
  "U.N. Avenue",
  "Pedro Gil",
  "Rajah Sulayman",
  "Quirino",
  "Pablo Ocampo",
  "Buendia",
  "EDSA Extension",
  "Baclaran",
  "Airport Road",
  "Coastal Road"
};

const char* SEGMENTS_SLEX[] = {
  "Magallanes",
  "Nichols",
  "Merville Exit",
  "C5 On-ramp",
  "Bicutan Exit",
  "Sucat Exit",
  "Alabang Exit"
};

const char* SEGMENTS_MARCOSHWY[] = {
  "SM City Marikina",
  "LRT-2 Station",
  "Doña Juana",
  "Amang Rodriguez",
  "F. Mariano Ave.",
  "Robinson's Metro East",
  "San Benildo School"
};


bool data_is_loaded() {
  return is_loaded;
}

bool data_set_data(uint8_t *data, int length) {

  if (LENGTH_SEGMENT_DATA == length) {

    APP_LOG(APP_LOG_LEVEL_DEBUG, "Data has correct length");

    // Copy to segment data array
    memcpy(&SEGMENT_DATA, data, length);
    is_loaded = true;
    
    return true;

  }
  else {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Data has INCORRECT length");
    return false;
  }
  
}