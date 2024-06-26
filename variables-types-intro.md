## What's News

A company specializing in finding actors to portray programmers in movies and on TV had a successful IPO today. Type Casting's shares rose 35% in their first day on the market.

## Just My Type

Although engaging in a discussion about the importance of types in a programming language with PL researchers and afficianados is sure to lead to a heated conversation, there is nothing controversial about variables having an associated type, _per se_. With the advent of modern high-level languages (In an academic article about the history of early programming languages, Don Knuth wrote that Zuse's Plankalkul was one of the first languages whose variables had associated types -- at least in a way that would be recognizable to us!), programmers gained the ability to specify, with precision, the valid values that a variable could hold and the valid operations a programmer could perform on those values. In other words, the programmer gained the power to specify the type of a variable.

Furthermore, just to be sure that _type_ doesn't run off on an ego trip, it is important to remember that the association between type and variable is a _binding_ just like the 5 other attribute-entity bindings that apply to variables. Given that a variable's type is just one of the variable's bindings, then we can conclude that the time those bindings are made can be differentiated depending on whether the association is made statically or dynamically.

## Statically Typed Language

In a statically typed programming language, the variable-type binding is made before the program executes and does not change throughout the entirety of program execution. That should not be a surprising statement given what we know about "the first 5" binding times and the definition of _static binding_s.

Common examples of statically typed programming languages are C++, Rust, Go, and Java.

## Dynamically Typed Language

On the other end of the spectrum are dynamically typed programming languages. A dynamically typed programming language is one whose variable-type association is made at runtime _or_ is made before runtime and may change throughout the program execution. Again, that statement should make sense given what we know about binding times.

Common examples of dynamically typed programming languages are Python, Ruby, and JavaScript.

## Associating Types With Variables

Whether variables are given types statically or dynamically, every language has a process of making that association. The associations between type and variable can be made _explicitly_ or _implicitly_.

> Note: With the just-introduced addition of the difference between implicitly and explicitly typed programming languages, we can create a chart with four quadrants to categorize languages with respect to their use of types: On one axis is static/dynamic and on the other axis is explicit/implicit. Therefore, it is possible to have an explicitly statically typed language or an implicitly dynamically typed language or even some other combination. In the future we will add another axis to the schema according to how strongly or weakly typed variables are in a given programming language!

### Explicit

When we, the tired programmer, are forced to expend what little energy we have in our fingers to type out the type (get it?) of each and every variable that we declare, we are working in an explicitly typed language. Until very recently, C++ was exclusively explicitly typed (see below for the _new_ thing in C++):

```C++
int main() {
    int x{0};
    int y{0};
    double z{0.0};
    return 0;
}
```

Notice how for each of the three variables we had to explicitly label the types. I am so tired.

### Implicit

If we are following best practices and always initializing our variables, then we are already giving the compiler an example of one of the valid values of a particular type to assign to a variable. If that initial value can be a member of the set of valid values of only one of the language's types, why do we need to repeat ourselves to the language (either the compiler or the interpreter)? 

#### Inference
In some implicitly typed programming languages, the types are _inferred_ from the code and we don't have to repeat ourselves! Consider this snippet of Go:

```Go
type Internet struct {
    // some fields here.
}

func main() {
    could := Internet{}
}
```

The `:=` is shorthand in Go for "declare a variable and give it some initial contents". In the case above, we are telling Go to declare a variable named `could` and give it the initial assignment of an instance of the `Internet` data structure. Go can look at the type of the expression defining the variable's initial value and _infer_ the type of the variable we are declaring. We don't have to type it again! That's awesome!

Think back to what you know about C++ ... is there a modern(ish) keyword in the language that gives it "implicit powers"? That's right, the `auto` keyword:

```C++
int main() {
    auto name{std::string{"Derek"}};
    return 0;
}
```

Because we are initializing `name` with an expression whose type is `std::string`, the compiler is smart enough to infer that we are declaring a string!

Even in dynamically typed languages, types can be bound to variables through inference. Consider this snippet of Python:

```Python
from bintrees import BinaryTree

class Address():
    def __init__(self, street: str):
        self.__street = street

if __name__ == "__main__":
    pine = Address("349 Pine Dr.")
    pine = BinaryTree()
    print("")
```

The type of `pine` is inferred from the type of the expression used to update its value. The first assignment to `pine` not only changes the value of `pine` but it also changes the type (to `Address`). The second assignment does something similar: it changes the value of `pine` and the type (to `BinaryTree`).

> Note: You can use the built-in function named `type` in Python to determine the type of a variable when the program is executing. For instance,
>

```Python
from bintrees import BinaryTree

class Address():
    def __init__(self, street: str):
        self.__street = street

if __name__ == "__main__":
    pine = Address("349 Pine Dr.")
    print(f"I live at {type(pine)}")
    pine = BinaryTree()
    print(f"I climb {type(pine)}-s")
    print("")
```
> will print

```
I live at <class '__main__.Address'>
I climb <class 'bintrees.bintree.BinaryTree'>-s
```

#### By Convention

And now for something weird and wild. There are certain modern languages that do not have types (in the strictest sense of the term). That makes it very difficult for programmers to determine whether their use of a variable is legal. One option when faced with this challenge is to write code that "gives" types to variables by convention on the way that variables are named. 

The earliest example of such a convention-for-types-according-to-names was in the original Fortran: As _Sebesta_ says:

> There were no data-typing statements in the Fortran I language. Variables whose names began with `I`, `J`, `K`, `L`, `M` and `N` were implicitly integer type, and all others were implicitly floating-point.

In a case of What's Old Is New Again, Charles Simonyi, a famous developer at Microsoft settled on a convention for naming variables that eventually became known as Hungarian Notation. Even though programmers at Microsoft now all use languages with data types, the Hungarian Notation convention persists in the code for the Windows operating system and the API. In Hungarian notation, the type of the variable is prepended to the name of the variable. If we used Hungarian Notation to keep track of variable names in JavaScript, we might write code that looks like:

```JavaScript
var fHappy = true;

if (fHappy == true) {
    szLocation = "PL Class"
} else {
    szLocation = "Calculus I"
}
```

The `f` prepended to `Happy` is Hungarian Notation for a _flag_ variable and the `sz` prepended to the `Location` variable stands for a _string_. 

When a programmer is working in a code base that uses Hungarian Notation and thought that the location variable was designed to hold GPS coordinates, they might write the following assignment statement:

```JavaScript
szLocation = { 'latitude': 84, 'longitude': 51 }
```

Immediately after writing that code they would realize they are in a heap of trouble -- a JavaScript object (which is written here between the `{` and `}`) is not a string and they could see their mistake thanks to the `sz` prefix!