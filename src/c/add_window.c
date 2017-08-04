#include <pebble.h>
#include "fonctions.h"
#include "add_window.h"
#include "list_window.h"

static GBitmap *s_res_action_icon_ok;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_action_icon_plus;
static GBitmap *s_res_action_icon_minus;
static GFont s_res_bitham_34_medium_numbers;
static GFont s_res_roboto_condensed_21;
static GBitmap *s_res_action_icon_right;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_action_icon_plus = gbitmap_create_with_resource(RESOURCE_ID_action_icon_plus);
  s_res_action_icon_minus = gbitmap_create_with_resource(RESOURCE_ID_action_icon_minus);
  s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_action_icon_right = gbitmap_create_with_resource(RESOURCE_ID_action_icon_right);
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorWhite);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_UP, s_res_action_icon_plus);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_action_icon_right);
  action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_DOWN, s_res_action_icon_minus);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(11, 53, 104, 42));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "00,00");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_bitham_34_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(6, 124, 51, 28));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text(s_textlayer_2, "x10");
  text_layer_set_font(s_textlayer_2, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
  gbitmap_destroy(s_res_action_icon_plus);
  gbitmap_destroy(s_res_action_icon_minus);
  gbitmap_destroy(s_res_action_icon_right);
}
// END AUTO-GENERATED UI CODE

float add_value=0.0;
float current_unit=10.0;
static char add_value_char[16];

// Click handlers
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if((add_value+current_unit)<100.0) {
    add_value+=current_unit;
  }
  else {
     add_value=0.0;
  }
  ftoa(add_value_char, add_value, 2);
  app_log(APP_LOG_LEVEL_DEBUG, "add_window.c", 63, "%s", add_value_char);
  text_layer_set_text(s_textlayer_1, add_value_char);
}
 
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {  
  if((add_value-current_unit)>=0.0) {
    add_value-=current_unit;
  }
  else {
     add_value=100.0-current_unit;
  }
  ftoa(add_value_char, add_value, 2);
  app_log(APP_LOG_LEVEL_DEBUG, "add_window.c", 63, "%s", add_value_char);
  text_layer_set_text(s_textlayer_1, add_value_char);
}
 
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (current_unit > 0.01) {
    current_unit = current_unit/10;
    if (current_unit < 0.1) {
      text_layer_set_text(s_textlayer_2, "x0.01");      
      s_res_action_icon_ok = gbitmap_create_with_resource(RESOURCE_ID_action_icon_ok);
      action_bar_layer_set_icon(s_actionbarlayer_1, BUTTON_ID_SELECT, s_res_action_icon_ok);
    } else if (current_unit < 1) {
      text_layer_set_text(s_textlayer_2, "x0.1");
    } else {
      text_layer_set_text(s_textlayer_2, "x1");
    }
  }
  else {
    show_list_window(add_value);
  }
}

void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
//   ... called on long click start ...
  show_list_window(add_value);
}

void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
//   ... called when long click is released ...
}

static void click_config_provider(void *context)
{
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  // long click config:
  window_long_click_subscribe(BUTTON_ID_SELECT, 500, select_long_click_handler, select_long_click_release_handler);
}

// Display window
static void handle_window_unload(Window* window) { 
  // Destroy UI
  destroy_ui();
}

void show_add_window() {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  add_value=0.0;
  current_unit=10.0;
  window_set_click_config_provider(s_window, click_config_provider);
  
  window_stack_push(s_window, true);
}

void hide_add_window(void) {
  window_stack_remove(s_window, true);
}
