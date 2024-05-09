#include "test_bigint.h"
#include "bigint.h"

void test_prime0() {
  bigint prime;
  big_init(&prime);
  big_read_string(&prime, "0x1F");
  print_test_result("Test prime 0", 0 == big_is_prime(&prime), "");
  big_free(&prime);
}

void test_prime1() {
  bigint prime;
  big_init(&prime);
  big_read_string(&prime, "0x16098B2CD");
  print_test_result("Test prime 1", 0 == big_is_prime(&prime), "");
  big_free(&prime);
}

void test_prime2() {
  bigint prime;
  big_init(&prime);
  big_read_string(&prime, "0xA00C84237ED9FF5F971F333108B9B12D765A38CB06B5431A34E50B6AD6AA6F34C9");
  print_test_result("Test prime 2", 0 == big_is_prime(&prime), "");
  big_free(&prime);
}

void test_prime3() {
  bigint prime;
  big_init(&prime);
  big_read_string(&prime, "3CB515BE64F457495BC9DCC5658A0BADC6ED7F3B9156FF2B548C205840E992F8094E387CCEF8FE253BD");
  print_test_result("Test prime 3", 0 == big_is_prime(&prime), "");
  big_free(&prime);
}

void test_composite0() {
  bigint composite;
  big_init(&composite);
  big_read_string(&composite, "0xAD33C7B1D8B1C4B7C096DCEA3991DB9A332506B209CE989021806C6A4D");
  int res = big_is_prime(&composite);
  printf("res: %d\n", res);
  print_test_result("Test composite 0",
                    ERR_BIGINT_NOT_ACCEPTABLE == res, "");
  big_free(&composite);
}

void test_carmichael0() {
  bigint carmichael;
  big_init(&carmichael);
  big_read_string(&carmichael, "0xD7DB6A899FA9C31");
  int res = big_is_prime(&carmichael);
  printf("res: %d\n", res);
  print_test_result("Test carmichael 0",
                    ERR_BIGINT_NOT_ACCEPTABLE == res, "");
  big_free(&carmichael);
}

void test_carmichael1() {
  bigint carmichael;
  big_init(&carmichael);
  big_read_string(&carmichael, "0x6C1");
  int res = big_is_prime(&carmichael);
  printf("res: %d\n", res);
  print_test_result("Test carmichael 1",
                    ERR_BIGINT_NOT_ACCEPTABLE == res, "");
  big_free(&carmichael);
}

void test_carmichael2() {
  bigint carmichael;
  big_init(&carmichael);
  big_read_string(&carmichael, "0x22CF");
  int res = big_is_prime(&carmichael);
  printf("res: %d\n", res);
  print_test_result("Test carmichael 2",
                    ERR_BIGINT_NOT_ACCEPTABLE == res, "");
  big_free(&carmichael);
}

void test_generate_primes() {
  bigint X;
  big_init(&X);
  for (size_t i = 0; i < 1; i++) {
    big_gen_prime(&X, 1000);
  }
  big_free(&X);
}

int main() {
  printf("*** TEST is_prime ***\n");
  test_prime0();
  test_prime1();
  test_prime2();
  test_prime3();
  test_composite0();
  // test_generate_primes();
  test_carmichael0();
  test_carmichael1();
  test_carmichael2();
  printf("\n");
}