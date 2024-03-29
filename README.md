_owner:`Ammar Ali`_ _contact:`m.ammarali98@gmail.com`_ *or* _[LinkedIn](https://www.linkedin.com/in/mammarali98)_

# 4x4 Crosswords Puzzle Generator

## Description
This code will generate a unique 4x4 crosswords puzzle every day using word list from an input .txt file.

### Prerequisites
```
1- C++ compiler (g++ 9.3.0 used).
2- Input txt file listing correct four letter words. (See 4.txt for example)
```
### Usage
```
Usage: ./crosswords [file.txt]
```

## Algorithm
It uses a 2d array of string vectors with dimensions 4x26. The 4 MxN arrays (where {M=0-3,N=0-25}) are arranged in a sense that Nth sub-array of Mth array contains all words of which the (M+1)th letter is the (N+1)th english alphabet.
For example:
```
example_array[0][0]="AMIR",example_array[1][0]="BARD",example_array[2][0]="BRAD"
example_array[0][2]="COOK",example_array[1][2]="ACID",example_array[2][2]="FACE" 
```
It then takes a seed generated from the date and number of failed attempts to select a unique starting word and populates a row with it. After that it tries to fill columns and rows in alternating fashion with valid words. If it fails to find a valid word to fill a row or column, it resets the puzzle and starts populating the puzzle again with incremented fail counter.
Upon finding a valid puzzle it prints it in the screen and into a file named "Output.txt".
The output on screen looks like this for date: 13-7-2020:
```
[Successful]
[DATE: 13-7-2020]

AMAH
LANA
FIST
AMAS

[PROGRAM DURATION] 52.0367ms
```
for date: 26-7-2020:
```
[Successful]
[DATE: 26-7-2020]

BLAB
LOMA
ARIA
BYES

[PROGRAM DURATION] 10.3822ms
```
The source for the words used is: _[source](http://www.scrabble.org.au/words/fours.htm)_

## Functions Description

crosswords::wordList::fetch():
```
Arguments - int A, char B.
Returns - const vector of all the words whose Ath letter is char B.

```

crosswords::puzzle::populateRow:
```
Arguments - int A, const wordList& B.
Returns - 1 for success, 0 for failed and increments fails if failed.
Operation - populates Ath row with a valid word from wordList B, if row is already completely filled then checks if the filled word is correct.

```
crosswords::puzzle::populateColumn:
```
Arguments - int A, const wordList& B.
Returns - 1 for success, 0 for failed and increments fails if failed.
Operation - populates Ath column with a valid word from wordList B, if column is already completely filled then checks if the filled word is correct.
```
crosswords::puzzle::print:
```
Arguments - void.
Returns - void.
Operation - prints the puzzle board on screen.
```
crosswords::puzzle::reset:
```
Arguments - void.
Returns - void.
Operation - resets the puzzle board (to spaces).
```
crosswords::puzzle::toFile:
```
Arguments - string filename.
Returns - void.
Operation - creates/overwrites filename.txt and stores current puzzle board in it.
```
### Time Spent Breakdown
```
1) Understanding the problem ~ 1 hour(s).
2) JS script for word scraping from source~ 1.5 hour(s).
3) Design of basic non unique randomized solution ~ 2 hour(s).
4) Implementation of wordList datastructure to store words effectively~ 1.5 hour(s).
5) Implementation of puzzle datastructure and methods for row and column operations~ 3 hour(s).
6) Implementation of puzzle generation algorithm for unique solution depending on date~ 2.5 hour(s)
```
_(This comprises strictly of time spent actively on the problem)_