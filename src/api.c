#include <pebble.h>
#include "api.h"
#include "data.h"
  
#define KEY_COMMAND 0
#define KEY_DATA 1
#define KEY_ERROR 2
#define KEY_REFRESH 3
  
#define COMMAND_READY 1
#define COMMAND_DATA 2
  
static ApiCallbacks api_callbacks;
static bool is_ready = false;

// Forward declaration. 'cuz you know. :P
static void open_message();
static void send_refresh_message(bool force_refresh);


static void handle_message_data(DictionaryIterator *received) {
  
  Tuple *error = dict_find(received, KEY_ERROR);
  
  // Success status
	if (error->value->uint32 == 0) {
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Message received!");
    
    Tuple *tup_data = dict_find(received, KEY_DATA);
    
    uint8_t* data = tup_data->value->data;
    int length = tup_data->length;
    
    if (data_set_data(data, length)) {
      if (api_callbacks.received != NULL) {
        api_callbacks.received(data, length);
      }    
    }
    else {
      if (api_callbacks.failed != NULL) {
        api_callbacks.failed("Incorrect data received from phone. :(");
      }
    }
    
	}
  else {
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Message received, has error");
    
    if (api_callbacks.failed != NULL) {
      api_callbacks.failed("Server timed out, please try again. :(");
    }
  }
  
}


static void message_received_callback(DictionaryIterator *received, void *context) {
  
  int32_t command = dict_find(received, KEY_COMMAND)->value->int32;
  
  switch (command) {
    case COMMAND_READY:
      is_ready = true;
      send_refresh_message(false);
      break;
    
    case COMMAND_DATA:
      handle_message_data(received);
      break;
  }
  
}

static void message_dropped_callback(AppMessageResult reason, void *context) {
 // incoming message dropped
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to receive message. reason: %d", reason);

  if (api_callbacks.failed != NULL) {
    api_callbacks.failed("Failed to communicate with your phone. :(");
  }
  
}


static void out_failed_callback(DictionaryIterator *failed, AppMessageResult reason, void *context) {
 // outgoing message failed
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send message. reason: %d", reason);

  if (api_callbacks.failed != NULL) {
    api_callbacks.failed("Unable to send message, please try again");
  }
  
}
  
static void handle_bluetooth_connection(bool connected) {
  if (connected) {
    open_message();
  }
  else {
    api_callbacks.failed("Pebble lost Bluetooth connection!");
    is_ready = false;
  }
}

static void open_message() {
  
  if (bluetooth_connection_service_peek()) {
  
    AppMessageResult res = app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
    APP_LOG(APP_LOG_LEVEL_DEBUG, "app message open result: %d", res);

    switch (res) {

      case APP_MSG_OK:
        if (api_callbacks.loading != NULL) api_callbacks.loading();
        break;

      default:
        if (api_callbacks.failed != NULL) api_callbacks.failed("Cannot communicate with your phone. :(");
        break;
    }
    
  }
  else {
    if (api_callbacks.failed != NULL) api_callbacks.failed("Pebble is not connected. :(");
  }
  
}

static void send_refresh_message(bool force_refresh) {

  DictionaryIterator *iter;
	
	app_message_outbox_begin(&iter);	

  dict_write_uint8(iter, KEY_REFRESH, force_refresh ? 1 : 0);
  
	dict_write_end(iter);
  	
  app_message_outbox_send();

  
}

void api_init() {
    
  // Register app message for fetching ads
  app_message_register_inbox_received(message_received_callback); 
  app_message_register_inbox_dropped(message_dropped_callback);
  app_message_register_outbox_failed(out_failed_callback);
  
  bluetooth_connection_service_subscribe(handle_bluetooth_connection);
  	
}

void api_deinit() {
  app_message_deregister_callbacks();
  bluetooth_connection_service_unsubscribe();
}

void api_set_callbacks(ApiCallbacks cb) {
  api_callbacks = cb;
}

void api_unset_callbacks() {
  api_callbacks = (ApiCallbacks){
    .received = NULL,
    .failed = NULL,
    .ready = NULL,
    .loading = NULL
  };
}

void api_refresh_data() {
  
  if (!is_ready) {
    open_message();
  }
  else {
    if (api_callbacks.loading != NULL) api_callbacks.loading();
    send_refresh_message(true);
  }
  
}

bool api_is_ready() {
  return is_ready;
}

