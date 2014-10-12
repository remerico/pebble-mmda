#include "window_loading.h"
#include <pebble.h>
#include "api.h"
#include "window_error.h"

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


static void handle_back_button(ClickRecognizerRef recognizer, void *context) {
}

static void handle_config_provider(Window *window) {
  window_single_click_subscribe(BUTTON_ID_BACK, handle_back_button);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_loading(void) {
  
  initialise_ui();
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  window_set_click_config_provider(s_window, (ClickConfigProvider) handle_config_provider);

  window_stack_push(s_window, true);
    
}

void hide_window_loading(void) {
  window_stack_remove(s_window, true);
}
