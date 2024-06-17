#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

typedef enum { LIT, IDT } TType;

typedef struct {
  char pair[2];
  TType tok_type;
  bool end;
} DPair;

typedef struct {
  TType type;
  char* token;
  bool end;
} Tok;

#endif
