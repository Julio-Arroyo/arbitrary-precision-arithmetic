#include "bigint.h"
#include "test_bigint.h"
#include "bigint_aux.h"

void test_no_inv_mod() {
  bigint x1, x2, mod_inv, mod_inv1;
  big_init(&x1);  big_init(&x2);  big_init(&mod_inv);  big_init(&mod_inv1);

  const char *x1_str = "AE27B9DE8";
  big_read_string(&x1, x1_str);

  const char *x2_str = "AAA5741E4070CC960";
  big_read_string(&x2, x2_str);

  print_test_result("Test no modular multiplicative inverse",
                    big_inv_mod(&mod_inv, &x1, &x2) == ERR_BIGINT_NOT_ACCEPTABLE &&
                    big_inv_mod(&mod_inv, &x2, &x1) == ERR_BIGINT_NOT_ACCEPTABLE,
                    "");

  big_free(&x1);  big_free(&x2);  big_free(&mod_inv);  big_free(&mod_inv1);
}

void test_bad_mod1() {
  bigint x1, x2, mod_inv;
  big_init(&x1);  big_init(&x2);  big_init(&mod_inv);

  const char *x1_str = "1";
  big_read_string(&x1, x1_str);

  const char *x2_str = "AAA5741E4070CC960";
  big_read_string(&x2, x2_str);

  print_test_result("Test bad (mod 1)",
                    big_inv_mod(&mod_inv, &x2, &x1) == ERR_BIGINT_BAD_INPUT_DATA, "");

  big_free(&x1);  big_free(&x2);  big_free(&mod_inv);
}

void test_mod_inv() {
  bigint ans1, ans2, X, Y;
  big_init(&ans1);  big_init(&ans2);  big_init(&X);  big_init(&Y);

  const char *xstr = "0x07A607BBE974EDD9B";
  big_read_string(&X, xstr);
  const char *ystr = "0xBEB3D713D";
  big_read_string(&Y, ystr);

  assert(0 == big_inv_mod(&ans1, &X, &Y));
  assert(0 == big_inv_mod(&ans2, &Y, &X));

  const char *solution1 = "B28DF56D";
  const char *solution2 = "73372E97ACD41FC5";

  char buf1[128];
  char buf2[128];
  size_t olen;
  big_write_string(&ans1, buf1, 128, &olen);
  big_write_string(&ans2, buf2, 128, &olen);

  print_test_result("Test mod_inv",
                    strcasecmp(buf1, solution1) == 0 && strcasecmp(buf2, solution2) == 0, "");
  big_free(&ans1);  big_free(&ans2);  big_free(&X);  big_free(&Y);
}

void test_textbook_example() {
  bigint ans1, ans2, X, Y;
  big_init(&ans1);  big_init(&ans2);  big_init(&X);  big_init(&Y);

  const char *xstr = "0x2B5";
  big_read_string(&X, xstr);
  const char *ystr = "0x261";
  big_read_string(&Y, ystr);

  big_inv_mod(&ans1, &X, &Y);

  const char *solution1 = "-B5";

  char buf1[128];
  size_t olen;
  big_write_string(&ans1, buf1, 128, &olen);

  print_test_result("Test modular multiplicative inverse",
                    strcasecmp(buf1, solution1) == 0, "");
  big_free(&ans1);  big_free(&ans2);  big_free(&X);  big_free(&Y);
}

void test_tiny_example() {
  bigint ans1, ans2, X, Y;
  big_init(&ans1);  big_init(&ans2);  big_init(&X);  big_init(&Y);

  const char *xstr = "40B";
  big_read_string(&X, xstr);
  const char *ystr = "0x1FC";
  big_read_string(&Y, ystr);

  big_inv_mod(&ans1, &X, &Y);

  const char *solution1 = "6B";

  char buf1[128];
  size_t olen;
  big_write_string(&ans1, buf1, 128, &olen);

  print_test_result("Test tiny example",
                    strcasecmp(buf1, solution1) == 0, "");
  big_free(&ans1);  big_free(&ans2);  big_free(&X);  big_free(&Y);
}

void test_m_mod_base() {
  bigint ans1, X, Y;
  big_init(&ans1);  big_init(&X);  big_init(&Y);

  const char *xstr = "0xC59AF3664FA25156B";
  big_read_string(&X, xstr);
  const char *ystr = "0x10000000000000000";
  big_read_string(&Y, ystr);

  assert(0 == big_inv_mod(&ans1, &X, &Y));

  const char *solution1 = "A5103BCB3A866F43";

  char buf1[128];
  size_t olen;
  big_write_string(&ans1, buf1, 128, &olen);

  print_test_result("Test m mod BASE", strcasecmp(buf1, solution1) == 0, "");
  big_free(&ans1);  big_free(&X);  big_free(&Y);
}

void test_revealed_bigint_inverse_12() {
  const size_t ntests = 16;
  const char *bases[ntests] = {"1a", "fd", "df", "14", "b3", "f8", "38",
                           "a0", "22", "65", "99", "d4", "6b", "ef", "5a", "31"};

  const char *moduli[ntests] = {"6df", "2d7", "dab", "1639", "178d", "1b41", "1fff",
                            "dff", "10bb", "1cb5", "a7", "1df", "bf", "10c9", "92b", "829"};

  const char *solutions[ntests] = {"cb", "fa", "b18", "c39", "2e5", "1a6", "176d", "2e3", "7e",
                              "16bd", "9b", "1a2", "19", "35f", "7d8", "4ff"};

  bigint base, modulus, answer, expected;
  big_init(&base);
  big_init(&modulus);
  big_init(&answer);
  big_init(&expected);
  bool passed = true;
  for (size_t i = 0; i < ntests; i++) {
    big_read_string(&base, bases[i]);
    big_read_string(&modulus, moduli[i]);
    big_inv_mod(&answer, &base, &modulus);

    big_read_string(&expected, solutions[i]);
    if (big_cmp(&answer, &expected) != 0) {
      passed = false;
      printf("Failed at test #%zu. ", i);
      printf("%s^-1 mod %s = %s but got ", bases[i], moduli[i], solutions[i]);
      big_print(&answer);
    }
  }
  print_test_result("Test revealed bigint-inverse-12", passed, "TODO");
  big_free(&base);
  big_free(&modulus);
  big_free(&answer);
  big_free(&expected);
}

int main() {
  printf("*** TESTS INV_MOD ***\n");
  test_textbook_example();
  test_tiny_example();
  test_no_inv_mod();
  test_bad_mod1();
  test_mod_inv();
  test_m_mod_base();
  test_revealed_bigint_inverse_12();
  printf("\n");
}
