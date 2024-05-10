#include "bigint.h"
#include "bigint_aux.h"
#include "test_bigint.h"

void test_scalar_gcd() {
  big_uint x = 1071;
  big_uint y = 462;
  print_test_result("Test scalar GCD", 21 == big_scalar_gcd(x, y), "");
}

void test_gcd0() {
  bigint x1, x2, gcd, gcd1;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);  big_init(&gcd1);

  const char *x1_str = "AE27B9DE8";
  big_read_string(&x1, x1_str);

  const char *x2_str = "AAA5741E4070CC960";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "8";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test GCD(bigint, limb)", strcasecmp(buf, expected) == 0, "");

  char buf1[5];
  big_binary_extended_gcd(NULL, NULL, &gcd1, &x1, &x2);
  big_write_string(&gcd, buf1, 5, &olen);
  print_test_result("Test binary extended GCD(bigint, limb)", strcasecmp(buf1, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);  big_free(&gcd1);
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
  print_test_result("Test GCD1", strcasecmp(buf, expected) == 0, "");

  buf[0] = 'j';  buf[1] = 'j';
  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test GCD1 binary extended", strcasecmp(buf, expected) == 0, "");
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
  print_test_result("Test gcd2", strcasecmp(buf, expected) == 0, "");

  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd2 binary extended", strcasecmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_gcd3() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "67327D13AD2E09C8E513F1C54DB57637A9EDE9107DDC9D36FC22C7106D6B768C9270CFB5B7AC550728DAAD6A09C2C3F023D9";
  big_read_string(&x1, x1_str);

  const char *x2_str = "6AB79075E2A62D524E5365DB3E1B16C441C7AEC9864E4F63B0C8CEA2F30FCC59087ACC8E7A7ACD098CD3DE88CECB2F25F3A77";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "1";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd3", strcasecmp(buf, expected) == 0, "");

  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd3 binary extended", strcasecmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_gcd4() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "5";
  big_read_string(&x1, x1_str);

  const char *x2_str = "A";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "5";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd4", strcasecmp(buf, expected) == 0, "");

  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd4 binary extended", strcasecmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_gcd5() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "0xd07687490f043aa";
  big_read_string(&x1, x1_str);

  const char *x2_str = "0x3ef71718efbaa1835f18bc8800d97efc3908390f5df0d3ad3ef38ed643be403aef529f912b6ebfcc2f4e1c3c60406fb877b42";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "6";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd5", strcasecmp(buf, expected) == 0, "");

  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test gcd5 binary extended", strcasecmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_self_gcd() {
  bigint A;
  big_init(&A);
  const char *str = "0x3ef71718efbaa1835f18bc8800d97efc3908390f5df0d3ad3ef38ed643be403aef529f912b6ebfcc2f4e1c3c60406fb877b42";
  big_read_string(&A, str);

  big_gcd(&A, &A, &A);
  char buf[256];
  size_t olen;
  assert(0 == big_write_string(&A, buf, 256, &olen));
  print_test_result("Test self GCD", strcasecmp(buf, str + 2) == 0, "");
  big_free(&A);
}

void test_gcd_number_and_zero() {
  bigint A, zero;
  big_init(&A);
  big_read_string(&A, "-0xEE");
  zero = BIG_ZERO;
  big_gcd(&A, &A, &zero);
  print_test_result("Test GCD(A, 0) = A", big_scalar_cmp(&A, 238) == 0, "");
  big_free(&A);
}

void test_gcd_number_and_zero2() {
  bigint A, zero;
  big_init(&A);
  big_read_string(&A, "-0xEE");
  big_set_zero(&zero);
  big_gcd(&A, &zero, &A);
  print_test_result("Test GCD(0, A) = A", big_scalar_cmp(&A, 238) == 0, "");
  big_free(&A);
  big_free(&zero);
}

void test_gcd_number_and_one() {
  bigint A, I;
  big_init(&A);
  big_init(&I);
  big_read_string(&A, "-0xEE");
  big_set_nonzero(&I, 1);
  big_gcd(&A, &A, &I);
  print_test_result("Test GCD(A, 1) = 1", big_scalar_cmp(&A, 1) == 0, "");
  big_free(&A);
  big_free(&I);
}

void test_negative_gcd1() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "-8";
  big_read_string(&x1, x1_str);

  const char *x2_str = "0xc";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);

  const char *expected = "4";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test negative gcd1", strcasecmp(buf, expected) == 0, "");

  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test negative gcd1 binary extended", strcasecmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

void test_negative_gcd2() {
  bigint x1, x2, gcd;
  big_init(&x1);  big_init(&x2);  big_init(&gcd);

  const char *x1_str = "0xd07687490f043aa";
  big_read_string(&x1, x1_str);

  const char *x2_str = "-1";
  big_read_string(&x2, x2_str);

  big_gcd(&gcd, &x1, &x2);
  const char *expected = "1";
  char buf[2];
  size_t olen;
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test negative gcd2", strcasecmp(buf, expected) == 0, "");

  big_binary_extended_gcd(NULL, NULL, &gcd, &x1, &x2);
  big_write_string(&gcd, buf, 2, &olen);
  print_test_result("Test negative gcd2 binary extended", strcasecmp(buf, expected) == 0, "");

  big_free(&x1);  big_free(&x2);  big_free(&gcd);
}

int main() {
  printf("*** TESTS GCD ***\n");
  test_scalar_gcd();
  test_gcd0();
  test_gcd1();
  test_gcd2();
  test_gcd3();
  test_gcd4();
  test_gcd5();
  test_self_gcd();
  test_gcd_number_and_zero();
  test_gcd_number_and_zero2();
  test_gcd_number_and_one();
  test_negative_gcd1();
  test_negative_gcd2();
  printf("\n");
}
