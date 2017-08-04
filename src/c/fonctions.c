#include <pebble.h>
#include "fonctions.h"

void ftoa(char* str, double val, int precision) {
  snprintf(str, 16, "%d,%02d", (int)val, (int)(val*100)%100);
}