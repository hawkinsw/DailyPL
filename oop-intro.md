We turn the page from imperative programming and begin our work on object-oriented programming!

### The Definitions of Object-Oriented Programming

We can define object-oriented programming using four different definitions:

1.  A language with support for abstraction of abstract data types (ADTs) (yes, I do mean to say that twice!).​ (from Sebesta)
2.  A language with support for objects which are containers of data (attributes, properties, fields, etc.) and code (methods).​ (from [Wikipedia](https://en.wikipedia.org/wiki/Object-oriented_programming))
3.  Pertaining to a technique or a programming language that supports objects, classes, and inheritance; Some authorities list the following requirements for object-oriented programming: information hiding or encapsulation, data abstraction, message passing, polymorphism, dynamic binding, and inheritance. (from ISO in standard 2382:2015)
4.  Messaging (i.e., message passing), local retention and protection and  hiding of state-process, and extreme late-binding of all things. (from [personal correspondence with Alan Kay](http://userpage.fu-berlin.de/~ram/pub/pub_jf47ht81Ht/doc_kay_oop_en))

As graduates of CS1021C and CS1080C, the second definition is probably not surprising. The first definition, however, leaves something to be desired. Using Definition (1) means that we have to a) know the definition of _abstraction_ and _abstract data types_ and b) know what it means to apply abstraction to ADTs.

### Abstraction (Reprise)

There are two fundamental types of abstractions in programming: process and data. We have talked about the former but the latter is new. When we talked previously about process abstractions, we did attempt to define the term abstraction and even had some success. Let's review that discussion and our conclusions.

_Sebesta_ formally defines _abstraction_ as the view or representation of an entity that includes only the most significant attributes. This definition seems to align with our notion of abstraction especially the way we use the term in phrases like "abstract away the details." It didn't feel like a good definition to me until I thought of it this way:

Consider that you and I are both humans. As humans, we are both carbon based and have to breath to survive. But, we may not have the same color hair. I can say that I have red hair and you have blue hair to point out the significant attributes that distinguish us. I need not say that we are both carbon based and have to breath to survive because we are both human and we have "abstracted away" those facts into our common humanity.

Again, this definition of abstraction feels intuitive especially when we put it together with the notion of inheritance (read on!).

There's another interesting definition of _abstraction_ that I think works slightly better. Let's try it on for size:

_Abstraction_: Removing the detail to simplify and focus attention on the essence.

Oh, I like that! Or, if that doesn't suit your fancy, how about this:

_Abstraction_: Remembering what is important in a given context and forgetting what's not.

That's pithy!

(Kramer, Jeff. Is Abstraction the Key to Computing? _Communications of the ACM._ April 2007. Vol. 50, No. 4)

### Abstract Data Types (ADTs)

We are all very familiar with process abstraction but we need to spend time talking about it's powerful sibling: _data abstraction_. As functions, procedures and methods are the syntactic and semantic means of abstracting processes in programming languages, ADTs are the syntactic and semantic means of abstracting _data_ in programming languages. ADTs combine (_encapsulate_) data (usually called the ADT's _attributes_, _properties_, etc) and operations that operate on that data (usually called the ADT's _methods_) into a single entity.

If that sounds almost exactly like the definition of a type, that's because ... well, it is! Remember how we said that a type defines 

1. The range of valid values; and
2. The range of valid operations on those values?

Well, (1) for ADTs is the data that we encapsulated (those properties or attributes) and (2) are the methods.

_Hiding_ is a significant advantage of ADTs. ADTs hide the data being represented and allow its manipulation only through pre-defined methods, the ADT's _interface_. The interface typically gives the ADT's user the ability to manipulate/access the data internal to the type and perform other semantically meaningful operations (e.g., sorting a list).

Although the term may be new, I am sure that you have used ADTs before:

1.  Stack
2.  Queue
3.  List
4.  Array
5.  Dictionary
6.  Graph
7.  Tree
8.  Heap

These are are so-called _user-defined ADTs_ because they are defined by the user (deep, huh?) of a programming language. In other words, they are not built in to the language by the language designers. A user-defined ADT can be composed of primitive data types _and_ other user-defined ADTs.

Here's something to consider: Are primitives a type of ADT? A primitive type, like floating point numbers, would seem to meet the definition of an abstract data type:

1.  It's underlying representation is hidden from the user (the programmer does not care whether FPs are represented according to IEEE754 or some other specification)
2.  There are operations that manipulate the data (addition, subtraction, multiplication, division).

#### Parameterized ADTs

One of the most _fundamental_ ADTs in the computer scientist's toolchest is the stack. I am sure that you have all worked with a stack before. The stack _contains_ a list of items chronologically ordered according to the time that they were added to the list. The stack is a last-in-first-out (LIFO) data structure. The stack supports the following operations:

1.  top: Retrieve a copy of the item most recently inserted into the list.
2.  pop: Retrieve the item most recently inserted into the list and remove it from the list.
3.  push: Add a new element to the list.

As developers we obviously want to know, just _what type_ of elements can we store in this "list"? Well, anything really, we just need to write the code appropriately. Let's say that we are writing a simple integer calculator so we will need a stack of numbers. In Java, we would have something that looked like this:

```Java
package edu.uc.cs.cs3003;

import java.util.ArrayList;
import java.util.EmptyStackException;
import java.util.List;

public class Stack {
    Stack() {
        m_data = new ArrayList<Integer>();
    }

    public void push(Integer newelement) {
        m_data.add(newelement);
    }

    public Integer top() throws EmptyStackException {
        if (m_data.size() == 0) {
            throw new EmptyStackException();
        }
        return m_data.get(m_data.size() - 1);
    }

    public Integer pop() throws EmptyStackException {
        if (m_data.size() == 0) {
            throw new EmptyStackException();
        }
        Integer top = top();
        m_data.remove(m_data.size() - 1);
        return top;
    }

    private List<Integer> m_data;
}
```

Great. We have all the operations that we need. We can easily use that data structure in a Java program like this:

```Java
package edu.uc.cs.cs3003;

import java.util.EmptyStackException;

public final class App {

    private static void TestStack() {
        Stack stack = new Stack();

        stack.push(5);
        stack.push(10);
        stack.push(15);
        stack.push(20);

        System.out.println(stack.pop());
        System.out.println(stack.pop());
        System.out.println(stack.pop());
        System.out.println(stack.pop());

        try {
            System.out.println(stack.pop());
        } catch (EmptyStackException ese) {
            System.out.println("Oops: " + ese.toString());
        }
    }

    public static void main(String[] args) {
        TestStack();
    }
}
```
When we run it, we see the output:

```console
20
15
10
5
Oops: java.util.EmptyStackException
```

Perfect! Exactly what we wanted. Even the logical error that we (I) committed is caught.

There's just one. small. problem. What do we do if there comes a time when I want to use my Stack ADT in an application that is not a calculator? In other words, I will need the Stack ADT to contain elements that are, say, characters when I am using a Stack ADT to determine if two strings are palindromic.

I guess I could just write the entire ADT again. I could name it something like `CharacterStack`. That just leads us to another question: What if, now, I need a Stack ADT that will let me contain elements that are Pancakes (what better thing in the world is there than a stack of pancakes?). I rewrite the Stack ADT and name it something like `PancakeStack` ... where does the craziness stop??

It stops right here, with _parameterized ADTs_: An ADT that can store elements of any type. (alternate definition: An ADT parameterized with respect to the component type [[courtesy](http://www.cs.kent.edu/~durand/CS43101Fall2004/DT-UserDefinedADT.html)]).

In Java, these parameterized ADTs are known as _generics_ and they look like templates in C++. Here is how we would write the same Stack in a generic manner:

```Java
package edu.uc.cs.cs3003;

import java.util.ArrayList;
import java.util.EmptyStackException;
import java.util.List;

public class GStack<ElementType> {
    GStack() {
        m_data = new ArrayList<ElementType>();

    }

    public void push(ElementType newelement) {
        m_data.add(newelement);
    }

    public ElementType top() throws EmptyStackException {
        if (m_data.size() == 0) {
            throw new EmptyStackException();
        }
        return m_data.get(m_data.size() - 1);
    }

    public ElementType pop() throws EmptyStackException {
        if (m_data.size() == 0) {
            throw new EmptyStackException();
        }
        ElementType top = top();
        m_data.remove(m_data.size() - 1);
        return top;
    }

    private List<ElementType> m_data;
}
```

`ElementType` here is a parameter to the class and will help Java create versions of the `Stack` class that are customized to the type of data that programmers want to store in their stacks.

`ElementType` acts like a variable, albeit a special variable. All variables in Java have types. `ElementType` has a type, too, and, as we know, that types define the range of valid values that a variable of that type can hold. So, just what are those valid values for a variable that represents a generic? 

Drumroll ...

_types_

The _type variable_ named `ElementType` can hold values like `String` or `int` or `float` or ... you get the idea. The class above, `Stack` is said to be _parameterized_ by a type. As you know, with functions, parameters usually need arguments. The same is true for type parameters. In order to instantiate an instance of the parametric `Stack` type, we need to give it a _type argument_. As arguments give a value to a parameter in a function, a type argument gives a value to the type parameter. As such, it should be one of the type variable's valid values.

In order to instantiate an element of the parametric `Stack` ADT that will hold, say, `char`acters, we would write something like

```Java
GStack<Character> stack = new GStack<Character>();
```

Let's use that to write something that is more than trivial to see how we can harness the power of generic types:

```Java
    private static void TestGStack() {
        GStack<Character> stack = new GStack<Character>();

        stack.push('a');
        stack.push('b');
        stack.push('c');
        stack.push('d');

        System.out.println(stack.pop());
        System.out.println(stack.pop());
        System.out.println(stack.pop());
        System.out.println(stack.pop());

        try {
            System.out.println(stack.pop());
        } catch (EmptyStackException ese) {
            System.out.println("Oops: " + ese.toString());
        }
    }
```

And look at this amazing output:

```console
d
c
b
a
Oops: java.util.EmptyStackException
```

If you want to see all the code for this demo so that you can explore it yourself, it's online [here](https://github.com/hawkinsw/cs3003/tree/main/adts/stack).