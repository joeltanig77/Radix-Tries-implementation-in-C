# Radix Tree

This program takes a word and inserts it into a radix tree. If you are not familiar of what a radix tree is or would like an animated example of what this project is doing click [here](https://www.cs.usfca.edu/~galles/visualization/RadixTree.html) to see the tree in action as you insert words! This data structure is meant for autocorrect which can predict what work the user will press next. 

## How to run
Download the project with its Makefile and type make run into the directory of the project 
```python
make run
```

## Features with its commands
1. Add words or phrases
```
i apple i dog i cat
```
2. Delete all nodes/words
```
e
```
3. Display the count of words in the tree
```
w
```
4. Display the count of nodes in the tree
```
n
```
5. Search if the word is already in the tree
```
s apple 
Word is already in trie
```
6. Checks if the word you want to add is already in a tree 
```
i apple i apple
Word is already in trie
```
7. Can print all the words in the trie in lexicographic order

```
i foo i bar i bat
p
bar
bat
foo
```

8. Can quit the program
```
q
