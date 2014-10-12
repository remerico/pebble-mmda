#include "window_loading.h"
#include <pebble.h>
#include "api.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24_bold;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(0, 40, 144, 59));
  text_layer_set_text(s_textlayer_1, "Loading data... Please wait!");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE


static bool is_loading = false;

static void refresh_data() {
  if (!is_loading) {
    is_loading = true;
    api_refresh_data();
  }
}

static void handle_api_received(uint8_t *data, int length) {
  is_loading = false;
  hide_window_loading();
}

static void handle_api_failed() {
  is_loading = false;
  text_layer_set_text(s_textlayer_1, "Loading failed. Please try again :(");
}

static void handle_window_unload(Window* window) {
  destroy_ui();
  api_unset_callbacks();
}

void show_window_loading(void) {
  
  initialise_ui();
  
  api_set_callbacks((ApiCallbacks){
    .received = handle_api_received,
    .failed = handle_api_failed
  });
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  window_stack_push(s_window, true);
  
  refresh_data();
}

void hide_window_loading(void) {
  window_stack_remove(s_window, true);
}
