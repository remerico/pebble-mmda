#include <pebble.h>
#include "api.h"
  
  
static void message_received_callback(DictionaryIterator *received, void *context) {

  ApiAdContext *ctx = (ApiAdContext*)context;
  
  Tuple *error = dict_find(received, KEY_ERROR);
  
  // Success status
	if (!error) {
    
    Tuple *response = dict_find(received, KEY_RESPONSE);
    AdData *ad;
    Tuple *ad_price;
    Tuple *ad_name;
    Tuple *ad_desc;
    
    switch (response->value->uint32) {
      case RESP_LIST_BEGIN:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Begin ad transfer");
        ctx->index = 0;
        ctx->length = dict_find(received, KEY_AD_COUNT)->value->uint32;
        ctx->ads = malloc(sizeof(int *) * ctx->length);
        break;
      
      case RESP_LIST_DATA:
      
        ad_name = dict_find(received, KEY_AD_TITLE);
        ad_price = dict_find(received, KEY_AD_PRICE);
        ad_desc = dict_find(received, KEY_AD_DESC);
    
        ad = create_ad_data(ad_name->value->cstring,
                           ad_price->value->cstring,
                           ad_desc->value->cstring);
      
        //APP_LOG(APP_LOG_LEVEL_DEBUG, "Ad transfered : %s  =  %s ", ad->name, ad->price);
      
        ctx->ads[ctx->index] = ad;
      
        ctx->index++;
        break;
      
      case RESP_LIST_END:
      
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Ad transfer ended successfully");
      
        if (ctx->received_callback != NULL) ctx->received_callback(ctx->ads, ctx->length);

        // We have transfered ownership of this memory to the app. Make sure we dont free it.
        ctx->ads = NULL;
        ctx->index = ctx->length = 0;
        break;
    }
    
	}
  else {
    if (ctx->failed_callback != NULL) ctx->failed_callback(error->value->uint32);
  }
	
  
}

static void message_dropped_callback(AppMessageResult reason, void *context) {
 // incoming message dropped
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to receive message. reason: %d", reason);
  ApiAdContext *ctx = (ApiAdContext*)context;
  if (ctx->failed_callback != NULL) ctx->failed_callback(ERROR_COMMUNICATION);
}


static void out_failed_callback(DictionaryIterator *failed, AppMessageResult reason, void *context) {
 // outgoing message failed
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send message. reason: %d", reason);
  ApiAdContext *ctx = (ApiAdContext*)context;
  if (ctx->failed_callback != NULL) ctx->failed_callback(ERROR_COMMUNICATION);
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
  free(ad_context);
}