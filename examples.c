// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#define CHAI_IMPLEMENTATION // This will insert the implementation of chai into this file.
#define PRINT_SPACE "  "    // This is used for pushing the printed values to the right.

#include <stdio.h>
#include "chai.h"

/// Creates a new list type.
/// The first argument is the type of the list item.
/// The second argument is the name of the list.
/// The third argument is the prefix that each procedure associated with the list will use.
CHAI_CREATE_LIST(int, Numbers, numbers)

void print_view(Chai_View view) {
    printf("%s\"", PRINT_SPACE);
    for (int i = 0; i < view.count; i += 1) {
        printf("%c", view.items[i]);
    }
    printf("\"\n");
}

void print_numbers(Numbers numbers) {
    printf("%s(capacity: %ld) ", PRINT_SPACE, numbers.capacity);
    printf("[");
    for (int i = 0; i < numbers.count; i += 1) {
        if (i != numbers.count - 1) {
            printf("%d, ", numbers.items[i]);
        } else {
            printf("%d]\n", numbers.items[i]);
        }
    }
}

int main(void) {
    printf("# View Example\n");
    Chai_View temp;
    Chai_View view = chai_view_new("orange carrot");
    print_view(view);
    print_view(chai_view_from(view, 0, view.count));
    print_view(chai_view_from(view, view.count, view.count));
    print_view(chai_view_trim_left(chai_view_new("    one.")));
    print_view(chai_view_trim_right(chai_view_new("two.    ")));
    print_view(chai_view_trim(chai_view_new("   three.  ")));
    print_view(chai_view_trim(chai_view_new("     ")));

    temp = view;
    chai_view_skip_over(&temp, chai_view_new("orange "));
    print_view(temp);
    chai_view_skip_over(&temp, chai_view_new("apple "));
    print_view(temp);
    
    temp = view;
    chai_view_skip_until(&temp, chai_view_new(" "));
    print_view(temp);
    chai_view_skip_until(&temp, chai_view_new(" "));
    print_view(temp);

    Chai_View csv = chai_view_new("1,2,3\na,b,c\ni,j,k\n");
    print_view(chai_view_skip_line(&csv));
    print_view(chai_view_skip_line(&csv));
    print_view(chai_view_skip_line(&csv));
    print_view(chai_view_skip_line(&csv));

    Chai_View cmd = chai_view_new("rm -rf ohno");
    print_view(chai_view_skip_arg(&cmd));
    print_view(chai_view_skip_arg(&cmd));
    print_view(chai_view_skip_arg(&cmd));
    print_view(chai_view_skip_arg(&cmd));

    printf("\n# List Example\n");
    Numbers numbers = numbers_new(0);
    for (int i = 0; i < 5; i += 1) {
        numbers_append(&numbers, i * 25);
    }
    print_numbers(numbers);

    numbers_clear(&numbers);
    for (int i = 0; i < 5; i += 1) {
        numbers_append(&numbers, i * 75);
    }
    print_numbers(numbers);

    numbers_resize(&numbers, 33);
    numbers_resize(&numbers, 32);
    numbers_shrink(&numbers);
    numbers_fill(&numbers, 1);
    print_numbers(numbers);

    numbers_resize(&numbers, 4);
    numbers_insert(&numbers, 0, 0);
    print_numbers(numbers);

    numbers_remove(&numbers, 0);
    numbers_resize(&numbers, 5);
    print_numbers(numbers);
    
    numbers_free(&numbers);
    return 0;
}
