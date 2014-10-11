#include "window_highway.h"
#include <pebble.h>
#include "data.h"
#include "window_segment_list.h"
  

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *s_menulayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // s_menulayer
  s_menulayer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_menulayer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_menulayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_menulayer);
}
// END AUTO-GENERATED UI CODE


// A callback is used to specify the amount of sections of menu items
// With this, you can dynamically add and remove sections
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 1;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return NUM_HIGHWAY;
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  menu_cell_basic_draw(ctx, cell_layer, HIGHWAYS[cell_index->row].name, NULL, NULL);
}

// Here we capture when a user selects a menu item
static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
//   switch (cell_index->row) {
  show_window_segment_list(cell_index->row);
}


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_highway(void) {
  initialise_ui();
  
  menu_layer_set_callbacks(s_menulayer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = NULL,
    .draw_header = NULL,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window_highway(void) {
  window_stack_remove(s_window, true);
}
