#include "bigint.h"
#include "bigint_aux.h"
#include "test_bigint.h"

void test_scalar_gcd() {
  big_uint x = 1071;
  big_uint y = 462;
  print_test_result("Test scalar GCD", 21 == big_scalar_gcd(x, y), "");
}

void test_gcd0() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "AE27B9DE8";
  big_read_string(&x1, x1_str);

  const char *x2_str = "AAA5741E4070CC960";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "8";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test GCD(bigint, limb)", strcmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_gcd1() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "FF6466C53306C453383AE630E85C281F43EC46463F1048F709";
  big_read_string(&x1, x1_str);

  const char *x2_str = "AC66216DDF9526DAF3662CD86176E60FF6A84500C66BF96F7612419EF3E";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "1";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result(&gcd, strcmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_gcd2() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "8FC456E967511DDC7BBBEA702C740F558";
  big_read_string(&x1, x1_str);

  const char *x2_str = "3A690ADB1ABD545DE2";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "A";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd2", strcmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

int main() {
  test_scalar_gcd();
  test_gcd0();
  test_gcd2();
  // test_gcd1();
}

