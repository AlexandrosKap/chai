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
    for (int i = 0; i < numbers.data.length; i += 1) {
        int item = *chai_list_i32_item(&numbers, i);
        if (i != numbers.data.length - 1) {
            printf("%d, ", item);
        } else {
            printf("%d]\n", item);
        }
    }
    print_list_info(numbers.data);
    printf("\n");
}

void print_text(Chai_String text) {
    printf("\"%s\"\n", (char *) text.data.items);
    print_list_info(text.data);
    printf("\n");
}

int main(void) {
    printf("--- List example\n\n");

    Chai_List_I32 numbers = chai_list_i32_new(0);
    for (int i = 0; i < 5; i += 1) {
        chai_list_i32_append(&numbers, i * 25);
    }
    print_numbers(numbers);

    chai_list_i32_clear(&numbers);
    for (int i = 0; i < 5; i += 1) {
        chai_list_i32_append(&numbers, i * 75);
    }
    print_numbers(numbers);

    chai_list_i32_resize(&numbers, 32);
    chai_list_i32_fill(&numbers, 1);
    print_numbers(numbers);

    chai_list_i32_resize(&numbers, 4);
    chai_list_i32_insert(&numbers, 0, 0);
    print_numbers(numbers);

    chai_list_i32_remove(&numbers, 0);
    chai_list_i32_resize(&numbers, 5);
    chai_list_i32_shrink(&numbers);
    print_numbers(numbers);

    chai_list_i32_free(&numbers);

    printf("--- String example\n\n");

    Chai_String text = chai_string_copy_str("Hello");
    print_text(text);

    chai_string_append_str(&text, " Snufkin!");
    print_text(text);

    chai_string_free(&text);

    return 0;
}
