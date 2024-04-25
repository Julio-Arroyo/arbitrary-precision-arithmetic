#include "bigint.h"

/**
 * \brief Test for reading binary and writing to string
 */
void test_read_binary_write_string() {
  bigint X;
  big_init(&X);
  uint8_t X_bin[] = {
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x12, 0x34,
      0x56, 0x78, 0x90, 0xAB,
      0xCD, 0xEF, 0x12, 0x34
  };
  assert(0 == big_read_binary(&X, X_bin, sizeof(X_bin)));

  char str_buf[32];
  size_t X_str_len;
  assert(0 == big_write_string(&X, str_buf, 32, &X_str_len));

  const char *ans = "1234567890ABCDEF1234";
  assert(X_str_len == strlen(ans) + 1);
  assert(strcmp(X_str_buf, ans) == 0);
}

/**
 * \brief Test for reading a string and writing to binary
 */
void test_read_string_write_binary() {
  const char *hex_string = "0000000000001234567890ABCDEF1234";
  bigint X;
  big_init(&X);
  uint8_t buffer[16]; // 16 bytes for 128-bit bigint

  // Initialize bigint from hex string
  int result = big_read_string(&X, hex_string);
  if (result != 0) {
      printf("Error reading hexadecimal string: %d\n", result);
      return;
  }

  // Write bigint to binary buffer
  result = big_write_binary(&X, buffer, sizeof(buffer));
  if (result != 0) {
      printf("Error writing bigint to binary: %d\n", result);
      return;
  }

  // Expected output for the given hex string
  uint8_t expected_buffer[] = {
      0x12, 0x34,
      0x56, 0x78, 0x90, 0xAB,
      0xCD, 0xEF, 0x12, 0x34
  };

  // Check if the output matches the expected output
  assert(memcmp(buffer, expected_buffer, sizeof(expected_buffer)) == 0);
  printf("Test passed: write binary matches expected output.\n");
}

int main() {
  test_read_binary_write_string();
  test_read_string_write_binary();
}

