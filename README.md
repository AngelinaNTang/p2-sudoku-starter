# Sudoku verifier and simple solver

- Written by: Angelina Tang
- Due: July 23rd, 2021
- Project: P2: Multi-Threaded Sudoku Validator

Works on sudoku puzzles of any size.
Uses multiple threads to check if a puzzle is valid.

For puzzles that have one "0"s, tries to find a valid number for the 0. Can solve simple puzzles where there is only one zero.

Includes following text cases:

- puzzle2-invalid.txt
```
3 4 2 2
2 1 3 4
1 3 4 2
4 2 1 3
```
- puzzle2-valid.txt
```
3 4 2 1
2 1 3 4
1 3 4 2
4 2 1 3
```
- puzzle5-invalid.txt
```
3 4 2 1 5
2 1 3 4 5
1 3 4 2 5
4 2 1 3 5
```
- puzzle9-fill-one-valid.txt
```
6 2 4 5 3 9 1 8 7
5 1 9 7 2 8 6 3 4
8 3 7 6 1 4 2 9 5
1 4 3 8 6 5 7 2 9
9 5 8 2 4 7 3 6 1
7 6 2 3 0 1 4 5 8
3 7 1 9 5 6 8 4 2
4 9 6 1 8 2 5 7 3
2 8 5 4 7 3 9 1 6
```
- puzzle9-valid.txt
```
6 2 4 5 3 9 1 8 7
5 1 9 7 2 8 6 3 4
8 3 7 6 1 4 2 9 5
1 4 3 8 6 5 7 2 9
9 5 8 2 4 7 3 6 1
7 6 2 3 9 1 4 5 8
3 7 1 9 5 6 8 4 2
4 9 6 1 8 2 5 7 3
2 8 5 4 7 3 9 1 6
```
