## What's News

In just a few weeks, the royalty of the fashion world will descend on NYC for Fashion Week. When they do, everyone will be trying to answer the question: who wore it best? Was there a conclusive winner? Viewers will likely decide, as they have in years past, that the best new collection depends on combination of the outfit and the people wearing it. In other words, the reputation and allure of fashion houses usually depend on how well suited (pun definitely intended) their attire is for the people wearing it!

## The Value of Studying Programming Languages

Every new language that you learn gives you new ways to think about and solve problems.

The famous computer scientist Alan Perlis once said, "A language that doesn't affect the way you think about programming, is not worth knowing."[^quotes]

[^quotes]: Alan J. Perlis. 1982. Special Feature: Epigrams on programming. SIGPLAN Not. 17, 9 (September 1982), 7–13. https://doi-org.uc.idm.oclc.org/10.1145/947955.1083808

There is a parallel here with natural languages. Certain written/spoken languages have words for concepts that others do not. Linguists have said that people can only conceive ideas for which there are words. I am not sure that is absolutely the case, but I do think that they have a point.

Can the same be said for programming languages? In certain languages there may be constructs ("words") that give you a power to solve problems and write algorithms in new, interesting ways. Having studied (broadly) programming languages, you will know these constructs and be able to deploy them appropriately to solve a given problem.

With a broad and complete knowledge of programming languages, you are equipped with the power to choose the right tool for the job. When all you have is a hammer, everything looks like a nail.

Knowing about myriad programming languages makes you an increasingly flexible programmer. In fact, the more you know about the concepts of programming languages (and how those concepts are embedded in the PLs that you know) the easier it is to learn new languages.

Finally, studying PLs will give you the ability to use the languages you know in better ways. Consider Python code that performs the task of opening a file and reading its contents. I want the code to be robust and worry that the file the user specifies is not available, so I use a try ... except block:

```Python
from typing import TextIO
def ioRead(file: TextIO) -> str:
    pass
if __name__=='__main__':
    try:
        readable = open("input.txt", mode="r")
        result = ioRead(readable)
    except OSError as ose:
        print(f"error: {ose}")
```

Well, that's great, but it is a little verbose. What's more, I forgot one important step: closing the file object that I opened. As PL pros, you would look at the situation and realize that there must be a better way. Indeed there is:

```Python
from typing import TextIO
def ioRead(file: TextIO) -> str:
    pass
if __name__=='__main__':
    with open("input.txt", mode="r") as readable:
        result = ioRead(readable)
```

Not only will you learn how to better use the languages you know on the syntactic level, you will also get a sense for how to leverage their semantics and take advantage of their implementation. Your "awareness" can give you insight into the "right way" to do something in a particular language. For example, if you know that recursion and looping are equally performant and computationally powerful, you can choose to use the combining form[^form]  that improves the readability of your code. However, if you know that iteration is faster (and speed is important for your application) then you will choose that method for invoking statements repeatedly.

[^form]: I am misappropriating _combining form_ from a paper by John Backus [that you will read later in the semester]. I am using it [loosely] the way that he does: to describe patterns or forms in programming languages that allow sequences of statements to be combined. e.g. `for`, `while`, `if` ... `else`.

## Programming Domains

We do not write programs in a vacuum -- we write them to solve real-world problems.

The problems that we are attempting to solve lend themselves to solutions in particular programming languages with certain characteristics. Some of those real-world problems are meta (no, not that [meta](https://www.meta.com/)) because they are all about helping others solve their real-world problems. The solutions to these problems are known as systems programs and include operating systems, utilities, compilers, interpreters, drivers, servers, etc. There are a number of good languages for writing these applications: C, C++, Rust, Python, Go, etc. Languages used to write systems software need to be fast, safe and allow access to the underlying hardware, to name a few of the requirements.

However, most of programs that are written are designed/written to solve actual, real-world problems:

- scientific calculations: these applications need to be fast (highly parallel?) and mathematically precise (work with numbers of many kinds). Scientific applications were the earliest programming domain and inspired the first high-level programming language, Fortran.
- artificial intelligence: What sets AI applications apart from other applications is that they compute my manipulating symbols (in particular, lists of symbols) as opposed to numbers. This application requirement gave rise to a special type of language designed especially for manipulating lists, Lisp (List Processor).
- world wide web: WWW applications must embed code in data (HTML). Because of how WWW applications advance so quickly, it is important that languages for writing these applications support rapid iteration. Common languages for writing web applications are PERL, Python, JavaScript, Ruby, Go, etc.
- business: business applications need to produce reports, process character-based data, describe and store numbers with specific precision (aka, decimals). COBOL has traditionally been the lingua franca of business application developers, although new business applications are being written in other languages these days (Java, the .Net languages). 
- machine learning: machine learning applications require sophisticated math and algorithms and most developers do not want to rewrite these when good alternatives are available. For this reason, a language with a good ecosystem of existing libraries makes an ideal candidate for writing ML programs (Python, Julia, Mojo).
- game development: So-called AAA games must be fast enough to generate lifelike graphics and immersive scenes in near-real time. For this reason, games are often written in a language like C++ that is expressive but generates code that is optimized. Other games do not require such high performance and are better written in a language that integrates well with a toolkit where interactivity is supported across multiple platforms. Examples of integrations between toolkit and language for writing games include Unity (C#) and Godot (GDScript).

This list of programming domains is non-exhaustive, obviously! Can you think of other good examples of common programming domains?