# 🍵 Chai

A personal header-only utility library for the C programming language.
Chai provides basic data structures such as lists and strings.

## Types

* Chai_View
* Chai_List
* Chai_String

## Examples

Examples of how to use the various data structures can be found in the examples.c file.
The following section is a short example of how to create a new list type:

```c
// The first argument is the name of the list that will be created.
// The second argument is the type of the list item.
// The third argument is the prefix that each procedure associated with this list will use.
CHAI_MAKE_LIST(Numbers, int, numbers)
```

## License

The project is released under the terms of the Apache-2.0 License.
Please refer to the LICENSE file.
