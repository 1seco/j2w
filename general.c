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
  unsigned short offset = 0;
  char* buf = malloc(5);
  if (!buf)
    return NULL;
  while (offset < 4) {
    if (**src == '\0' || isIn(**src, split) == true)
      break;
    buf[offset++] = *((*src)++);
  }
  if (offset < 4) {
    char* new_buf = realloc(buf, offset + 1);
    if (!new_buf)
      buf = new_buf;
  }
  buf[offset] = '\0';
  return buf;
}

char** splitStr(char* src, char* split) {
  char** final = calloc(5, sizeof(void*));
  for (unsigned index = 0; index < 5; index++) {
    char* temp = readTill(&src, split);
    if (temp == NULL)
      break;
    final[index] = temp;
    if (*src != '\0')
      src++;
  }
  if (final[0] == NULL)
    return NULL;
  return final;
}

int deInit(char** src) {
  size_t index = 0;
  if (!src) return 1;
  while(src[index] != NULL) {
    free(src[index++]);
  }
  return 0;
}
