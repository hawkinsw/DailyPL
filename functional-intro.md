## Introduction to Functional Programming

As we said at the beginning of the semester when we were learning about programming paradigms, FP is very different than imperative programming. In imperative programming, developers tell the computer how to do the operation. While functional programming is _not_ logic programming (where developers just tell the computer _what_ to compute and leave the _how_ entirely to the language implementation), the writer of a program in a functional PL is much more concerned with specifying what to compute than how to compute it.

![](./graphics/Programming-Language-What-How-Continuum.png)

### Four Characteristics of Pure, Strongly-Typed Functional Programming

In this class, we are going to study a subset of functional programming languages. We are going to study pure, strongly-typed functional programming languages. There are four characteristics that epitomize these languages:

1.  There is no state
2.  Functions are central
    1.  Functions can be parameters to other functions
    2.  Functions can be return values from other others
    3.  Program execution _is_ function evaluation
3.  Control flow is performed by recursion and conditional expressions
4.  Lists are a fundamental data type

In a pure, strongly-typed functional programming language, there are no variables, per se. And because there are no variables, there is no state. That does _not_ mean there are no names. Names are still important. It simply means that names refer to expressions themselves and not their values. The distinction will become more obvious as we continue to learn more about writing programs in functional languages.

Because there is no state, a pure, strongly-typed functional programming language is not _history sensitive._ A language that is _history sensitive_ means that results of operations in that language can be affected by operations that have come before it. For example, in an imperative programming language, a function may be history sensitive if it relies on the value of a global variable to calculate its return value. Why does that count as history sensitive? Because the value in the global variable could be affected by prior operations.

A language that is not history sensitive has _referential transparency._ We learned the definition of referential transparency before, but now it might make a little more sense. In a language that has referential transparency, the same function called with the same arguments generates the same result no matter what operations have preceded it.

In all functional programming languages, there are no loops (unless they are added as syntactic sugar) -- recursion is _the_ way to accomplish repetition. Selective execution (as opposed to sequential execution) is accomplished using the _conditional expression_. A conditional expression is, well, an _expression_ that evaluates to one of two values depending on the value of a condition. We have seen conditional expressions in STIMPL. That a conditional statement can have a value (thus making it a conditional expression) is relatively surprising for people who only have experience in imperative programming languages. Nevertheless, the conditional expression is a very, very sharp sword in the sheath of the functional programmer.

A functional program is a series of functions and the execution of a functional program is simply an evaluation of those functions. That sounds abstract at this point, but will become more clear when we see some real functional programs.

Lists are a fundamental data type in functional programming languages. Powerful syntactic tools for manipulating lists are built in to most functional PLs. Understanding how to wield these tools effectively is vital for writing code in functional PLs.

## The Historical Setting of the Development of Functional PLs

The first functional programming language was developed in the mid-1950s by [John McCarthy](https://en.wikipedia.org/wiki/John_McCarthy_(computer_scientist)). At the time, computing was most associated with mathematical calculations. McCarthy was instead focused on artificial intelligence which involved symbolic computing. Computer scientists thought that it was possible to represent cognitive processes as lists of symbols. A language that made it possible to process those lists would allow developers to build systems that work like our brains, or so they thought.

![](./graphics/johnmccarthy.jpg)

McCarthy started with the goal of writing a system of meta notation that programmers could attach to Fortran. These meta notations would be reduced to actual Fortran programs, he thought. As they did their work, they found their way to a program representation built entirely of lists (and lists of lists, and lists of lists of lists, etc.). Their thinking resulted in the development of Lisp, a *lis*t *p*rocessing language. In Lisp, both data and programs are lists. McCarthy and his team showed that list processing, the basis of the semantics of Lisp, is capable of universal computing. In other words, Lisp, and other list processing languages, is/are Turing complete.

The inability to execute a Lisp program efficiently on a physical computer based on the von Neumann model has given Lisp (and other functional programming languages) a reputation as slow and wasteful. 

> Note:_ This is _not true_ today!

Until the late 1980s hardware vendors thought that it would be worthwhile to build physical machines with non-von Neumann architectures. In fact, they built one such machine that made executing Lisp programs faster. Here is an image of a so-called Lisp Machine.

![](./graphics/LISP_machine.jpg)

## LISP

Though we will not study Lisp in this course, there are a few aspects of Lisp that you should know because they pervade the general field of computer science.

First, you should know `CAR`, `CDR` and `CONS` -- pronounced *car*, *could-er*, and *cahns*, respectively. `CAR` is a function that takes a list as a parameter and returns the first element of the list. `CDR` is a function that takes a list as a parameter and returns the tail, everything but the head, of the list. `CONS` takes two parameters -- a single element and a list -- and *cons*tructs a new list with the first argument appended to the front of the second argument.

For instance,

```lisp
(car (1 2 3))  
```

```lisp
is `1`.
```

```lisp
(cdr (1 2 3))
```

is `(2 3)`.  

Second, you should know that, in Lisp, all data are lists _and_ programs are lists.

```lisp
(a b c)
```

is a list in Lisp. In Lisp, `(a b c)` could be interpreted as a list of _atoms_ `a`, `b` and `c` _or_ an invocation of function _a_ with parameters _b_ and _c_. ​

## Lambda Calculus

Lambda Calculus is the theoretical basis of functional programming languages in the same way that the Turing Machine is the theoretical basis of the imperative programming languages. The Lambda Calculus is nothing like "calculus" -- the word calculus is used here in its strict sense: [a method or system of calculation](https://en.wikipedia.org/wiki/Calculus_(disambiguation)). It is better to think of Lambda Calculus as a (albeit primitive) programming language rather than a branch of mathematics.

Lambda Calculus is a model of computation defined entirely by function application. The Lambda Calculus is as powerful as a Turning Machine which means that anything computable can be computed in the Lambda Calculus. For a language as simple as the Lambda Calculus, that's remarkable!

The entirety of the Lambda Calculus is made up of three entities:

1.  Expression: a _name_, a _function_ or an _application_
2.  Function:  $\lambda$ *\<name\>* `.` *\<expression\>*
3.  Application: *\<expression\>* *\<expression\>*

Notice how the elements of the Lambda Calculus are defined in terms of themselves. In most cases it is possible to restrict _name_s in the Lambda Calculus to be any single letter of the alphabet -- `a` is a name, `z` is a name, etc. Strictly speaking, functions in the Lambda Calculus are anonymous -- in other words they have no name. The _name_ after the $\lambda$ in a function in the Lambda Calculus can be thought of as the parameter of the function. Here's an example of a function in the Lambda Calculus:

$$
\lambda x . x
$$

Lambda Calculiticians (yes, I just made up that term) refer to this as the _identity_ function. This function simply returns the value of its argument! But didn't I say that functions in the Lambda Calculus don't have names? Yes, I did. _Within_ the language there is no way to name a function. That does not mean that we cannot assign semantic values to those functions. In fact, associating meaning with functions of a certain format is _exactly_ how high-level computing is done with the Lambda Calculus.