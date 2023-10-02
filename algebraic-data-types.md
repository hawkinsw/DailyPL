## What's News

More and more educators are beginning to teach elementary algebra according to a new technique. The new methods are making it easier for youngsters to use math to prove that $1 + 1$ really does equal $2$.

## Algebraic Data Types

Computer scientists love to name things. Too bad that they aren't very good at it. As the [adage](https://martinfowler.com/bliki/TwoHardThings.html) [goes](https://twitter.com/timbray/status/817025379109990402?cn=cmVwbHk%3D), there's only two things that are really hard about computer science:

1.  Cache invalidation;
2.  Naming things;
3.  Off-by-1 errors.

Get the joke? Yeah, it's bad. Algebraic Data Types (ADTs, but do _not_ confuse these ADTs with the ADTs of abstract data types fame) are one of the concepts in computer science that, I think, have an ungainly name that makes the concept harder to grasp than it needs to be. There are two kinds of ADTs: the _sum type_ and the _product type_.

Sum types look like a union. To be more precise, sum types look like discriminated unions. Like a union, the value of a sum-typed variable is one of $n$ different types (the valid possible types are listed at the time the sum type is declared -- it's not a free for all!). At runtime, the value of a sum-typed variable is either type $a$, type $b$, type $c$, etc. It is never more than one type at the same time and the type that it holds can change as the program executes. In C++, sum types are known as [_variants_](https://en.cppreference.com/w/cpp/utility/variant). In Rust, sum types are known as [`enums`](https://doc.rust-lang.org/book/ch06-01-defining-an-enum.html).

Like discriminated unions, we programmers can always ask about the type of value that is _active_ in a sum-typed variable. We can write code that looks like this:

    ActionSumType = { GoAction | StopAction }
    function handle_action(action ActionSumType) {
      if (IsGoAction(action)) {
        // make it go.
      } else if (IsStopAction(action)) {
        // make it stop.
      } else {
        // There's no way for this case to ever happen!
      }
    }

What differentiates sum types from discriminated unions (and one of the reasons that computer scientists decided to give them a unique name), is _usually_ the way that they interact with other parts of a programming language. Values for sum-typed variables are usually instantiated with a _constructor_. Yes, you know the term constructor from object-oriented languages like Java and C++ and the concept here is very similar. Returning to the `ActionSumType` example from above, we would instantiate a variable with the `ActionSumType` type by using a constructor like this:

```
    ActionSumType myAction = GoAction()
```

Later, I could reassign it to a `StopAction`:

```
    myAction = StopAction()
```

The second unique power of sum-typed variables is their ability to work with _pattern matching_. Pattern matching is a really amazing language construct that came from functional programming languages and is now making its way in to imperative programming languages (e.g., Rust, Python, C++.). Pattern matching against a sum type is akin to a `switch` statement. In a switch statement, we programmers define a series of actions to execute depending on the _value_ of a variable. However, in pattern matching, we programmers define a series of actions depending on the _type_ of a variable. Now _that_ is neat! Let's replace the `if`/`else-if` in the code from above using pattern matching:

```
    ActionSumType = { GoAction | StopAction }
    function handle_action(action ActionSumType) {
      match action: {
        case GoAction: {
          // make it go.
        }
        case StopAction: {
          // make it stop.
        } 
      }
    }
```

So far in our example, the `GoAction` and the `StopAction` are missing a crucial piece of information: the action to _go_ or the action to _stop_. So, let's add a piece of data that a sum-typed variable of type `ActionSumType` of value `GoAction` or of value `StopAction` carries to indicate the action to "go" and a flag to indicate whether to "stop" momentum:

```
    ActionSumType = { GoAction(action: string) | StopAction(momentum: bool)}
```

(Note: Very importantly, the data carried by two different types of variables that belong to the same sum type do _not_ have to have the same name. They don't even have to have the same type. They don't even have to be the same size!)

In our hypothetical language, our constructors for `GoAction` and `StopAction` will need syntax that allows us programmers the ability to set the value of `action`. Let's say that it looks something like this:

```
    ActionSumType myAction = GoAction(action = "run")
    ActionSumType myOtherAction = StopAction(momentum = true)
```

Awesome. Now an instance of our `ActionSumType` sum-typed variable carries around with it an `action`. But, how can we access that action?

Wait for it.

Pattern matching!

```
    ActionSumType = { GoAction(action: string) | StopAction(momentum: bool)}
    function handle_action(action ActionSumType) {
      match action: {
        case GoAction(action = vx): {
          print("I am going " + vx + " action!")
        }
        case StopAction(momentum = vx): {
          print("I am stopping.")
          if (vx) {
            print("I will have to deal with momentum!")
          } else {
            print("I don't have to worry about momentum!")
          }
        } 
      }
    }
```

The pattern matching statement reaches into the variable being matched and can pull out the value of the things that it contains! That's really cool!

The problem is that I am terribly averse to `if` statements and I still see one in the code! What can I do?

Are you sick of this yet?

Pattern Matching!

I can add a condition in the pattern to make the requirements for matching even more explicit:

```
    ActionSumType = { GoAction | StopAction }
    function handle_action(action ActionSumType) {
      match action: {
        case GoAction(action = vx): {
          print("I am going " + vx + " action!")
        }
        case StopAction(momentum = true): {
          print("I am stopping and I have to deal with momentum.")
        } 
        case StopAction(momentum = false): {
          print("I am stopping and I don't have to deal with momentum.")
        } 
      }
    }
```

Now, if you don't think that's cool, well, ...

We have been coding our examples in a pseudo language and each language that supports pattern matching has a slightly different syntax: [C++](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p1371r2.pdf), [Rust](https://doc.rust-lang.org/book/ch06-02-match.html), [Haskell](https://www.haskell.org/tutorial/patterns.html), [Python](https://peps.python.org/pep-0634/).

For a tutorial/introduction to pattern matching in Python, check out the special edition of the Daily PL on the subject!

### Product Types

That was a long explanation of sum types, wasn't it? Are you ready for another long explanation of product types? Well, you aren't going to get one! Product types are much, much closer to a type of variable that is near and dear to our hearts: records. (Remember that records are just the fancy name for `struct`s in C/C++, Go, etc or data classes in Python or object literals (kinda) in JavaScript ...) In our pseudo language, a record type might be declared like this:

```
    record Album {
      title: string
      artist: string
      songs: int
      length: Duration
      rating: Stars
    }
```

And we could construct such a product type like this:

```
    Album dynamo_of_volition = Album{ title: "Dynamo of Volition", artist: "Jason Mraz" ... }
```

To access the elements contained in an instance of a product-typed variable, we usually use the `.`:

```
    print(dynamo_of_volition.title + " got " + dynamo_of_volition.rating + " stars from Rolling Stone magazine.")
```

Like I said, the utility and use of product types is much easier to comprehend!

## Why the Odd (Even?) Names?

The names are a product (pun intended) of the number of unique values that a variable whose type is sum or product can hold. I think that the concept is best defined using examples. Let's assume that we have a sum type defined like this:

```
    SomeSumType = bool | uint8
```

where `bool` is a Boolean type (can hold either true or false) and `uint8` is a integral type that can hold all the values greater than or equal to zero that can fit in 8 bits. A variable with the type `SomeSumType` can be either a `bool` or an `uint8` at any given time during the execution of a program. If that variable is a `bool` then its value could be either true or false (there's two (2) values!). If that variable is a `uint8`, then its value could be either $0$, or $1$, or $2$, or ... $2^8-1$ (there's $2^8$ more values). So, in total, the number of possible values of that variable at any given time during program execution is $2 + 2^8$. What's another term for _plus_? That's right, _sum_. Boom.

| | Active Type | Value |
|--  | -- | -- |
| 1 | `bool` | `true` |
| 2 | `bool` | `false` |
| 3 | `uint8` | $0$ |
| 4 | `uint8` | $1$ |
| ... | ... | ... |
| 258 | `uint8` | $255$ |

I bet that you can see where this is going.

Let's assume that we have a product type defined like this:
```
    SomeProductType {
      bool b 
      uint8 u
    }
```

A variable with the type `SomeProductType` contains a `bool` and an `uint8` at any given time during the execution of a program. That variable could have a `b` that is either True or False. For each of those values of `b`, the variable could have a `u` that is any of the possible values between $0$ and $2^8-1$.

| | `b` Value | `u` Value |
|--  | -- | -- |
| 1 | `true` | $0$ |
| 2 | `true` | $1$ |
| 3 | `true` | $2$ |
| 4 | `true` | $3$ |
| 5 | `true` | $4$ |
| ... | ... | ... |
| 255 | `true` | $255$ |
| 256 | `false` | $0$ |
| 257 | `false` | $1$ |
| 258 | `false` | $2$ |
| 259 | `false` | $3$ |
| 260 | `false` | $4$ |
| ... | ... | ... |
| 510 | `false` | $255$ |

So, in total, the number of possible values of a variable whose type is `SomeProductType` is $2*2^8$. What's another term for _multiply_? That's right, _product_. Boom, Boom.