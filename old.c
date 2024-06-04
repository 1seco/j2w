#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char delim;
  char escape;
  bool end;
} Delim;

Delim* charInDelimArr(char a, Delim* delim, size_t num_delim) {
  for (unsigned int delim_ind = 0; delim_ind < num_delim; delim_ind++) {
    if (a == delim[delim_ind].delim) {
      return &delim[delim_ind];
    }
  }
  return NULL;
}

int countDelim(Delim* delim) {
  int count = 0;
  while (delim[count].end != true) {
    count++;
  }
  if (delim[count].end == true)
    count = 1;
  return count;
}

int readTill(char* src_str, char escape) {
  int bufsize = 4, index = 0;
  char* buffer;
  int c;
  while ((c = src_str[index]) != '\0') {
    if (c == escape) {
      break;
    }
    // realloc
    if (index == bufsize - 1 || !buffer) {
      bufsize *= 2;
      char* newbuf = realloc(buffer, bufsize);

      if (newbuf == NULL && buffer != NULL) {
        free(buffer);
        return 3;
      }

      buffer = newbuf; /* dont forget */
    }
    buffer[index++] = c;
  }

  if (index == 0) {
    return 2;
  }

  if (index < bufsize - 1) {
    char* newbuf = realloc(buffer, index + 1);
    if (newbuf == NULL) {
      free(buffer);
      return 1;
    }
    buffer = newbuf;
  }
  buffer[index] = '\0';
  return 0;
}

int tokenizer(char* src, Delim* delim, size_t num_delim, char** token,
              char** err) {
  unsigned int index = 0;
  if (*err != NULL){
    src = *err;
  } 
  Delim* found_delim = NULL;
  while (src[index] == ' ' || src[index] == '\t') {
    src++;
  }
  if ((found_delim = charInDelimArr(src[index], delim, num_delim)) !=
      NULL) {
    readTill(src, found_delim->escape);
  } else {
    readTill(src, ' ');
  }
  *err = *token;

  if (token == NULL) {
    return 1;
  }
  return 0;
}

int main(void) {
  char* src = "hello there \"this text is inside a quote\" and this is not!";
  Delim delim[] = {{'\"', '\"', true}};
  char* token;
  int err = 0;
  char* err_char = NULL;
  while ((err = tokenizer(src, delim, countDelim(delim), &token, &err_char)) != 1 &&
         token != NULL) {
    printf("%s", token);
    free(token);
  }
  return err;
}
