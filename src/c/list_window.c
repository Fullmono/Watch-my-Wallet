#include <pebble.h>
#include <math.h>
#include "fonctions.h"
#include "list_window.h"
#include "add_window.h"
#include "add_success_window.h"

  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *s_menulayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // s_menulayer_1
  s_menulayer_1 = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_menulayer_1, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_menulayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_menulayer_1);
}
// END AUTO-GENERATED UI CODE

float categories_values[6];
float add_value2=0.0;


// Cells
void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    char total_char[16];
    ftoa(total_char, categories_values[cell_index->row], 2);
//     APP_LOG(APP_LOG_LEVEL_INFO, total_char);
   //Which row is it?
    switch(cell_index->row) {
      case 0:
        menu_cell_basic_draw(ctx, cell_layer, "Nourriture", total_char, NULL);
        break;
      case 1:
        menu_cell_basic_draw(ctx, cell_layer, "Sorties", total_char, NULL);
        break;
      case 2:
        menu_cell_basic_draw(ctx, cell_layer, "Hardware", total_char, NULL);
        break;
      case 3:
        menu_cell_basic_draw(ctx, cell_layer, "Voyage", total_char, NULL);
        break;
      case 4:
        menu_cell_basic_draw(ctx, cell_layer, "Frais fixes", total_char, NULL);
        break;
      case 5:
        menu_cell_basic_draw(ctx, cell_layer, "Hors catégorie", total_char, NULL);
        break;
  }
}
 
uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
  return 6;
}
 
void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
  if (add_value2 > 0.0) {
    //Get which row
    int row_number = cell_index->row;
    show_add_success_window(add_value2, row_number);
    hide_add_window();
    hide_list_window();
  }
}

static void handle_window_unload(Window* window) {
     // Writing Data in Persistent Storage
  persist_write_int(KEY_CATEGORY_1, (int)(categories_values[0]*100));
  persist_write_int(KEY_CATEGORY_2, (int)(categories_values[1]*100));
  persist_write_int(KEY_CATEGORY_3, (int)(categories_values[2]*100));
  persist_write_int(KEY_CATEGORY_4, (int)(categories_values[3]*100));
  persist_write_int(KEY_CATEGORY_5, (int)(categories_values[4]*100));
  persist_write_int(KEY_CATEGORY_6, (int)(categories_values[5]*100));
  // Destroy UI
  destroy_ui();
}

void show_list_window(float add_value_param) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  //Give MenuLayer its callbacks
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback
  };
  menu_layer_set_callbacks(s_menulayer_1, NULL, callbacks);  
  
  // Reading Data From Persistent Storage
  categories_values[0] = ((float)persist_read_int(KEY_CATEGORY_1))/100;
  categories_values[1] = ((float)persist_read_int(KEY_CATEGORY_2))/100;
  categories_values[2] = ((float)persist_read_int(KEY_CATEGORY_3))/100;
  categories_values[3] = ((float)persist_read_int(KEY_CATEGORY_4))/100;
  categories_values[4] = ((float)persist_read_int(KEY_CATEGORY_5))/100;
  categories_values[5] = ((float)persist_read_int(KEY_CATEGORY_6))/100;
  
  add_value2 = add_value_param;
  
  window_stack_push(s_window, true);
}

void hide_list_window(void) {
  window_stack_remove(s_window, true);
}
