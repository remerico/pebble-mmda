#pragma once

#define NUM_HIGHWAY              9

#define NUM_SEGMENT_EDSA         37
#define NUM_SEGMENT_C5           19
#define NUM_SEGMENT_ORTIGAS      15
#define NUM_SEGMENT_COMMONWEALTH 0 /*12*/
#define NUM_SEGMENT_QUEZONAVE    0 /*25*/
#define NUM_SEGMENT_ESPANA       0 /*8*/
#define NUM_SEGMENT_ROXAS        0 /*12*/
#define NUM_SEGMENT_SLEX         0 /*7*/
#define NUM_SEGMENT_MARCOSHWY    0 /*7*/
  
#define SEGMENT_FRAME 2  // for north/south bound data
#define LENGTH_SEGMENT_DATA ((NUM_SEGMENT_EDSA + NUM_SEGMENT_C5 + NUM_SEGMENT_ORTIGAS + \
                             NUM_SEGMENT_COMMONWEALTH + NUM_SEGMENT_QUEZONAVE + NUM_SEGMENT_ESPANA + \
                             NUM_SEGMENT_ROXAS + NUM_SEGMENT_SLEX + NUM_SEGMENT_MARCOSHWY) * SEGMENT_FRAME)
  
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
  const char *name;
  int id;
  unsigned char north;
  unsigned char south;
} Segment;


extern const Highway HIGHWAYS[NUM_HIGHWAY];

extern const char* SEGMENTS_EDSA[NUM_SEGMENT_EDSA];
extern const char* SEGMENTS_C5[NUM_SEGMENT_C5];
extern const char* SEGMENTS_ORTIGAS[NUM_SEGMENT_ORTIGAS];
extern const char* SEGMENTS_COMMONWEALTH[NUM_SEGMENT_COMMONWEALTH];
extern const char* SEGMENTS_QUEZONAVE[NUM_SEGMENT_QUEZONAVE];
extern const char* SEGMENTS_ESPANA[NUM_SEGMENT_ESPANA];
extern const char* SEGMENTS_ROXAS[NUM_SEGMENT_ROXAS];
extern const char* SEGMENTS_SLEX[NUM_SEGMENT_SLEX];
extern const char* SEGMENTS_MARCOSHWY[NUM_SEGMENT_MARCOSHWY];

extern const char** SEGMENTS[NUM_HIGHWAY];
extern const int SEGMENT_COUNT[NUM_HIGHWAY];

extern const char* VOLUMES[];

extern uint8_t SEGMENT_DATA[LENGTH_SEGMENT_DATA];

Segment get_segment_data(int highway, int segment);
bool data_is_loaded();
bool data_set_data(uint8_t *data, int length);