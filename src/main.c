#include <pebble.h>
#include <math.h>
#include "fonctions.h"
#include "add_window.h"
#include "list_window.h"
  
// Persist Mem keys
#define KEY_CATEGORY_1_1 0
#define KEY_CATEGORY_1_2 1
#define KEY_CATEGORY_2_1 2
#define KEY_CATEGORY_2_2 3
#define KEY_CATEGORY_3_1 4
#define KEY_CATEGORY_3_2 5
#define KEY_CATEGORY_4_1 6
#define KEY_CATEGORY_4_2 7
#define KEY_CATEGORY_5_1 8
#define KEY_CATEGORY_5_2 9
#define KEY_CATEGORY_6_1 10
#define KEY_CATEGORY_6_2 11
#define KEY_TOTAL_1 12
#define KEY_TOTAL_2 13
  
// AppMessage keys
#define KEY_NEW_CATEGORY 0
  
static Window *s_main_window;

static GFont s_res_roboto_condensed_21;
static GBitmap *s_res_action_icon_refresh;
static GBitmap *s_res_action_icon_add;
static GBitmap *s_res_action_icon_list;
static GFont s_res_bitham_34_medium_numbers;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static BitmapLayer *s_bitmaplayer_1;
static BitmapLayer *s_bitmaplayer_2;
static BitmapLayer *s_bitmaplayer_3;
static BitmapLayer *s_bitmaplayer_4;

float categories_values[6];
float total;

static void main_window_load(Window *window) {
  window_set_fullscreen(s_main_window, false);
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_action_icon_refresh = gbitmap_create_with_resource(RESOURCE_ID_action_icon_refresh);
  s_res_action_icon_add = gbitmap_create_with_resource(RESOURCE_ID_action_icon_add);
  s_res_action_icon_list = gbitmap_create_with_resource(RESOURCE_ID_action_icon_list);
  s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(18, 35, 100, 30));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "Total");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(2, 66, 108, 40));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, "00,00");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_2, s_res_bitham_34_medium_numbers);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_textlayer_2);
  
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(29, 64, 80, 1));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_bitmaplayer_1);
  
  // s_bitmaplayer_2
  s_bitmaplayer_2 = bitmap_layer_create(GRect(120, 115, 23, 23));
  bitmap_layer_set_bitmap(s_bitmaplayer_2, s_res_action_icon_list);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_bitmaplayer_2);
  
  // s_bitmaplayer_3
  s_bitmaplayer_3 = bitmap_layer_create(GRect(120, 67, 23, 23));
  bitmap_layer_set_bitmap(s_bitmaplayer_3, s_res_action_icon_add);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_bitmaplayer_3);
  
  // s_bitmaplayer_4
  s_bitmaplayer_4 = bitmap_layer_create(GRect(120, 17, 23, 23));
  bitmap_layer_set_bitmap(s_bitmaplayer_4, s_res_action_icon_refresh);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_bitmaplayer_4);
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  bitmap_layer_destroy(s_bitmaplayer_1);
  bitmap_layer_destroy(s_bitmaplayer_2);
  bitmap_layer_destroy(s_bitmaplayer_3);
  bitmap_layer_destroy(s_bitmaplayer_4);
  gbitmap_destroy(s_res_action_icon_add);
  gbitmap_destroy(s_res_action_icon_refresh);
  gbitmap_destroy(s_res_action_icon_list);
}

// Read data
void read_data() {  
  // Reading Data From Persistent Storage
  categories_values[0] = (float)persist_read_int(KEY_CATEGORY_1_1) + ((float)persist_read_int(KEY_CATEGORY_1_2)/100);
  categories_values[1] = (float)persist_read_int(KEY_CATEGORY_2_1) + ((float)persist_read_int(KEY_CATEGORY_2_2)/100);
  categories_values[2] = (float)persist_read_int(KEY_CATEGORY_3_1) + ((float)persist_read_int(KEY_CATEGORY_3_2)/100);
  categories_values[3] = (float)persist_read_int(KEY_CATEGORY_4_1) + ((float)persist_read_int(KEY_CATEGORY_4_2)/100);
  categories_values[4] = (float)persist_read_int(KEY_CATEGORY_5_1) + ((float)persist_read_int(KEY_CATEGORY_5_2)/100);
  categories_values[5] = (float)persist_read_int(KEY_CATEGORY_6_1) + ((float)persist_read_int(KEY_CATEGORY_6_2)/100);
  total = (float)persist_read_int(KEY_TOTAL_1) + ((float)persist_read_int(KEY_TOTAL_2)/100);
}

// Write data
void write_data() {    
  // Writing Data in Persistent Storage
  persist_write_int(KEY_CATEGORY_1_1, (int)categories_values[0]);
  persist_write_int(KEY_CATEGORY_1_2, (int)((categories_values[0]-floor(categories_values[0]))*100) );
  persist_write_int(KEY_CATEGORY_2_1, (int)categories_values[1]);
  persist_write_int(KEY_CATEGORY_2_2, (int)((categories_values[1]-floor(categories_values[1]))*100) );
  persist_write_int(KEY_CATEGORY_3_1, (int)categories_values[2]);
  persist_write_int(KEY_CATEGORY_3_2, (int)((categories_values[2]-floor(categories_values[2]))*100) );
  persist_write_int(KEY_CATEGORY_4_1, (int)categories_values[3]);
  persist_write_int(KEY_CATEGORY_4_2, (int)((categories_values[3]-floor(categories_values[3]))*100) );
  persist_write_int(KEY_CATEGORY_5_1, (int)categories_values[4]);
  persist_write_int(KEY_CATEGORY_5_2, (int)((categories_values[4]-floor(categories_values[4]))*100) );
  persist_write_int(KEY_CATEGORY_6_1, (int)categories_values[5]);
  persist_write_int(KEY_CATEGORY_6_2, (int)((categories_values[5]-floor(categories_values[5]))*100) );
  persist_write_int(KEY_TOTAL_1, (int)total);
  persist_write_int(KEY_TOTAL_2, (int)((total-floor(total))*100) );
}

// Display total
void display_total() {  
  static char total_char[16];
  ftoa(total_char, total, 2);
  text_layer_set_text(s_textlayer_2, total_char); 
}

// Click handlers

void up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
//   ... called on long click start ...
  total=0.0;
  categories_values[0]=0.0;
  categories_values[1]=0.0;
  categories_values[2]=0.0;
  categories_values[3]=0.0;
  categories_values[4]=0.0;
  categories_values[5]=0.0;
  vibes_short_pulse();
  text_layer_set_text(s_textlayer_2, "0,00"); 
}

void up_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
//   ... called when long click is released ...
}
 
void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  write_data();
  show_list_window(0.0);
}
 
void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "select_click_handler");
  write_data();
  show_add_window();
}

void click_config_provider(void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "click_config_provider");
  window_long_click_subscribe(BUTTON_ID_UP, 500, up_long_click_handler, up_long_click_release_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  
  read_data();
  display_total();
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  // Store incoming information
//   static char total_value[16];
  
  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case KEY_NEW_CATEGORY:
//       snprintf(categories_buffer[0][0], sizeof(categories_buffer[0][0]), "%s", t->value->cstring);
      APP_LOG(APP_LOG_LEVEL_INFO, "%s", t->value->cstring);
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  
//   text_layer_set_text(s_textlayer_2, total_value);
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_set_click_config_provider(s_main_window, click_config_provider);  
  
  read_data();
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  display_total();
}

static void deinit() {
  write_data();
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
