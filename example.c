// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include "chai.h"

void print_list_info(Chai_List *list) {
    printf("Length: %ld\n", list->length);
    printf("Capacity: %ld\n", list->capacity);
}

void print_list_i32(Chai_List_I32 *list) {
    printf("[");
    for (int i = 0; i < list->data.length; i += 1) {
        int item = *chai_list_i32_item(list, i);
        if (i != list->data.length - 1) {
            printf("%d, ", item);
        } else {
            printf("%d]\n", item);
        }
    }
    print_list_info(CHAI_CAST(Chai_List *) list);
    printf("\n");
}

int main(void) {
    printf("--- List examples\n");

    Chai_List_I32 numbers = chai_list_i32_new(0);
    for (int i = 0; i < 5; i += 1) {
        chai_list_i32_append(&numbers, i * 25);
    }
    print_list_i32(&numbers);

    chai_list_i32_clear(&numbers);
    for (int i = 0; i < 5; i += 1) {
        chai_list_i32_append(&numbers, i * 75);
    }
    print_list_i32(&numbers);

    chai_list_i32_resize(&numbers, 32);
    chai_list_i32_fill(&numbers, 1);
    print_list_i32(&numbers);

    chai_list_i32_resize(&numbers, 4);
    chai_list_i32_insert(&numbers, 0, 0);
    print_list_i32(&numbers);

    chai_list_i32_remove(&numbers, 0);
    chai_list_i32_resize(&numbers, 5);
    chai_list_i32_shrink(&numbers);
    print_list_i32(&numbers);

    chai_list_i32_free(&numbers);

    printf("--- String examples\n");
    printf("TODO: Add string examples.\n");

/*
    Chai_String text = chai_string_copy_str("Hello");
    printf("%s\n", (char*)text.data.items);
    chai_string_append_str(&text, " Snufkin!");
    printf("%s\n", (char*)text.data.items);
    chai_string_free(&text);
*/

    return 0;
}