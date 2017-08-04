#include <pebble.h>
#include <math.h>
#include "fonctions.h"
#include "add_success_window.h"
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_34_medium_numbers;
static GFont s_res_roboto_condensed_21;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;
static TextLayer *s_textlayer_3;
static TextLayer *s_textlayer_4;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(9, 15, 127, 41));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "00,00");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_bitham_34_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(13, 56, 119, 59));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, "added successfully");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_2, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(38, 113, 103, 32));
  text_layer_set_background_color(s_textlayer_3, GColorClear);
  text_layer_set_text(s_textlayer_3, "Category");
  text_layer_set_font(s_textlayer_3, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // s_textlayer_4
  s_textlayer_4 = text_layer_create(GRect(13, 113, 26, 28));
  text_layer_set_background_color(s_textlayer_4, GColorClear);
  text_layer_set_text(s_textlayer_4, "to");
  text_layer_set_font(s_textlayer_4, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_4);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(s_textlayer_4);
}
// END AUTO-GENERATED UI CODE

float categories_values[6];
float total;
AppTimer *timer;
  
void timer_callback(void *data) {
  hide_add_success_window(); 
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  hide_add_success_window(); 
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void handle_window_unload(Window* window) {  
  //Cancel timer
  app_timer_cancel(timer);
  
     // Writing Data in Persistent Storage
  persist_write_int(KEY_CATEGORY_1, (int)(categories_values[0]*100));
    
  app_log(APP_LOG_LEVEL_DEBUG, "add_succes.c", 84, "write %d", ((int) (categories_values[0]*100)));
  persist_write_int(KEY_CATEGORY_2, (int)(categories_values[1]*100));
  persist_write_int(KEY_CATEGORY_3, (int)(categories_values[2]*100));
  persist_write_int(KEY_CATEGORY_4, (int)(categories_values[3]*100));
  persist_write_int(KEY_CATEGORY_5, (int)(categories_values[4]*100));
  persist_write_int(KEY_CATEGORY_6, (int)(categories_values[5]*100));
  persist_write_int(KEY_TOTAL, (int)(total*100));
  
  // Destroy UI
  destroy_ui();
}

void show_add_success_window(float add_value_param, int category) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });  
  
  window_set_click_config_provider(s_window, click_config_provider);
  
  // Reading Data From Persistent Storage
    // Reading Data From Persistent Storage
  categories_values[0] = ((float)persist_read_int(KEY_CATEGORY_1))/100;
  categories_values[1] = ((float)persist_read_int(KEY_CATEGORY_2))/100;
  categories_values[2] = ((float)persist_read_int(KEY_CATEGORY_3))/100;
  categories_values[3] = ((float)persist_read_int(KEY_CATEGORY_4))/100;
  categories_values[4] = ((float)persist_read_int(KEY_CATEGORY_5))/100;
  categories_values[5] = ((float)persist_read_int(KEY_CATEGORY_6))/100;
  total = ((float)(persist_read_int(KEY_TOTAL)))/100;
  
  total+=add_value_param;
  categories_values[category]+=add_value_param;
  
  // Load categories
  static char categories[6][32];
  snprintf(categories[0], sizeof(categories[0]), "%s", "Nourriture");
  snprintf(categories[1], sizeof(categories[1]), "%s", "Sorties");
  snprintf(categories[2], sizeof(categories[2]), "%s", "Hardware");
  snprintf(categories[3], sizeof(categories[3]), "%s", "Voyage");
  snprintf(categories[4], sizeof(categories[4]), "%s", "Frais fixes");
  snprintf(categories[5], sizeof(categories[5]), "%s", "Hors catégories");
  
  static char add_value_char[16];
  ftoa(add_value_char, add_value_param, 2);
//   APP_LOG(APP_LOG_LEVEL_INFO, add_value_char);
//   APP_LOG(APP_LOG_LEVEL_INFO, categories[category]);
  text_layer_set_text(s_textlayer_1, add_value_char);
  text_layer_set_text(s_textlayer_3, categories[category]);

  
  // Show the Window on the watch
  window_stack_push(s_window, true);
  
  timer = app_timer_register(2000, (AppTimerCallback) timer_callback, NULL);
}

void hide_add_success_window(void) {
  window_stack_remove(s_window, true);
}
