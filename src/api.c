#include <pebble.h>
#include "api.h"
#include "data.h"
  
#define KEY_COMMAND 0
#define KEY_DATA 1
#define KEY_ERROR 2
  
#define COMMAND_READY 1
#define COMMAND_DATA 2
  
static ApiCallbacks api_callbacks;
static bool is_ready = false;  

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
        api_callbacks.failed();
      }
    }
    
	}
  else {
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Message received, has error");
    
    if (api_callbacks.failed != NULL) {
      api_callbacks.failed();
    }
  }
  
}


static void message_received_callback(DictionaryIterator *received, void *context) {
  
  int32_t command = dict_find(received, KEY_COMMAND)->value->int32;
  
  switch (command) {
    case COMMAND_READY:
      is_ready = true;
      if (api_callbacks.ready != NULL) api_callbacks.ready();
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
    api_callbacks.failed();
  }
  
}


static void out_failed_callback(DictionaryIterator *failed, AppMessageResult reason, void *context) {
 // outgoing message failed
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send message. reason: %d", reason);

  if (api_callbacks.failed != NULL) {
    api_callbacks.failed();
  }
  
}
  

void api_init() {
    
  // Register app message for fetching ads
  app_message_register_inbox_received(message_received_callback); 
  app_message_register_inbox_dropped(message_dropped_callback);
  app_message_register_outbox_failed(out_failed_callback);
  
	AppMessageResult res = app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "app message open result: %d", res);
  
}

void api_deinit() {
  app_message_deregister_callbacks();
}

void api_set_callbacks(ApiCallbacks cb) {
  api_callbacks = cb;
}

void api_unset_callbacks() {
  api_callbacks = (ApiCallbacks){
    .received = NULL,
    .failed = NULL,
    .ready = NULL
  };
}

void api_refresh_data() {

  DictionaryIterator *iter;
	
	app_message_outbox_begin(&iter);	

  dict_write_uint8(iter, KEY_DATA, 1);
  
	dict_write_end(iter);
  	
  app_message_outbox_send();
}

bool api_is_ready() {
  return is_ready;
}

