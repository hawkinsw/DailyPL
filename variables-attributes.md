### What's News

NASA held a press conference today announcing the results a long-running study that the investigators promised would give us insight into the fundamental fabric of nature. Their trillion dollar study concluded that the only thing that stays the same is that everything changes.

### Variables

At the risk of sounding repetitive, it is important to remember that programs written in imperative programming languages exist to modify their state. That is _the_ reason that we write programs in the procedural programming paradigm. Programs written in procedural programming language keep their state in the memory of the system -- a system that is typically arranged according to the Von Neumann architecture. 

These imperative programming languages provide access to the state through _variables_. The way that we change the program's state is through assignment of values to variables and making sure that we change the state in the proper way is fundamental to writing correct programs. One way to make it easier to write correct programs in the imperative paradigm is for the language to help us assign only meaningful values to those variables.

"Meaningful" values, in this context, can be defined in comparison to meaningless values. Meaningless values are values that just don't make sense. For example, does it make any sense to assign the date July 4, 1776 to a variable that is designed to hold a temperature? Of course not!

The variable is nothing more than a thin, simple abstraction of a memory cell, albeit a very important one. In languages that fit in the procedural paradigm, variables have 6 attributes that make it easier for the programming and the programming language to ensure that only correct programs are written:

1.  _type_: Collection of a variable's valid data values and the collection of valid operations on those values.
2.  _name_: String of characters used to identify the variable in the program's source code.
3.  _scope_: The range of statements in a program in which a variable is visible. **Using _binding_, there is an alternative definition**: The range of statements where the name's binding to the variable is active.
4.  _lifetime_: The period of time during program execution when a variable is associated with computer memory.
5.  _address_: The place in memory where a variable's contents (value) are stored. This is sometimes called the variable's _l-value_ because only a variable associated with an address can be placed on the _left_ side of an assignment operator.
6.  _value_: The contents of the variable. The value is sometimes call the variable's _r-value_ because a variable with a value can be used on the _right_ side of an assignment operator.
