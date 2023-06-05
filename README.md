# 이응 (Ieung)
## Introduction
When at the start of words, the Korean ```ㅇ``` symbol is silent.

Similar to markdown, Ieung intends to be human readable, powerful in capability, and be visually similar 
to a normal text file. It strives to get out of your way, and in a sense, be silent.

Every line in Ieung has a left-aligned type identifier for the first two characters, followed by an empty space.
This makes parsing files significantly easier, and also ensures that .ng files (the default file extention) are cool to look at.

The following is a short snippet of Ieung:
```Ieung
x  A Ieung Snippet 
@  example test
#  Note: this file can be viewed/edited in "res/testing.ng"

xx Text
~  The tilde notes that text follows

xx Lists
x3 This is an example of how to use lists
.  foo
.. bar

x3 This is another way of using lists
.1 foo
.2 bar
.3 bam
```
The relevant HTML output can be observed by running ```make && make run```.

## Features
- [x] Titles
- [x] Tags
- [x] Comments
- [x] Lists
- [ ] Code snippets
