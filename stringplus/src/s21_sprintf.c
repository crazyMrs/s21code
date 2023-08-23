#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct {
  /*флаги*/
  int plus_on;
  int minus_on;
  int space_on;
  int zero_last;
  int zero_flag;
  /*числа*/
  int accuracy;
  int width;
  int dot_presence;
  int accuracy_on;
  int additional_accuracy;
  int additional_width;
  /*длины*/
  int size_h;
  int size_l;
  int size_double;
} properties;

typedef struct {
  int c;
  int d;
  int i;
  int e;
  int E;
  int f;
  int g;
  int G;
  int o;
  int s;
  int u;
  int x;
  int X;
  int p;
  int n;
  int percent;
} flags;

void text_output(char* str, int* len, const char* ptr_text_output);
int check_options(flags* s, properties* character,
                  const char** ptr_text_output);
void add_accuracy_width(const char* ptr_text_output, properties* character);
void initiate_struct(properties* character);
int check_flags(flags* s, const char* ptr_text_output);
void processing_specifiers(char* str, int* len, const char* ptr_text_output,
                           va_list ap, flags* s, properties* character);
void handling_int_idu(char* str, int* len, va_list ap, properties* character,
                      flags* s);
char* number_to_string(long int final, int accuracy, int accuracy_on);
void w_and_accuracy(char* str, int* len, char* str_add, properties* character,
                    int accuracy_null);
void add_accuracy(char* str, int* len, int accuracy_null, char* str_add);
void add_accuracy_zero(char* str, int* len, char* str_add,
                       properties* character);
void handling_float_f(char* str, int* len, va_list ap, properties* character,
                      flags* s);
void no_zero_prosto_width(char* str, int* len, char* str_add,
                          properties* character);
void minus_character_add(char* str, int* len, char* str_add,
                         properties* character, int accuracy_null);
void accuracy_f(properties* character);
char* str_num_double(long double num_double, properties* character);
void s21_back_str(char* str, int before_num, int* len);
void octothorpe_and_no(properties* character, char* nash_num_double,
                       int* num_arr, long double num_double);
void recovery_processing(properties* character, int treatment,
                         char* nash_num_double, int* num_arr,
                         long double num_double);
void handling_exp_eE(char* str, int* len, va_list ap, properties* character,
                     flags* s);
void handling_exp_gG(char* str, int* len, va_list ap, properties* character,
                     flags* s);
void out_str(char* str_f, char* str, int* len, flags* s);
void check_conditions_wa(va_list ap, properties* character);
char* str_num_double_eE(long double num_double, properties* character,
                        flags* s);
char* str_num_double_gG(long double num_double, properties* character,
                        flags* s);
void add_main_num_exp(int* len_e, long double num_double);
void s21_specifiers_xX(char* str, int* len, va_list ap, properties* character,
                       flags* s);
void s21_specifiers_o(char* str, int* len, va_list ap, properties* character,
                      flags* s);
void handling_char_c(char* str, int* len, va_list ap, properties* character);
void handling_string_s(char* str, int* len, va_list ap, properties* character);
void s21_specifier_p(char* str, int* len, va_list ap, properties* character,
                     const char* ptr_text_output);
void s21_accuracy(char* str, int* len, int before_num, properties* character,
                  flags* s);
void s21_sign_flag(char* str, int* len, int before_num, properties* character);
void s21_flag_width(char* str, properties* character);
void s21_str_hl(char* str, int* len, int before_num, unsigned long long number,
                flags* s);
void s21_str_ol(char* str, int* len, int before_num, unsigned long long number,
                properties* character);
void urezaem_null_tochka(char* str, int* num);

int s21_sprintf(char* str, const char* format, ...) {
  int len = 0;
  va_list ap;
  va_start(ap, format);
  properties character;
  const char* ptr_text_output = S21_NULL;
  for (ptr_text_output = format; *ptr_text_output != '\0'; ptr_text_output++) {
    if (*ptr_text_output != '%') {
      text_output(str, &len, ptr_text_output);
    }
    if (*ptr_text_output == '%') {
      flags s = {0};
      initiate_struct(&character);
      if (check_options(&s, &character, &ptr_text_output)) {
        processing_specifiers(str, &len, ptr_text_output, ap, &s, &character);
      }
    }
  }
  va_end(ap);
  str[len] = '\0';
  return s21_strlen(str);
}

void initiate_struct(properties* character) {
  character->plus_on = 0;
  character->minus_on = 0;
  character->space_on = 0;
  character->zero_last = 0;
  character->accuracy = 0;
  character->width = 0;
  character->dot_presence = 0;
  character->size_h = 0;
  character->size_l = 0;
  character->size_double = 0;
  character->zero_flag = 0;
  character->additional_width = 0;
  character->additional_accuracy = 0;
  character->accuracy_on = 0;
}

void text_output(char* str, int* len, const char* ptr_text_output) {
  str[*len] = *ptr_text_output;
  *len += 1;
}

void s21_specifiers_xX(char* str, int* len, va_list ap, properties* character,
                       flags* s) {
  unsigned long int li_number;
  unsigned short int si_number;
  unsigned int i_number;
  int before_num = *len;
  if (character->size_h) {
    si_number = (short unsigned int)va_arg(ap, unsigned int);
    s21_str_hl(str, len, before_num, si_number, s);
  } else if (character->size_l) {
    li_number = (long unsigned int)va_arg(ap, unsigned long int);
    s21_str_hl(str, len, before_num, li_number, s);
  } else {
    i_number = (unsigned int)va_arg(ap, unsigned int);
    s21_str_hl(str, len, before_num, i_number, s);
  }
  s21_accuracy(str, len, before_num, character, s);
  s21_sign_flag(str, len, before_num, character);
  s21_flag_width(str, character);
}

void add_accuracy_width(const char* ptr_text_output, properties* character) {
  int add = *ptr_text_output - '0';
  int process_o = 0;
  if (*ptr_text_output == '0') {
    process_o = 1;
    if (character->dot_presence == 1) {
      if (character->accuracy == 0) {
        character->accuracy += add;
        character->accuracy_on = 1;
      } else {
        character->accuracy *= 10;
        character->accuracy += add;
      }
    } else {
      if (character->zero_flag == 0 && character->width == 0) {
        character->zero_flag = 1;
      } else {
        character->width *= 10;
      }
    }
  }
  if (process_o == 0) {
    if (character->dot_presence == 0) {
      if (character->width == 0) {
        character->width += add;
      } else {
        character->width *= 10;
        character->width += add;
      }
    } else {
      if (character->accuracy == 0) {
        character->accuracy += add;
      } else {
        character->accuracy *= 10;
        character->accuracy += add;
      }
    }
  }
}

int check_flags(flags* s, const char* ptr_text_output) {
  int flag = 1;
  if (*ptr_text_output == 'c') {  //
    s->c = 1;
  } else if (*ptr_text_output == 'd') {  //
    s->d = 1;
  } else if (*ptr_text_output == 'i') {  //
    s->i = 1;
  } else if (*ptr_text_output == 'e') {
    s->e = 1;
  } else if (*ptr_text_output == 'E') {
    s->E = 1;
  } else if (*ptr_text_output == 'f') {  //
    s->f = 1;
  } else if (*ptr_text_output == 'g') {
    s->g = 1;
  } else if (*ptr_text_output == 'G') {
    s->G = 1;
  } else if (*ptr_text_output == 'o') {  //
    s->o = 1;
  } else if (*ptr_text_output == 's') {  //
    s->s = 1;
  } else if (*ptr_text_output == 'u') {  //
    s->u = 1;
  } else if (*ptr_text_output == 'x') {
    s->x = 1;
  } else if (*ptr_text_output == 'X') {
    s->X = 1;
  } else if (*ptr_text_output == 'p') {  //
    s->p = 1;
  } else if (*ptr_text_output == 'n') {
    s->n = 1;
  } else if (*ptr_text_output == '%') {  //
    s->percent = 1;
  } else {
    flag = 0;
  }
  return flag;
}

int check_options(flags* s, properties* character,
                  const char** ptr_text_output) {
  int flag_end = 1;
  for (; flag_end;) {
    *ptr_text_output += 1;
    if (**ptr_text_output ==
        ' ') {  //Если знак не будет выведен, перед значением вставляется
                //пробел. Не работает с флагом '+'
      character->space_on = 1;
    } else if (**ptr_text_output == '+') {
      character->plus_on = 1;
    } else if (**ptr_text_output == '-') {
      character->minus_on = 1;
    } else if (**ptr_text_output == '#') {
      character->zero_last = 1;
    } else if (**ptr_text_output == '.' || **ptr_text_output == ',') {
      character->dot_presence = 1;
    } else if (**ptr_text_output == '*') {
      if (character->dot_presence == 0) {
        character->additional_width = 1;
      } else {
        character->additional_accuracy = 1;
      }
    } else if (**ptr_text_output > 47 && **ptr_text_output < 58) {
      add_accuracy_width(*ptr_text_output, character);
    } else if (check_flags(s, *ptr_text_output)) {
      break;
    } else if (**ptr_text_output == 'h') {
      character->size_h = 1;
    } else if (**ptr_text_output == 'l') {
      character->size_l = 1;
    } else if (**ptr_text_output == 'L') {
      character->size_double = 1;
    } else {
      flag_end = 0;
    }
  }
  return flag_end;
}
void check_conditions_wa(va_list ap, properties* character) {
  if (character->additional_width ==
      1) {  //если встречается * перед точкой - считываем ширину через va_arg
    character->width = va_arg(ap, int);
  }
  if (character->additional_accuracy ==
      1) {  //если встречается * после - считываем точность через va_arg
    character->accuracy = va_arg(ap, int);
  }
}
void accuracy_pos(properties* character, char* str_add, int* accuracy_null) {
  if (character->accuracy > 0) {
    int i = 0;
    int size_buf = 0;
    if (str_add[0] ==
        '-') {  //символ '-' в точность не входит, поэтому его не учитываем
      i++;
    }
    for (; str_add[i] != '\0'; i++) {  //количество символов в массиве
      size_buf += 1;
    }
    if ((character->accuracy - size_buf) <=
        0) {  //если сиволов в массиве больше, чем accuracy
      *accuracy_null = 0;
    } else {  // если символов в массиве меньше, чем в accuracy
      *accuracy_null = character->accuracy - size_buf;
    }
  }
}

void handling_int_idu(char* str, int* len, va_list ap, properties* character,
                      flags* s) {
  long int final = 0;
  if (s->u) {
    if (character->size_h) {
      final = (unsigned short int)va_arg(ap, unsigned int);
    } else if (character->size_l) {
      final = va_arg(ap, unsigned long int);
    } else {
      final = va_arg(ap, unsigned int);
    }
  } else if (character->size_h) {
    final = (short int)va_arg(ap, int);
  } else if (character->size_l) {
    final = va_arg(ap, long int);
  } else {
    final = va_arg(ap, int);
  }
  char* str_add =
      number_to_string(final, character->accuracy, character->accuracy_on);
  int accuracy_null = 0;
  if (character->accuracy_on == 1 && final == 0 &&
      character->accuracy ==
          0) {  //если мы ввели число 0 и после точки ввели точность '0' - то
                //строка будет принимать значение '\0'
    str[*len] = '\0';
  } else {
    accuracy_pos(character, str_add, &accuracy_null);
  }
  if (accuracy_null > 0) {  //проверяем условия, где точность ТОЧНО будет
    if (character->width >= 0 && !character->minus_on) {
      w_and_accuracy(str, len, str_add, character, accuracy_null);
    }
    add_accuracy(str, len, accuracy_null, str_add);
  } else {  //где точности нулей НЕ БУДЕТ
    if (character->width > 0 && character->zero_flag) {
      add_accuracy_zero(
          str, len, str_add,
          character);  //присутствует флаг 0(т.к с точностью он не работает)
    } else if (character->width > 0 && !character->zero_flag) {
      no_zero_prosto_width(
          str, len, str_add,
          character);  //просто ширина без точности.(с флагами '+' и '-' и ' ')
    } else {
      if (character->space_on && character->width == 0 &&
          *str_add != '-') {  //если ширина '0' и первый str_add символ не '-'
        str[*len] = ' ';
        *len += 1;
      } else if (character->width == 0 && final >= 0 && character->plus_on) {
        str[*len] = '+';
        *len += 1;
      } else if (character->width == 0 && *str_add == '-') {
        str[*len] = '-';
        *len += 1;
      }
    }
  }
  for (int i = 0; i < (int)s21_strlen(str_add); i++) {
    if (str_add[i] != '-') {
      str[*len] = str_add[i];
      *len += 1;
    }
  }
  if (character->minus_on) {
    minus_character_add(str, len, str_add, character, accuracy_null);
  }
  str[*len] = '\0';
  free(str_add);
}

void handling_exp_gG(char* str, int* len, va_list ap, properties* character,
                     flags* s) {
  long double num_double_gG =
      character->size_double ? va_arg(ap, long double) : va_arg(ap, double);
  if (character->accuracy == 0 && character->dot_presence) {
    character->accuracy = 1;
  }
  if (s->G) {
    s->E = 1;
  } else {
    s->e = 1;
  }
  char* str_double = str_num_double_gG(num_double_gG, character, s);
  if (character->width > 0 && character->zero_flag) {
    add_accuracy_zero(str, len, str_double, character);
  } else if (character->width > 0 && !character->zero_flag) {
    no_zero_prosto_width(str, len, str_double, character);
  } else if (character->space_on && character->width == 0 &&
             *str_double != '-') {
    str[*len] = ' ';
    *len += 1;
  } else if (character->width == 0 && num_double_gG >= 0 &&
             character->plus_on) {
    str[*len] = '+';
    *len += 1;
  } else if (character->width == 0 && *str_double == '-') {
    str[*len] = '-';
    *len += 1;
  }
  out_str(str_double, str, len, s);
  if (character->minus_on) {
    minus_character_add(str, len, str_double, character, 0);
  }
  free(str_double);
}

char* str_num_double_gG(long double num_double, properties* character,
                        flags* s) {
  char* str_add = (char*)malloc(sizeof(char) * 120);
  int num_add = 0;
  int len_e = 0;
  if (num_double != 0.) {
    add_main_num_exp(&len_e, num_double);
  }
  if (num_double > 1 || num_double < -1) {
    if (len_e != 0) {
      len_e -= 1;
    }
  }
  if (num_double < 0) {
    str_add[num_add] = '-';
    num_add += 1;
  }
  char* add_float = S21_NULL;
  if (num_double == 0.) {
    str_add[num_add] = '0';
    num_add += 1;
  } else if (-1. < num_double && num_double < 1) {
    if (len_e >= 5) {
      if (!character->dot_presence && !character->accuracy) {
        character->accuracy = 5;
      } else if (character->accuracy > 0) {
        character->accuracy = character->accuracy - 1;
      }
      add_float = str_num_double_eE(num_double, character, s);
      out_str(add_float, str_add, &num_add, s);
    } else if (len_e <= 4) {
      int urez = 1;
      if (!character->dot_presence && !character->accuracy) {
        character->accuracy = 6;
      }
      add_float = str_num_double(num_double, character);
      out_str(add_float, str_add, &num_add, s);
      if (urez == 1) {
        urezaem_null_tochka(str_add, &num_add);
      }
    }
  } else if (num_double >= 1. || num_double <= -1.) {
    if (len_e >= 6 && character->dot_presence == 0) {
      if (!character->dot_presence && !character->accuracy) {
        character->accuracy = 5;
      } else if (character->accuracy > 0) {
        character->accuracy = character->accuracy - 1;
      }
      add_float = str_num_double_eE(num_double, character, s);
      out_str(add_float, str_add, &num_add, s);
    } else {
      if (character->accuracy <= len_e && character->dot_presence) {
        character->accuracy -= 1;
        add_float = str_num_double_eE(num_double, character, s);
        out_str(add_float, str_add, &num_add, s);
      } else if (character->accuracy == 0 && !character->dot_presence) {
        character->accuracy = 6 - (len_e + 1);
        add_float = str_num_double(num_double, character);
        out_str(add_float, str_add, &num_add, s);
      } else if (character->dot_presence && len_e < character->accuracy) {
        character->accuracy -= len_e + 1;
        add_float = str_num_double(num_double, character);
        out_str(add_float, str_add, &num_add, s);
        urezaem_null_tochka(str_add, &num_add);
      }
    }
  }
  str_add[num_add] = '\0';
  free(add_float);
  return str_add;
}

void minus_character_add(char* str, int* len, char* str_add,
                         properties* character, int accuracy_null) {
  int size_add = character->width - s21_strlen(str_add) - accuracy_null;
  if (str_add[0] != '-' && character->space_on) {
    size_add -= 1;
  }
  if (str_add[0] != '-' && character->plus_on) {
    size_add -= 1;
  }
  for (int i = 0; i < size_add; i++) {
    str[*len] = ' ';
    *len += 1;
  }
}
void add_accuracy(char* str, int* len, int accuracy_null, char* str_add) {
  if (accuracy_null > 0) {
    if (str_add[0] == '-') {
      str[*len] = '-';
      *len += 1;
      for (int i = 0; i < accuracy_null; i++) {
        str[*len] = '0';
        *len += 1;
      }
    } else {
      for (int i = 0; i < accuracy_null; i++) {
        str[*len] = '0';
        *len += 1;
      }
    }
  }
  str[*len] = '\0';
}

void add_accuracy_zero(char* str, int* len, char* str_add,
                       properties* character) {
  int num_zero = 0;
  int space = 0;
  if (character->space_on == 1 && str_add[0] != '-') {
    str[*len] = ' ';
    *len += 1;
    space = 1;
  }
  if (character->plus_on == 0 && str_add[0] == '-') {
    num_zero = character->width - (int)s21_strlen(str_add);
  } else if (character->plus_on == 1 && str_add[0] == '-') {
    num_zero = character->width - (int)s21_strlen(str_add);
  } else if (character->plus_on == 1 && str_add[0] != '-') {
    num_zero = character->width - (int)s21_strlen(str_add) - 1;
  } else {
    num_zero = character->width - (int)s21_strlen(str_add) - space;
  }
  if (num_zero > 0) {
    if (character->plus_on && str_add[0] != '-') {
      str[*len] = '+';
      *len += 1;
      for (int i = 0; i < num_zero; i++) {
        str[*len] = '0';
        *len += 1;
      }
    } else {
      if (str_add[0] == '-') {
        str[*len] = '-';
        *len += 1;
      }
      for (int i = 0; i < num_zero; i++) {
        str[*len] = '0';
        *len += 1;
      }
    }
  } else {
    if (character->plus_on == 1 && str_add[0] != '-') {
      str[*len] = '+';
      *len += 1;
    } else if (str_add[0] == '-') {
      str[*len] = '-';
      *len += 1;
    }
  }
  str[*len] = '\0';
}

void processing_specifiers(char* str, int* len, const char* ptr_text_output,
                           va_list ap, flags* s, properties* character) {
  if (s->i || s->d || s->u) {
    if (s->u) {
      character->space_on = 0;
      character->plus_on = 0;
    }
    check_conditions_wa(ap, character);
    handling_int_idu(str, len, ap, character, s);
  } else if (s->f) {
    check_conditions_wa(ap, character);
    handling_float_f(str, len, ap, character, s);
  } else if (s->percent) {
    str[*len] = *ptr_text_output;
    *len += 1;
  } else if (s->e || s->E) {
    check_conditions_wa(ap, character);
    handling_exp_eE(str, len, ap, character, s);
  } else if (s->g || s->G) {
    check_conditions_wa(ap, character);
    handling_exp_gG(str, len, ap, character, s);
  } else if (s->n) {
    int* p = va_arg(ap, int*);
    *p = (int)*len;
  } else if (s->x || s->X) {
    s21_specifiers_xX(str, len, ap, character, s);
  } else if (s->o) {
    s21_specifiers_o(str, len, ap, character, s);
  } else if (s->c) {
    handling_char_c(str, len, ap, character);
  } else if (s->s) {
    handling_string_s(str, len, ap, character);
  } else if (s->p) {
    s21_specifier_p(str, len, ap, character, ptr_text_output);
  };
}

void s21_specifier_p(char* str, int* len, va_list ap, properties* character,
                     const char* ptr_text_output) {
  unsigned long value = va_arg(ap, unsigned long);
  unsigned long base = 16;
  unsigned long quotient = value;
  int number, before_num = *len;
  char* str_add =
      number_to_string(value, character->accuracy, character->accuracy_on);
  do {
    number = quotient % base;
    str[(*len)++] =
        (char)((number < 10) ? ('0' + number) : ('a' + number - 10));
    quotient /= base;
  } while (quotient > 0);
  str[(*len)++] = 'x';
  str[(*len)++] = '0';
  if (character->width > 0) {
    int num_space = character->width - s21_strlen(str_add) + 1;
    if (num_space > 0 && character->minus_on == 0) {
      for (int i = 0; i < num_space; i++) {
        str[(*len)++] = ' ';
      }
    }
    if (ptr_text_output == S21_NULL) {
      str[(*len)] = ' ';
    }
  }
  s21_back_str(str, before_num, len);
  if (character->width > 0) {
    int num_space = character->width - s21_strlen(str_add) + 1;
    if (num_space > 0 && character->minus_on == 1) {
      for (int i = 0; i < num_space; i++) {
        str[(*len)++] = ' ';
      }
    }
    if (ptr_text_output == S21_NULL) {
      str[(*len)] = ' ';
    }
  }
  free(str_add);
  str[*len] = '\0';
}

void handling_string_s(char* str, int* len, va_list ap, properties* character) {
  char* str_buffer = va_arg(ap, char*);
  if (character->accuracy < (int)s21_strlen(str_buffer) &&
      character->dot_presence == 1) {
    str_buffer[character->accuracy] = '\0';
  }

  char ch = ' ';
  if (((s21_size_t)character->width <
       s21_strlen(str_buffer))) { /* если ширина меньше текста, пробелы не
                                     заполняются */
    for (s21_size_t i = 0; i < s21_strlen(str_buffer); i++) {
      text_output(str, len, &str_buffer[i]);
    }
  } else if (((s21_size_t)character->width >= s21_strlen(str_buffer)) &&
             !(character->minus_on)) { /* если нет минуса и ширина больше
                                          текста, для заполнения пробелами */
    for (s21_size_t i = 0; i < (s21_size_t)character->width; i++) {
      if ((i + s21_strlen(str_buffer)) < ((s21_size_t)character->width)) {
        text_output(str, len, &ch);
      } else {
        text_output(str, len,
                    &str_buffer[(int)i + (int)s21_strlen(str_buffer) -
                                character->width]);
      }
    }
  } else if (((s21_size_t)character->width >= s21_strlen(str_buffer)) &&
             (character->minus_on)) { /* если есть минус и ширина больше или
                                         равна ширине текста */
    for (s21_size_t i = 0; i < s21_strlen(str_buffer); i++) {
      text_output(str, len, &str_buffer[i]);
    }
    for (s21_size_t i = s21_strlen(str_buffer);
         i < (s21_size_t)character->width; i++) {
      text_output(str, len, &ch);
    }
  }
}

void handling_char_c(char* str, int* len, va_list ap, properties* character) {
  char ch = ' ';
  if ((character->width > 0) && (!(character->minus_on))) {
    while (character->width != 1) {
      character->width -= 1;
      text_output(str, len, &ch);
    }
  }
  str[*len] = va_arg(ap, int);
  *len += 1;
  if ((character->minus_on) && (character->width > 0)) {
    while (character->width != 1) {
      character->width -= 1;
      text_output(str, len, &ch);
    }
  }
}

void s21_specifiers_o(char* str, int* len, va_list ap, properties* character,
                      flags* s) {
  unsigned long int li_number;
  unsigned short int si_number;
  unsigned int i_number;
  int before_num = *len;
  if (character->size_h) {
    si_number = (short unsigned int)va_arg(ap, unsigned int);
    s21_str_ol(str, len, before_num, si_number, character);
  } else if (character->size_l) {
    li_number = (long unsigned int)va_arg(ap, unsigned long int);
    s21_str_ol(str, len, before_num, li_number, character);
  } else {
    i_number = (unsigned int)va_arg(ap, unsigned int);
    s21_str_ol(str, len, before_num, i_number, character);
  }
  s21_accuracy(str, len, before_num, character, s);
  s21_sign_flag(str, len, before_num, character);
  s21_flag_width(str, character);
}

char* str_num_double_eE(long double num_double, properties* character,
                        flags* s) {
  char* str_double_eE = (char*)malloc(sizeof(char) * 120);
  long double copy_num_double = num_double;
  int num = 0;
  int len_e = 0;
  if (num_double < 0) {
    str_double_eE[num] = '-';
    num += 1;
  }
  char eorE = 'e';
  if (s->E) {
    eorE = 'E';
  }
  char plusorminus = '+';
  if (num_double > -1 && num_double < 1 && num_double != 0) {
    plusorminus = '-';
  }
  if (num_double == 0) {
    len_e = 0;
  } else {
    add_main_num_exp(&len_e, num_double);
  }
  if (copy_num_double > 1 || copy_num_double < -1) {
    if (len_e != 0) {
      len_e -= 1;
    }
  }
  if (num_double > 1. || num_double < -1.) {
    for (int i = 0; i < len_e; i++) {
      num_double /= 10;
    }
  } else if (num_double < 1 && num_double > -1 && num_double != 0) {
    for (int i = 0; i < len_e; i++) {
      num_double *= 10;
    }
  } else {
    num_double = 0.;
  }
  if ((long int)num_double == 0) {
    str_double_eE[num] = '0';
    num += 1;
  } else {
    long int num_d = (long int)num_double;
    if (num_d < 0) num_d = -num_d;
    while (num_d != 0) {
      long int add_n = num_d % 10;
      str_double_eE[num] = '0' + add_n;
      num += 1;
      num_d /= 10;
    }
    if (str_double_eE[0] == '-') {
      s21_back_str(str_double_eE, 1, &num);
    } else {
      s21_back_str(str_double_eE, 0, &num);
    }
  }
  octothorpe_and_no(character, str_double_eE, &num, num_double);
  if (s->g || s->G) {
    urezaem_null_tochka(str_double_eE, &num);
  }
  str_double_eE[num] = eorE;
  num += 1;
  str_double_eE[num] = plusorminus;
  num += 1;
  if (len_e < 10) {
    str_double_eE[num] = '0';
    num += 1;
    long int add_n = len_e % 10;
    str_double_eE[num] = '0' + add_n;
    num += 1;
  } else {
    if (len_e == 0 && copy_num_double == 0) {
      str_double_eE[num] = '0';
      num += 1;
      str_double_eE[num] = '0';
      num += 1;
    } else {
      while (len_e != 0) {
        long int add_n = len_e % 10;
        str_double_eE[num] = '0' + add_n;
        num += 1;
        len_e /= 10;
      }
      str_double_eE[num] = '\0';
      s21_back_str(str_double_eE, s21_strlen(str_double_eE) - 2, &num);
    }
  }
  str_double_eE[num] = '\0';
  return str_double_eE;
}

void urezaem_null_tochka(char* str, int* num) {
  int touch = 0;
  for (int i = *num; i >= 0 && !touch; i--) {
    if (str[i] == '.') {
      touch = 1;
    }
  }
  if (touch) {
    int i = *num - 1;
    for (; touch && str[i] == '0'; i -= 1) {
      if (str[i] == '.') {
        touch = 0;
      }
      str[i] = '\0';
      *num -= 1;
    }
    if (str[i] == '.') {
      touch = 0;
    }
    if (touch == 0) {
      *num -= 1;
      str[i] = '\0';
    }
  }
}

void handling_exp_eE(char* str, int* len, va_list ap, properties* character,
                     flags* s) {
  long double num_double =
      character->size_double ? va_arg(ap, long double) : va_arg(ap, double);
  accuracy_f(character);
  char* str_double = str_num_double_eE(num_double, character, s);
  if (character->width > 0 && character->zero_flag) {
    add_accuracy_zero(
        str, len, str_double,
        character);  //присутствует флаг 0(т.к с точностью он не работает)
  } else if (character->width > 0 && !character->zero_flag) {
    no_zero_prosto_width(
        str, len, str_double,
        character);  //просто ширина без точности.(с флагами '+' и '-' и ' ')
  } else if (character->space_on && character->width == 0 &&
             *str_double !=
                 '-') {  //если ширина '0' и первый str_add символ не '-'
    str[*len] = ' ';
    *len += 1;
  } else if (character->width == 0 && num_double >= 0 && character->plus_on) {
    str[*len] = '+';
    *len += 1;
  } else if (character->width == 0 && *str_double == '-') {
    str[*len] = '-';
    *len += 1;
  }
  out_str(str_double, str, len, s);
  if (character->minus_on) {
    minus_character_add(str, len, str_double, character, 0);
  }
  free(str_double);
}

void handling_float_f(char* str, int* len, va_list ap, properties* character,
                      flags* s) {
  long double num_double =
      character->size_double ? va_arg(ap, long double) : va_arg(ap, double);
  accuracy_f(character);
  char* str_f = str_num_double(num_double, character);
  if (character->width > 0 && character->zero_flag) {
    add_accuracy_zero(
        str, len, str_f,
        character);  //присутствует флаг 0(т.к с точностью он не работает)
  } else if (character->width > 0 && !character->zero_flag) {
    no_zero_prosto_width(
        str, len, str_f,
        character);  //просто ширина без точности.(с флагами '+' и '-' и ' ')
  } else if (character->space_on && character->width == 0 &&
             *str_f != '-') {  //если ширина '0' и первый str_add символ не '-'
    str[*len] = ' ';
    *len += 1;
  } else if (character->width == 0 && num_double >= 0 && character->plus_on) {
    str[*len] = '+';
    *len += 1;
  } else if (character->width == 0 && *str_f == '-') {
    str[*len] = '-';
    *len += 1;
  }
  out_str(str_f, str, len, s);
  if (character->minus_on) {
    minus_character_add(str, len, str_f, character, 0);
  }
  free(str_f);
}
void out_str(char* str_f, char* str, int* len, flags* s) {
  int i = 0;
  if ((s->e || s->E) && str_f[0] == '-') {
    i += 1;
  }
  for (; i < (int)s21_strlen(str_f); i++) {
    if (str_f[i] != '-' || (str_f[i] == '-' && (s->E || s->e))) {
      str[*len] = str_f[i];
      *len += 1;
    }
  }
}

void s21_accuracy(char* str, int* len, int before_num, properties* character,
                  flags* s) {
  char* num_str = (char*)calloc(1000 + character->width + 2, sizeof(char));
  if (num_str) {
    s21_size_t str_len = s21_strlen(str);
    int shift;
    char* p = (char*)S21_NULL;
    char* n = (char*)S21_NULL;
    p = num_str;
    n = str;
    int sign = *n == '-' ? -1 : 0;
    if (character->zero_flag == 1) {
      if (character->accuracy > character->width) {
        character->accuracy = character->accuracy;
      } else {
        character->accuracy = character->width;
      }
    } else {
      if (character->accuracy > (int)str_len + sign) {
        character->accuracy = character->accuracy;
      } else {
        character->accuracy = (int)str_len + sign;
      }
    }
    if (s->x && character->zero_last == 1) {
      shift = 32;
    } else {
      shift = 0;
    }
    s21_back_str(str, before_num, len);
    for (int i = 0; i < character->accuracy; i++) {
      if (i < (int)str_len + sign)
        *(p++) = *(n++);
      else
        *(p++) = '0';
    }
    if (character->zero_last == 1 && s->X + shift) {
      *(p++) = (char)('X' + shift);
      *(p++) = '0';
    }
    if (sign < 0) *(p++) = '-';
    *p = '\0';
    s21_back_str(num_str, before_num, len);
    s21_strcpy(str, num_str);
    free(num_str);
  }
}
void s21_str_ol(char* str, int* len, int before_num, unsigned long long number,
                properties* character) {
  int flag = 1;
  while (flag) {
    unsigned int ostatok;
    if (number > 7) {
      ostatok = number % 8;
      number = (number - ostatok) / 8;
    } else {
      ostatok = number;
      flag = 0;
    }
    str[*len] = (char)(ostatok + '0');
    *len += 1;
  }
  if (character->zero_last == 1) {
    str[*len] = '0';
    *len += 1;
  }
  str[*len] = '\0';
  s21_back_str(str, before_num, len);
}

char* str_num_double(long double num_double, properties* character) {
  char* nash_num_double = (char*)malloc(sizeof(char) * 120);
  int numm = 0;
  int* num_arr = &numm;
  if (num_double < 0) {
    nash_num_double[*num_arr] = '-';
    *num_arr += 1;
  }
  if ((long int)num_double == 0) {
    nash_num_double[*num_arr] = '0';
    *num_arr += 1;
  } else {
    long int num = (long int)num_double;
    if (num < 0) num = -num;
    while (num != 0) {
      long int add_n = num % 10;
      nash_num_double[*num_arr] = '0' + add_n;
      *num_arr += 1;
      num /= 10;
    }
    if (nash_num_double[0] == '-') {
      s21_back_str(nash_num_double, 1, num_arr);
    } else {
      s21_back_str(nash_num_double, 0, num_arr);
    }
  }
  octothorpe_and_no(character, nash_num_double, num_arr, num_double);
  nash_num_double[*num_arr] = '\0';
  return nash_num_double;
}

void recovery_processing(properties* character, int treatment,
                         char* nash_num_double, int* num_arr,
                         long double num_double) {
  int sign_minus = 0;
  if (num_double < 0) {
    sign_minus = 1;
    num_double = -num_double;
  }
  long double whole = 0;                              //целая
  long double remainder = modfl(num_double, &whole);  //нецелая 0.123 2
  long long int round_number = roundl(num_double) - whole;
  int one_chara = 0;
  one_chara =
      nash_num_double[0] == '-' ? nash_num_double[0 + 1] : nash_num_double[0];
  if (treatment) {
    int i = character->accuracy;
    while (i--) {
      remainder *= 10;                       // 2
      remainder = modfl(remainder, &whole);  // 1.23 - 1
      nash_num_double[*num_arr] = '0' + (int)whole;
      *num_arr += 1;
    }
    nash_num_double[*num_arr] = '\0';
    remainder *= 10;
    remainder = modfl(remainder, &whole);  // 0.12

    if ((int)whole >= 5) {
      *num_arr -= 1;
      int ch = (nash_num_double[*num_arr] + 1 - '0') % 10;
      nash_num_double[*num_arr] = ch + '0';
      if (ch == 0) {
        int size_arr = *num_arr - 1;
        int a = 1;
        while (size_arr >= 0) {  // 00.09
          if (nash_num_double[size_arr] == '-') {
            break;
          }
          if (nash_num_double[size_arr] != '.' &&
              nash_num_double[size_arr] != ',') {
            int ch = (nash_num_double[size_arr] + a - '0') % 10;
            nash_num_double[size_arr] = ch + '0';
            if (ch != 0) {
              a = 0;
            }
          }
          size_arr -= 1;
        }
      }
      *num_arr += 1;
    }
  } else {
    if (round_number > 0) {
      int size_arr = *num_arr;
      size_arr -= 1;
      int a = 1;
      while (size_arr >= 0) {
        if (nash_num_double[size_arr] == '-') {
          break;
        }
        int ch = (nash_num_double[size_arr] + a - '0') % 10;
        nash_num_double[size_arr] = ch + '0';
        if (ch != 0) {
          a = 0;
        }
        size_arr -= 1;
      }
    }
    if (character->zero_last == 1) {
      *num_arr += 1;
    }
  }
  if (one_chara != nash_num_double[sign_minus] && one_chara == '9') {
    for (int i = (int)s21_strlen(nash_num_double); i > 0; i--) {
      if (nash_num_double[i] != '-')
        nash_num_double[i] = nash_num_double[i - 1];
    }
    nash_num_double[sign_minus] = '1';
    *num_arr += 1;
  }
  nash_num_double[*num_arr] = '\0';
}

void octothorpe_and_no(properties* character, char* nash_num_double,
                       int* num_arr, long double num_double) {
  long double remainder = num_double - (long int)num_double;
  if (remainder != 0 && character->dot_presence && character->accuracy == 0) {
    if (character->zero_last) {  //- есть #
      nash_num_double[*num_arr] = '.';
      recovery_processing(character, 0, nash_num_double, num_arr, num_double);
      // 0
    } else {
      recovery_processing(character, 0, nash_num_double, num_arr, num_double);
      // 0
    }
  } else if (remainder == 0) {
    if (character->dot_presence && character->accuracy == 0) {
      if (character->zero_last) {
        nash_num_double[*num_arr] = '.';
        recovery_processing(character, 0, nash_num_double, num_arr, num_double);
        // 0
      } else {
        recovery_processing(character, 0, nash_num_double, num_arr, num_double);
        // 0
      }
    } else {
      nash_num_double[*num_arr] = '.';
      *num_arr += 1;
      recovery_processing(character, 1, nash_num_double, num_arr, num_double);
      // 1
    }
  } else {
    nash_num_double[*num_arr] = '.';
    *num_arr += 1;
    recovery_processing(character, 1, nash_num_double, num_arr, num_double);
    // 1
  }
}

void accuracy_f(properties* character) {
  if (character->dot_presence && !character->accuracy) {
    character->accuracy = 0;
  } else if (!character->dot_presence) {
    character->accuracy = 6;
  }
}

void w_and_accuracy(char* str, int* len, char* str_add, properties* character,
                    int accuracy_null) {
  int num_probel = 0;
  if (character->plus_on == 0 && str_add[0] == '-') {
    num_probel = character->width - accuracy_null - s21_strlen(str_add);
  } else if (character->plus_on == 1 && str_add[0] == '-') {
    num_probel = character->width - accuracy_null - s21_strlen(str_add);
  } else if (character->plus_on == 1 && str_add[0] != '-') {
    num_probel = character->width - accuracy_null - s21_strlen(str_add) - 1;
  } else {
    num_probel = character->width - accuracy_null - s21_strlen(str_add);
  }
  if (num_probel > 0) {
    for (int i = 0; i < num_probel; i++) {
      str[*len] = ' ';
      *len += 1;
    }
    if (*str_add != '-' && character->plus_on) {
      str[*len] = '+';
      *len += 1;
    }
  }
  if (num_probel <= 0) {
    if (*str_add != '-' && character->space_on) {
      str[*len] = ' ';
      *len += 1;
    } else if (*str_add != '-' && character->plus_on) {
      str[*len] = '+';
      *len += 1;
    }
  }
  str[*len] = '\0';
}
void s21_sign_flag(char* str, int* len, int before_num, properties* character) {
  if (((*str) >= '0' && (*str) <= '9') || *str == 'i') {
    char num_str[2] = "";
    char* p = (char*)S21_NULL;
    p = num_str;
    if (character->plus_on)
      *(p++) = '+';
    else if (character->space_on)
      *(p++) = ' ';
    *p = '\0';
    s21_back_str(str, before_num, len);
    s21_strcat(str, num_str);
    s21_back_str(str, before_num, len);
  }
}
char* number_to_string(long int final, int accuracy, int accuracy_on) {
  char* arr_num = (char*)malloc(sizeof(char) * 120);
  int num = 0;
  if (final == 0 && accuracy == 0 && accuracy_on == 1) {
    arr_num[num] = '\0';
  } else if (final == 0) {
    arr_num[num] = '0';
    num += 1;
    arr_num[num] = '\0';
  } else {
    if (final < 0) {
      final *= -1;
      arr_num[num] = '-';
      num += 1;
    }
    for (int ch; final != 0; final /= 10) {
      ch = final % 10;
      arr_num[num] = '0' + ch;
      num += 1;
    }
    arr_num[num] = '\0';
    if (arr_num[0] == '-') {
      s21_back_str(arr_num, 1, &num);
    } else {
      s21_back_str(arr_num, 0, &num);
    }
  }
  return arr_num;
}

void no_zero_prosto_width(char* str, int* len, char* str_add,
                          properties* character) {
  int num_space = 0;
  int space = 0;
  if (character->space_on == 1 && str_add[0] != '-') {
    str[*len] = ' ';
    *len += 1;
    space += 1;
  }
  if (character->plus_on == 0 && str_add[0] == '-') {
    num_space = character->width - s21_strlen(str_add);
  } else if (character->plus_on == 1 && str_add[0] == '-') {
    num_space = character->width - s21_strlen(str_add);
  } else if (character->plus_on == 1 && str_add[0] != '-') {
    num_space = character->width - s21_strlen(str_add) - 1;
  } else {
    num_space = character->width - s21_strlen(str_add) - space;
  }
  if (num_space > 0) {
    if (character->plus_on && str_add[0] != '-') {
      if (!character->minus_on) {
        for (int i = 0; i < num_space; i++) {
          str[*len] = ' ';
          *len += 1;
        }
      }
      str[*len] = '+';
      *len += 1;
    } else {
      if (!character->minus_on) {
        for (int i = 0; i < num_space; i++) {
          str[*len] = ' ';
          *len += 1;
        }
      }
      if (str_add[0] == '-') {
        str[*len] = '-';
        *len += 1;
      }
    }
  } else {
    if (character->plus_on == 1 && str_add[0] != '-') {
      str[*len] = '+';
      *len += 1;
    } else if (str_add[0] == '-') {
      str[*len] = '-';
      *len += 1;
    }
  }
  str[*len] = '\0';
}

void s21_back_str(char* str, int before_num, int* len) {
  char ch;  //символ ch
  int last = 1;
  for (int i = before_num; i < before_num + ((*len - before_num) / 2); i++) {
    ch = str[i];
    str[i] = str[*len - last];
    str[*len - last] = ch;
    last += 1;
  }
}

void add_main_num_exp(int* len_e, long double num_double) {
  long int ceiloe = (long int)num_double;
  if (ceiloe < -1 || ceiloe > 1) {
    for (; ceiloe != 0; *len_e += 1) {
      ceiloe /= 10;
    }
  } else {
    for (; (long int)num_double == 0; *len_e += 1) {
      num_double *= 10;
    }
  }
}

void s21_flag_width(char* str, properties* character) {
  int str_len = (int)s21_strlen(str);
  if (character->width > (int)str_len) {
    char* num_str = (char*)calloc(1000 + character->width + 2, sizeof(char));
    if (num_str) {
      for (int i = 0; i < character->width; i++) {
        if (character->minus_on == 1) {
          if (i < str_len) {
            num_str[i] = str[i];
          } else {
            num_str[i] = ' ';
          }
        } else {
          if (i < character->width - str_len) {
            num_str[i] = ' ';
          } else {
            num_str[i] = str[i - (character->width - str_len)];
          }
        }
      }
      num_str[character->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
}

void s21_str_hl(char* str, int* len, int before_num, unsigned long long number,
                flags* s) {
  int flag = 1, sdvig;
  if (s->x) {
    sdvig = 32;
  } else {
    sdvig = 0;
  }
  while (flag) {
    unsigned int ostatok;
    if (number > 15) {
      ostatok = number % 16;
      number = (number - ostatok) / 16;
    } else {
      ostatok = number;
      flag = 0;
    }
    if (ostatok < 10) {
      str[*len] = (char)(ostatok + '0');
      *len += 1;
    } else {
      str[*len] = (char)(ostatok + 'A' + sdvig - 10);
      *len += 1;
    }
  }
  str[*len] = '\0';
  s21_back_str(str, before_num, len);
}