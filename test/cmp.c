#include "bigint.h"
#include "test_bigint.h"

void test_cmp_two_limb_numbers() {
  const char* test_name = "Test compare two-limb numbers";
  bigint X, Y;
  big_init(&X);
  uint8_t X_bin[] = {
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x12, 0x34,
      0x56, 0x78, 0x90, 0xAB,
      0xCD, 0xEF, 0x12, 0x34
  };
  big_read_binary(&X, X_bin, sizeof(X_bin));

  big_init(&Y);
  const char *Ystr = "1234567890ABCDEF1234";
  big_read_string(&Y, Ystr);

  print_test_result(test_name, 0 == big_cmp(&X, &Y), "");

  big_free(&X);
  big_free(&Y);
}

void test_positive_zero_equal_negative_zero() {

}

void test_leading_zeros_equal_wo_leading_zeros() {
  
}

int main() {
  printf("*** TEST cmp ***\n");
  test_cmp_two_limb_numbers();
  printf("\n");
}

