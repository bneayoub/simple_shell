# Simple Shell Project - ALX
This is the second academic project in alx software engineering program.

we will be creating a simple shell with C.

Our shell will mainly handle a commannde without or with argument, handle exit (with and without arguments), handle env.

we ll be implementing all string handling functions later too, to work with them.

## Approach

We will be writing full code without splitting , make sure it is working, then start to refactor it.
Refactoring a code, makes it possible so that we could pass task 0 for betty requirements, and also make our code more readable.

### Why did we need to write full block before splitting it into functions?:

the main reason is to make it possible to free whatever memory was dynamically allocated and avoid duplicate frees when switchinf to multiple functions refactoring.