#include <stdlib.h>

void* arrayInator(void* pointer, size_t memsize, size_t newsize) {
  void* temp = NULL;
  temp = realloc(pointer, memsize);
  if (temp != NULL) {
    pointer = temp;
    return pointer;
  }
  return NULL;
}
