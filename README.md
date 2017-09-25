# Statula

***

### Simple terminal-based program for descriptive statistics
##### *Current version: 0.1.13*
[![Build Status](https://travis-ci.org/PiotrOsiewicz/Statula.svg?branch=master)](https://travis-ci.org/PiotrOsiewicz/Statula)
[![license](https://img.shields.io/github/license/PiotrOsiewicz/statula.svg)]()

Initially developed as a leeway from statistics exam, this small piece of software is supposed to allow quick data analysis of big datasets.
The main focus of this project is speed.

***
#### Usage

In order to perform analysis, just type:
./statula dataset_filename
into your terminal. Data should be in text file which contains only whitespaces and floating point numbers.  
In case there is a character that does not meet above demands, all remaining characters of the current line shall be skipped.

##### Starting Parameters
>**-h/--help**		*Prints simple help panel*  
**-o/--open**		*Open specified file*  
**-s/--save**		*Save result to specified file. Amount of targets must be equal to amount of files opened via --o*  
**-l/--language**	*Print result using specified language (language file has to be present in the current directory.*  
**--precision**		*Print result using specified float precision.*
**--silent**		*Disable printing to standard output.*  
**--nosort**		*Disable sorting the input. It results in vast performance improvement at the risk of incorrect results in mode, median and skewness.* **USE WITH CAUTION**   
**--stdin**		*Read directly from stdin. It is the default behaviour if Statula does not receive any starting parameters. Use EOF combination (which is CTRL+D on most systems) to finish data input.*  
**--print_name**	*Print file names directly above each printed dataset.*   

*If there is just one string after "./statula" (not starting with "-"), then it shall be used as a default filename for the session.*

*** 
****Bit fields****  
Following section might come in useful if you plan to familiarize yourself with the code. Macro definitions can be found in header files.
  
  
**Dataset:**  

|   Bit  |   1  |       0      |
|:------:|:----:|:------------:|
| Option | SORT | MODE_PRESENT |  
  
  
**Statula:**  
  
|   Bit  |       3         |      2     |   1   |        0        |
|:------:|:---------------:|:----------:|:-----:|:---------------:|
| Option | PRINT_FILE_NAME | PRINT_HELP | STDIN | PRINT_TO_STDOUT |
  
***
#### *QTYMCUW*
##### Questions that you might come up with.  

Q: What do "memory allocation responsibilities" mean?   
A: In short: "None" means that the function doesn't allocate memory that's
visible outside of it's scope.  

"Delegated to other functions" - memory allocation is delegated to other
functions, but if you were to compare memory usage from before and after
calling the function, new memory is allocated. It's just not done by that
function itself.  

"Allocates memory" speaks for itself.  

You can sort of deduce complexity of a function based on it's memory allocation
responsibilities - high-level ones usually have
second type of memory allocation responsibilities, whereas primitives may allocate memory (init_
functions) or not (is_ boolean functions).

#### *TODO*

  * Mathematical statistics

  * Extend fuctionalities in descriptive statistics

  * Get around limitations of current language system for help panel*


*I think help panel should work even if Statula is unable to load strings from file, however I am not quite sure how can I avoid hard-coding
it into the program itself. 

Tests are written using [Criterion](https://github.com/Snaipe/Criterion) library - it is not neccessary to download it in order to use Statula, however I recommend it as it is a great piece of software. Thanks for everything [Snaipe](https://github.com/Snaipe)!
***


