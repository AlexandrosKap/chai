// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#include <stdio.h>
#include "chai.h"

int main(void) {
    Chai_String text = chai_string_clone_str("Hello");

    printf("%s\n", text.items);
    chai_string_append_str(&text, " Snufkin!");
    printf("%s\n", text.items);
    chai_string_free(&text);

    return 0;
}