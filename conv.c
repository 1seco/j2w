#include "common.h"
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t current =  0;
struct tm* current_local = {0};

regex_t regex;
const char* format = "^([0-9]{2}|%)/[0-9]{2}/[0-9]{4}-([0-9]{2}|%)[:][0-9]{2}$";

int compileRegex() {
  int result = regcomp(&regex, format, REG_EXTENDED);
  return result;
}

int verifyRepeatString(const char* src) {
  return regexec(&regex, src, 0, NULL, 0);
}

void initTime(void) {
  current = time(NULL);
  current_local = localtime(&current);
  compileRegex();
}

void deInitAll() {
  free(current_local);
  current_local = NULL;
  regfree(&regex);
}

bool isLeap(int year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

void attemptSetDate(Date* date, char** split_str) {
  date->time.tm_mday = atoi(split_str[0]);
  date->time.tm_mon = atoi(split_str[1]);
  date->time.tm_year = atoi(split_str[2]);
  date->time.tm_hour = atoi(split_str[3]);
  date->time.tm_min = atoi(split_str[4]);
  for (short i = 0; i < 5; i++) {
    date->is_repeat[i] = *split_str[i] == '%' ? true : false;
  }
}

bool verifyDate(Date in) {
  if (in.time.tm_hour > 23 || in.time.tm_hour < 0)
    return false;
  if (in.time.tm_min > 59 || in.time.tm_min < 0)
    return false;
  if (in.time.tm_year > current_local->tm_year + 500 ||
      in.time.tm_year < current_local->tm_year - 500) {
    return false;
  }
  if (in.time.tm_mon < 0 || in.time.tm_mon > 12)
    return false;
  if (in.time.tm_mday < 0 || in.time.tm_mday > 31)
    return false;
  if (in.time.tm_mon == 2) {
    if (isLeap(in.time.tm_year + 1900))
      return (in.time.tm_mday <= 29);
    else
      return (in.time.tm_mday <= 28);
  }
  if (in.time.tm_mon == 4 || in.time.tm_mon == 6 || in.time.tm_mon == 9 ||
      in.time.tm_mon == 11)
    return (in.time.tm_mday <= 30);
  return true;
}

Date convMain(char* src, char* format) {
  Date temp = {0};
  unsigned short len = 0;
  char* splitters = "/^:";
  char** split_strings = splitStr(src, splitters);
  for (; len <= 5; len++) {
    if (split_strings[len] != NULL)
      len++;
    else break;
  }
  if (len < 5)
    return temp;

  if (verifyRepeatString(src) != 0) {
    printf("error conv.c line 63");
    return temp;
  }
  attemptSetDate(&temp, split_strings);
  if (verifyDate(temp) == false) {
    return (Date){0};
  }

  return temp;
}
