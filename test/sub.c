#include "test_bigint.h"
#include "bigint.h"

void test_negative_ans() {

}

void test_sub1() {
  const char *test_name = "Test sub1";

  const char *x1_str = "0x89FBB9FFA177072A380B6B5451CAB81119DFE79472FB0";
  bigint x1;
  big_init(&x1);
  assert(0 == big_read_string(&x1, x1_str));

  const char *x2_str = "89FBB9FFA177072B293322573641C9A80D75BCCBD85CB";
  bigint x2;
  big_init(&x2);
  assert(0 == big_read_string(&x2, x2_str));

  bigint ans;
  big_init(&ans);
  big_sub(&ans, &x2, &x1);

  char ans_buf[50];
  size_t ans_str_len;
  if (0 != big_write_string(&ans, ans_buf, 50, &ans_str_len)) {
    print_test_result(test_name, 0, "could not write string");
  }

  const char *expected = "F127B702E4771196F395D5376561B";
  bigint bi_expected;
  big_init(&bi_expected);
  big_read_string(&bi_expected, expected);

  print_test_result(test_name,
                    ((0 == big_cmp(&bi_expected, &ans)) &&   // testing big_cmp
                     (ans_str_len == strlen(expected) + 1) &&  // expected olen
                     (strcmp(ans_buf, expected) == 0)), // expected output of write_string
                    "");
}

int main() {
  test_sub1();
}

