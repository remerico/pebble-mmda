#include "window_segment_detail.h"
#include <pebble.h>
#include "data.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_24;
static TextLayer *s_textSegment;
static TextLayer *s_textNorthLabel;
static TextLayer *s_textSouthLabel;
static TextLayer *s_textNorthValue;
static TextLayer *s_textSouthValue;
static ActionBarLayer *s_actionbar;
static InverterLayer *s_inverterlayer1;
static InverterLayer *s_inverterlayer2;
static TextLayer *s_textHighway;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  // s_textSegment
  s_textSegment = text_layer_create(GRect(4, 23, 119, 62));
  text_layer_set_background_color(s_textSegment, GColorClear);
  text_layer_set_text(s_textSegment, "Robinson's East");
  text_layer_set_font(s_textSegment, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textSegment);
  
  // s_textNorthLabel
  s_textNorthLabel = text_layer_create(GRect(4, 89, 44, 20));
  text_layer_set_text(s_textNorthLabel, "North:");
  text_layer_set_text_alignment(s_textNorthLabel, GTextAlignmentRight);
  text_layer_set_font(s_textNorthLabel, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textNorthLabel);
  
  // s_textSouthLabel
  s_textSouthLabel = text_layer_create(GRect(4, 120, 44, 20));
  text_layer_set_text(s_textSouthLabel, "South:");
  text_layer_set_text_alignment(s_textSouthLabel, GTextAlignmentRight);
  text_layer_set_font(s_textSouthLabel, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textSouthLabel);
  
  // s_textNorthValue
  s_textNorthValue = text_layer_create(GRect(56, 81, 59, 29));
  text_layer_set_background_color(s_textNorthValue, GColorClear);
  text_layer_set_text(s_textNorthValue, "L-M");
  text_layer_set_text_alignment(s_textNorthValue, GTextAlignmentCenter);
  text_layer_set_font(s_textNorthValue, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textNorthValue);
  
  // s_textSouthValue
  s_textSouthValue = text_layer_create(GRect(56, 114, 59, 29));
  text_layer_set_background_color(s_textSouthValue, GColorClear);
  text_layer_set_text(s_textSouthValue, "L");
  text_layer_set_text_alignment(s_textSouthValue, GTextAlignmentCenter);
  text_layer_set_font(s_textSouthValue, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textSouthValue);
  
  // s_actionbar
  s_actionbar = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbar, s_window);
  action_bar_layer_set_background_color(s_actionbar, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbar);
  
  // s_inverterlayer1
  s_inverterlayer1 = inverter_layer_create(GRect(56, 85, 59, 29));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer1);
  
  // s_inverterlayer2
  s_inverterlayer2 = inverter_layer_create(GRect(56, 118, 59, 29));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer2);
  
  // s_textHighway
  s_textHighway = text_layer_create(GRect(4, -1, 100, 29));
  text_layer_set_background_color(s_textHighway, GColorClear);
  text_layer_set_text(s_textHighway, "Ortigas");
  text_layer_set_font(s_textHighway, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textHighway);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textSegment);
  text_layer_destroy(s_textNorthLabel);
  text_layer_destroy(s_textSouthLabel);
  text_layer_destroy(s_textNorthValue);
  text_layer_destroy(s_textSouthValue);
  action_bar_layer_destroy(s_actionbar);
  inverter_layer_destroy(s_inverterlayer1);
  inverter_layer_destroy(s_inverterlayer2);
  text_layer_destroy(s_textHighway);
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
  text_layer_set_text(s_textSegment, get_segments(highwayId)[segmentId]);
  
  window_stack_push(s_window, true);
}

void hide_window_segment_detail(void) {
  window_stack_remove(s_window, true);
}
