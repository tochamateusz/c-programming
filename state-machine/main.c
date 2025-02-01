typedef enum state_name_t {
  Idle,
  Walking,
  Running,
} state_name_t;

typedef struct Idle {
  state_name_t type;
} Idle_t;

typedef struct Walking {
  state_name_t type;
} Walking_t;

typedef struct Running {
  state_name_t type;
} Running_t;

typedef union states {
  Idle_t idle;
  Walking_t walking;
  Running_t runing;
} states_t;

int main(void) {
  states_t States;

  Idle_t idle = {.type = Idle};
  States.idle = idle;

  Running_t runing = {.type = Running};
  States.runing = runing;

  return 0;
}
