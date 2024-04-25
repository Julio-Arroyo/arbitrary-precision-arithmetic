#include "bigint.h"

void test_big_add() {
  bigint x1, x2, ans, soln;

  big_init(&x1);  // TODO: init inside methods
  uint8_t x1_bin[2] = {0xB0, 0x00};
  big_read_binary(&x1, x1_bin, 2);

  big_init(&x2);
  const char *x2_str = "0002";
  big_read_string(&x2, x2_str);

  big_init(&ans);
  big_add(&ans, &x1, &x2);

  big_init(&soln);
  uint8_t ans[2] = {0xB0, 0x02};
  big_read_binary(&soln, ans, 2);

  assert(0 == big_cmp(soln, ans));
  assert(-1 == big_cmp(BIG_ZERO, ans));
  assert(1 == big_cmp(ans, BIG_ZERO));
}

int main() {
  test_big_add();
}

