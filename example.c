// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include "chai.h"

void print_list_info(Chai_List list) {
    printf("Length: %ld\n", list.length);
    printf("Capacity: %ld\n", list.capacity);
}

void print_numbers(Chai_List_I32 numbers) {
    printf("[");
    for (size_t i = 0; i < numbers.data.length; i += 1) {
        int item = *chai_list_i32_item(numbers, i);
        if (i != numbers.data.length - 1) {
            printf("%d, ", item);
        } else {
            printf("%d]\n", item);
        }
    }
    print_list_info(numbers.data);
}

void print_text(Chai_String text) {
    printf("\"%s\"\n", (char *) text.data.items);
    print_list_info(text.data);
}

void print_view(Chai_View view) {
    printf("\"");
    for (size_t i = 0; i < view.length; i += 1) {
        char item = *chai_view_item(view, i);
        printf("%c", item);
    }
    printf("\"\n");
}

int main(void) {
    printf("--- View example\n");

    printf("\n");
    Chai_View view = chai_view_new("Orange Carrot");
    print_view(view);
    print_view(chai_view_from_view(view, 0, 6));
    print_view(chai_view_from_view(view, 7, view.length));
    print_view(chai_view_from_view(view, view.length, view.length));
    print_view(chai_view_trim_left(chai_view_new("    One.")));
    print_view(chai_view_trim_right(chai_view_new("Two.    ")));
    print_view(chai_view_trim(chai_view_new("   Three.  ")));
    print_view(chai_view_trim(chai_view_new("     ")));

    printf("\n");
    printf("equals             = %d\n", chai_view_equals(view, view));
    printf("equals_ignore_case = %d\n", chai_view_equals_ignore_case(view, chai_view_new("orange carrot")));
    printf("starts_with        = %d\n", chai_view_starts_with(view, chai_view_new("Orange")));
    printf("ends_with          = %d\n", chai_view_ends_with(view, chai_view_new("Carrot")));
    printf("count              = %d\n", chai_view_count(view, chai_view_new("a")) == 2);
    printf("find_left          = %d\n", chai_view_find_left(view, chai_view_new("a")) == 2);
    printf("find_right         = %d\n", chai_view_find_right(view, chai_view_new("a")) == 8);

    printf("\n");
    printf("--- List example\n");

    printf("\n");
    Chai_List_I32 numbers = chai_list_i32_new(0);
    for (int i = 0; i < 5; i += 1) {
        chai_list_i32_append(&numbers, i * 25);
    }
    print_numbers(numbers);

    printf("\n");
    chai_list_i32_clear(&numbers);
    for (int i = 0; i < 5; i += 1) {
        chai_list_i32_append(&numbers, i * 75);
    }
    print_numbers(numbers);

    printf("\n");
    chai_list_i32_resize(&numbers, 32);
    chai_list_i32_fill(&numbers, 1);
    print_numbers(numbers);

    printf("\n");
    chai_list_i32_resize(&numbers, 4);
    chai_list_i32_insert(&numbers, 0, 0);
    print_numbers(numbers);

    printf("\n");
    chai_list_i32_remove(&numbers, 0);
    chai_list_i32_resize(&numbers, 5);
    chai_list_i32_shrink(&numbers);
    print_numbers(numbers);

    chai_list_i32_free(&numbers);

    printf("\n");
    printf("--- String example\n");

    printf("\n");
    Chai_String text = chai_string_copy_str("Hello");
    chai_string_append_str(&text, " Snufkin!!!");
    print_text(text);

    chai_string_free(&text);

    return 0;
}
