#include <pebble.h>
#include "data.h"

const char** get_segments(int highway) {
  
  switch (highway) {
    case HIGHWAY_EDSA: 
      return SEGMENTS_EDSA;
    case HIGHWAY_C5:
      return SEGMENTS_C5;
    case HIGHWAY_ORTIGAS:
      return SEGMENTS_ORTIGAS;
    case HIGHWAY_COMMONWEALTH:
      return SEGMENTS_COMMONWEALTH;
    case HIGHWAY_QUEZONAVE:
      return SEGMENTS_QUEZONAVE;
    case HIGHWAY_ESPANA:
      return SEGMENTS_ESPANA;
    case HIGHWAY_ROXAS:
      return SEGMENTS_ROXAS;
    case HIGHWAY_SLEX:
      return SEGMENTS_SLEX;
    case HIGHWAY_MARCOSHWY:
      return SEGMENTS_MARCOSHWY;
    default: 
      return 0;
  }
  
}

int get_segment_count(int highway) {
  
  switch (highway) {
    case HIGHWAY_EDSA: 
      return NUM_SEGMENT_EDSA;
    case HIGHWAY_C5:
      return NUM_SEGMENT_C5;
    case HIGHWAY_ORTIGAS:
      return NUM_SEGMENT_ORTIGAS;
    case HIGHWAY_COMMONWEALTH:
      return NUM_SEGMENT_COMMONWEALTH;
    case HIGHWAY_QUEZONAVE:
      return NUM_SEGMENT_QUEZONAVE;
    case HIGHWAY_ESPANA:
      return NUM_SEGMENT_ESPANA;
    case HIGHWAY_ROXAS:
      return NUM_SEGMENT_ROXAS;
    case HIGHWAY_SLEX:
      return NUM_SEGMENT_SLEX;
    case HIGHWAY_MARCOSHWY:
      return NUM_SEGMENT_MARCOSHWY;
    default: 
      return 0;
  }
  
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
};

const char* SEGMENTS_QUEZONAVE[] = {
};

const char* SEGMENTS_ESPANA[] = {
};

const char* SEGMENTS_ROXAS[] = {
};

const char* SEGMENTS_SLEX[] = {
};

const char* SEGMENTS_MARCOSHWY[] = {
};

