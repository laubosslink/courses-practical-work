#ifndef INCLUDED_H_LIFO
#define INCLUDED_H_LIFO

typedef struct Lifo* Lifo;

typedef struct Node* Node;

Lifo lifo_init();

void lifo_add_elmt(Lifo l, void* elmt);

void* lifo_pop_elmt(Lifo l);

void* lifo_head_elmt(Lifo l);

int lifo_is_empty(Lifo l);

int lifo_length(Lifo l);

Lifo lifo_reverse(Lifo l);

#endif
