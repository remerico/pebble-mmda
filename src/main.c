#include <pebble.h>
#include "api.h"
#include "data.h"
#include "window_highway.h"
#include "window_loading.h"

  
int main(void) {
  api_init();
  
  show_window_highway();
  
  if (!data_is_loaded()) {
    show_window_loading();
  }
  
  app_event_loop();
  
  api_deinit();
  
  return 0;
}
