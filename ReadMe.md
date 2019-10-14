# B+ trees 

The file implements B+tree's insertion and finding of numbers.(For maximum number of keys of 3)

functions used are - 

***createNode*** : creates the structure needed for the B+trees

***print*** : prints the whole tree level by level

***findKey*** : given value is checked to be existing the B+tree or not

***countKey*** : returns count of given key in the B+tree

***rangeCountKey*** : returns the count of elements in the B+tree for the given range(included both sides)

***splitNode*** : depending on the leaf or not , the node having more than 3 keys are split and the new node created and the element to be added to the root is returned back to the root

***insertKey*** : inserts the given key

***processCommand*** : depending on the given command, the neccessary funtion will be called

```
g++ B+trees.cpp
./a.out filename
````

# Linear Hashing 

Implements Linear hashing. (Maximum capacity of 3)

functions used are -

***calcIndex*** : calculates the hash value for given number to be inserted

***printData*** : prints the whole dictionary and overflow bin

***search*** : searches for value in the complete structure

***processCommand*** : inserts the value if not already found 

```
g++ LinearHashing.cpp
./a.out filename 
```
