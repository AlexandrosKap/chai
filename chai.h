// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#ifndef CHAI_HEADER
#define CHAI_HEADER

#include <stdbool.h>
#include <stdlib.h>

typedef struct Chai_View {
    const char *items;
    size_t count;
} Chai_View;

void * chai_malloc(size_t size);
void * chai_realloc(void *ptr, size_t size);
void chai_free(void *ptr);

bool chai_is_upper(char c);
bool chai_is_lower(char c);
bool chai_is_alpha(char c);
bool chai_is_space(char c);
bool chai_is_digit(char c);
char chai_to_upper(char c);
char chai_to_lower(char c);
int chai_to_digit(char c);
size_t chai_find_list_capacity(size_t count);

void chai_mem_set(const void *mem, unsigned char value, size_t count);
void chai_mem_copy(const void *mem, const void *source, size_t count);
bool chai_mem_equals(const void *mem, const void *other, size_t count);

Chai_View chai_view_new(const char *str);
Chai_View chai_view_from(Chai_View view, size_t a, size_t b);
const char * chai_view_item(Chai_View view, size_t index);
bool chai_view_equals(Chai_View view, Chai_View other);
bool chai_view_equals_ignore(Chai_View view, Chai_View other);
bool chai_view_starts_with(Chai_View view, Chai_View start);
bool chai_view_ends_with(Chai_View view, Chai_View end);
int chai_view_count(Chai_View view, Chai_View item);
int chai_view_find_left(Chai_View view, Chai_View item);
int chai_view_find_right(Chai_View view, Chai_View item);
Chai_View chai_view_trim_left(Chai_View view);
Chai_View chai_view_trim_right(Chai_View view);
Chai_View chai_view_trim(Chai_View view);
Chai_View chai_view_skip_over(Chai_View *view, Chai_View content); // Think about it and test it later.
Chai_View chai_view_skip_until(Chai_View *view, Chai_View content); // Think about it and test it later.
Chai_View chai_view_skip_line(Chai_View *view); // Think about it and test it later.
Chai_View chai_view_skip_arg(Chai_View *view); // Think about it and test it later.
bool chai_view_to_str(Chai_View view, char *buffer);
bool chai_view_to_int(Chai_View view, int *buffer);
bool chai_view_to_float(Chai_View view, float *buffer);

#define CHAI_SPACE " \t\v\r\n\f"
#define CHAI_LIST_START_CAPACITY 16

#define CHAI_CAST(type) (type)

#ifndef CHAI_MALLOC
#define CHAI_MALLOC(size) malloc(size)
#endif // CHAI_MALLOC

#ifndef CHAI_REALLOC
#define CHAI_REALLOC(ptr, size) realloc(ptr, size)
#endif // CHAI_REALLOC

#ifndef CHAI_FREE
#define CHAI_FREE(ptr) free(ptr)
#endif // CHAI_FREE

/// Creates a new list type.
/// The first argument is the type of the list item.
/// The second argument is the name of the list.
/// The third argument is the prefix that each procedure associated with the list will use.
#define CHAI_CREATE_LIST_TYPE(Item_Type, List_Type, prefix)                                             \
    typedef struct List_Type {                                                                          \
        Item_Type *items;                                                                               \
        size_t count;                                                                                   \
        size_t capacity;                                                                                \
    } List_Type;                                                                                        \
                                                                                                        \
    List_Type prefix ## _new(size_t count) {                                                            \
        List_Type result;                                                                               \
        if (count == 0) {                                                                               \
            result.items = NULL;                                                                        \
            result.count = 0;                                                                           \
            result.capacity = 0;                                                                        \
        } else {                                                                                        \
            size_t capacity = chai_find_list_capacity(count);                                           \
            result.items = chai_malloc(capacity * sizeof(Item_Type));                                   \
            chai_mem_set(result.items, 0, capacity * sizeof(Item_Type));                                \
            result.count = count;                                                                       \
            result.capacity = capacity;                                                                 \
        }                                                                                               \
        return result;                                                                                  \
    }                                                                                                   \
                                                                                                        \
    List_Type prefix ## _clone(List_Type other) {                                                       \
        List_Type result;                                                                               \
        if (other.capacity == 0) {                                                                      \
            result.items = NULL;                                                                        \
            result.count = 0;                                                                           \
            result.capacity = 0;                                                                        \
        } else {                                                                                        \
            result.items = chai_malloc(other.capacity * sizeof(Item_Type));                             \
            chai_mem_copy(result.items, other.items, other.capacity * sizeof(Item_Type));               \
            result.count = other.count;                                                                 \
            result.capacity = other.capacity;                                                           \
        }                                                                                               \
        return result;                                                                                  \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _free(List_Type  list) {                                                             \
        chai_free(list.items);                                                                          \
    }                                                                                                   \
                                                                                                        \
    Item_Type * prefix ## _item(List_Type list, size_t index) {                                         \
        if (index >= list.count) {                                                                      \
            return NULL;                                                                                \
        }                                                                                               \
        return list.items + index;                                                                      \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _fill(List_Type *list, Item_Type item) {                                             \
        for (size_t i = 0; i < list->count; i += 1) {                                                   \
            list->items[i] = item;                                                                      \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _append(List_Type *list, Item_Type item) {                                           \
        list->count += 1;                                                                               \
        if (list->count > list->capacity) {                                                             \
            size_t capacity = chai_find_list_capacity(list->count);                                     \
            list->items = chai_realloc(list->items, capacity * sizeof(Item_Type));                      \
            list->capacity = capacity;                                                                  \
        }                                                                                               \
        list->items[list->count - 1] = item;                                                            \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _insert(List_Type *list, size_t index, Item_Type item) {                             \
        if (index > list->count) {                                                                      \
            return;                                                                                     \
        }                                                                                               \
        list->count += 1;                                                                               \
        if (list->count > list->capacity) {                                                             \
            size_t capacity = chai_find_list_capacity(list->count);                                     \
            list->items = chai_realloc(list->items, capacity * sizeof(Item_Type));                      \
            list->capacity = capacity;                                                                  \
        }                                                                                               \
        for (size_t i = list->count - 1; i > index; i -= 1) {                                           \
            list->items[i] = list->items[i - 1];                                                        \
        }                                                                                               \
        list->items[index] = item;                                                                      \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _remove(List_Type *list, size_t index) {                                             \
        if (index >= list->count) {                                                                     \
            return;                                                                                     \
        }                                                                                               \
        for (size_t i = index; i < list->count - 1; i += 1) {                                           \
            list->items[i] = list->items[i + 1];                                                        \
        }                                                                                               \
        list->count -= 1;                                                                               \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _remove_swap(List_Type *list, size_t index) {                                        \
        if (index >= list->count) {                                                                     \
            return;                                                                                     \
        }                                                                                               \
        list->items[index] = list->items[list->count - 1];                                              \
        list->count -= 1;                                                                               \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _resize(List_Type *list, size_t count) {                                             \
        size_t old_count = list->count;                                                                 \
        list->count = count;                                                                            \
        if (list->count > list->capacity) {                                                             \
            size_t capacity = chai_find_list_capacity(list->count);                                     \
            list->items = chai_realloc(list->items, capacity * sizeof(Item_Type));                      \
            list->capacity = capacity;                                                                  \
        }                                                                                               \
        if (list->count > old_count) {                                                                  \
            chai_mem_set(list->items + old_count, 0, (list->count - old_count) * sizeof(Item_Type));    \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _reserve(List_Type *list, size_t additional) {                                       \
        size_t temp_count = list->count;                                                                \
        list->count = list->count + additional;                                                         \
        if (list->count > list->capacity) {                                                             \
            size_t capacity = chai_find_list_capacity(list->count);                                     \
            list->items = chai_realloc(list->items, capacity * sizeof(Item_Type));                      \
            list->capacity = capacity;                                                                  \
        }                                                                                               \
        list->count = temp_count;                                                                       \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _shrink(List_Type *list) {                                                           \
        size_t capacity = chai_find_list_capacity(list->count);                                         \
        if (capacity != list->capacity) {                                                               \
            list->items = chai_realloc(list->items, capacity * sizeof(Item_Type));                      \
            list->capacity = capacity;                                                                  \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    void prefix ## _clear(List_Type *list) {                                                            \
        prefix ## _resize(list, 0);                                                                     \
    }

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

bool chai_is_upper(char c) {
    return c >= 65 && c <= 90;
}

bool chai_is_lower(char c) {
    return c >= 97 && c <= 122;
}

bool chai_is_alpha(char c) {
    return chai_is_upper(c) || chai_is_lower(c);
}

bool chai_is_space(char c) {
    const char *space = CHAI_SPACE;
    while (*space != '\0') {
        if (c == *space) {
            return true;
        }
        space += 1;
    }
    return false;
}

bool chai_is_digit(char c) {
    return c >= 48 && c <= 57;
}

char chai_to_upper(char c) {
    if (chai_is_lower(c)) {
        return c - 32;
    } else {
        return c;
    }
}

char chai_to_lower(char c) {
    if (chai_is_upper(c)) {
        return c + 32;
    } else {
        return c;
    }
}

int chai_to_digit(char c) {
    if (chai_is_digit(c)) {
        return c - 48;
    } else {
        return -1;
    }
}

size_t chai_find_list_capacity(size_t count) {
    size_t result = CHAI_LIST_START_CAPACITY;
    while (result < count) {
        result *= 2;
    }
    return result;
}

void chai_mem_set(const void *mem, unsigned char value, size_t count) {
    for (size_t i = 0; i < count; i += 1) {
        (CHAI_CAST(unsigned char *) mem)[i] = value;
    }
}

void chai_mem_copy(const void *mem, const void *source, size_t count) {
    for (size_t i = 0; i < count; i += 1) {
        (CHAI_CAST(unsigned char *) mem)[i] = (CHAI_CAST(unsigned char *) source)[i];
    }
}

bool chai_mem_equals(const void *mem, const void *other, size_t count) {
    for (size_t i = 0; i < count; i += 1) {
        if ((CHAI_CAST(char *) mem)[i] != (CHAI_CAST(char *) other)[i]) {
            return false;
        }
    }
    return true;
}

Chai_View chai_view_new(const char *str) {
    Chai_View result;
    result.items = str;
    result.count = 0;
    while (str[result.count] != '\0') {
        result.count += 1;
    }
    return result;
}

Chai_View chai_view_from(Chai_View view, size_t a, size_t b) {
    Chai_View result;
    result.items = NULL;
    result.count = 0;
    if (a > b || a > view.count || b > view.count) {
        return result;
    }
    result.items = view.items + a;
    result.count = b - a;
    return result;
}

const char * chai_view_item(Chai_View view, size_t index) {
    if (index >= view.count) {
        return NULL;
    }
    return view.items + index;
}

bool chai_view_equals(Chai_View view, Chai_View other) {
    if (view.count != other.count) {
        return false;
    }
    for (size_t i = 0; i < view.count; i += 1) {
        if (view.items[i] != other.items[i]) {
            return false;
        }
    }
    return true;
}

bool chai_view_equals_ignore(Chai_View view, Chai_View other) {
    if (view.count != other.count) {
        return false;
    }
    for (size_t i = 0; i < view.count; i += 1) {
        if (chai_to_lower(view.items[i]) != chai_to_lower(other.items[i])) {
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
    int result = 0;
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
            return CHAI_CAST(int) i;
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
            return CHAI_CAST(int) i;
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
        if (chai_is_space(result.items[0])) {
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
        if (chai_is_space(result.items[result.count - 1])) {
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

Chai_View chai_view_skip_over(Chai_View *view, Chai_View content) {
    if (chai_view_starts_with(*view, content)) {
        *view = chai_view_from(*view, content.count, view->count);
        return content;
    } else {
        return chai_view_new("");
    }
}

Chai_View chai_view_skip_until(Chai_View *view, Chai_View content) {
    if (view->count == 0 || content.count == 0 || view->count < content.count) {
        return chai_view_new("");
    }
    for (size_t i = 0; i <= view->count - content.count; i += 1) {
        Chai_View part = chai_view_from(*view, i, i + content.count);
        if (chai_view_equals(part, content)) {
            Chai_View left_part = chai_view_from(*view, 0, i + part.count);
            *view = chai_view_from(*view, i + part.count, view->count);
            return left_part;
        }
    }
    return chai_view_new("");
}

Chai_View chai_view_skip_line(Chai_View *view) {
    for (size_t i = 0; i <= view->count; i += 1) {
        if (i == view->count || view->items[i] == '\n') {
            Chai_View left_part = chai_view_from(*view, 0, i);
            *view = chai_view_from(*view, i + 1, view->count);
            return left_part;
        }
    }
    return chai_view_new("");
}

Chai_View chai_view_skip_arg(Chai_View *view) {
    for (size_t i = 1; i <= view->count; i += 1) {
        if (i == view->count || (view->items[i - 1] != ' ' && view->items[i] == ' ')) {
            Chai_View left_part = chai_view_trim_left(chai_view_from(*view, 0, i));
            *view = chai_view_from(*view, i + 1, view->count);
            return left_part;
        }
    }
    return chai_view_new("");
}

bool chai_view_to_str(Chai_View view, char *buffer) {
    for (size_t i = 0; i < view.count; i += 1) {
        buffer[i] = view.items[i];
    }
    buffer[view.count] = '\0';
    return true;
}

bool chai_view_to_int(Chai_View view, int *buffer) {
    if (view.count == 0) {
        return false;
    }

    int sign = 1;
    if (view.count != 0) {
        if (view.items[0] == '-') {
            sign = -1;
            view = chai_view_from(view, 1, view.count);
        } else if (view.items[0] == '+') {
            sign = 1;
            view = chai_view_from(view, 1, view.count);
        }
    }

    int level = 1;
    for (size_t i = 1; i < view.count; i += 1) {
        level *= 10;
    }

    int result = 0;
    for (size_t i = 0; i < view.count; i += 1) {
        if (chai_is_digit(view.items[i])) {
            result += sign * level * chai_to_digit(view.items[i]);
            level /= 10;
        } else {
            return false;
        }
    }
    *buffer = result;
    return true;
}

bool chai_view_to_float(Chai_View view, float *buffer) {
    if (view.count == 0) {
        return false;
    }

    int sign = 1;
    if (view.count != 0) {
        if (view.items[0] == '-') {
            sign = -1;
            view = chai_view_from(view, 1, view.count);
        } else if (view.items[0] == '+') {
            sign = 1;
            view = chai_view_from(view, 1, view.count);
        }
    }

    int level = 1;
    for (size_t i = 1; i < view.count; i += 1) {
        if (view.items[i] == '.') {
            break;
        }
        level *= 10;
    }

    bool is_after_dot = false;
    int dot_level = 10;
    float result = 0.0f;
    for (size_t i = 0; i < view.count; i += 1) {
        if (view.items[i] == '.' && !is_after_dot) {
            is_after_dot = true;
        } else if (chai_is_digit(view.items[i])) {
            if (is_after_dot) {
                result += (1.0f * CHAI_CAST(float) (sign * chai_to_digit(view.items[i]))) / CHAI_CAST(float) dot_level;
                dot_level *= 10;
            } else {
                result += CHAI_CAST(float) (sign * level * chai_to_digit(view.items[i]));
                level /= 10;
            }
        } else {
            return false;
        }
    }
    *buffer = result;
    return true;
}

#endif // CHAI_IMPLEMENTATION_ADDED
#endif // CHAI_IMPLEMENTATION
