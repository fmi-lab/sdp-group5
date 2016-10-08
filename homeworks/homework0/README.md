### 08.10.2016

**Deadline:** ` 12.10.2016`

#### Problem 0

Implement a template vector with the following functionalities provided for the user:
* Construct, copy and destruction
* Add element to the back
* Remove element from the back
* Add element at a given position
* Remove element from a given position
* Reserve a memory with a given capacity. (If the given capacity if smaller than the current -> do nothing)
* Resize the vector. [Details](http://www.cplusplus.com/reference/vector/vector/resize/)
* Check out if the vector is empty
* Check out the size of the vector
* Check out the capacity of the vector
* Check out and/or change an element from the vector by a given index. (operator [])
* Check out and/or change an element from the vector by a given *valid* index. (at(...) throw out_of_range exception if the index is invalid)
* Check out and/or change the first element of the vector
* Check out and/or change the last element of the vector

---

#### Problem 1

Implement a *template* stack or queue based on the parity of your faculty number:
* Even numbers implement stack
* Uneven numbers implement queue

A user of the stack should have some the ability to:
* Construct, copy and desctruct a stack
* Add element to the top of the stack (push)
* Remove element from the top (pop)
* Check the top element (top) (const and non-const versions)
* Check if the stack is empty or not (empty)
* Check the size of the stack (size)

The queue should have similiar methods:
* Construct, copy and destruct a queue 
* Add element to the rear of the queue
* Remove element from the front
* Method returning the front element (const and non-const versions)
* Method returning the back element (const and non-const versions)
* Empty check
* Method returning the size of the queue
 
Should you use pointers or just an dynamic array to implement the data structures from problem 1 is your decision. You should research and choose the best way.  
For both problem 0 and 1 it is recommended to name the member functions similiar(or the same) as their counterparts in the standart library.
