# 4x4 Crosswords Puzzle Generator

## Description
-This project will generate a unique 4x4 crosswords puzzle every day using word list from an input .txt file.

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
```
1- It uses a 2d array of vectors with dimensions 4x26.
2- The 4 [MxN](M=0-3,N=0-25) arrays are sorted in a sense that it's Nth array contains all words of which the (M+1)th letter is the (N+1)th english alphabet.
```