// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#define CHAI_IMPLEMENTATION

#include "chai.h"
#include <assert.h>
#include <stdio.h>

#define TEST(body) assert(body)
#define TODO(msg) assert(msg && 0)

CHAI_CREATE_LIST_TYPE(int, Numbers, numbers)

void test_utils() {
    TEST(chai_is_upper(' ') == false);
    TEST(chai_is_upper('9') == false);
    TEST(chai_is_upper('a') == false);
    TEST(chai_is_upper('A') == true);
    TEST(chai_is_upper('z') == false);
    TEST(chai_is_upper('Z') == true);

    TEST(chai_is_lower(' ') == false);
    TEST(chai_is_lower('9') == false);
    TEST(chai_is_lower('a') == true);
    TEST(chai_is_lower('A') == false);
    TEST(chai_is_lower('z') == true);
    TEST(chai_is_lower('Z') == false);

    TEST(chai_is_alpha(' ') == false);
    TEST(chai_is_alpha('9') == false);
    TEST(chai_is_alpha('a') == true);
    TEST(chai_is_alpha('A') == true);
    TEST(chai_is_alpha('z') == true);
    TEST(chai_is_alpha('Z') == true);

    TEST(chai_is_space(' ') == true);
    TEST(chai_is_space('9') == false);
    TEST(chai_is_space('a') == false);
    TEST(chai_is_space('A') == false);
    TEST(chai_is_space('z') == false);
    TEST(chai_is_space('Z') == false);

    TEST(chai_is_digit(' ') == false);
    TEST(chai_is_digit('9') == true);
    TEST(chai_is_digit('a') == false);
    TEST(chai_is_digit('A') == false);
    TEST(chai_is_digit('z') == false);
    TEST(chai_is_digit('Z') == false);

    TEST(chai_to_upper(' ') == ' ');
    TEST(chai_to_upper('9') == '9');
    TEST(chai_to_upper('a') == 'A');
    TEST(chai_to_upper('A') == 'A');
    TEST(chai_to_upper('z') == 'Z');
    TEST(chai_to_upper('Z') == 'Z');

    TEST(chai_to_lower(' ') == ' ');
    TEST(chai_to_lower('9') == '9');
    TEST(chai_to_lower('a') == 'a');
    TEST(chai_to_lower('A') == 'a');
    TEST(chai_to_lower('z') == 'z');
    TEST(chai_to_lower('Z') == 'z');

    TEST(chai_to_digit(' ') == -1);
    TEST(chai_to_digit('9') == 9);
    TEST(chai_to_digit('a') == -1);
    TEST(chai_to_digit('A') == -1);
    TEST(chai_to_digit('z') == -1);
    TEST(chai_to_digit('Z') == -1);

    TEST(chai_find_list_capacity(0) == CHAI_LIST_START_CAPACITY);
    TEST(chai_find_list_capacity(CHAI_LIST_START_CAPACITY) == CHAI_LIST_START_CAPACITY);
    TEST(chai_find_list_capacity(CHAI_LIST_START_CAPACITY + 1) == CHAI_LIST_START_CAPACITY * 2);
}

void test_mem() {
    int a = 69;
    int b = 420;

    chai_mem_set(&a, 0, sizeof(a));
    TEST(a == 0);

    chai_mem_copy(&a, &b, sizeof(a));
    TEST(a == b);

    TEST(chai_mem_equals(&a, &b, sizeof(a)) == true);
}

void test_view() {
    const char *str = "Hello.";

    Chai_View view = chai_view_new(str);
    TEST(view.items == str);
    TEST(view.count == 6);

    Chai_View temp;

    temp = chai_view_from(view, 0, view.count);
    TEST(temp.items[0] == view.items[0]);
    TEST(temp.items[temp.count - 1] == view.items[view.count - 1]);
    temp = chai_view_from(view, 0, view.count - 1);
    TEST(temp.items[0] == view.items[0]);
    TEST(temp.items[temp.count - 1] != view.items[view.count - 1]);

    temp = chai_view_from(view, 0, 0);
    TEST(temp.count == 0);
    temp = chai_view_from(view, view.count, view.count);
    TEST(temp.count == 0);

    TEST(chai_view_item(view, 0) != NULL);
    TEST(chai_view_item(view, view.count - 1) != NULL);
    TEST(chai_view_item(view, view.count) == NULL);

    temp = chai_view_new("");
    TEST(chai_view_equals(view, temp) == false);
    temp = view;
    TEST(chai_view_equals(view, temp) == true);
    
    TEST(chai_view_starts_with(view, view) == true);
    TEST(chai_view_ends_with(view, view) == true);
    TEST(chai_view_count(view, view) == 1);
    TEST(chai_view_find_left(view, view) == 0);
    TEST(chai_view_find_right(view, view) == 0);
    TEST(chai_view_trim(chai_view_new("  Hi. ")).count == 3);

    char buffer_str[128];
    temp = chai_view_new("Make me a null-terminated string.");
    TEST(chai_view_to_str(temp, buffer_str) == true);
    TEST(buffer_str[0] == temp.items[0]);
    TEST(buffer_str[temp.count - 1] == temp.items[temp.count - 1]);
    TEST(buffer_str[temp.count] == '\0');

    int buffer_int;
    temp = chai_view_new("420");
    TEST(chai_view_to_int(temp, &buffer_int) == true);
    TEST(buffer_int == 420);
    temp = chai_view_new("+420");
    TEST(chai_view_to_int(temp, &buffer_int) == true);
    TEST(buffer_int == 420);
    temp = chai_view_new("-420");
    TEST(chai_view_to_int(temp, &buffer_int) == true);
    TEST(buffer_int == -420);

    float buffer_float;
    temp = chai_view_new("69.420");
    TEST(chai_view_to_float(temp, &buffer_float) == true);
    TEST(buffer_float == 69.420f);
    temp = chai_view_new("+69.420");
    TEST(chai_view_to_float(temp, &buffer_float) == true);
    TEST(buffer_float == 69.420f);
    temp = chai_view_new("-69.420");
    TEST(chai_view_to_float(temp, &buffer_float) == true);
    TEST(buffer_float == -69.420f);
}

void test_list() {
    TODO("Write list test.");
}

int main() {
    test_utils();
    test_mem();
    test_view();
    test_list();
    printf("OK!\n");
    return 0;
}
