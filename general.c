#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isIn(char src, char* split) {
  while (*split != '\0') {
    if (src == *split)
      return true;
    split++;
  }
  return false;
}

char* readTill(char** src, char* split) {
  size_t offset = 0, bufsize = 1;
  char* buf = NULL;
  if (!src)
    return NULL;
  while (**src != '\0' && isIn(**src, split) == false) {
    if (offset == bufsize - 1) {
      bufsize *= 2;
      char* new_buf = realloc(buf, bufsize);
      if (!new_buf) {
        free(buf);
        return NULL;
      }
      buf = new_buf;
    }
    buf[offset++] = *((*src)++);
  }
  if (offset < bufsize - 1) {
    char* new_buf = realloc(buf, offset + 1);
    if (!new_buf)
      buf = new_buf;
  }
  buf[offset] = '\0';
  return buf;
}

char** splitStr(char* src, char* split) {
  size_t offset = 0, bufsize = 1;
  char** final = NULL;
  if (!src)
    return NULL;
  while (*src == ' ')
    src++;
  while (*src != '\0') {
    if (offset == bufsize - 1) {
      bufsize *= 2;
      char** new_buf = realloc(final, bufsize);
      if (!new_buf) {
        free(final);
        return NULL;
      }
      final = new_buf;
    }
    final[offset++] = readTill(&src, split);
  }
  if (offset == bufsize - 1) {
    char** new_buf = realloc(final, offset + 1);
    if (new_buf)
      final = new_buf;
  }
  final[offset] = NULL;
  return final;
}

void deInit(char** src) {
  size_t index = 0;
  if (src) {
    while (src[index] != NULL) {
      free(src[index++]);
    }
  }
}
