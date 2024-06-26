#include "test_bigint.h"
#include "bigint.h"
#include "bigint_aux.h"

void test_big_add() {
  const char *test_name = "Test big add";

  bigint x1, x2, ans, soln, zero;

  big_init(&x1);
  uint8_t x1_bin[2] = {0xB0, 0x00};
  big_read_binary(&x1, x1_bin, 2);

  big_init(&x2);
  const char *x2_str = "0002";
  big_read_string(&x2, x2_str);

  big_init(&ans);
  big_add(&ans, &x1, &x2);

  big_init(&soln);
  uint8_t soln_bin[2] = {0xB0, 0x02};
  big_read_binary(&soln, soln_bin, 2);

  zero = BIG_ZERO;
  print_test_result(test_name,
                    ((0 == big_cmp(&soln, &ans)) &&
                     (-1 == big_cmp(&zero, &ans)) &&
                     (1 == big_cmp(&ans, &zero))),
                    "");

  big_free(&x1);
  big_free(&x2);
  big_free(&ans);
  big_free(&soln);
}

void test_big_add_three_and_two_limb_numbers() {
  const char *test_name = "Test add three and two limb numbers";

  const char *x1_str = "0x89FBB9FFA177072A380B6B5451CAB81119DFE79472FB0";
  bigint x1;
  big_init(&x1);
  assert(0 == big_read_string(&x1, x1_str));

  const char *x2_str = "0xF127B702E4771196F395D5376561B";
  bigint x2;
  big_init(&x2);
  assert(0 == big_read_string(&x2, x2_str));

  bigint ans;
  big_init(&ans);
  big_add(&ans, &x1, &x2);

  char ans_buf[50];
  size_t ans_str_len;
  if (0 != big_write_string(&ans, ans_buf, 50, &ans_str_len)) {
    print_test_result(test_name, 0, "could not write string");
  }

  const char *expected = "89FBB9FFA177072B293322573641C9A80D75BCCBD85CB";
  bigint bi_expected;
  big_init(&bi_expected);
  big_read_string(&bi_expected, expected);

  print_test_result(test_name,
                    ((0 == big_cmp(&bi_expected, &ans)) &&   // testing big_cmp
                     (ans_str_len + 1 == strlen(x1_str)) &&  // expected olen
                     (strcasecmp(ans_buf, expected) == 0)), // expected output of write_string
                    "");

  big_free(&x1);
  big_free(&x2);
  big_free(&ans);
  big_free(&bi_expected);
}

void test_two_digits_minus_one_digit() {
  bigint x, y;
  big_init(&x);
  big_init(&y);
  big_read_string(&x, "10");
  char y_str[3] = {'-', '\0', '\0'};
  for (char ch = '0'; ch <= '9'; ch++) {
    y_str[1] = ch;
    big_read_string(&y, y_str);
    big_add(&y, &x, &y);
    printf("y: ");  big_print(&y);
  }

  big_free(&x);
  big_free(&y);
}

void test_one_digit_additive_identity() {
  bool passed = true;
  bigint x, y;
  big_init(&x);
  big_init(&y);
  big_read_string(&x, "0");
  char y_str[2] = {'0', '\0'};
  char buf[2];
  size_t olen;
  for (char ch = '0'; ch <= '9'; ch++) {
    y_str[0] = ch;
    big_read_string(&y, y_str);
    big_add(&y, &y, &x);
    big_write_string(&y, buf, 2, &olen);
    if (strcasecmp(buf, y_str) != 0) {
      passed = false;
      break;
    }
  }
  if (passed) {
    for (char ch = 'a'; ch <= 'f'; ch++) {
      y_str[0] = ch;
      big_read_string(&y, y_str);
      big_add(&y, &y, &x);
      big_write_string(&y, buf, 2, &olen);
    }
  }

  print_test_result("Test one digit additive identity", passed, "");

  big_free(&x);
  big_free(&y);
}

void test_associativity() {
  // TODO
}

void test_commutativity() {
  // TODO
}

void test_ans_same_size() {
  // TODO: in general, adding two n-limb numbers gives a n+1 limb number, but
  // it may just be n if the operands are not large enough. Test most-significant
  // bit after adding two numbers that do not result in an increased number of limbs
}

void test_same_addr() {
  const char *x_str = "89FBB9FFA177072A380B6B5451CAB81119DFE79472FB0";
  bigint X;
  big_init(&X);
  big_read_string(&X, x_str);

  big_add(&X, &X, &X);

  char twice_x_buf[60];
  size_t olen;
  assert(0 == big_write_string(&X, twice_x_buf, 60, &olen));
  const char *twice_x_expected_str = "113F773FF42EE0E547016D6A8A395702233BFCF28E5F60";
  print_test_result("Test src/dest same address",
                    0 == strcasecmp(twice_x_expected_str, twice_x_buf),
                    "");

  big_free(&X);
}

void test_reveal() {
  bigint x, y;
  big_init(&x);
  big_init(&y);

  big_read_string(&x, "2abc");
  big_read_string(&y, "-abc");

  big_add(&y, &x, &y);
  char buf[5];
  size_t olen;
  big_write_string(&y, buf, 5, &olen);

  uint8_t expected_bytes[] = {0x20, 0x00};
  uint8_t ans_bytes[2];
  assert(0 == big_write_binary(&y, ans_bytes, 2));
  print_test_result("Test Reveal0",
                    0 == strcasecmp(buf, "2000") &&
                    olen == 5 &&
                    0 == memcmp(ans_bytes, expected_bytes, 2), "");

  big_free(&x);
  big_free(&y);
}

int main() {
  printf("*** TEST add ***\n");
  test_big_add();
  test_big_add_three_and_two_limb_numbers();
  test_same_addr();
  test_reveal();
  test_two_digits_minus_one_digit();
  test_one_digit_additive_identity();
  printf("\n");
}

