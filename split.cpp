/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

/*
random-oneline-list of nums : divide it into (odd)list and (even)list
after code : nums fill odd and even and the origin in is empty
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */
//current->value : int / current->next : Node*

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
  if(in == nullptr) //when recursive hits (null)
  {
    return; //back to previous recursion
  }

  Node* current = in; //current also points first node of in
  in = in->next; //current still remember first node
                //in's point move 1,2,3,...,null(final)

  split(in, odds, evens); //recursive!
  //(1,2,3) > (2,3) > (3) > (null)

  if(current->value % 2 != 0) //if the num is odd
  {
    current->next = odds; //current's pointer points odd's start
    odds = current; //now odd is pointing new-added odd num list
  }
  else { //if the num is even
    current->next = evens;
    evens = current;
  }
}

/* If you needed a helper function, write it here */
