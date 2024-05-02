#include "test_bigint.h"
#include "bigint_aux.h"
#include "bigint.h"

void test_all_remainder() {
  bigint x1, x2;
  const char *x1_str = "0xCD10645CC6728";
  big_init(&x1);
  big_read_string(&x1, x1_str);

  const char *x2_str = "0xAD77";
  big_init(&x2);
  big_read_string(&x2, x2_str);

  bigint q, r;
  big_init(&q);
  big_init(&r);
  big_div(&q, &r, &x2, &x1);

  const char *q_str_expected = "0";
  char qbuf[100];
  size_t qolen;
  big_write_string(&q, qbuf, 100, &qolen);
  const char *r_str_expected = x2_str;
  char rbuf[32];
  size_t rolen;
  big_write_string(&r, rbuf, 32, &rolen);

  print_test_result("Test all remainder",
                    ((rolen == 5) &&
                     (0 == strcmp(q_str_expected, qbuf)) &&
                     (0 == strcmp("AD77", rbuf))),
                    "");
  big_free(&x1);
  big_free(&x2);
  big_free(&q);
  big_free(&r);
}

void test_scalar_div() {
  bigint q1, r1, q2, r2, dividend, divisor1, divisor2;
  big_init(&q1);  big_init(&q2);  big_init(&dividend);  big_init(&divisor1);  big_init(&divisor2);
  big_init(&r1);  big_init(&r2);

  const char *dividend_str = "0x8370AF5D4CC7FF942";
  const char *divisor1_str = "0xC";
  const char *divisor2_str = "0x7";
  big_read_string(&dividend, dividend_str);
  big_read_string(&divisor1, divisor1_str);
  big_read_string(&divisor2, divisor2_str);

  big_div(&q1, NULL, &dividend, &divisor1);
  big_div(&q2, NULL, &dividend, &divisor2);
  big_div(NULL, &r1, &dividend, &divisor1);
  big_div(NULL, &r2, &dividend, &divisor2);

  char buf1[100]; char bufr1[100];
  char buf2[100]; char bufr2[50];
  size_t olen1;
  size_t olen2;
  big_write_string(&q1, buf1, 100, &olen1);
  big_write_string(&q2, buf2, 100, &olen2);
  big_write_string(&r1, bufr1, 100, &olen1);
  big_write_string(&r2, bufr2, 100, &olen2);

  const char *q1_str = "AF40E9D1BBB554C5";
  const char *q2_str = "12C6F47B0AF7FFF09";
  print_test_result("Test scalar div",
                    (0 == strcmp(q1_str, buf1) && 0 == strcmp(q2_str, buf2) &&
                     0 == strcmp("6", bufr1) && 0 == strcmp("3", bufr2)),
                    "");

  big_free(&q1);  big_free(&q2);  big_init(&dividend);  big_init(&divisor1);  big_free(&divisor2);
  big_free(&r1);  big_free(&r2);
}

void test_div0() {
  bigint x1, x2;
  const char *x1_str = "0xCD10645CC6728";
  big_init(&x1);
  big_read_string(&x1, x1_str);

  const char *x2_str = "312CB2D039D";
  big_init(&x2);
  big_read_string(&x2, x2_str);

  bigint q, r;
  big_init(&q);
  big_init(&r);
  big_div(&q, &r, &x1, &x2);

  const char *q_str_expected = "42B";
  char qbuf[100];
  size_t qolen;
  big_write_string(&q, qbuf, 100, &qolen);
  const char *r_str_expected = "1B1712E57C9";
  char rbuf[32];
  size_t rolen;
  big_write_string(&r, rbuf, 32, &rolen);

  print_test_result("Test div0",
                    ((0 == strcmp(q_str_expected, qbuf)) &&
                     (0 == strcmp(r_str_expected, rbuf))),
                    "");
  big_free(&x1);
  big_free(&x2);
  big_free(&q);
  big_free(&r);
}

void test_div1() {
  bigint x1, x2;
  const char *x1_str = "673292DA701784AC955D6417A94552C77D5BCBD147E47FB9F"
                       "4964F0943EB8E5F749FE08379C08A812C1EDC5292C5E6CCDB9";
  big_init(&x1);
  big_read_string(&x1, x1_str);

  const char *x2_str = "8D0891B6EB237BE0B256B8A4C420AF6";
  big_init(&x2);
  big_read_string(&x2, x2_str);

  bigint q, r;
  big_init(&q);
  big_init(&r);
  big_div(&q, &r, &x1, &x2);

  const char *q_str_expected = "BB5240BE9A3346A1805116DC5760D84891F2CBBA854723E962B60ABCCD8D235504AA";
  char qbuf[100];
  size_t qolen;
  big_write_string(&q, qbuf, 100, &qolen);
  const char *r_str_expected = "88E693DA97FBF32C81635396CB7AE5D";
  char rbuf[32];
  size_t rolen;
  big_write_string(&r, rbuf, 32, &rolen);

  print_test_result("Test div1",
                    ((rolen == 32) &&
                     (0 == strcmp(q_str_expected, qbuf)) &&
                     (0 == strcmp(r_str_expected, rbuf))),
                    "");
  big_free(&x1);
  big_free(&x2);
}


int main() {
  test_all_remainder();
  test_scalar_div();
  test_div0();
  test_div1();
}

