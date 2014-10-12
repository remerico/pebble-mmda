#include <pebble.h>
#include "api.h"
#include "window_highway.h"
#include "window_loading.h"
  

void handle_api_ready() {
  if (!api_is_loaded()) {
    show_window_loading();
  }
}

  
int main(void) {
  api_set_ready_callback((ApiReadyCallback)handle_api_ready);
  api_init();
  
  show_window_highway();
  app_event_loop();
  
  api_deinit();
  
  return 0;
}
