#include <pebble.h>
#include "fonctions.h"

void ftoa(char* str, double val, int precision) {
  //  start with positive/negative
  if (val < 0) {
    *(str++) = '-';
    val = -val;
  }
//   // add 0 before to have a 2-digit int (eg. 05,26)
//   if (val < 10) {
//     *(str++) = '0';
//   }
  //  integer value
  snprintf(str, 12, "%d", (int) val);
  str += strlen(str);
  val -= (int) val;
  //  decimals
  if (precision > 0) {
    //  add period
    *(str++) = ',';
    //  loop through precision
    for (int i = 0;  i < precision;  i++)
      if (val > 0) {
        val *= 10;
        *(str++) = '0' + (int) (val + ((i == precision - 1) ? .5 : 0));
        val -= (int) val;
      } 
      else {
        *(str++) = '0';
      }
  }
  //  terminate
  *str = '\0';
}

void select_unit(char* str, char* val, int unit) {
  *(str++) = val[unit];
  //  terminate
  *str = '\0';
}