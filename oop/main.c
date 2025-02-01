#include <stdio.h>
#include <stdlib.h>

typedef struct Entity {
  int field;
  void (*add)(struct Entity *e, int value);
} Entity_t;

static void add(Entity_t *e, int value) { e->field += value; };

static Entity_t *new_entity() {
  Entity_t *e = malloc(sizeof(Entity_t));
  e->field = 0;
  e->add = add;
  return e;
}

int main(void) {
  Entity_t *e = new_entity();
  e->add(e, 5);
  e->add(e, 5);
  printf("%d", e->field);
  return 0;
}
