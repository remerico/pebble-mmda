#include "window_error.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_24;
static TextLayer *s_textlayer_1;
static InverterLayer *s_inverterlayer_1;
static TextLayer *s_textError;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(2, 14, 141, 27));
  text_layer_set_text(s_textlayer_1, "ERROR!");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_inverterlayer_1
  s_inverterlayer_1 = inverter_layer_create(GRect(19, 15, 107, 30));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer_1);
  
  // s_textError
  s_textError = text_layer_create(GRect(10, 50, 126, 98));
  text_layer_set_text(s_textError, "Pebble is not connected via Bluetooth!");
  text_layer_set_text_alignment(s_textError, GTextAlignmentCenter);
  text_layer_set_font(s_textError, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textError);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  inverter_layer_destroy(s_inverterlayer_1);
  text_layer_destroy(s_textError);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_error(char *text) {
  initialise_ui();
  
  text_layer_set_text(s_textError, text);
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window_error(void) {
  window_stack_remove(s_window, true);
}
