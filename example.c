// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#define CHAI_IMPLEMENTATION

#include "chai.h"
#include <stdio.h>

CHAI_MAKE_LIST(Numbers, int, numbers)

void print_view(Chai_View view) {
    printf("\"");
    for (size_t i = 0; i < view.count; i += 1) {
        char item = *chai_view_item(view, i);
        printf("%c", item);
    }
    printf("\"\n");
}

void print_list_info(Chai_List *list) {
    printf("Count: %ld\n", list->count);
    printf("Capacity: %ld\n", list->capacity);
}

void print_text(Chai_String *text) {
    printf("\"%s\"\n", (const char *) text->data.items);
    print_list_info(&text->data);
}

void print_numbers(Numbers *numbers) {
    printf("[");
    for (size_t i = 0; i < numbers->data.count; i += 1) {
        int item = *numbers_item(numbers, i);
        if (i != numbers->data.count - 1) {
            printf("%d, ", item);
        } else {
            printf("%d]\n", item);
        }
    }
    print_list_info(&numbers->data);
}

int main(void) {
    printf("# View example\n");

    Chai_View view = chai_view_new("Orange Carrot");
    print_view(view);
    print_view(chai_view_from_view(view, 0, 6));
    print_view(chai_view_from_view(view, 7, view.count));
    print_view(chai_view_from_view(view, view.count, view.count));
    print_view(chai_view_trim_left(chai_view_new("    One.")));
    print_view(chai_view_trim_right(chai_view_new("Two.    ")));
    print_view(chai_view_trim(chai_view_new("   Three.  ")));
    print_view(chai_view_trim(chai_view_new("     ")));

    printf("equals             = %d\n", chai_view_equals(view, view));
    printf("equals_ignore_case = %d\n", chai_view_equals_ignore_case(view, chai_view_new("orange carrot")));
    printf("starts_with        = %d\n", chai_view_starts_with(view, chai_view_new("Orange")));
    printf("ends_with          = %d\n", chai_view_ends_with(view, chai_view_new("Carrot")));
    printf("count              = %d\n", chai_view_count(view, chai_view_new("a")) == 2);
    printf("find_left          = %d\n", chai_view_find_left(view, chai_view_new("a")) == 2);
    printf("find_right         = %d\n", chai_view_find_right(view, chai_view_new("a")) == 8);

    printf("# List example\n");

    Numbers numbers = numbers_new(0);
    for (int i = 0; i < 5; i += 1) {
        numbers_append(&numbers, i * 25);
    }
    print_numbers(&numbers);

    numbers_clear(&numbers);
    for (int i = 0; i < 5; i += 1) {
        numbers_append(&numbers, i * 75);
    }
    print_numbers(&numbers);

    numbers_resize(&numbers, 32);
    numbers_fill(&numbers, 1);
    print_numbers(&numbers);

    numbers_resize(&numbers, 4);
    numbers_insert(&numbers, 0, 0);
    print_numbers(&numbers);

    numbers_remove(&numbers, 0);
    numbers_resize(&numbers, 5);
    numbers_shrink(&numbers);
    print_numbers(&numbers);

    numbers_free(&numbers);

    printf("# String example\n");

    Chai_String text = chai_string_copy_str("Hello");
    chai_string_append_str(&text, " Snufkin!!!");
    print_text(&text);

    chai_string_free(&text);

    return 0;
}
