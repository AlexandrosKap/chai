// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include "chai.h"

int main(void) {
    printf("--- String examples\n");

    Chai_String text = chai_string_clone_str("Hello");
    printf("%s\n", text.items);
    chai_string_append_str(&text, " Snufkin!");
    printf("%s\n", text.items);
    chai_string_free(&text);

    printf("--- List examples\n");

    Chai_List_F32 numbers = chai_list_f32_new(0);
    for (int i = 0; i < 5; i += 1) {
        chai_list_f32_append(&numbers, i * 0.25f);
    }
    for (int i = 0; i < numbers.length; i += 1) {
        printf("%g\n", numbers.items[i]);
    }
    numbers.length = 0;
    for (int i = 0; i < 5; i += 1) {
        chai_list_f32_append(&numbers, i * 0.75f);
    }
    for (int i = 0; i < numbers.length; i += 1) {
        printf("%g\n", numbers.items[i]);
    }
    chai_list_f32_free(&numbers);

    return 0;
}