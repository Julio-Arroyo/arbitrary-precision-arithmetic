#include "test_bigint.h"
#include "bigint.h"

void test_mul0() {
  bigint x1;
  uint8_t x1_bin[] = {0x08};
  big_init(&x1);
  big_read_binary(&x1, x1_bin, 1);

  bigint x2;
  uint8_t x2_bin[] = {0x0A};
  big_init(&x2);
  big_read_binary(&x2, x2_bin, 1);

  bigint ans;
  big_init(&ans);
  big_mul(&ans, &x1, &x2);

  bigint soln;
  uint8_t soln_bin[] = {0x50};
  big_init(&soln);
  big_read_binary(&soln, soln_bin, 1);

  print_test_result("Test mul0", 0 == big_cmp(&ans, &soln), "");

  big_free(&x1);
  big_free(&x2);
  big_free(&ans);
  big_free(&soln);
}

void test_negative_mul() {
  bigint x1;
  uint8_t x1_bin[] = {0x08, 0x34, 0xC6, 0xDA};
  big_init(&x1);
  big_read_binary(&x1, x1_bin, 4);

  bigint x2;
  big_init(&x2);
  const char *x2_str = "-8A25835A4805D3E48843E19";
  big_read_string(&x2, x2_str);

  bigint prod;
  big_init(&prod);
  big_mul(&prod, &x1, &x2);

  const char *expected = "-46DA70828207E640586FED6DB8374A";
  // char ans[50];
  // size_t ans_len;
  // big_write_string(&prod, ans, 50, &ans_len);
  bigint expected_prod;
  big_init(&expected_prod);
  big_read_string(&expected_prod, expected);

  print_test_result("Test negative_mul",
                    ((0 == big_cmp(&expected_prod, &prod)))//  &&
                    //  (ans_len == strlen(expected) + 1) &&
                    //  (strcmp(ans, expected) == 0))
                    , "");
  big_free(&x1);
  big_free(&x2);
  big_free(&prod);
  big_free(&expected_prod);
}

void test_negative_scalar_mul() {
  printf("TODO test negative scalar mul\n");
  // TODO
}

// TODO test same addr

int main() {
  printf("*** TEST mul ***\n");
  test_mul0();
  test_negative_mul();
  test_negative_scalar_mul();
  printf("\n");
}
