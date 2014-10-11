#include "window_main.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static MenuLayer *s_menulayer;
static TextLayer *s_textLoading;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_menulayer
  s_menulayer = menu_layer_create(GRect(0, 0, 144, 168));
  menu_layer_set_click_config_onto_window(s_menulayer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_menulayer);
  
  // s_textLoading
  s_textLoading = text_layer_create(GRect(0, 47, 144, 77));
  text_layer_set_background_color(s_textLoading, GColorClear);
  text_layer_set_text(s_textLoading, "Refreshing data...");
  text_layer_set_text_alignment(s_textLoading, GTextAlignmentCenter);
  text_layer_set_font(s_textLoading, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textLoading);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_menulayer);
  text_layer_destroy(s_textLoading);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window_main(void) {
  window_stack_remove(s_window, true);
}
