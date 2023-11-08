// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef CHAI_HEADER
#define CHAI_HEADER

#define CHAI_WHITESPACE " \t\v\r\n\f"
#define CHAI_LIST_START_CAPACITY 32

typedef struct Chai_View {
    const char *items;
    size_t count;
} Chai_View;

typedef struct Chai_List {
    void *items;
    size_t count;
    size_t capacity;
    size_t item_size;
} Chai_List;

typedef struct Chai_String {
    Chai_List data;
} Chai_String;

void * chai_malloc(size_t size);
void * chai_realloc(void *ptr, size_t size);
void chai_free(void *ptr);

bool chai_mem_equals(const void *ptr, const void *other, size_t count);
void chai_mem_set(const void *ptr, unsigned char value, size_t count);
void chai_mem_copy(const void *ptr, const void *value, size_t count);

size_t chai_str_count(const char *str);

size_t chai_find_capacity(size_t count);
bool chai_is_upper_case(char c);
bool chai_is_lower_case(char c);
bool chai_is_alphabetic(char c);
bool chai_is_whitespace(char c);
bool chai_is_digit(char c);
char chai_to_upper_case(char c);
char chai_to_lower_case(char c);

Chai_View chai_view_new(const char *str);
Chai_View chai_view_from_str(const char *str, size_t a, size_t b);
Chai_View chai_view_from_string(Chai_String list, size_t a, size_t b);
Chai_View chai_view_from_view(Chai_View view, size_t a, size_t b);
const char * chai_view_item(Chai_View view, size_t index);
bool chai_view_equals(Chai_View view, Chai_View other);
bool chai_view_equals_ignore_case(Chai_View view, Chai_View other);
bool chai_view_starts_with(Chai_View view, Chai_View start);
bool chai_view_ends_with(Chai_View view, Chai_View end);
int chai_view_count(Chai_View view, Chai_View item);
int chai_view_find_left(Chai_View view, Chai_View item);
int chai_view_find_right(Chai_View view, Chai_View item);
Chai_View chai_view_trim_left(Chai_View view);
Chai_View chai_view_trim_right(Chai_View view);
Chai_View chai_view_trim(Chai_View view);

Chai_List chai_list_new(size_t count, size_t item_size);
Chai_List chai_list_copy(Chai_List other);
void * chai_list_item(Chai_List *list, size_t index);
void chai_list_fill(Chai_List *list, void *item);
void chai_list_append(Chai_List *list, void *item);
void chai_list_insert(Chai_List *list, size_t index, void *item);
void chai_list_remove(Chai_List *list, size_t index);
void chai_list_remove_swap(Chai_List *list, size_t index);
void chai_list_resize(Chai_List *list, size_t count);
void chai_list_reserve(Chai_List *list, size_t additional);
void chai_list_shrink(Chai_List *list);
void chai_list_clear(Chai_List *list);
void chai_list_free(Chai_List *list);

Chai_String chai_string_new(size_t count);
Chai_String chai_string_copy(Chai_String other);
char * chai_string_item(Chai_String *list, size_t index);
void chai_string_fill(Chai_String *list, char item);
void chai_string_append(Chai_String *list, char item);
void chai_string_insert(Chai_String *list, size_t index, char item);
void chai_string_remove(Chai_String *list, size_t index);
void chai_string_remove_swap(Chai_String *list, size_t index);
void chai_string_resize(Chai_String *list, size_t count);
void chai_string_reserve(Chai_String *list, size_t additional);
void chai_string_shrink(Chai_String *list);
void chai_string_clear(Chai_String *list);
void chai_string_free(Chai_String *list);
Chai_String chai_string_copy_view(Chai_View view);
void chai_string_append_view(Chai_String *list, Chai_View view);
void chai_string_insert_view(Chai_String *list, size_t index, Chai_View view);
Chai_String chai_string_copy_str(const char *str);
void chai_string_append_str(Chai_String *list, const char *str);
void chai_string_insert_str(Chai_String *list, size_t index, const char *str);

#ifndef CHAI_ASSERT
#define CHAI_ASSERT(value) assert(value)
#endif // CHAI_ASSERT

#ifndef CHAI_MALLOC
#define CHAI_MALLOC(size) malloc(size)
#endif // CHAI_MALLOC

#ifndef CHAI_REALLOC
#define CHAI_REALLOC(ptr, size) realloc(ptr, size)
#endif // CHAI_REALLOC

#ifndef CHAI_FREE
#define CHAI_FREE(ptr) free(ptr)
#endif // CHAI_FREE

#define CHAI_CAST(type) (type)
#define CHAI_PANIC(message) CHAI_ASSERT(message && 0)
#define CHAI_PANIC_INDEX() CHAI_PANIC("Index is out of range.")

#define CHAI_MAKE_LIST_PROCEDURES(List_Type, Item_Type, prefix)             \
    List_Type prefix ## _new(size_t count) {                                \
        List_Type result;                                                   \
        result.data = chai_list_new(count, sizeof(Item_Type));              \
        return result;                                                      \
    }                                                                       \
                                                                            \
    List_Type prefix ## _copy(List_Type other) {                            \
        List_Type result;                                                   \
        result.data = chai_list_copy(other.data);                           \
        return result;                                                      \
    }                                                                       \
                                                                            \
    Item_Type * prefix ## _item(List_Type *list, size_t index) {            \
        if (index >= list->data.count) {                                    \
            CHAI_PANIC_INDEX();                                             \
            return NULL;                                                    \
        }                                                                   \
        return CHAI_CAST(Item_Type *) chai_list_item(&list->data, index);   \
    }                                                                       \
                                                                            \
    void prefix ## _fill(List_Type *list, Item_Type item) {                 \
        chai_list_fill(&list->data, &item);                                 \
    }                                                                       \
                                                                            \
    void prefix ## _append(List_Type *list, Item_Type item) {               \
        chai_list_append(&list->data, &item);                               \
    }                                                                       \
                                                                            \
    void prefix ## _insert(List_Type *list, size_t index, Item_Type item) { \
        if (index > list->data.count) {                                     \
            CHAI_PANIC_INDEX();                                             \
            return;                                                         \
        }                                                                   \
        chai_list_insert(&list->data, index, &item);                        \
    }                                                                       \
                                                                            \
    void prefix ## _remove(List_Type *list, size_t index) {                 \
        if (index >= list->data.count) {                                    \
            CHAI_PANIC_INDEX();                                             \
            return;                                                         \
        }                                                                   \
        chai_list_remove(&list->data, index);                               \
    }                                                                       \
                                                                            \
    void prefix ## _remove_swap(List_Type *list, size_t index) {            \
        if (index >= list->data.count) {                                    \
            CHAI_PANIC_INDEX();                                             \
            return;                                                         \
        }                                                                   \
        chai_list_remove_swap(&list->data, index);                          \
    }                                                                       \
                                                                            \
    void prefix ## _resize(List_Type *list, size_t count) {                 \
        chai_list_resize(&list->data, count);                               \
    }                                                                       \
                                                                            \
    void prefix ## _reserve(List_Type *list, size_t additional) {           \
        chai_list_reserve(&list->data, additional);                         \
    }                                                                       \
                                                                            \
    void prefix ## _shrink(List_Type *list) {                               \
        chai_list_shrink(&list->data);                                      \
    }                                                                       \
                                                                            \
    void prefix ## _clear(List_Type *list) {                                \
        chai_list_clear(&list->data);                                       \
    }                                                                       \
                                                                            \
    void prefix ## _free(List_Type *list) {                                 \
        chai_list_free(&list->data);                                        \
    }

#define CHAI_MAKE_LIST(List_Type, Item_Type, prefix)                        \
    typedef struct List_Type {                                              \
        Chai_List data;                                                     \
    } List_Type;                                                            \
                                                                            \
    CHAI_MAKE_LIST_PROCEDURES(List_Type, Item_Type, prefix)

#endif // CHAI_HEADER

#ifdef CHAI_IMPLEMENTATION
#ifndef CHAI_IMPLEMENTATION_ADDED
#define CHAI_IMPLEMENTATION_ADDED

void * chai_malloc(size_t size) {
    return CHAI_MALLOC(size);
}

void * chai_realloc(void *ptr, size_t size) {
    return CHAI_REALLOC(ptr, size);
}

void chai_free(void *ptr) {
    CHAI_FREE(ptr);
}

bool chai_mem_equals(const void *ptr, const void *other, size_t count) {
    for (size_t i = 0; i < count; i += 1) {
        if ((CHAI_CAST(char *) ptr)[i] != (CHAI_CAST(char *) other)[i]) {
            return false;
        }
    }
    return true;
}

void chai_mem_set(const void *ptr, unsigned char value, size_t count) {
    for (size_t i = 0; i < count; i += 1) {
        (CHAI_CAST(unsigned char *) ptr)[i] = value;
    }
}

void chai_mem_copy(const void *ptr, const void *value, size_t count) {
    for (size_t i = 0; i < count; i += 1) {
        (CHAI_CAST(unsigned char *) ptr)[i] = (CHAI_CAST(unsigned char *) value)[i];
    }
}

size_t chai_str_count(const char *str) {
    size_t result = 0;
    while (str[result] != '\0') {
        result += 1;
    }
    return result;
}

size_t chai_find_capacity(size_t count) {
    size_t result = CHAI_LIST_START_CAPACITY;
    while (result < count) {
        result *= 2;
    }
    return result;
}

bool chai_is_upper_case(char c) {
    return c >= 65 && c <= 90;
}

bool chai_is_lower_case(char c) {
    return c >= 97 && c <= 122;
}

bool chai_is_alphabetic(char c) {
    return chai_is_upper_case(c) || chai_is_lower_case(c);
}

bool chai_is_whitespace(char c) {
    const char *whitespace = CHAI_WHITESPACE;
    while (*whitespace != '\0') {
        if (c == *whitespace) {
            return true;
        }
        whitespace += 1;
    }
    return false;
}

bool chai_is_digit(char c) {
    return c >= 48 && c <= 57;
}

char chai_to_upper_case(char c) {
    if (chai_is_lower_case(c)) {
        return c - 32;
    } else {
        return c;
    }
}

char chai_to_lower_case(char c) {
    if (chai_is_upper_case(c)) {
        return c + 32;
    } else {
        return c;
    }
}

Chai_View chai_view_new(const char *str) {
    Chai_View result;
    result.items = str;
    result.count = chai_str_count(str);
    return result;
}

Chai_View chai_view_from_str(const char *str, size_t a, size_t b) {
    Chai_View result;
    result.items = NULL;
    result.count = 0;
    size_t str_count = chai_str_count(str);
    if (a > b || a > str_count || b > str_count) {
        CHAI_PANIC_INDEX();
        return result;
    }
    result.items = str + a;
    result.count = b - a;
    return result;
}

Chai_View chai_view_from_string(Chai_String list, size_t a, size_t b) {
    Chai_View result;
    result.items = NULL;
    result.count = 0;
    if (a > b || a > list.data.count || b > list.data.count) {
        CHAI_PANIC_INDEX();
        return result;
    }
    result.items = CHAI_CAST(char *) list.data.items + a;
    result.count = b - a;
    return result;
}

Chai_View chai_view_from_view(Chai_View view, size_t a, size_t b) {
    Chai_View result;
    result.items = NULL;
    result.count = 0;
    if (a > b || a > view.count || b > view.count) {
        CHAI_PANIC_INDEX();
        return result;
    }
    result.items = view.items + a;
    result.count = b - a;
    return result;
}

const char * chai_view_item(Chai_View view, size_t index) {
    if (index >= view.count) {
        CHAI_PANIC_INDEX();
        return NULL;
    }
    return view.items + index;
}

bool chai_view_equals(Chai_View view, Chai_View other) {
    if (view.count != other.count) {
        return false;
    }
    return chai_mem_equals(view.items, other.items, other.count);
}

bool chai_view_equals_ignore_case(Chai_View view, Chai_View other) {
    if (view.count != other.count) {
        return false;
    }
    for (size_t i = 0; i < view.count; i += 1) {
        if (chai_to_lower_case(view.items[i]) != chai_to_lower_case(other.items[i])) {
            return false;
        }
    }
    return true;
}

bool chai_view_starts_with(Chai_View view, Chai_View start) {
    if (view.count < start.count) {
        return false;
    }
    return chai_mem_equals(view.items, start.items, start.count);
}

bool chai_view_ends_with(Chai_View view, Chai_View end) {
    if (view.count < end.count) {
        return false;
    }
    return chai_mem_equals(view.items + view.count - end.count, end.items, end.count);
}

int chai_view_count(Chai_View view, Chai_View item) {
    size_t result = 0;
    if (view.count < item.count || item.count == 0) {
        return result;
    }
    for (size_t i = 0; i <= view.count - item.count; i += 1) {
        if (chai_mem_equals(view.items + i, item.items, item.count)) {
            result += 1;
            i += item.count - 1;
        }
    }
    return result;
}

int chai_view_find_left(Chai_View view, Chai_View item) {
    if (view.count < item.count || item.count == 0) {
        return -1;
    }
    for (size_t i = 0; i <= view.count - item.count; i += 1) {
        if (chai_mem_equals(view.items + i, item.items, item.count)) {
            return i;
        }
    }
    return -1;
}

int chai_view_find_right(Chai_View view, Chai_View item) {
    if (view.count < item.count || item.count == 0) {
        return -1;
    }
    for (size_t i = view.count - item.count;; i -= 1) {
        if (chai_mem_equals(view.items + i, item.items, item.count)) {
            return i;
        }
        if (i == 0) {
            return -1;
        }
    }
    return -1;
}

Chai_View chai_view_trim_left(Chai_View view) {
    Chai_View result = view;
    while (result.count > 0) {
        if (chai_is_whitespace(result.items[0])) {
            result.items += 1;
            result.count -= 1;
        } else {
            break;
        }
    }
    return result;
}

Chai_View chai_view_trim_right(Chai_View view) {
    Chai_View result = view;
    while (result.count > 0) {
        if (chai_is_whitespace(result.items[result.count - 1])) {
            result.count -= 1;
        } else {
            break;
        }
    }
    return result;
}

Chai_View chai_view_trim(Chai_View view) {
    return chai_view_trim_left(chai_view_trim_right(view));
}

Chai_List chai_list_new(size_t count, size_t item_size) {
    Chai_List result;
    if (count == 0) {
        result.items = NULL;
        result.count = 0;
        result.capacity = 0;
        result.item_size = item_size;
    } else {
        size_t capacity = chai_find_capacity(count);
        result.items = chai_malloc(capacity * item_size);
        result.count = count;
        result.capacity = capacity;
        result.item_size = item_size;
        chai_mem_set(result.items, 0, capacity * item_size);
    }
    return result;
}

Chai_List chai_list_copy(Chai_List other) {
    Chai_List result;
    if (other.capacity == 0) {
        result.items = NULL;
        result.count = 0;
        result.capacity = 0;
        result.item_size = other.item_size;
    } else {
        result.items = chai_malloc(other.capacity * other.item_size);
        result.count = other.count;
        result.capacity = other.capacity;
        result.item_size = other.item_size;
        chai_mem_copy(result.items, other.items, other.capacity * other.item_size);
    }
    return result;
}

void * chai_list_item(Chai_List *list, size_t index) {
    return (CHAI_CAST(char *) list->items) + index * list->item_size;
}

void chai_list_fill(Chai_List *list, void *item) {
    for (size_t i = 0; i < list->count; i += 1) {
        chai_mem_copy(chai_list_item(list, i), item, list->item_size);
    }
}

void chai_list_append(Chai_List *list, void *item) {
    list->count += 1;
    if (list->count > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->count);
        list->items = chai_realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    chai_mem_copy(chai_list_item(list, list->count - 1), item, list->item_size);
}

void chai_list_insert(Chai_List *list, size_t index, void *item) {
    list->count += 1;
    if (list->count > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->count);
        list->items = chai_realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    for (size_t i = list->count - 1; i > index; i -= 1) {
        chai_mem_copy(chai_list_item(list, i), chai_list_item(list, i - 1), list->item_size);
    }
    chai_mem_copy(chai_list_item(list, index), item, list->item_size);
}

void chai_list_remove(Chai_List *list, size_t index) {
    if (list->count == 0) {
        return;
    }
    for (size_t i = index; i < list->count - 1; i += 1) {
        chai_mem_copy(chai_list_item(list, i), chai_list_item(list, i + 1), list->item_size);
    }
    list->count -= 1;
}

void chai_list_remove_swap(Chai_List *list, size_t index) {
    if (list->count == 0) {
        return;
    }
    chai_mem_copy(chai_list_item(list, index), chai_list_item(list, list->count - 1), list->item_size);
    list->count -= 1;
}

void chai_list_resize(Chai_List *list, size_t count) {
    size_t old_count = list->count;
    list->count = count;
    if (list->count > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->count);
        list->items = chai_realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    if (list->count > old_count) {
        chai_mem_set(chai_list_item(list, old_count), 0, (list->count - old_count) * list->item_size);
    }
}

void chai_list_reserve(Chai_List *list, size_t additional) {
    size_t temp_count = list->count;
    list->count = list->count + additional;
    if (list->count > list->capacity) {
        size_t new_capacity = chai_find_capacity(list->count);
        list->items = chai_realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
    list->count = temp_count;
}

void chai_list_shrink(Chai_List *list) {
    size_t new_capacity = chai_find_capacity(list->count);
    if (new_capacity != list->capacity) {
        list->items = chai_realloc(list->items, new_capacity * list->item_size);
        list->capacity = new_capacity;
    }
}

void chai_list_clear(Chai_List *list) {
    chai_list_resize(list, 0);
}

void chai_list_free(Chai_List *list) {
    chai_free(list->items);
}

Chai_String chai_string_new(size_t count) {
    Chai_String result;
    result.data = chai_list_new(count + 1, sizeof(char));
    result.data.count -= 1;
    return result;
}

Chai_String chai_string_copy(Chai_String other) {
    Chai_String result;
    result.data = chai_list_copy(other.data);
    return result;
}

char * chai_string_item(Chai_String *list, size_t index) {
    if (index >= list->data.count) {
        CHAI_PANIC_INDEX();
        return NULL;
    }
    return CHAI_CAST(char *) chai_list_item(&list->data, index);
}

void chai_string_fill(Chai_String *list, char item) {
    chai_list_fill(&list->data, CHAI_CAST(char *) &item);
}

void chai_string_append(Chai_String *list, char item) {
    char cute_zero = '\0';
    chai_list_append(&list->data, CHAI_CAST(char *) &item);
    chai_list_append(&list->data, CHAI_CAST(char *) &cute_zero);
    list->data.count -= 1;
}

void chai_string_insert(Chai_String *list, size_t index, char item) {
    if (index > list->data.count) {
        CHAI_PANIC_INDEX();
        return;
    }
    if (index == list->data.count) {
        const char cute_zero = '\0';
        chai_list_append(&list->data, CHAI_CAST(char *) &item);
        chai_list_append(&list->data, CHAI_CAST(char *) &cute_zero);
        list->data.count -= 1;
    } else {
        chai_list_insert(&list->data, index, CHAI_CAST(char *) &item);
    }
}

void chai_string_remove(Chai_String *list, size_t index) {
    if (index >= list->data.count) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove(&list->data, index);
}

void chai_string_remove_swap(Chai_String *list, size_t index) {
    if (index >= list->data.count) {
        CHAI_PANIC_INDEX();
        return;
    }
    chai_list_remove_swap(&list->data, index);
}

void chai_string_resize(Chai_String *list, size_t count) {
    chai_list_resize(&list->data, count + 1);
    *(CHAI_CAST(char *) chai_list_item(&list->data, count)) = '\0';
    list->data.count -= 1;
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
    list->data.count -= 1;
}

void chai_string_free(Chai_String *list) {
    chai_list_free(&list->data);
}

Chai_String chai_string_copy_view(Chai_View view) {
    Chai_String result = chai_string_new(view.count);
    result.data.count = 0;
    for (size_t i = 0; i < view.count; i += 1) {
        chai_string_append(&result, view.items[i]);
    }
    return result;
}

void chai_string_append_view(Chai_String *list, Chai_View view) {
    for (size_t i = 0; i < view.count; i += 1) {
        chai_string_append(list, view.items[i]);
    }
}

void chai_string_insert_view(Chai_String *list, size_t index, Chai_View view) {
    for (size_t i = 0; i < view.count; i += 1) {
        chai_string_insert(list, index, view.items[i]);
        index += 1;
    }
}

Chai_String chai_string_copy_str(const char *str) {
    size_t str_count = chai_str_count(str);
    Chai_String result;
    result.data = chai_list_new(str_count + 1, sizeof(char));
    result.data.count -= 1;
    for (size_t i = 0; i < str_count; i += 1) {
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

#endif // CHAI_IMPLEMENTATION_ADDED
#endif // CHAI_IMPLEMENTATION
