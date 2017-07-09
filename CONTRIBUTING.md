# Contributing to the project

We currently look for help with introducing new:
- file interpreters (used by read_data)
- parts of dataset
- starting parameters
- unit tests
- translations of .lang files

General whitespace improvements are also welcome. The list is not definite
- feel free to come up with revolutionary ideas!  

Keep in mind that **ideas are contributions in itself** - if you are not able to implement
the concept, sharing it will still be a net positive.

Whenever you make actual change to the codebase, please:  
- respect our coding style guide
- (try to) stick to commit message conventions
- run present unit tests

### Commit messages
Whenever you make a commit, give it a meaningful message. A good template to
stick to is:
- Changed_file_name(s) - Changed_function_name(s) - Short description of change  
 
First field can be replaced with "general". Second field can be ommited.   
"General" should be used for changes such as:
- General - Clean up variable naming
- General - New file en-us.lang  

Keep in mind that new source files should have their own field - for example:
- General - New file new_awesome_functionality.c
is incorrect. Use:  
- new_awesome_functionality.c - New file. Includes new awesome functionality
  for server connection  
First field can include multiple files if changes concern only those files.
Second field can include multiple functions.  
In new versions, first line of the commit message must start with 'v' - for
version - followed by new version number.

### Short Code style guide
#### Naming  
  
Names should not be too long (~15 characters is maximum). All lowercase, underscore-separated.  

#### Braces
TL;DR: **1TBS** (Google it up). Every conditional statement and loop is followed by opening brace on the same line. Closing brace is on separate from the last line
of code and it shall be the sole visible character on it`s line (unless
it is followed by 'else','else if' or 'while').  
Function opening brace shall be on separate line from the function
header.
Loops must have body - even in case there is no need for such, include opening
and closing braces on line following the loop (that is the only case where
opening brace of loop can be on new line).

#### Whitespace  
##### Function arguments
In function argument list every comma has to be followed by a space.
##### Indentation
A tab for every indent-level. Do not nest conditionals/loops too deeply (5
indentation levels should be a fine line). Breaking the traditional
80-characters-per-line limit is allowed, but not recommended.
##### Operators
Every operator has to be separated from next and previous visible character with one space;

Noone will sudoku you for not obeying the rules - they are meant to make life
easier, but who am I to guide you.
