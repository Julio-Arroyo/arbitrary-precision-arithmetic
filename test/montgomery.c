#include "bigint.h"
#include "bigint_aux.h"
#include "test_bigint.h"

void test_two_limb_raised_scalar() {
  const char *base_str = "0x25CE0AB2F";
  const char *mod_str = "0x07A607BBE974EDD9B";
  const char *ans_str = "0x5C69F15DE8B0535";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&modulo, mod_str);
  big_set_nonzero(&exponent, 7);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[51];
  size_t olen;
  big_write_string(&ans, ans_buf, 51, &olen);
  printf("her: %s\n", ans_buf);

  print_test_result("Test exp mod two-limb number to small scalar", 0 == strcmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
}

void test_montgomery_mul() {
  const char *x_str = "0x07A607BBE974EDD9B";
  const char *y_str = "0x25CE0AB2F";
  const char *m_str = "0xC59AF3664FA25156B";
  const char *soln_str = "6AB02CC1F21BE3F2E";

  bigint x, y, m, soln, ans;
  big_init(&x);  big_init(&y);  big_init(&m);  big_init(&soln);  big_init(&ans);
  big_read_string(&x, x_str);
  big_read_string(&y, y_str);
  big_read_string(&m, m_str);
  big_read_string(&soln, soln_str);

  big_montgomery_mul(&ans, &x, &y, &m);

  print_test_result("Test montgomery multiplication: ", big_cmp(&ans, &soln) == 0, "");

  big_free(&x);  big_free(&y);  big_free(&m);  big_free(&soln);  big_free(&ans);
}

int main() {
  // test_two_limb_raised_scalar();
  test_montgomery_mul();
}

