#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <regex.h>
typedef struct tm Date;

typedef struct {
  Date* array;
  
  size_t len;
} DateArray;

time_t* current = NULL;
Date* current_local = NULL;

regex_t regex;
const char *format = "^([0-9]{2}|%)/[0-9]{2}/[0-9]{4}-([0-9]{2}|%)[:][0-9]{2}$";

int compileRegex() {
  int result = regcomp(&regex, format, REG_EXTENDED);
  return result;
}

int verifyRepeatString(const char* src) {
  return regexec(&regex, src, 0, NULL, 0);
}

void initTime(void) {
  *current = time(NULL);
  current_local = localtime(current);
  compileRegex();
}

bool isLeap(int year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool valiDate(Date in) {
  if (in.tm_year > current_local->tm_year + 500 ||
      in.tm_year < current_local->tm_year - 500) {
    return false;
  }
  if (in.tm_mon < 0 || in.tm_mon > 12)
    return false;
  if (in.tm_mday < 0 || in.tm_mday > 31)
    return false;
  if (in.tm_mon == 2) {
    if (isLeap(in.tm_year + 1900))
      return (in.tm_mday <= 29);
    else
      return (in.tm_mday <= 28);
  }
  if ( in.tm_mon == 4 || in.tm_mon == 6 || 
        in.tm_mon == 9 || in.tm_mon == 11) 
        return (in.tm_mday <= 30);
  return true;
}

Date convertStuff(char* src, char* format) {
  Date temp = {};
  char* splitters = "/^:";
  char* end_res = NULL;
  if (verifyRepeatString(src) != 0){
    printf("error conv.c line 63");
    exit(EXIT_FAILURE);
  } 
  temp.tm_year -= 1900;
  if (valiDate(temp) == false) {
    return (Date){};
  }
  return temp;
}

int main(void) {
  char* format_str = "dmy";
  char* string = "4/7/5^8:00";
}
