#include "test_bigint.h"
#include "bigint.h"

/**
 * \brief Test for reading binary and writing to string
 */
void test_read_binary_write_string() {
  const char* test_name = "Test read binary write string";
  bigint X;
  big_init(&X);
  uint8_t X_bin[] = {
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x12, 0x34,
      0x56, 0x78, 0x90, 0xAB,
      0xCD, 0xEF, 0x12, 0x34
  };
  if (0 != big_read_binary(&X, X_bin, sizeof(X_bin))) {
    print_test_result(test_name, 0, "could not read binary");
  }

  char str_buf[32];
  size_t X_str_len;
  if (0 != big_write_string(&X, str_buf, 32, &X_str_len)) {
    print_test_result(test_name, 0, "could not write string");
  }

  const char *ans = "1234567890ABCDEF1234";
  print_test_result(test_name, (X_str_len == strlen(ans) + 1) && (strcmp(str_buf, ans) == 0), "");
  big_free(&X);
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
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x12, 0x34,
      0x56, 0x78, 0x90, 0xAB,
      0xCD, 0xEF, 0x12, 0x34
  };

  // Check if the output matches the expected output
  int test_result = 0 == memcmp(buffer, expected_buffer, sizeof(expected_buffer));
  const char *test_name = "Test read string write binary";
  print_test_result(test_name, test_result, "");
  big_free(&X);
}

void test_binary_edge_cases() {
  bigint a;
  big_init(&a);
  uint8_t a_input_buf[] = {0x10};
  big_read_binary(&a, a_input_buf, 1);

  bigint b;
  big_init(&b);
  big_read_string(&b, "a");

  big_sub(&a, &a, &b);

  // edge case 1 cannot fill small buffer
  uint8_t small_output_buf[0];
  int small_res = big_write_binary(&a, small_output_buf, 0);

  // edge case 2 fill 
  size_t huge_size = 35;
  uint8_t huge_output_buf[huge_size];
  uint8_t expected_huge_output_buf[huge_size];
  for (size_t i = 0; i < huge_size; i++) {
    expected_huge_output_buf[i] = 0;
    if (i == huge_size - 1) {
      expected_huge_output_buf[i] = 6;
    }
  }
  assert(0 == big_write_binary(&a, huge_output_buf, huge_size));
  int huge_res = memcmp(huge_output_buf, expected_huge_output_buf, huge_size);
  printf("huge_res: %d\n", huge_res);

  // edge case 3 read huge output buf
  bigint huge_expected;
  big_init(&huge_expected);
  big_read_binary(&huge_expected, expected_huge_output_buf, huge_size);
  int cmp_res = big_cmp(&huge_expected, &a);

  print_test_result("Test binary edge cases",
                    small_res == ERR_BIGINT_BUFFER_TOO_SMALL &&
                    huge_res == 0 &&
                    cmp_res == 0,
                    "");

  big_free(&a);
  big_free(&b);
  big_free(&huge_expected);
}

int main() {
  printf("*** TEST io ***\n");
  test_read_string_write_binary();
  test_read_binary_write_string();
  test_binary_edge_cases();
  printf("\n");
}

