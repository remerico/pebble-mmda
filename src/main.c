#include <pebble.h>
#include "api.h"
#include "data.h"
#include "window_highway.h"
#include "window_loading.h"
#include "window_error.h"
  
static void handle_api_loading() {
  show_window_loading();
}

static void handle_api_received(uint8_t *data, int length) {
  hide_window_loading();
}

static void handle_api_failed(char *message) {
  hide_window_loading();
  show_window_error(message);
}
  
int main(void) {
  
  api_set_callbacks((ApiCallbacks){
    .received = handle_api_received,
    .failed = handle_api_failed,
    .loading = handle_api_loading
  });
  
  api_init();
  
  show_window_highway();
  
  if (!data_is_loaded()) {
    api_refresh_data();
  }
  
  app_event_loop();
  
  api_deinit();
  api_unset_callbacks();
  
  return 0;
}
