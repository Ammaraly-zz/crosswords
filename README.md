# 4x4 Crosswords Puzzle Generator

## Description
This project will generate a unique 4x4 crosswords puzzle every day using word list from an input .txt file.

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
1- It uses a 2d array of vectors with dimensions 4x26.
<<<<<<< HEAD
2- The 4 MxN where (M=0-3,N=0-25) arrays are sorted in a sense that it's Nth array contains all
||||||| f05f601
2- The 4 [MxN](M=0-3,N=0-25) arrays are sorted in a sense that it's Nth array contains all.
=======
2- The 4 [MxN](M=0-3,N=0-25) arrays are sorted in a sense that it's Nth array contains all
>>>>>>> ae9d90c621b2fbcac59f95413f6505629ef4fb5e
words of which the (M+1)th letter is the (N+1)th english alphabet.
for example:
```
example_array[0][0]="AMIR",example_array[1][0]="BARD",example_array[2][0]="BRAD".
example_array[0][2]="COOK",example_array[1][2]="ACID",example_array[2][2]="FACE" 
```