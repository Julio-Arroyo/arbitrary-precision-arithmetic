#include "test_bigint.h"
#include "bigint.h"
#include "bigint_aux.h"

void test_self_subtraction() {
  const char *test_name = "Test self subtraction";

  const char *x1_str = "0x89FBB9FFA177072A380B6B5451CAB81119DFE79472FB0";
  bigint x1;
  big_init(&x1);
  assert(0 == big_read_string(&x1, x1_str));

  big_sub(&x1, &x1, &x1);

  assert(big_is_zero(&x1));
  char ans_buf[59];
  size_t ans_str_len;
  if (0 != big_write_string(&x1, ans_buf, 59, &ans_str_len)) {
    print_test_result(test_name, 0, "could not write string");
  }
  print_test_result(test_name, 0 == strcmp(ans_buf, "0"), "");

  big_free(&x1);
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

  big_free(&x1);
  big_free(&x2);
  big_free(&ans);
  big_free(&bi_expected);
}

void test_negative_result() {
  const char * small_str = "BEDFB48CC092DF72DA7F31AEBA930944DC687741817A6C75"
                           "F13995CECC4C9DC3C0D6A0E62DDC9252919A6577AECE480B"
                           "CF61215C2900F3EDC462F11F4AE5460A7B90890939AB50C6"
                           "8FD701DF3F3689271FBE05948AA75201FDCEDB4AD6BB1990"
                           "6D1CC3373C8E143FC64FBBB34DAE38DBC9D76A969BE2A416"
                           "95211CFB000E97862CBC95429F84F93ABCECD0439FEC7261"
                           "216AA3AEB0C226912DB40D33367410B61A5576F5A3F24D1A"
                           "1B119B4C4C84342503C8DA6F4B2C2AB83387A5F1BC8E2FDF"
                           "FDC505F77698DA7A4E7B757CEF9AE48888F58";
  const char *big_str = "7822D73571FD3108BE50A3A3203DA6DBA3175CF76D02E9A6E"
                        "B2026150C707E078DDB5F9D5ACC75139CB1CD6489457B05C12"
                        "D3E147AF2120FF372F7F947D8015B711E4E466066A663B96D"
                        "155E85BCFC0201F7DDA75A59D7C29348B80AB0DC3314285B9"
                        "DD8A7205E83C518B800B7529713CC4A79C45E6E3927910D82"
                        "BA786DA0334AE1CDD6C9123FDB97848858046FF0A412404ED"
                        "CB56342E4DBDD2ECC553D56B7DB7431C25EC6B69697C3D390"
                        "BEA5F25F14A25F3B360F400197FA1832D97E3678704952585"
                        "F29D762DA74138CEBE53BFCED30E4131FE6F8192AF1F53510"
                        "D68FACF66F688D4C2BAA991B2C7514983E977CD78E038CBA4"
                        "89EF3AC3D437A532EACEEA6FC2384C0313A58F213A4A52812"
                        "C248EBE1CE94B2ADA62B9E031D17B6930C2362837A131D15C034ED0FA966";
  const char* small_minus_big = "-7822D73571FD3108BE50A3A3203DA6DBA3175CF76D02E9A6EB"
                                "2026150C707E078DDB5F9D5ACC75139CB1CD6489457B05C12D3E1"
                                "47AF2120FF372F7F947D8015B711E4E466066A663B96D155E85BC"
                                "FC0201F7DDA75A59D7C2933CCA0F681029E6312DF5E58C34B5533"
                                "0CAF179433A7F6D04EB662B0181745DB4D175506A0AC26A25B8B4"
                                "30719752F716C79245EEAD6094D36408ADA36E94907B3575C3C4A"
                                "9BC02CF0B345240D2C32E0551D7B0655D47E9F482824D8161D44F"
                                "FEF34666A60A6D972C4CED5CA3F4FC7F4CB77616427B7DD2ABC79"
                                "2015036F72FB28F296BBCAC975D62C399C047F1ABD1F51A5E6A5D"
                                "538B5A6E7B284BE71537B2A0DB9E22E3D46DC9D55A726B0B6C721"
                                "5AFC36817811E0F86405E961A5391DD48A00340C7571BA295BADE925BC546C686A4871A0E";
  bigint small, big;
  big_init(&small);
  assert(0 == big_read_string(&small, small_str));
  big_init(&big);
  assert(0 == big_read_string(&big, big_str));
  big_sub(&small, &small, &big);
  char buf[600 + 1 + 1];
  size_t olen;
  big_write_string(&small, buf, 602, &olen);
  print_test_result("Test negative result", strcmp(buf, small_minus_big) == 0, "");

  big_free(&small);
  big_free(&big);
}

void test_negative_self_subtraction() {
  const char *test_name = "Test negative self subtraction";

  const char *x1_str = "-137B22A5DC3DF61CC";
  const char *x2_str = "1554AE83C80E1992C";

  bigint x1;
  big_init(&x1);
  assert(0 == big_read_string(&x1, x2_str));

  bigint x2;
  big_init(&x2);
  assert(0 == big_read_string(&x2, x1_str));

  big_sub(&x2, &x2, &x1);

  char ans_buf[50];
  size_t ans_str_len;
  if (0 != big_write_string(&x2, ans_buf, 50, &ans_str_len)) {
    print_test_result(test_name, 0, "could not write string");
  }

  const char *expected = "-28CFD129A44C0FAF8";
  bigint bi_expected;
  big_init(&bi_expected);
  big_read_string(&bi_expected, expected);

  print_test_result(test_name,
                    ((0 == big_cmp(&bi_expected, &x2)) &&   // testing big_cmp
                     (ans_str_len == strlen(expected) + 1) &&  // expected olen
                     (strcmp(ans_buf, expected) == 0)), // expected output of write_string
                    "");
  big_free(&x1);  big_free(&x2);  big_free(&bi_expected);
}

void test_inv_mod_bug() {
  const char *test_name = "Test -0x308 - 0x113";

  const char *D_str = "-0x308";
  bigint D;
  big_init(&D);
  assert(0 == big_read_string(&D, D_str));

  const char *B_str = "-0x113";
  bigint B;
  big_init(&B);
  assert(0 == big_read_string(&B, B_str));

  big_sub(&D, &D, &B);

  char ans_buf[50];
  size_t ans_str_len;
  if (0 != big_write_string(&D, ans_buf, 50, &ans_str_len)) {
    print_test_result(test_name, 0, "could not write string");
  }

  const char *expected = "-1F5";
  bigint bi_expected;
  big_init(&bi_expected);
  big_read_string(&bi_expected, expected);

  print_test_result(test_name,
                    ((0 == big_cmp(&bi_expected, &D)) &&   // testing big_cmp
                     (ans_str_len == strlen(expected) + 1) &&  // expected olen
                     (strcmp(ans_buf, expected) == 0)), // expected output of write_string
                    "");
  big_free(&B);  big_free(&D);  big_free(&bi_expected);
}

int main() {
  printf("*** TEST BIG_SUB ***\n");
  test_sub1();
  test_self_subtraction();
  test_negative_result();
  test_negative_self_subtraction();
  test_inv_mod_bug();
  printf("\n");
}

