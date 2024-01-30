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

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val)
{
  //If list is empty or if no more room in the back
  if (tail_ == nullptr || tail_->last == ARRSIZE)
  {
    Item* newItem = new Item();

    if (tail_ == nullptr)
    {
      head_ = newItem;
      tail_ = newItem;
    }
    //for case when list isn't empty
    else
    {
      tail_->next = newItem;
      newItem->prev = tail_;
      tail_ = newItem;
    }
  }
  //adding val to the array 
  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}

void ULListStr::pop_back()
{
  if (empty())
  {
    return;
  }

  tail_->last--;
  if (tail_->first == tail_->last)
  {
    Item* temp = tail_;
    tail_ = tail_->prev;
    if (tail_)
    {
      tail_->next = nullptr;
    }
    else
    {
      //list is empty 
      head_ = nullptr;
    }
    delete temp;
  }
  size_--;
}
void ULListStr::push_front(const std::string& val)
{
  if (head_ == nullptr || head_->first == 0)
  {
    Item* newItem = new Item();
    //if list is empty
    if (head_ == nullptr)
    {
      head_ = newItem;
      tail_ = newItem;
    }
    //for when the case isn't empty
    else
    {
      head_->prev = newItem;
      newItem->next = head_;
      head_ = newItem;
    }
    //changing first and last to ARRSIZE as video instructions said
    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }

  //Inserting string
  head_->first--;
  head_->val[head_->first] = val;
  size_++;
}

void ULListStr::pop_front()
{
  if (empty())
  {
    return;
  }

  head_->first++;
  
  if (head_->first == head_->last)
  {
    Item* temp = head_;
    head_ = head_->next;
    delete temp;

    if (head_)
    {
      head_->prev = nullptr;
    }
    else
    {
      tail_ = nullptr;
    }
  }
  size_--;
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc >= size_)
  {
    return nullptr;
  }

  Item* curr = head_;
  while (curr != nullptr)
  {
    size_t itemsInNode = curr->last - curr->first;
    if (loc < itemsInNode)
    {
      return &curr->val[curr->first + loc];
    }

    loc = loc - itemsInNode;

    curr = curr->next;
  }

  return nullptr;
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
