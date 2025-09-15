### What's News

With the recent changes in the economic outlook for the United States and other Western countries, employees are losing the upper hand in compensation negotiations. Employers are increasingly asking their employees to sign binding agreements that govern everything from how many free snacks they will eat per day to the number of days that they need to be in the office each week.

### The Ties That Bind Us

The better that we understand a programming language and the better that we understand the meaning of code written in that language, the better we are at writing correct programs in that language. Every bit of code that we write has meaning. That meaning is derived from the position of a piece of code in the overall program, the keywords that are used, the variables that hold values and so on. In other words, the _entities_ (e.g., key words, symbols, variable names, etc) of every piece of code that we write contribute, in their own way, to the meaning of a program through the _value_ of their _attributes_. See the chart below for examples of entities in programming languages and some of their attributes.

| Entity | Attribute | Example |
| -- | -- | -- |
| Symbol | Operation | `::` can be used in C++ to specify in which scope to look for a name. |
| Variable | Type | Variables in Java can have `Object` type. |
| Key word | Position | `in` can be used in a `for` statement in Python. |

Knowing the attributes of a particular entity is important but so is knowing how/when attributes are associated with an entity. A _binding_ is an association between an _attribute_ and an _entity_ in a programming language.

_Bindings_ between entities and attributes can happen at various times:

1.  Language design (when the language's syntax and semantics are defined or standardized)
2.  Language implementation (when the language's compiler or interpreter is implemented)
3.  Compilation (when the program is compiled [note: This "time" is not applicable for all languages])
4.  Linking (when all modules of compiled code for a program are collected into a complete, executable program [note: Again, this "time" may not apply in all cases])
5.  Loading (when a program [either compiled or interpreted] is loaded into memory for the purpose of execution)
6.  Run time (program execution)

A _static binding_ occurs before runtime (times 1 through 5 above) and, _crucially_, does not change throughout program execution. A _dynamic binding_ occurs at runtime (time 6 above) and/or occurs in times 1 through 5 but changes during program execution.

> **Note**: To be very clear, even though a binding between an attribute and an entity may happen before program execution, if something about that binding changes during execution it is still considered a dynamic binding.

To better realize the importance of understanding binding and when bindings happen for writing correct code, let's analyze two snippets of code: one from C++ and the other from Python. 

#### C++

```C++
void operate_on(int left, int right) {  
    int result = left * right;  
    return result;
}
```

There are _so_ many entities in even that little snippet of code and there is _so_ little time. Let's talk about `result`. `result` is a name (an entity) and we can see that it identifies (the attribute) a variable because of its position in the code. The language's syntax tell us (and the compiler) that any name in the same position as `result` in the code above would identify a variable. Therefore, the binding between a piece of code in that position and it's purpose in the program is done at language design time. However, the binding between the actual name and the variable to which it refers is done when the program executes. (because it is a local variable with stack dynamic lifetime). Because any variable can have any type in C++, the binding between a type and variable cannot be done until the program is compiled. The compiler cannot completely determine the type of, e.g., `result` until the program is compiled. Because C++ is a statically typed language (a term we will learn in a few sessions), the binding between a variable and its type happens before the program executes and does not change at runtime. Depending on the platform and/or the compiler, the amount of bytes that are allocated to hold an `int` [can vary](https://eel.is/c++draft/basic.fundamental#:width_of_integral_type) (as long as it is at least 16 bits). That means the time of the binding between the number of bits needed to hold the value (the attribute) of a variable whose type is `int` (the entity) happens at _implementation time_.

One of the neatest parts of C++ is that the programmer has the ability to change/define the functionality of a particular operator when applied to variables with a user-defined type. There is enormous flexibility in this feature (e.g., a programmer that defines a matrix type can specify that matrix multiplication occurs when the `*` is used between two instances of their class) and it has implications for the time of the binding of the semantics (the attribute) to a symbol (the entity). In the example above, because neither `left` nor `right`  have a user-defined type, the meaning of the `*` is defined according to the language's standards (i.e., it happens at language design time). However, that association cannot be made until the time that the program is compiled because it is not until that moment that it is possible to tell the types of `left` and `right`. If, returning to the example above, the types of `left` and `right` were a user-defined matrix type, then the meaning of the `*` could have been different. How cool?!

#### Python

To truly highlight how important it is to understand the (timing of) bindings in a particular language, let's compare the following Python with the C++ above.

```Python
def operate_on(left, right):  
    result = left * right
    return result
```

The two snippets look eerily similar. We discussed the meaning of the C++ code but never ran it. Sad. Let's not make the same mistake again. What happens when we execute `operate_on` with some different arguments:

```Python
if __name__=="__main__":
    value = operate_on(5, 2)
    print(f"{value=}")
``` 

```
value=10
```

Okay, there's really no surprise there. The program operates exactly how most of us expected. But, Python is not C++ ...

```Python
if __name__=="__main__":
    value = operate_on("ha", 2)
    print(f"{value=}")
``` 

```
value="haha"
```

What? I mean, it's _really_ not C++:

```Python
if __name__=="__main__":
    value = operate_on([1,2,3], 2)
    print(f"{value=}")
``` 

```
value=[1,2,3,1,2,3]
```

Okay. Enough trickery. The point is not that you need to memorize that Python exhibits this behavior. The point _is_ that you need to know that a language could exhibit this behavior _and_ you need to be able to use the proper vocabulary to that behavior. Because the meaning of the `*` changes based on the type of `left` and `right`, the binding cannot be made until those types are known. In Python, the type of a variable is not known until the program is executed. In other words, the binding of the semantics (attribute) of the `*` (entity) cannot happen in Python until runtime. That is far, far different than the situation with binding the meaning to the `*` in C++.

These are just a few examples of the importance of the role of (times of) binding between attributes and entities in a programming language (or a program written in that language). In the next edition of the Daily PL, look for an in-depth journalistic investigation into the six (6) different attributes of variables and how the times of the binding of those attributes to values can play a big role in whether or not a program you write is correct.