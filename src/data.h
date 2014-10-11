#pragma once

#define NUM_HIGHWAY              9
#define NUM_SEGMENT_EDSA         37
#define NUM_SEGMENT_C5           19
#define NUM_SEGMENT_ORTIGAS      15
#define NUM_SEGMENT_COMMONWEALTH 12
#define NUM_SEGMENT_QUEZONAVE    25
#define NUM_SEGMENT_ESPANA       8
#define NUM_SEGMENT_ROXAS        12
#define NUM_SEGMENT_SLEX         7
#define NUM_SEGMENT_MARCOSHWY    7
  
#define HIGHWAY_EDSA         0
#define HIGHWAY_C5           1
#define HIGHWAY_ORTIGAS      2
#define HIGHWAY_COMMONWEALTH 3
#define HIGHWAY_QUEZONAVE    4
#define HIGHWAY_ESPANA       5
#define HIGHWAY_ROXAS        6
#define HIGHWAY_SLEX         7
#define HIGHWAY_MARCOSHWY    8
  
typedef struct {
  char *name;
  int id;
} Highway;

typedef struct {
  char *name;
  int id;
  int north;
  int south;
} Segment;


extern const Highway HIGHWAYS[NUM_HIGHWAY];

extern const char* SEGMENTS_EDSA[NUM_SEGMENT_EDSA];
extern const char* SEGMENTS_C5[NUM_SEGMENT_C5];
extern const char* SEGMENTS_ORTIGAS[NUM_SEGMENT_ORTIGAS];
extern const char* SEGMENTS_COMMONWEALTH[0];
extern const char* SEGMENTS_QUEZONAVE[0];
extern const char* SEGMENTS_ESPANA[0];
extern const char* SEGMENTS_ROXAS[0];
extern const char* SEGMENTS_SLEX[0];
extern const char* SEGMENTS_MARCOSHWY[0];

const char** get_segments(int highway);
int get_segment_count(int highway);