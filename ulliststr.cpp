#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}


/*
//types
head, tail, prev, next : Item*
val : string array
val[] : string
==>so, tail_ & tail_->next both Item* type

[first, last) -- []include / ()exclude
[first node, number of node]

//push_front
front space o : dont nove value just first--;
no front space : needed new Item
//<== same with pust_back
back space o : dont move value just last++;
no back space : needed new Item
<==there's max num of list : arrsize=10

- size_ : total string num
- head_ : pointer very first Item
- tail_ : pointer very last Item

==> so empty list? Null == head_, tail_ / size_==0

getValAtLoc() <= if no loc, return null
*/


// WRITE YOUR CODE HERE

/**
 * Adds a new value to the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::push_back(const std::string& val)
{
  if(size_ == 0) //case1 : if the list itself is empty
  {
    Item* temp = new Item; //make new item
    head_ = temp; //assign each part as head&tail
    tail_ = temp;
  }
  else if(tail_->last == ARRSIZE) //case2 : if list is already full
  {
    Item* newItem = new Item; //make new item
    tail_->next = newItem; //connects both sides
    newItem->prev = tail_;
    tail_ = newItem; //change tail to real end of the lists
  }

  tail_->val[tail_->last] = val; //add value to the back
  tail_->last++; //change the last index's number
  size_++; //adding increases the size
}

/**
 * Adds a new value to the front of the list.
 * If there is room before the 'first' value in
 * the head node add it there, otherwise, 
 * allocate a new head node.
 *   - MUST RUN in O(1)
 */
void ULListStr::push_front(const std::string& val)
{
  if(size_ == 0)
  {
    Item* temp = new Item;

    temp->first = ARRSIZE-1; //need to put at the last part of empty list
    temp->last = ARRSIZE;
    temp->val[temp->first] = val;

    head_ = temp;
    tail_ = temp;
  }
  else if(head_->first == 0)
  {
    Item* newItem = new Item;
    //same but at the newItem which would be placed at the front of current one
    newItem->first = ARRSIZE-1; 
    newItem->last = ARRSIZE;
    newItem->val[newItem->first] = val;

    head_->prev = newItem;
    newItem->next = head_;
    head_ = newItem;
  }
  else{
    head_->first--;
    head_->val[head_->first] = val;
  }

  size_++;
}

/**
 * Removes a value from the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_back()
{
  if(size_ == 0) //if its null, there's nothig to delete
  {
    return;
  }

  tail_->last--; //since deleted one ele
  size_--;

  //exp case : if tail item is empty after deleting, need to delete Item also
  if(tail_->first == tail_->last)
  {
    Item* temp = tail_;
    tail_ = tail_->prev;

    if(tail_ == NULL) head_ = NULL;
    else tail_->next = NULL;

    delete temp; //for memory (check val..)
  }
}

/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front()
{
  if(size_ == 0)
  {
    return;
  }

  head_->first++;
  size_--; //deleting one ele

  //ext case also
  if(head_->first == head_->last)
  {
    Item* temp = head_;
    head_ = head_->next;

    if(head_ == NULL) tail_ = NULL;
    else head_->prev = NULL;

    delete temp;
  }
}

/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::back() const
{
  if(size_ == 0) //cannot return anything
  {
    throw std::invalid_argument("Empty list");
  }

  return tail_->val[tail_->last -1]; //last is not in the scope ()
}

/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::front() const
{
  if(size_ == 0)
  {
    throw std::invalid_argument("Empty list");
  }  

  return head_->val[head_->first];
}

/** 
 * Returns a pointer to the item at index, loc,
 *  if loc is valid and NULL otherwise
 *   - MUST RUN in O(n) 
 */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc >= size_) //nth item cannot exceed the whole size
  {
    return NULL;
  }

  Item* current = head_; //starting point

  while(current !=NULL)
  {
    size_t temp = current->last - current->first; //number of items in each loop

    if(loc < temp) //if the list has locth item
    {
      return &(current->val[current->first + loc]); //since its string* type
    }

    loc -= temp; //already went through whole Item box
    current = current->next; //lets go to next
  }

  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
