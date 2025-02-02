#include "main.h"

typedef struct coroutine_t {
  float elapsed;
  int index;
} coroutine_t;

#define COROUTINE_START(co)                                                    \
  do {                                                                         \
    switch (co->index) {                                                       \
    default:

#define COROUTINE_CASE(co, name)                                               \
  case __LINE__:                                                               \
  name:                                                                        \
    co->index = __LINE__;

#define COROUTINE_EXIT(co)                                                     \
  do {                                                                         \
    goto __co_end;                                                             \
  } while (0)

#define COROUTINE_YIELD(co)                                                    \
  do {                                                                         \
    co->index = __LINE__;                                                      \
    COROUTINE_EXIT(co);                                                        \
  case __LINE__:;                                                              \
  } while (0)

#define COROUTINE_WAIT(co, time, dt)                                           \
  do {                                                                         \
  case __LINE__:                                                               \
    co->index = __LINE__;                                                      \
    co->elapsed += dt;                                                         \
    do {                                                                       \
      if (co->elapsed < time) {                                                \
        goto __co_end;                                                         \
      } else {                                                                 \
        co->elapsed = 0;                                                       \
      }                                                                        \
    } while (0);                                                               \
  } while (0)

#define COROUTINE_END(co)                                                      \
  }                                                                            \
  co->index = 0;                                                               \
  __co_end:;                                                                   \
  }                                                                            \
  while (0)

int run() {
  static coroutine_t s_co;
  coroutine_t *co = &s_co;
  static int loop_count = 0;
  int keep_going = 1;

  COROUTINE_START(co);

  COROUTINE_CASE(co, loop_start);
  printf("State 0\n");
  COROUTINE_YIELD(co);
  printf("State 1\n");
  COROUTINE_YIELD(co);
  printf("State 2\n");
  COROUTINE_YIELD(co);
  ++loop_count;
  if (loop_count == 3) {
    keep_going = 0;
  }
  goto loop_start;

  COROUTINE_END(co);

  return keep_going;
}

int run2() {
  static coroutine_t s_co;
  coroutine_t *co = &s_co;
  static int loop_count = 0;
  int keep_going = 1;

  do {
    switch (co->index) {
    default:;

    case 87:
    loop_start:
      co->index = 87;
      ;
      printf("State 0\n");
      do {
        co->index = 92;
        do {
          goto __co_end;
        } while (0);
      case 92:;
      } while (0);
      printf("State 1\n");
      do {
        co->index = 100;
        do {
          goto __co_end;
        } while (0);
      case 100:;
      } while (0);
      printf("State 2\n");
      do {
        co->index = 108;
        do {
          goto __co_end;
        } while (0);
      case 108:;
      } while (0);
      ++loop_count;
      if (loop_count == 3) {
        keep_going = 0;
      }
      goto loop_start;
    }
    co->index = 0;
  __co_end:;
  } while (0);

  return keep_going;
}
