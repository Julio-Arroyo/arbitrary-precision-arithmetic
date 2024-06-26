#ifndef TEST_BIGINT_H
#define TEST_BIGINT_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <string.h>
#include <stdio.h>

void print_test_result(const char *test_name, int passed, const char *extra_info) {
  printf("%s: %s%s", test_name, passed ? ANSI_COLOR_GREEN : ANSI_COLOR_RED, passed ? "PASSED" : "FAILED");
  printf(ANSI_COLOR_RESET "\n");
  if (strlen(extra_info) > 0) {
    printf("\t %s%s%s\n", ANSI_COLOR_YELLOW, extra_info, ANSI_COLOR_RESET);
  }
}

#endif

