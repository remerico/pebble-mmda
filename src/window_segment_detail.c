#include "window_segment_detail.h"
#include <pebble.h>
#include "data.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_18_bold;
static GFont s_res_bitham_30_black;
static GFont s_res_gothic_24;
static TextLayer *s_textSegment;
static TextLayer *s_textNorthLabel;
static TextLayer *s_textSouthLabel;
static TextLayer *s_textSouthValue;
static TextLayer *s_textNorthValue;
static TextLayer *s_textHighway;
static InverterLayer *s_inverterlayer_1;
static InverterLayer *s_inverterlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  // s_textSegment
  s_textSegment = text_layer_create(GRect(4, 93, 136, 72));
  text_layer_set_background_color(s_textSegment, GColorClear);
  text_layer_set_text(s_textSegment, "Robinson's East");
  text_layer_set_font(s_textSegment, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textSegment);
  
  // s_textNorthLabel
  s_textNorthLabel = text_layer_create(GRect(11, 42, 44, 20));
  text_layer_set_text(s_textNorthLabel, "North");
  text_layer_set_text_alignment(s_textNorthLabel, GTextAlignmentCenter);
  text_layer_set_font(s_textNorthLabel, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textNorthLabel);
  
  // s_textSouthLabel
  s_textSouthLabel = text_layer_create(GRect(86, 42, 44, 20));
  text_layer_set_text(s_textSouthLabel, "South");
  text_layer_set_text_alignment(s_textSouthLabel, GTextAlignmentCenter);
  text_layer_set_font(s_textSouthLabel, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textSouthLabel);
  
  // s_textSouthValue
  s_textSouthValue = text_layer_create(GRect(75, 8, 65, 35));
  text_layer_set_text(s_textSouthValue, "Hi");
  text_layer_set_text_alignment(s_textSouthValue, GTextAlignmentCenter);
  text_layer_set_font(s_textSouthValue, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textSouthValue);
  
  // s_textNorthValue
  s_textNorthValue = text_layer_create(GRect(1, 8, 65, 35));
  text_layer_set_background_color(s_textNorthValue, GColorClear);
  text_layer_set_text(s_textNorthValue, "Low");
  text_layer_set_text_alignment(s_textNorthValue, GTextAlignmentCenter);
  text_layer_set_font(s_textNorthValue, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textNorthValue);
  
  // s_textHighway
  s_textHighway = text_layer_create(GRect(4, 67, 137, 29));
  text_layer_set_background_color(s_textHighway, GColorClear);
  text_layer_set_text(s_textHighway, "Ortigas");
  text_layer_set_font(s_textHighway, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textHighway);
  
  // s_inverterlayer_1
  s_inverterlayer_1 = inverter_layer_create(GRect(0, 0, 70, 66));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer_1);
  
  // s_inverterlayer_2
  s_inverterlayer_2 = inverter_layer_create(GRect(72, 0, 72, 66));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textSegment);
  text_layer_destroy(s_textNorthLabel);
  text_layer_destroy(s_textSouthLabel);
  text_layer_destroy(s_textSouthValue);
  text_layer_destroy(s_textNorthValue);
  text_layer_destroy(s_textHighway);
  inverter_layer_destroy(s_inverterlayer_1);
  inverter_layer_destroy(s_inverterlayer_2);
}
// END AUTO-GENERATED UI CODE


int highwayId;
int segmentId;

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_segment_detail(int highway, int segment) {
  
  highwayId = highway;
  segmentId = segment;
  
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  text_layer_set_text(s_textHighway, HIGHWAYS[highwayId].name);
  text_layer_set_text(s_textSegment, SEGMENTS[highwayId][segmentId]);
  
  Segment seg = get_segment_data(highway, segment);
  text_layer_set_text(s_textNorthValue, VOLUMES[seg.north]);
  text_layer_set_text(s_textSouthValue, VOLUMES[seg.south]);
  
  window_stack_push(s_window, true);
}

void hide_window_segment_detail(void) {
  window_stack_remove(s_window, true);
}
