// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#ifndef CHAI_HEADER
#define CHAI_HEADER

#ifndef CHAI_NO_STD
#include <stdbool.h>
#include <stdlib.h>
#endif // CHAI_NO_STD

#ifdef CHAI_BASIC_TYPES
typedef signed char        i8;
typedef short              i16;
typedef int                i32;
typedef long long          i64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef float              f32;
typedef double             f64;
typedef size_t             su64;
typedef ssize_t            si64;
#endif // CHAI_BASIC_TYPES

#ifndef CHAI_CAPACITY_UNIT
#define CHAI_CAPACITY_UNIT 32
#endif // CHAI_CAPACITY_UNIT

#define CHAI_CAST(type) (type)

typedef struct {
    char *items;
    size_t length;
    size_t capacity;
} Chai_String;

typedef struct {
    int *items;
    size_t length;
    size_t capacity;
} Chai_List_I32;

typedef struct {
    float *items;
    size_t length;
    size_t capacity;
} Chai_List_F32;

// --- List Macros

// Dependencies:
// * proc: calloc
// * proc: realloc
// * proc: chai_calculate_capacity

#define CHAI_GEN_IMP_LIST_NEW(Type_List, Type_Item, value_length)                  \
    Type_List result;                                                              \
    do {                                                                           \
        size_t capacity = chai_calculate_capacity(value_length);                   \
        result.items = CHAI_CAST(Type_Item *) calloc(capacity, sizeof(Type_Item)); \
        result.length = value_length;                                              \
        result.capacity = capacity;                                                \
    } while (0)                                                                    \

#define CHAI_GEN_IMP_LIST_EMPTY(Type_List, Type_Item, value_length) \
    CHAI_GEN_IMP_LIST_NEW(Type_List, Type_Item, value_length);      \
    do {                                                            \
        result.length = 0;                                          \
    } while (0)                                                     \

#define CHAI_GEN_IMP_LIST_CLONE(Type_List, Type_Item, value_other)   \
    CHAI_GEN_IMP_LIST_NEW(Type_List, Type_Item, value_other.length); \
    do {                                                             \
        for (size_t i = 0; i < value_other.length; i += 1) {         \
            result.items[i] = value_other.items[i];                  \
        }                                                            \
    } while (0)                                                      \

#define CHAI_GEN_IMP_LIST_APPEND(Type_List, Type_Item, value_list, value_item)                                   \
    do {                                                                                                         \
        value_list->length += 1;                                                                                 \
        if (value_list->length > value_list->capacity) {                                                         \
            size_t capacity = chai_calculate_capacity(value_list->length);                                       \
            value_list->items = CHAI_CAST(Type_Item *) realloc(value_list->items, capacity * sizeof(Type_Item)); \
            value_list->capacity = capacity;                                                                     \
        }                                                                                                        \
        value_list->items[value_list->length - 1] = value_item;                                                  \
    } while (0)                                                                                                  \

#define CHAI_GEN_IMP_LIST_FREE(value_list) \
    do {                                   \
        free(value_list->items);           \
        value_list->items = NULL;          \
        value_list->length = 0;            \
        value_list->capacity = 0;          \
    } while (0)                            \

// --- Definitions

size_t chai_calculate_capacity(size_t length);

Chai_String chai_string_new(size_t length);
Chai_String chai_string_empty(size_t length);
Chai_String chai_string_clone(const Chai_String other);
Chai_String chai_string_clone_str(const char *str);
void chai_string_append(Chai_String *list, const char item);
void chai_string_append_str(Chai_String *list, const char *str);
void chai_string_free(Chai_String *list);

Chai_List_I32 chai_list_i32_new(size_t length);
Chai_List_I32 chai_list_i32_empty(size_t length);
Chai_List_I32 chai_list_i32_clone(const Chai_List_I32 other);
void chai_list_i32_append(Chai_List_I32 *list, const char item);
void chai_list_i32_free(Chai_List_I32 *list);

Chai_List_F32 chai_list_f32_new(size_t length);
Chai_List_F32 chai_list_f32_empty(size_t length);
Chai_List_F32 chai_list_f32_clone(const Chai_List_F32 other);
void chai_list_f32_append(Chai_List_F32 *list, const char item);
void chai_list_f32_free(Chai_List_F32 *list);

// --- Implementations

size_t chai_calculate_capacity(size_t length) {
    size_t result = CHAI_CAPACITY_UNIT;
    while (result < length) {
        result += CHAI_CAPACITY_UNIT;
    }
    return result;
}

Chai_String chai_string_new(size_t length) {
    CHAI_GEN_IMP_LIST_NEW(Chai_String, char, length + 1);
    result.items[result.length - 1] = '\0';
    result.length -= 1;
    return result;
}

Chai_String chai_string_empty(size_t length) {
    Chai_String result = chai_string_new(length);
    result.length = 0;
    return result;
}

Chai_String chai_string_clone(const Chai_String other) {
    Chai_String result = chai_string_new(other.length);
    for (size_t i = 0; i < other.length; i += 1) {
        result.items[i] = other.items[i];
    }
    return result;
}

Chai_String chai_string_clone_str(const char *str) {
    Chai_String result = chai_string_empty(0);
    chai_string_append_str(&result, str);
    return result;
}

void chai_string_append(Chai_String *list, char item) {
    CHAI_GEN_IMP_LIST_APPEND(Chai_String, char, list, item);
    CHAI_GEN_IMP_LIST_APPEND(Chai_String, char, list, '\0');
    list->length -= 1;
}

void chai_string_append_str(Chai_String *list, const char *str) {
    while (*str != '\0') {
        chai_string_append(list, *str);
        str += 1;
    }
}

void chai_string_free(Chai_String *list) {
    CHAI_GEN_IMP_LIST_FREE(list);
}

Chai_List_I32 chai_list_i32_new(size_t length) {
    CHAI_GEN_IMP_LIST_NEW(Chai_List_I32, int, length);
    return result;
}

Chai_List_I32 chai_list_i32_empty(size_t length) {
    CHAI_GEN_IMP_LIST_EMPTY(Chai_List_I32, int, length);
    return result;
}

Chai_List_I32 chai_list_i32_clone(const Chai_List_I32 other) {
    CHAI_GEN_IMP_LIST_CLONE(Chai_List_I32, int, other);
    return result;
}

void chai_list_i32_append(Chai_List_I32 *list, const char item) {
    CHAI_GEN_IMP_LIST_APPEND(Chai_List_I32, int, list, item);
}

void chai_list_i32_free(Chai_List_I32 *list) {
    CHAI_GEN_IMP_LIST_FREE(list);
}

Chai_List_F32 chai_list_f32_new(size_t length) {
    CHAI_GEN_IMP_LIST_NEW(Chai_List_F32, float, length);
    return result;
}

Chai_List_F32 chai_list_f32_empty(size_t length) {
    CHAI_GEN_IMP_LIST_EMPTY(Chai_List_F32, float, length);
    return result;
}

Chai_List_F32 chai_list_f32_clone(const Chai_List_F32 other) {
    CHAI_GEN_IMP_LIST_CLONE(Chai_List_F32, float, other);
    return result;
}

void chai_list_f32_append(Chai_List_F32 *list, const char item) {
    CHAI_GEN_IMP_LIST_APPEND(Chai_List_F32, float, list, item);
}

void chai_list_f32_free(Chai_List_F32 *list) {
    CHAI_GEN_IMP_LIST_FREE(list);
}

#endif // CHAI_HEADER