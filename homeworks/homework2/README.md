### 12.11.2016

**Deadline:** ` 20.11.2016`  
**Use the tree implemented in the lectures for the tasks that don't specify otherwise**  

[Upload Link](https://my.pcloud.com/#page=puplink&code=oFhZJtcHKutRYm89vUD3OdsAGQTrlJRV)

#### Problem 0 (3 Points)

Implement an iterative (without recursion or stack) "find" member-function, which by a given data returns *true* if the tree contains the data and *false* if it doesn't.  
The function should presume the tree is BST and should work in O(logn) time and O(1) memory.    
Also implement iterative versions of the DeleteElement and insertBOT member-functions, which should also work in O(logn) time.   
For these methods you don't need helper-functions in order to implement them.  

---

#### Problem 1 (3 Points)

The diameter of a tree is the number of nodes on the longest path between two leaves in the tree.  
Write a member-function for the class BTree, which find the diameter of the tree and returns it.  
The solutions with better complexities and faster runtime will get more points.  
For this function there is no need for the tree to be BST.  

[Example](https://gyazo.com/8374800c93780f8f14b5c1bb856a0939)

---

#### Problem 2 (4 Points)

Write a member-function which prints the columns of a tree in order with the nodes in each column printed top to bottom.
When two nodes of one column share the same height e.g. 7 and 9 in Example 1, you may print them in either order.  
For this function there is no need for the tree to be BST. 

[Example1](https://gyazo.com/352bd12945606847aadf9c3c646cb78c)  

[Example2](https://gyazo.com/6d994248aa637fc96f27c587f4d9ba8f)  

---  


#### BONUS (5 Points)

Implement a member-function "balance" which checks if the BST(Binary Search Tree) is balanced and returns true/false.   
If the tree isn't balanced then the function balances it.
