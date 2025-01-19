#include <stdio.h>

int run();
int run2();

int main(void) {
  while (1) {
    int keep_going = run2();
    if (!keep_going)
      break;
  }

  return 0;
}
