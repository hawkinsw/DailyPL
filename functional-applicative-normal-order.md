## What's News

Although the economy is cooling off going in to the holiday shopping season and consumers are looking out for bargains wherever they can find them, job seekers continue to apply for jobs! It looks like a state of tightness in the labor market is something that will be part of the *new normal*.

## Function Invocation in Functional Programming Languages

In imperative programming languages, it may matter to the correctness of a program the order in which parameters to a function are evaluated. 

> Note: For the purposes of this discussion we will assume that all operators [`+`, `-`, `/`, etc] are implemented as functions that take the operands as arguments. That will simplify the discussion! In other words, when describing the order of evaluation of a function's arguments we are also talking about the order of evaluation of the operands to a binary (or unary) operator.

While the choice of the order in which we evaluate the operands is the language designer's prerogative, the choice has consequences. Why? Because of side effects! For example:

```C++
#include <stdio.h>

int operation(int parameter) {
  static int divisor = 1;
  return parameter / (divisor++);
}

int main() {
  int result = operation(5) + operation(2);
  printf("result: %d\n", result);
  return 0;
}
```

prints

```
result: 6
```

whereas

```C++
#include <stdio.h>

int operation(int parameter) {
  static int divisor = 1;
  return parameter / (divisor++);
}

int main() {
  int result = operation(2) + operation(5);
  printf("result: %d\\n", result);
  return 0;
}
```

prints

```console
result: 4
```

In the difference between the two programs we see vividly the role that the `static` variable plays in the state of the program and its ultimate output.

Because of the referential transparency in pure functional programming languages, the designer of such a language does not need to worry about the consequences of the decision about the order of evaluation of arguments to functions. However, that does not mean that the language designer of a pure functional programming language does not have choices to make in this area.

A very important choice the designer has to make is the _time_ when function arguments are evaluated. There are two options available:

1.  All function arguments are evaluated _before_ the function is invoked.
2.  Function arguments are evaluated _only when their results are needed by the function_.

Let's look at an example: Assume that there are two functions: `dbl`, a function that doubles its input, and `average`, a function that averages its three parameters:

```haskell
dbl x \= (+) x x
average a b c \= (/) ((+) a ((+) b c)) 3
```

Both functions are written using prefix notation (i.e., (<_operator_> <_operand1_> ... <_operandN_>). We will call these functions like this:

```haskell
dbl (average 3 4 5)
```

If the language designer chooses to evaluate function arguments _only when their results are needed_, the execution of this function call proceeds as follows:

```console
dbl (average 3 4 5)
+ (average 3 4 5) (average 3 4 5)
+ ((/) ((+) 3 ((+) 4 5)) 3) (average 3 4 5)
+ (4) (average 3 4 5)
+ (4) ((/) ((+) 3 ((+) 4 5)) 3)
+ (4) (4)
8
```

The outermost function is always _reduced_ (expanded) before the inner functions. Note: Primitive functions (`+`, and `/` in this example) cannot be expanded further so we move inward in evaluation if we encounter such a function for reduction.

If, however, the language designer chooses to evaluate function arguments before the function is evaluated, the execution of the function call proceeds as follows:

```console
dbl (average 3 4 5)
dbl ((/) ((+) 3 ((+) 4 5)) 3)
dbl ((/) ((+) 3 9) 3)
dbl ((/) 12 3)
dbl 4
+ 4 4
8
```

No matter the designer's choice, the outcome of the evaluation is the same. However, there is something strikingly different about the two. Notice that in the first derivation, the calculation of the average of the three numbers happens twice. In the second derivation, it happens only once! That efficiency is not a fluke! Generally speaking, the method of function invocation where arguments are evaluated _before_ the function runs faster.

These two techniques have technical names:

1.  _applicative order_:  "all the arguments to ... procedures are evaluated when the procedure is applied."​
2.  _normal order_: "delay evaluation of procedure arguments until the actual argument values are needed."​

These definitions come from

[Abelson, H., Sussman, G. J.,, with Julie Sussman (1996). Structure and Interpretation of Computer Programs. Cambridge: MIT Press/McGraw-Hill. ISBN: 0-262-01153-0](http://uclid.uc.edu/record=b2528617~S39)

It is obvious, then, that any serious language designer would choose applicative order for their language. 

There's no obvious redeeming value for the inefficiency of normal order.

## The Implications of Applicative Order

Scheme is a [Lisp _dialect_](https://en.wikipedia.org/wiki/Lisp_(programming_language)#Major_dialects). I told you that we weren't going to work much with Lisp, but I lied. Sort of. Scheme is an applicative-order language with the same list-is-everything syntax as all other Lisps. In Scheme, you would define an _if_ function named `myif` like this:

```scheme
(define (myif c t f) (cond (c t) (else f)))
```

`c` is a boolean and `myif` returns `t` when `c` is true and `f` when `c` is false. No surprises.

We can define a name `a` and set its value to 5:

```scheme
(define a 5)
 ```

Now, let's call `myif`:

```scheme
(myif (\= a 0) 1 (/ 1 a))
```

If `a` is equal to 0, then the call returns 1. Perfect. If `a` is not zero, the call returns the reciprocal of `a`. Given the value of `a`, the result is `1/7`.

Let's define the name `b` and set its value to 0:

```scheme
(define b 0)
```

Now, let's call `myif`:

```scheme
(myif (\= b 0) 1 (/ 1 b))
```

If `b` is equal to $0$, then the call returns $1$. If `b` is not zero, the call returns the reciprocal of `b`. Given the value of `b`, the result is $1$:

```console
/: division by zero
  context...:
   "/home/hawkinsw/code/uc/cs3003/scheme/applicative/applicative.rkt": \[running body\]
   temp37\_0
   for-loop
   run-module-instance!125
   perform-require!78
```

That looks _exactly_ like $1$. Uhm, no! What happened?

Remember we said that Scheme is an applicative order language. No matter what the value of `b`, both of the arguments are going to be evaluated _before_ `myif` starts. Therefore, Scheme attempts to evaluate `1 / b` which is `1 / 0` which is `division by zero`.

Thanks to situations like this, the Scheme programming language is forced into defining special semantics for certain functions, like the built-in _if_ expression. As a result, function invocation is not _orthogonal_ in Scheme -- the general rules of function evaluation in Scheme must make an exception for applying functions like the built-in if expression. Remember that the orthogonality decreases as exceptions in a language's specification increase.

### Sidebar: Solving the problem in Scheme

Feel free to skip this section if you are not interested in details of the Scheme programming language. That said, the concepts in this section are applicable to other languages.

In Scheme, you can specify that the evaluation of an expression be `delay`ed until it is `force`d.

```scheme
(define d (delay (/ 1 7)))
```

defines `d` to be the _eventual_ result of the evaluation of the division of $1$ by $7$. If we ask Scheme to print out `d`, we see

```console
#<promise:d>
```

To bring the future tense into the present tense, we `force` a `delay`ed evaluation:

```scheme
(force d)
```

If we ask Scheme to print the result of that expression, we see:

```console
1/7
```

Exactly what we expect! With this newfound knowledge, we can rewrite the `myif` function:


```scheme
(define (myif c t f) (cond (c (force t)) (else (force f))))
```

Now `myif` can accept `t`s and `f`s that are `delay`ed and we can use `myif` safely:

```scheme
(define b 0)
(myif (**\=** b 0) (delay 1) (delay (**/** 1 b)))
```

and we see the reasonable result:

```console
1
```

Kotlin, a modern language, has a concept similar to `delay` called [lazy](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/lazy.html). OCaml, an object-oriented functional programming language, [contains the same concept](https://ocaml.org/manual/coreexamples.html#s:lazy-expr). Swift has some sense of [laziness](https://docs.swift.org/swift-book/LanguageGuide/Properties.html), too!

## Well, We Are Back to Normal Order

I guess that we are stuck with the inefficiency inherent in the normal order function application. Going back to the `dbl`/`average` example, we will just have to live with invoking `average` twice.

Or will we?

Real-world functional programming languages that are normal order use an interesting optimization to avoid these recalculations! When an expression is passed around and it is unevaluated, Haskell and languages like it represent it as a [_thunk_](https://wiki.haskell.org/Thunk). The thunk data structure is generated in such a way that it can calculate the value of its associated expression some time in the future when the value is needed. Additionally, the thunk then caches (or _memoizes)_ the value so that future evaluations of the associated expression do not need to be repeated.

As a result, in the dbl/average example,

1.  a thunk is created for `(average 3 4 5)`,
2.  that thunk is passed to `dbl`, where it is duplicated during the reduction of `dbl`,
3.  `(average 3 4 5)` is (eventually) calculated when the value of `(average 3 4 5)` is needed,
4.  4 is stored (cached, memoized) in the thunk, and
5.  the cached/memoized value is retrieved from the thunk instead of doing a fresh evaluation the next time that the value of `(average 3 4 5)`is needed.

A thunk, then, is the mechanism that allows the programmer to have the efficiency of applicative order function invocation with the semantics of the normal order function invocation! The best of both worlds!