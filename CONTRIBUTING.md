# Contributing guidelines

**This guideline has not been finished yet...**

**All hail our friendship!**

It is highly exciting to cooperate with all of you, create a project and grab high score in the final examination. But to make the development experience efficient and elegant, we need to reach an agreement about following some certain rules.

# Environment

## Compiler

We are using `gcc` to compile our project, which is widely used among other major open-source projects. Compared with `MSVC`, `gcc` provides better support with new standards.

## IDE

We are using `JetBrains CLion 2017` as our IDE (Integrated Development Environment). `CLion` comes with perfect support with GNU tools, such as `gcc`, `CMake` and `gdb`. You can retrieve a genuine copy of `CLion` for free using your educational email.

# Code Style

## Naming

We use **camel case** to name variables, functions and more in our project.  

Name of variables should reflect there **real meanings in English**.

Here we provide some examples:

variable:		`roomInfo`  

function: 	`getRoomInfo()`  

##Indentation

We use **K&R** style for indentation.  

Here we provide an example:

```cpp
if (condition) {
    funcOne();
} else {
    funcTwo();
}
```

## Spacing & Line breaking

We prefer to set `TAB` to **4 spaces**.

As for line breaking, we prefer  `LF (UNIX style)` over `CRLF (Windows style)`. 

