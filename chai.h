// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

// TODO(AlexandrosKap): Add view struct for strings.
// TODO(AlexandrosKap): Write macros for malloc, realloc, free, assert.
// TODO(AlexandrosKap): Write macro procedure generator for simple lists.

#ifndef CHAI_HEADER
#define CHAI_HEADER

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define CHAI_START_CAPACITY 16
#define CHAI_CAST(type) (type)
#define CHAI_TODO(message) assert("TODO" && message && 0);
#define CHAI_PANIC(message) assert("ERROR" && message && 0)
#define CHAI_PANIC_INDEX() CHAI_PANIC("Index is out of range.")

typedef struct {
    void *items;
    size_t length;
    size_t capacity;
    size_t item_size;
} Chai_List;

typedef struct {
    Chai_List data;
} Chai_List_I32;

typedef struct {
    Chai_List data;
} Chai_List_F32;

typedef struct {
    Chai_List data;
} Chai_String;

// --- Definitions

size_t chai_find_capacity(size_t length);

Chai_List chai_list_new(size_t length, size_t item_size);
Chai_List chai_list_copy(Chai_List other);
void * chai_list_item(Chai_List *list, size_t index);
void chai_list_fill(Chai_List *list, void *item);
void chai_list_append(Chai_List *list, void *item);
void chai_list_insert(Chai_List *list, size_t index, void *item);
void chai_list_remove(Chai_List *list, size_t index);
void chai_list_remove_swap(Chai_List *list, size_t index);
void chai_list_resize(Chai_List *list, size_t length);
void chai_list_reserve(Chai_List *list, size_t additional);
void chai_list_shrink(Chai_List *list);
void chai_list_clear(Chai_List *list);
void chai_list_free(Chai_List *list);

Chai_List_I32 chai_list_i32_new(size_t length);
Chai_List_I32 chai_list_i32_copy(Chai_List_I32 other);
int * chai_list_i32_item(Chai_List_I32 *list, size_t index);
void chai_list_i32_fill(Chai_List_I32 *list, int item);
void chai_list_i32_append(Chai_List_I32 *list, int item);
void chai_list_i32_insert(Chai_List_I32 *list, size_t index, int item);
void chai_list_i32_remove(Chai_List_I32 *list, size_t index);
void chai_list_i32_remove_swap(Chai_List_I32 *list, size_t index);
void chai_list_i32_resize(Chai_List_I32 *list, size_t length);
void chai_list_i32_reserve(Chai_List_I32 *list, size_t additional);
void chai_list_i32_shrink(Chai_List_I32 *list);
void chai_list_i32_clear(Chai_List_I32 *list);
void chai_list_i32_free(Chai_List_I32 *list);

Chai_List_F32 chai_list_f32_new(size_t length);
Chai_List_F32 chai_list_f32_copy(Chai_List_F32 other);
float * chai_list_f32_item(Chai_List_F32 *list, size_t index);
void chai_list_f32_fill(Chai_List_F32 *list, float item);
void chai_list_f32_append(Chai_List_F32 *list, float item);
void chai_list_f32_insert(Chai_List_F32 *list, size_t index, float item);
void chai_list_f32_remove(Chai_List_F32 *list, size_t index);
void chai_list_f32_remove_swap(Chai_List_F32 *list, size_t index);
void chai_list_f32_resize(Chai_List_F32 *list, size_t length);
void chai_list_f32_reserve(Chai_List_F32 *list, size_t additional);
void chai_list_f32_shrink(Chai_List_F32 *list);
void chai_list_f32_clear(Chai_List_F32 *list);
void chai_list_f32_free(Chai_List_F32 *list);

Chai_String chai_string_new(size_t length);
Chai_String chai_string_copy(Chai_String other);
char * chai_string_item(Chai_String *list, size_t index);
void chai_string_fill(Chai_String *list, const char item);
void chai_string_append(Chai_String *list, const char item);
void chai_string_insert(Chai_String *list, size_t index, const char item);
void chai_string_remove(Chai_String *list, size_t index);
void chai_string_remove_swap(Chai_String *list, size_t index);
void chai_string_resize(Chai_String *list, size_t length);
void chai_string_reserve(Chai_String *list, size_t additional);
void chai_string_shrink(Chai_String *list);
void chai_string_clear(Chai_String *list);
void chai_string_free(Chai_String *list);
Chai_String chai_string_copy_str(const char *str);
void chai_string_append_str(Chai_String *list, const char *str);
void chai_string_insert_str(Chai_String *list, size_t index, const char *str);

// --- Implementations

size_t chai_find_capacity(size_t length) {
    size_t result = CHAI_START_CAPACITY;
    while (result < length) {
        result *= 2;
    }
    return result;
}

Chai_List chai_list_new(size_t length, size_t item_size) {
    Chai_List result;
    if (length == 0) {
        result.items = NULL;
        result.length = 0;
        result.capacity = 0;
        result.item_size = item_size;
    } else {
        size_t capacity = chai_find_capacity(length);
        result.items = malloc(capacity * item_size);
        result.length = length;
        result.capacity = capacity;
        result.item_size = item_size;
        memset(result.items, 0, capacity * item_size);
    }
    return result;
}

Chai_List chai_list_copy(Chai_List other) {
    Chai_List result;
    if (other.capacity == 0) {
        result.items = NULL;
        result.length = 0;
        result.capacity = 0;
        result.item_size = other.item_size;
    } else {
        result.items = malloc(other.capacity * other.item_size);
        result.length = other.length;
        result.capacity = other.capacity;
        result.item_size = other.item_size;
        memcpy(result.items, other.items, other.capacity * other.item_size);
    }
    return result;
}

void * chai_list_item(Chai_List *list, size_t index) {
    return (CHAI_CAST(char *) list->items) + index * list->item_size;
}

void chai_list_fill(Chai_List *list, void *item) {
    for (size_t i = 0; i < list->length; i += 1) {
        memcpy(chai_list_item(list, i), item, list->item_size);
    }
}

void chai_list_append(Chai_List *list, void *item) {
    list->length += 1;
    if (list->length > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->length);
        list->items = realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    memcpy(chai_list_item(list, list->length - 1), item, list->item_size);
}

void chai_list_insert(Chai_List *list, size_t index, void *item) {
    list->length += 1;
    if (list->length > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->length);
        list->items = realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    for (size_t i = list->length - 1; i > index; i -= 1) {
        memcpy(chai_list_item(list, i), chai_list_item(list, i - 1), list->item_size);
    }
    memcpy(chai_list_item(list, index), item, list->item_size);
}

void chai_list_remove(Chai_List *list, size_t index) {
    if (list->length == 0) {
        return;
    }
    for (size_t i = index; i < list->length - 1; i += 1) {
        memcpy(chai_list_item(list, i), chai_list_item(list, i + 1), list->item_size);
    }
    list->length -= 1;
}

void chai_list_remove_swap(Chai_List *list, size_t index) {
    if (list->length == 0) {
        return;
    }
    memcpy(chai_list_item(list, index), chai_list_item(list, list->length - 1), list->item_size);
    list->length -= 1;
}

void chai_list_resize(Chai_List *list, size_t length) {
    size_t old_length = list->length;
    list->length = length;
    if (list->length > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->length);
        list->items = realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    if (list->length > old_length) {
        memset(chai_list_item(list, old_length), 0, (list->length - old_length) * list->item_size);
    }
}

void chai_list_reserve(Chai_List *list, size_t additional) {
    size_t temp_length = list->length;
    list->length = list->length + additional;
    if (list->length > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->length);
        list->items = realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    list->length = temp_length;
}

void chai_list_shrink(Chai_List *list) {
    size_t new_capacity = chai_find_capacity(list->length);
    if (new_capacity != list->capacity) {
        list->items = realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
}

void chai_list_clear(Chai_List *list) {
    chai_list_resize(list, 0);
}

void chai_list_free(Chai_List *list) {
    if (list->items != NULL) {
        free(list->items);
        list->items = NULL;
        list->length = 0;
        list->capacity = 0;
    }
}

Chai_List_I32 chai_list_i32_new(size_t length) {
    Chai_List_I32 result;
    result.data = chai_list_new(length, sizeof(int));
    return result;
}

Chai_List_I32 chai_list_i32_copy(Chai_List_I32 other) {
    Chai_List_I32 result;
    result.data = chai_list_copy(other.data);
    return result;
}

int * chai_list_i32_item(Chai_List_I32 *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return NULL;
    }
    return CHAI_CAST(int *) chai_list_item(&list->data, index);
}

void chai_list_i32_fill(Chai_List_I32 *list, int item) {
    chai_list_fill(&list->data, &item);
}

void chai_list_i32_append(Chai_List_I32 *list, int item) {
    chai_list_append(&list->data, &item);
}

void chai_list_i32_insert(Chai_List_I32 *list, size_t index, int item) {
    if (index > list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_insert(&list->data, index, &item);
}

void chai_list_i32_remove(Chai_List_I32 *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove(&list->data, index);
}

void chai_list_i32_remove_swap(Chai_List_I32 *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove_swap(&list->data, index);
}

void chai_list_i32_resize(Chai_List_I32 *list, size_t length) {
    chai_list_resize(&list->data, length);
}

void chai_list_i32_reserve(Chai_List_I32 *list, size_t additional) {
    chai_list_reserve(&list->data, additional);
}

void chai_list_i32_shrink(Chai_List_I32 *list) {
    chai_list_shrink(&list->data);
}

void chai_list_i32_clear(Chai_List_I32 *list) {
    chai_list_clear(&list->data);
}

void chai_list_i32_free(Chai_List_I32 *list) {
    chai_list_free(&list->data);
}

Chai_List_F32 chai_list_f32_new(size_t length) {
    Chai_List_F32 result;
    result.data = chai_list_new(length, sizeof(float));
    return result;
}

Chai_List_F32 chai_list_f32_copy(Chai_List_F32 other) {
    Chai_List_F32 result;
    result.data = chai_list_copy(other.data);
    return result;
}

float * chai_list_f32_item(Chai_List_F32 *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return NULL;
    }
    return CHAI_CAST(float *) chai_list_item(&list->data, index);
}

void chai_list_f32_fill(Chai_List_F32 *list, float item) {
    chai_list_fill(&list->data, &item);
}

void chai_list_f32_append(Chai_List_F32 *list, float item) {
    chai_list_append(&list->data, &item);
}

void chai_list_f32_insert(Chai_List_F32 *list, size_t index, float item) {
    if (index > list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_insert(&list->data, index, &item);
}

void chai_list_f32_remove(Chai_List_F32 *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove(&list->data, index);
}

void chai_list_f32_remove_swap(Chai_List_F32 *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove_swap(&list->data, index);
}

void chai_list_f32_resize(Chai_List_F32 *list, size_t length) {
    chai_list_resize(&list->data, length);
}

void chai_list_f32_reserve(Chai_List_F32 *list, size_t additional) {
    chai_list_reserve(&list->data, additional);
}

void chai_list_f32_shrink(Chai_List_F32 *list) {
    chai_list_shrink(&list->data);
}

void chai_list_f32_clear(Chai_List_F32 *list) {
    chai_list_clear(&list->data);
}

void chai_list_f32_free(Chai_List_F32 *list) {
    chai_list_free(&list->data);
}

Chai_String chai_string_new(size_t length) {
    Chai_String result;
    result.data = chai_list_new(length + 1, sizeof(char));
    result.data.length -= 1;
    return result;
}

Chai_String chai_string_copy(Chai_String other) {
    Chai_String result;
    result.data = chai_list_copy(other.data);
    return result;
}

char * chai_string_item(Chai_String *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return NULL;
    }
    return CHAI_CAST(char *) chai_list_item(&list->data, index);
}

void chai_string_fill(Chai_String *list, const char item) {
    chai_list_fill(&list->data, &item);
}

void chai_string_append(Chai_String *list, const char item) {
    const char cute_zero = '\0';
    chai_list_append(&list->data, CHAI_CAST(char *) &item);
    chai_list_append(&list->data, CHAI_CAST(char *) &cute_zero);
    list->data.length -= 1;
}

void chai_string_insert(Chai_String *list, size_t index, const char item) {
    if (index > list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    if (index == list->data.length) {
        const char cute_zero = '\0';
        chai_list_append(&list->data, CHAI_CAST(char *) &item);
        chai_list_append(&list->data, CHAI_CAST(char *) &cute_zero);
        list->data.length -= 1;
    } else {
        chai_list_insert(&list->data, index, &item);
    }
}

void chai_string_remove(Chai_String *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove(&list->data, index);
}

void chai_string_remove_swap(Chai_String *list, size_t index) {
    if (index >= list->data.length) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove_swap(&list->data, index);
}

void chai_string_resize(Chai_String *list, size_t length) {
    chai_list_resize(&list->data, length + 1);
    *(CHAI_CAST(char *) chai_list_item(&list->data, length)) = '\0';
    list->data.length -= 1;
}

void chai_string_reserve(Chai_String *list, size_t additional) {
    chai_list_reserve(&list->data, additional + 1);
}

void chai_string_shrink(Chai_String *list) {
    chai_list_shrink(&list->data);
}

void chai_string_clear(Chai_String *list) {
    chai_list_clear(&list->data);
    chai_list_resize(&list->data, 1);
    list->data.length -= 1;
}

void chai_string_free(Chai_String *list) {
    chai_list_free(&list->data);
}

Chai_String chai_string_copy_str(const char *str) {
    size_t str_length = strlen(str);
    Chai_String result;
    result.data = chai_list_new(str_length + 1, sizeof(char));
    result.data.length -= 1;
    for (size_t i = 0; i < str_length; i += 1) {
        *(CHAI_CAST(char *) chai_list_item(&result.data, i)) = str[i];
    }
    return result;
}

void chai_string_append_str(Chai_String *list, const char *str) {
    while (*str != '\0') {
        chai_string_append(list, *str);
        str += 1;
    }
}

void chai_string_insert_str(Chai_String *list, size_t index, const char *str) {
    while (*str != '\0') {
        chai_string_insert(list, index, *str);
        index += 1;
        str += 1;
    }
}

#endif // CHAI_HEADER
