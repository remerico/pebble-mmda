#include "window_highway.h"
#include <pebble.h>
#include "data.h"
#include "api.h"
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


// Number of sections
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 2;
}

// Number of rows per section
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0: return 1;
    case 1: return NUM_HIGHWAY;
    default: return 0;
  }
}
//  layer_remove_from_parent(text_layer_get_layer(s_menulayer));

// Draw row
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section) {
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Refresh", NULL, NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, HIGHWAYS[cell_index->row].name, NULL, NULL);
      break;
  }
}

// Row click callback
static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {  
  switch (cell_index->section) {
    case 0:
      api_refresh_data();
      break;
    case 1:
      show_window_segment_list(cell_index->row);
      break;
  }
}


static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window_highway(void) {
  initialise_ui();
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Highway menu initialized");
  
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
