### What's News

Zoologists have long studied the odd fashion sensibilities of wolves. The mod [canis lupus](https://en.wikipedia.org/wiki/Wolf) is the envy of all North American canines and can be regularly seen on the runway in New York's Fashion Week. Scientists this week have finally discovered why they like dressing up in [sheep's clothing](https://en.wikipedia.org/wiki/Wolf_in_sheep%27s_clothing) as much as they do.

## Subprograms - Polymorphism

_Polymorphism_ allows subprograms to take different types of parameters on different invocations. There are two types of polymorphism:

1.  _ad-hoc polymorphism:_ A type of polymorphism where the semantics of the function may change depending on the parameter types.
2.  _parametric polymorphism_: A type of polymorphism where subprograms take an implicit/explicit type parameter used to define the types of their subprogram's parameters; no matter the value of the type parameter, in parametric polymorphism the subprogram's semantics are always the same.​

Ad-hoc polymorphism is sometimes call function overloading (C++). Subprograms that participate in ad-hoc polymorphism share the same name but must have different protocols. If the subprograms' protocols and names were the same, how would the compiler/interpreter choose which one to invoke? Although a subprogram's protocol includes its return type, not all languages allow ad-hoc polymorphism to depend on the return type (e.g., C++). See the various definitions of `add` in the C++ code here: [https://github.com/hawkinsw/cs3003/blob/main/subprograms/subprograms.cpp](https://github.com/hawkinsw/cs3003/blob/main/subprograms/subprograms.cpp). Note how they all have different protocols. Further, note that not all the versions of the function `add` perform an actual addition! That's the point of _ad-hoc polymorphism_ -- the programmer can change the meaning of a function.

Functions that are parametrically polymorphic are sometimes called function templates (C++) or generics (Java, Go, Rust). A parametrically polymorphic function is like the blueprint for a house with a variable number of floors. A home buyer may want a home with three stories -- the architect takes their variably floored house blueprint and "stamps out" a version with three floors. Languages variously call the process _instantiating_ a parametrically polymorphic function. Others call it [monomorphization](https://en.wikipedia.org/wiki/Monomorphization).

The type parameter of a parametrically polymorphic function can be either inferred from the types of the arguments to a particular invocation (or call) of the function or specified explicitly.

Here's an example from C++:

1 template <typename T> T minimum(T a, T b) {
2   if (a <= b) {
3     return a;
4   } else {
5     return b;
6   }
7 }
8 

Note that there is only _one_ definition of the function! In C++, the type parameter referred to in the definition of _parametric polymorphism_ is explicit -- in this case `T`. When a programmer uses a parametrically polymorphic function by calling it, a value for `T` is deduced from the types of the arguments in the call. Every time the compiler sees a user make a call with a different version of `T`, the compiler will "stamp out" a new copy of `minimum` with different types that replace `T`.

When the programmer writes,

    auto m = minimum(5, 4);

the compiler will generate

1 int minimum(int a, int b) {
2   if (a <= b) {
3     return a;
4   } else {
5     return b;
6   }
7 }

behind the scenes.

You can verify that this is, indeed, the case by using an awesome tool known as [C++ Insights](https://cppinsights.io/). The particular example just explored can be seen [here](https://cppinsights.io/s/1b8aa1e2).

In Go, the newest language to offer such parametric polymorphism, the same example would look like:

    import (
        "fmt"
        "golang.org/x/exp/constraints"
    )
    
    func minimum[T constraints.Ordered](a T, b T) T {
        if a < b {
            return a
        } else {
            return b
        }
    }

There is a very interesting difference between the Go version of `minimum` and the C++ version. In addition to requiring that the developer specify that the function `minimum` takes a parametric type (named `T` in this case), Go requires an additional bit of information (in this case `constraints.Ordered`). The additional bit of information is (not surprisingly) known as a _constraint_. Constraints on type parameters are like types on variables -- they limit the range of valid values for the type parameter. In this case, the `constraints.Orderable` constraint specified by the programmer for `minimum` tells the user of the parametrically polymorphic `minimum` function that the only valid types that can be accepted by an instance of the `minimum` function are those that can be _ordered_. The constraint specifies the operations that a type must support to be usable in the context. For instance, for `minimum`, it would make no sense to call the function with two arguments whose values cannot be ordered relative to one another (how could you calculate the minimum, then?). C++ has added similar functionality (known as concepts) and Rust has traits.