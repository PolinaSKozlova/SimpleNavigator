#include "s21_list.h"

namespace containers{
template <typename T>
list<T>::list() : size_(0), head_(nullptr), tail_(nullptr), shadow_node_(new Node<T>) {
  shadow_node_->next_ = shadow_node_->prev_ = shadow_node_;
  head_ = tail_ = shadow_node_;
  shadow_node_->value_ = size_;
}

template <typename T>
list<T>::list(size_type n) : size_(0), head_(nullptr), tail_(nullptr), shadow_node_(new Node<T>) {
  shadow_node_->next_ = shadow_node_->prev_ = shadow_node_;
  head_ = tail_ = shadow_node_;
  while (size_ < n) {
    push_back(T());
  }
  shadow_node_->value_ = n;
  size_ = n;
}

template <typename T>
s21::list<T>::list(std::initializer_list<T> const &items)
    : size_(0), head_(nullptr), tail_(nullptr), shadow_node_(new Node<T>) {
  shadow_node_->next_ = shadow_node_->prev_ = shadow_node_;
  shadow_node_->value_ = size_;
  head_ = tail_ = shadow_node_;
  for (const_reference element : items) {
    push_back(element);
  }
}

template <typename T>
list<T>::list(const list &l) : size_(0), head_(nullptr), tail_(nullptr), shadow_node_(new Node<T>) {
  head_ = tail_ = shadow_node_;
  *this = l;
}

template <typename T>
list<T>::list(list &&l) : size_(0), head_(nullptr), tail_(nullptr), shadow_node_(nullptr) {
  swap(l);
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (!empty()) {
    clear();
    size_ = 0;
  }
  iterator iter = l.begin();
  for (; iter != l.end(); ++iter) {
    push_back(*iter);
  }
  l.clear();
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (!empty()) {
    clear();
  }
  const_iterator iter = l.cbegin();
  for (; iter != l.cend(); ++iter) {
    push_back(*iter);
  }
  size_ = l.size_;
  return *this;
}

template <typename T>
list<T>::~list() {
  clear();
  delete shadow_node_;
}

template <typename T>
const T &list<T>::front() const {
  return head_->value_;
}

template <typename T>
const T &list<T>::back() const {
  return tail_->value_;
}

template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  iterator begin_iterator(head_);
  return begin_iterator;
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  iterator end_iterator(shadow_node_);
  return end_iterator;
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
  const_iterator cbegin_iterator(head_);
  return cbegin_iterator;
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
  const_iterator cend_iterator(shadow_node_);
  return cend_iterator;
}

template <typename T>
void list<T>::clear() noexcept {
  while (size_) {
    pop_back();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else if (pos == end()) {
    push_back(value);
  } else {
    Node<T> *current_node = pos.getIterator();
    Node<T> *node_to_insert =
        new Node(value, current_node, current_node->prev_);
    current_node->prev_->next_ = node_to_insert;
    current_node->prev_ = node_to_insert;
    ++size_;
  }
  shadow_node_->value_ = size_;
  return --pos;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (size_) {
    if (pos == begin()) {
      pop_front();
    } else if (pos == --end()) {
      pop_back();
    } else {
      Node<T> *current_node = pos.getIterator();
      current_node->next_->prev_ = current_node->prev_;
      current_node->prev_->next_ = current_node->next_;
      --size_;
      delete current_node;
    }
    shadow_node_->value_ = size_;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  if (!size_) {
    tail_ = new Node<T>(value, shadow_node_, shadow_node_);
    head_ = tail_;
    shadow_node_->prev_ = tail_;
    shadow_node_->next_ = head_;
  } else {
    Node<T> *new_tail = new Node<T>(value, shadow_node_, tail_);
    tail_->next_ = new_tail;
    tail_ = new_tail;
    shadow_node_->prev_ = tail_;
  }
  ++size_;
  shadow_node_->value_ = size_;
}

template <typename T>
void list<T>::pop_back() {
  Node<T> *node_to_delete = tail_;
  tail_ = tail_->prev_;
  shadow_node_->prev_ = tail_;
  delete node_to_delete;
  if (size_ == 1) {
    head_ = tail_;
  }
  --size_;
  shadow_node_->value_ = size_;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  if (!size_) {
    head_ = new Node<T>(value, shadow_node_, shadow_node_);
    tail_ = head_;
    shadow_node_->next_ = head_;
    shadow_node_->prev_ = tail_;
  } else {
    Node<T> *new_head = new Node<T>(value, head_, shadow_node_);
    head_->prev_ = new_head;
    head_ = new_head;
    shadow_node_->next_ = head_;
  }
  ++size_;
  shadow_node_->value_ = size_;
}

template <typename T>
void list<T>::pop_front() {
  Node<T> *node_to_delete = head_;
  head_ = head_->next_;
  delete node_to_delete;
  if (size_ == 1) {
    tail_ = head_;
  }
  shadow_node_->next_ = head_;
  --size_;
  shadow_node_->value_ = size_;
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(shadow_node_, other.shadow_node_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list &other) {
  if (*this != other) {
    int list_is_sorted = 0;
    for (iterator current = begin(); current != end() && !list_is_sorted;
         ++current) {
      for (iterator next = current; next != end(); ++next) {
        if (*current > *next) {
          list_is_sorted = 1;
        }
      }
    }
    if (!list_is_sorted) {
      splice(cbegin(), other);
      sort();
    } else {
      splice(++cbegin(), other);
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (empty() && !other.empty()) {
    swap(other);
  } else if (!other.empty()) {
    if (pos == cbegin()) {
      other.tail_->next_ = head_;
      head_->prev_ = other.tail_;
      head_ = other.head_;
      head_->prev_ = shadow_node_;
      shadow_node_->next_ = head_;
    } else if (pos == cend()) {
      other.head_->prev_ = tail_;
      tail_->next_ = other.head_;
      tail_ = other.tail_;
      tail_->next_ = shadow_node_;
      shadow_node_->prev_ = tail_;
    } else {
      Node<T> *current_node = pos.getConstIterator();
      current_node->prev_->next_ = other.head_;
      other.head_->prev_ = current_node->prev_;
      current_node->prev_ = other.tail_;
      other.tail_->next_ = current_node;
    }
    size_ += other.size_;
    shadow_node_->value_ = size_;
    other.shadow_node_->value_ = other.size_ = 0;
    other.shadow_node_->next_ = other.shadow_node_->prev_ = other.shadow_node_;
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  if (size_ > 1) {
    iterator last = end();
    for (iterator first = begin(); first != last; --first) {
      first.ChangeNextPrev();
    }
    last.ChangeNextPrev();
    std::swap(head_, tail_);
  }
}

template <typename T>
void list<T>::unique() {
  if (!empty()) {
    Node<T> *current_node = head_;
    size_t list_size = size() - 1;
    while (list_size--) {
      Node<T> *next_node = current_node->next_;
      if (current_node->value_ == next_node->value_) {
        current_node->next_ = next_node->next_;
        next_node->next_->prev_ = current_node;
        --size_;
        delete next_node;
      } else {
        current_node = current_node->next_;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    for (iterator current = begin(); current != end(); ++current) {
      for (iterator next = current; next != end(); ++next) {
        if (*current > *next) {
          std::swap(*current, *next);
        }
      }
    }
  }
}

template <typename T>
bool list<T>::empty() const noexcept {
  return (cbegin() == cend());
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return (__SIZE_MAX__ / sizeof(Node<T>) / 2);
}

template <typename T>
template <typename... Args>
typenamelist<T>::iterator list<T>::emplace(const_iterator pos,
                                                      Args &&...args) {
  list<T> temp_list{args...};
  const_iterator iter = cbegin();
  splice(pos, temp_list);
  iterator result = begin();
  for (; iter != pos; ++iter) {
    ++result;
  }
  return --result;
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
  (push_back(args), ...);
}

template <typename T>
template <typename... Args>
void list<T>::emplace_front(Args &&...args) {
  list<T> temp_list{args...};
  splice(cbegin(), temp_list);
}
};
