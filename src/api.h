#pragma once
  
typedef void (*DataReceivedCallback)(uint8_t *data, int length);
typedef void (*DataFailedCallback)();
typedef void (*ApiReadyCallback)();

typedef struct {
  DataReceivedCallback received;
  DataFailedCallback failed;
} ApiCallbacks;

  
void api_init();
void api_deinit();
void api_set_callbacks(ApiCallbacks callbacks);
void api_unset_callbacks();
void api_refresh_data();
bool api_is_loaded();
void api_set_ready_callback(ApiReadyCallback callback);