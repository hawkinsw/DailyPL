### What's News

Increasingly desperate programmers are searching high and low for deals on variable names in light of rising inflation. Economists and sociologists say the ones that are succeeding are relying on their knowledge of scope resolution to sniff out value. But first, the Census Bureau released their latest actuarial numbers saying that the expected lifetime of a variable edged up this year from Implicit Heap Dynamic to Stack Dynamic.

### Variables' Storage Bindings

The storage binding is related to the variable's _lifetime_, the time during which a variable is bound to memory. There are four common lifetimes:

1. **static**: Variable is bound to storage before execution and remains bound to the same storage throughout program execution.
    1. Variables with static storage binding cannot share memory with other variables (they need their storage throughout execution).
    2. Variables with static storage binding can be accessed directly (in other words, their access does not require redirection through a pointer) because the address of their storage is constant throughout execution. Direct addressing means that accesses are faster.
    3. Storage for variables with static binding does not need to be repeatedly allocated and deallocated throughout execution -- this will make program execution faster.
    4. In C++, variables with static storage binding are declared using the `static` keyword inside functions and classes.
    5. Variables with static storage binding are sometimes referred to as _history sensitive_ because they retain their value throughout execution.
2.  **stack dynamic**: Variable is bound to storage when it's declaration statements are _elaborated_, the time when a declaration statement is executed.
    1. Variables with stack dynamic storage bindings make recursion possible because their storage is allocated anew every time that their declaration is elaborated. To fully understand this point it is necessary to understand the way that function invocation is handled using a runtime stack. We will cover this topic next week. Stay tuned!
    2. Variables with stack dynamic storage bindings cannot be directly accessed. Accesses must be made through an intermediary which makes them slower. Again, this will make more sense when we discuss the typical mechanism for function invocation.
    3. The storage for variables with stack dynamic storage bindings are constantly allocated and deallocated which adds to runtime overhead.
    4. Variables with stack dynamic storage bindings are _not_ history sensitive.
3.  **Explicit heap dynamic**: Variable is bound to storage by explicit instruction from the programmer. E.g., `new`/`malloc` in C/C++.
    1. The binding to storage is done at runtime when these explicit instructions are executed.
    2. The storage sizes can be customized for the use.
    3. The storage is hard to manage and requires careful attention from the programmer.
    4. The storage for variables with explicit heap dynamic storage bindings are constantly allocated and deallocated which adds to runtime overhead.
4. **Implicit heap dynamic**: Variable is bound to storage when it is assigned a value at runtime.
    1. All storage bindings for variables in Python are handled in this way: "It is important to understand that the management of the Python heap is performed by the interpreter itself and that the user has no control over it, even if they regularly manipulate object pointers to memory blocks inside that heap. The allocation of heap space for Python objects and other internal buffers is performed on demand by the Python memory manager through the Python/C API functions listed in this document." [Cite](https://docs.python.org/3/c-api/memory.html) 
    2. When a variable with implicit heap dynamic storage bindings is assigned a value, storage for that variable is dynamically allocated.
    3. Allocation and deallocation of storage for variables with implicit heap dynamic storage bindings is handled automatically by the language compiler/interpreter. (More on this when we discuss memory management techniques in Module 3).

### A Brain Teaser:

Here's something that I hope will make you think ... What does the following program print? Working through the expectation of the output will help you check whether you understand what we've discussed so far.

```C++
#include <iostream>
 
bool *function1() {
  bool return_value = true;
  return &return_value;
}
 
int function2() {
  int return_value = 0;
  return return_value;
}
 
int main() {
  bool *function1_result = function1();
  int function2_result = function2();

  if (*function1_result) {
    std::cout << "True!n";
  } else {
    std::cout << "False!n";
  }
  return 0;
}
```

<details><summary>Answer</summary>

The program contains undefined behavior (!!). `function1` returns a pointer to a variable whose lifetime is stack dynamic. As a result, the lifetime of that variable ends when the function completes execution. Therefore, the storage associated with that variable is given back to the system for reuse by another variable. 

However, back in `main`, we dereference that pointer, assuming that the target of the pointer is to memory that we still own. Because that is not the case, the pointer is considered invalid and

> Indirection through an invalid pointer value and passing an invalid pointer value to a deallocation function have undefined behavior.

Sad trombone.

</details>
