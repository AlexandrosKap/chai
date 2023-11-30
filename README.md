# 🍵 Chai

A personal header-only utility library for the C programming language.
Chai provides basic data structures such as lists.

## Types

* Chai_View
* Macro_List

## Examples

Examples of how to use the various data structures can be found in the examples.c file.
The following section is a short example of how to create a new list type:

```c
// The first argument is the type of the list item.
// The second argument is the name of the list.
// The third argument is the prefix that each procedure associated with the list will use.
CHAI_CREATE_LIST(int, Numbers, numbers)
```

## License

The project is released under the terms of the Apache-2.0 License.
Please refer to the LICENSE file.
