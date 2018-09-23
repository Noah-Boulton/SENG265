# Test error files for Assignment 3

There are 5 pairs of error files. Each file begins with e_ as shown below.

* e_in05.txt: contains text and formatting commands for first test
* e_out05.txt: expected output to be produced when e_in01.txt is the input

The first two error files test negative value errors. These errors occur when the 
user inputs a negative value for either the line width or the margin. In either case
the line number, error type, and a short description are printed to stderr.

Tests three and four test for word length issues. These occur when the lenght of a word 
is longer then the width of the page with or without the margin being set. In either case
the line number, error type, and a short description are printed to stderr. The word is printed
accross two lines to accomidate the extra length.

Test five is for case issues with the formatting on and off command. This occurs when 
the users has the formatting command in uppercase. The line number of the error, error type,
and a description of the error are printed to stderr.

