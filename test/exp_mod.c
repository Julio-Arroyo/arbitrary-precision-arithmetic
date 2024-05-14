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

  print_test_result("Test exp mod two-limb number to small scalar", 0 == strcasecmp(ans_str, ans_buf), "");

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

  print_test_result("Test exp_mod scalar to scalar", 0 == strcasecmp(ans_str, ans_buf), "");

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
  big_init(&ans);
  big_set_nonzero(&one, 1);
  big_read_string(&exp, "0x1");
  big_read_string(&m, "0xFD");

  char buf[2];
  size_t olen;
  big_exp_mod(&ans, &one, &exp, &m, NULL);
  big_write_string(&ans, buf, 2, &olen);

  print_test_result("Test exponentiate one", 0 == strcasecmp("1", buf), "");

  big_free(&one);
  big_free(&exp);
  big_free(&m);
  big_free(&ans);
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

void test_bug_is_prime() {
  bigint A, exp, m, ans;
  big_init(&A);
  big_init(&exp);
  big_init(&m);
  big_init(&ans);
  big_read_string(&A, "0xF3");
  big_read_string(&exp, "0x16098B2CC");
  big_read_string(&m, "0x16098B2CD");

  char buf[2];
  size_t olen;
  big_exp_mod(&ans, &A, &exp, &m, NULL);
  big_write_string(&ans, buf, 2, &olen);

  print_test_result("Test bug in is_prime", 0 == strcasecmp("1", buf), "");

  big_free(&A);
  big_free(&exp);
  big_free(&m);
  big_free(&ans);
}

void test_exponentiate_zero() {
  bigint zero = BIG_ZERO;
  bigint exp;
  bigint mod;
  bigint ans;
  big_init(&ans);
  big_init(&exp);
  big_init(&mod);
  big_read_string(&exp, "deadbeef");
  big_read_string(&mod, "fedcba01");
  big_exp_mod(&ans, &zero, &exp, &mod, NULL);
  print_test_result("Test exponentiate zero", big_is_zero(&ans), "");
  big_free(&ans);
  big_free(&exp);
  big_free(&mod);
}

void test_exponentiate_negative_number() {
  const char *base_str = "-5";
  const char *mod_str = "0x65";
  const char *ans_str = "60";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&modulo, mod_str);
  big_set_nonzero(&exponent, 1);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[51];
  size_t olen;
  big_write_string(&ans, ans_buf, 51, &olen);
  printf("soln: %s", ans_buf);

  print_test_result("Test (-5)^1 mod 100 = 95", 0 == strcasecmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
}

void test_large_exponentiate_negative_number() {
  const char *base_str = "-0xb799a32586b2dc37b77324e85027633cb1814b7515b3b8713a13d38d182bf7c5640e0e072ca8b0f7c53d156e519ef2bdf01f";
  const char *exp_str = "0xcdd8b2460a9c04f";
  const char *mod_str = "0xd2175dd692ce8939ff13d503423284771c6eeb0181699b44894bcdfec0a271189f2635f88b3079eae9068d8507ed806e761d3";
  const char *ans_str = "9a59544d3f4ab66406524f23961c8af1b92b3e059839e495bfd1737573d735797ee5cd6010c5e72fcb54dc76646c80711a678";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&exponent, exp_str);
  big_read_string(&modulo, mod_str);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[102];
  size_t olen;
  assert(0 == big_write_string(&ans, ans_buf, 102, &olen));

  print_test_result("Test large exponentiate negative number", 0 == strcasecmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
}

void test_base_larger_than_mod() {
  const char *base_str = "0x10000000000000001";
  const char *exp_str = "0x3";
  const char *mod_str = "0x3";
  const char *ans_str = "2";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&exponent, exp_str);
  big_read_string(&modulo, mod_str);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[102];
  size_t olen;
  assert(0 == big_write_string(&ans, ans_buf, 102, &olen));
  printf("ans_buf %s", ans_buf);

  print_test_result("Test base larger than modulus", 0 == strcasecmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
}

void test_power_of_one() {
  const char *mod_str1 = "0x1abc";  // is even
  const char *mod_str2 = "0x1abd";
  const char *exp_str = "0x1";
  const char *base_str = "0x1fffff";
  const char *ans_str = "a15";

  bigint base, exponent, ans, modulo;
  big_init(&base);  big_init(&exponent);  big_init(&ans);  big_init(&modulo);

  big_read_string(&base, base_str);
  big_read_string(&exponent, exp_str);
  big_read_string(&modulo, mod_str1);

  // fails since modulus is even
  assert(ERR_BIGINT_BAD_INPUT_DATA == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  big_read_string(&modulo, mod_str2);

  assert(0 == big_exp_mod(&ans, &base, &exponent, &modulo, NULL));

  char ans_buf[4];
  size_t olen;
  assert(0 == big_write_string(&ans, ans_buf, 102, &olen));
  assert(olen == 4);
  print_test_result("Test base larger than modulus power of one", 0 == strcasecmp(ans_str, ans_buf), "");

  big_free(&base);  big_free(&exponent);  big_free(&ans);  big_free(&modulo);
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
  test_bug_is_prime();
  test_exponentiate_zero();
  test_exponentiate_negative_number();
  test_large_exponentiate_negative_number();
  // test_base_larger_than_mod();
  test_power_of_one();
  printf("\n");
}
