### What's News

In recent weeks it was revealed that an almost-complete nuclear sub*marine* sunk to the bottom of the sea. That stunning development stole the spotlight from sub*programs* that have recently made their share of headlines.

## Subprograms

A _subprogram_ is a type of abstraction. It is _process abstraction_ where the _how_ of a process is hidden from the user who concerns themselves only with the _what_. A _subprogram_ provides process abstraction by naming a collection of statements that define parameterized computations.​ Again, the collection of statements determines how the process is implemented. _Subprogram_ _parameters_ give the subprogram user the ability to control the way that the calculation performed by the subprogram executes. There are three types of subprograms:

1. Procedure: A subprogram that does _not_ return a value.
2. Function: A subprogram that _does_ return a value.
3. Method: A subprogram that operates with an implicit association to an object; a method may or may not return a value.

Pay close attention to the book's explanation and definitions of terms like _parameter,_ _parameter profile_, _argument,_ _protocol_, _definition_, and _declaration_[^confuse].

[^confuse]: I always get them confused!

Subprograms are characterized by three facts:

1.  A subprogram has only one entry point;
2.  Only one subprogram is executing at any time;
    - Note: There may be more than one subprogram that has started but not yet completed. Those subprograms are known as _active_ subprograms. Again, there may be multiple active subprograms, but there is only one executing subprogram.
3.  Program execution returns to the caller upon completion of a subprogram.

### Calling a Subprogram: Matching Parameters with Arguments
There is a difference between (formal) _parameters_ and actual parameters (also know as _arguments_). (Formal) parameters belong with the subprogram definition (or the declaration, protocol). They give names to variables that the subprogram implementation can use to refer to values that the user specifies at the time that the subprogram is called. Those values (specified by the user at the time the subprogram is invoked) are called the arguments. The number, type and order of arguments "must" (well, almost "must" -- see below!) match the number, type and order of the parameters. In most cases, order is used to match the arguments to the parameters. The first parameter is matched to the first argument and the second parameter is matched to the second argument, and so on. Arguments that are matched with parameters in this way are known as _positional arguments_. Once the arguments are matched to the parameters, a confirmation is made that their types are compatible. Matching arguments to parameters by their position implies that there are the same number of arguments and parameters.

So, why the caveat?

Languages offer different mechanisms to make matching parameters with arguments possible. Some languages offer _default arguments_ for subprograms, which allow the caller to leave off an argument and accept the subprogram's implementer's choice of a default value.

```C++
int get_random(int max_random = 500) {
    int actual_random{rng() % max_random};
    return actual_random;
}
```

is an example of a subprogram (what is called a function in C++) that has a default parameter. Even though the default value is written with the parameter, C++ actually calls such a thing a default argument. I know.

Because of the default argument in C++, these two programs perform the same calculations:

```C++
int main() {
    int random_number{get_random()};
    std::cout << "I got a random number: " << random_number << std::endl;
    return 0;
}
```

```C++
int main() {
    int random_number{get_random(500)};
    std::cout << "I got a random number: " << random_number << std::endl;
    return 0;
}
```

Of course, if I (as the user of the `random_number` subprogram) want a random number within a smaller range, then I can always do that:

```C++

int main() {
    int random_number{get_random(10)};
    std::cout << "I got a random number: " << random_number << std::endl;
    return 0;
}
```

In other words, with a default argument in C++, the caller always has the opportunity to override the default. But, if they don't, then the default value is used!

Some languages offer _keyword arguments_, which allow the caller to match a particular argument with a particular parameter out of order.

Python is a language that allows all those "features", and more!

![Actual, formal parameters; Positional, keyword parameters; Calling a subprogram - Python .png](./graphics/Actual,%20formal%20parameters;%20Positional,%20keyword%20parameters;%20Calling%20a%20function%20-%20Python.png)

The terminology used so far seems to imply that two-way communication between caller and called via arguments/parameters is not possible. There is an implication that communication from the called to the caller is only possible through a _return value_. This is most certainly not the case in every programming languages. Parameters can be:

1. _in mode parameters_: The traditional type of parameter where the caller communicates to the called (one way).
2. _out mode parameters_: A decidedly unusual type of parameter where the called communicates with the caller (one way).
3. _in/out mode parameters_: Something that is common, but not overly so: the caller and the called can communicate bidirectionally.

Those three definitions specify the semantics of communication between caller and called, but do not describe the mechanics. There are many ways that these modes of communication can be implemented and each have their own benefits and drawbacks:

1. _Pass by value_: Used to implement in-mode parameters. A local variable (from the perspective of the subprogram implementation) with the name of the formal parameter is given _the value_ of the corresponding actual parameter. That value is usually obtained by copying the value of the argument into the memory associated with the parameter -- hence the name.
2. _Pass by result_: Used to implement out-mode parameters. A local variable (from the perspective of the subprogram implementation) with the name of the formal parameter is available to the subprogram implementation. Upon termination of the subprogram's execution, the value of that local variable is copied to the space associated with the corresponding actual parameter.
3. _Pass by reference_: Used to implement in-out-mode parameters. A local variable (from the perspective of the subprogram) with the name of the formal parameter contains an _access path_ (usually a pointer or a reference) to the argument. In the subprogram implementation, all accesses/updates to the variable are done through the access path. Those accesses/updates are simultaneously visible to the called and the caller.

There are myriad ways that the choice of implementation methods for parameter passing can cause unexpected behavior. The most common issue that arises has to do with _aliasing_. When two (or more) names refer to the same variable, those names are said to be aliases. When there are two or more different names that refer to the same variable, either one can change its value. Obviously this can be surprising to the programmer who believes that an assignment statement giving a new value to the variable bound to two _different_ names is changing the value of two different variables. Aliasing is such a difficult problem to solve that some languages (C++) put the onus on the programmer to ensure that it never happens and make no guarantees about a program's behavior when aliasing is present.


add rsp, 0x8
```