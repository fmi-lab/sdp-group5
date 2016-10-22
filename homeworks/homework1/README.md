### 21.10.2016

**Deadline:** ` 28.10.2016`  
[Upload Link](https://my.pcloud.com/#page=puplink&code=JkbZ40CikLTXSs4ApylJCjsN250wQQEy)

#### Problem 0 (5 Points)
You got a group of N people represented by the numbers from 0 to n-1. Everyone has some phone numbers of people from the group. 
Messages between two participants in the group can be sent only directly - through phone calls between two people.    
Write a program, which finds if person X can convey a message to person Y and how many calls are necessary for it to happen.   

**Input:**   
*n* - the number of people from the group
The next n lines have the following format: *Number_of_phone_numbers phone1 phone2 phone3*       
The phone numbers in the i-th line belong to the i-th person from the group.   
After n lines there is one last one with two numbers in the range [0,n-1], which gives you between which two people you will convey the message.

**Output:  **
The number of necessary phone calls in order for the message to be conveyed or -1 if it is impossible.

Example:  

5 (n=5)
2 3 4 (person 0 has 2 tel. nums - 3's number and 4's number)   
1 0 (person 1 has 1 tel. num - 0's number)   
1 1 (person 2 has 1 tel. num - 1's number)   
2 0 2 (person 3 has 2 tel. nums - 0's number and 2's number)     
2 2 3 (person 4 has 2 tel. nums - 2's number and 3's number)    

1 2 (person Х=1, person У=2)   
   
**Output:** 3 (1->0->4->2 or 1->0->3->2)     

---

#### Problem 1 (5 Points)

Write a program which receives as input an arithmetic expression with an arbitrary length.
The expression can contain real number, variables, operators +, -, , /, %, =, parenthesis (), {}, [].
The program should check if the parenthesis in the expression are balanced 
(for every opening parenthesis there is corresponding closing one in the right place, there isn't closing parenthesis without opening ones and so on)

Examples:   

(x+1)\*5 = [(2.5+3.5)\*(-6)-5]\*0.1 -> balanced    
(2+3)\*5\*[10-(7+8-0.5+9]) -> unbalanced    
10-(2+3)) -> unbalanced    
{10+20-30)\*5 -> unbalanced   
(x+2 = 10+20) -> unbalanced    
 
---  


#### BONUS (5 Points)

Write a program which detects and removes duplicate parenthesis in an expression.

Example:   

((a+b)*((c+d))) ->  ((a+b)*(c+d))
