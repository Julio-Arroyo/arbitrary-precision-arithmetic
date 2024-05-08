#include "bigint.h"
#include "bigint_aux.h"
#include "test_bigint.h"
#include "number_theory.h"

void test_two_limb_raised_scalar() {
  const char *base_str = "0x25CE0AB2F";
  const char *mod_str = "0x07A607BBE974EDD9B";
  const char *ans_str = "5C69F15DE8B0535";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&modulo, mod_str);
  big_set_nonzero(&exponent, 7);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[51];
  size_t olen;
  big_write_string(&ans, ans_buf, 51, &olen);

  print_test_result("Test exp mod two-limb number to small scalar", 0 == strcmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
}

void test_scalar_raised_scalar() {
  const char *base_str = "0x4";
  const char *mod_str = "0x1F";
  const char *ans_str = "1";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&modulo, mod_str);
  big_set_nonzero(&exponent, 30);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[51];
  size_t olen;
  big_write_string(&ans, ans_buf, 51, &olen);

  print_test_result("Test exp_mod scalar to scalar", 0 == strcmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
}

void test_fermat_big_prime() {
  const char *bigprime_str = "0xA00C84237ED9FF5F971F333108B9B12D765A38CB06B5431A34E50B6AD6AA6F34C9";
  const char *random_str = "0x11C88075B8C2E37C661FE93E564D8576D442E9DDAB69793BCCFD0144C284B705DD";
  bigint big_prime, random_base;
  big_init(&big_prime);
  big_init(&random_base);

  big_read_string(&big_prime, bigprime_str);
  big_read_string(&random_base, random_str);
  // big_fill_random(&random_base, (big_prime.num_limbs - 1) * 8);

  print_test_result("Test Fermat's Test Big Prime",
                    PROBABLY_PRIME == fermat_test(&random_base, &big_prime), "");

  big_free(&big_prime);
  big_free(&random_base);
}

void test_fermat_small_prime() {
  const char *bigprime_str = "0x1F";
  const char *random_str = "0x12";
  bigint big_prime, random_base;
  big_init(&big_prime);
  big_init(&random_base);

  big_read_string(&big_prime, bigprime_str);
  big_read_string(&random_base, random_str);
  // big_fill_random(&random_base, (big_prime.num_limbs - 1) * 8);

  print_test_result("Test Fermat's Test Small Prime",
                    PROBABLY_PRIME == fermat_test(&random_base, &big_prime), "");

  big_free(&big_prime);
  big_free(&random_base);
}

void test_fermat_medium_prime() {
  const char *medium_prime_str = "0x16098B2CD";
  const char *random_str = "0x1C";
  bigint medium_prime, random_base;
  big_init(&medium_prime);
  big_init(&random_base);

  big_read_string(&medium_prime, medium_prime_str);
  big_read_string(&random_base, random_str);
  // big_fill_random(&random_base, (medium_prime.num_limbs - 1) * 8);

  print_test_result("Test Fermat's Test Medium Prime",
                    PROBABLY_PRIME == fermat_test(&random_base, &medium_prime), "");

  big_free(&medium_prime);
  big_free(&random_base);
}

void test_exponentiate_one() {
  bigint one, exp, m, ans;
  big_init(&one);
  big_init(&exp);
  big_init(&m);
  big_set_nonzero(&one, 1);
  big_read_string(&exp, "0x1");
  big_read_string(&m, "0xFD");

  char buf[2];
  size_t olen;
  big_exp_mod(&ans, &one, &exp, &m, NULL);
  big_write_string(&ans, buf, 2, &olen);

  print_test_result("Test exponentiate one", 0 == strcmp("1", buf), "");

  big_free(&one);
  big_free(&exp);
  big_free(&m);
}

void test_fooled_fermat() {
  const char *bigprime_str = "0x6C1";  // pseudo prime 1729
  const char *random_str = "0x29F";
  bigint big_prime, random_base;
  big_init(&big_prime);
  big_init(&random_base);

  big_read_string(&big_prime, bigprime_str);
  big_read_string(&random_base, random_str);
  // big_fill_random(&random_base, (big_prime.num_limbs - 1) * 8);

  print_test_result("Test Carmichael 1729 fools Fermat",
                    PROBABLY_PRIME == fermat_test(&random_base, &big_prime), "");

  big_free(&big_prime);
  big_free(&random_base);
}

int main() {
  printf("*** Test exp_mod ***\n");
  test_scalar_raised_scalar();
  test_two_limb_raised_scalar();
  test_fermat_small_prime();
  test_fermat_big_prime();
  test_fermat_medium_prime();
  test_fooled_fermat();
  test_exponentiate_one();
  printf("\n");
}
