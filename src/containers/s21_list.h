#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace containers {
template <typename T>
class list {
 private:
  template <typename value_type>
  class Node {
   public:
    explicit Node(const value_type &value = value_type(), Node *next = nullptr,
                  Node *prev = nullptr)
        : value_(value), next_(next), prev_(prev){};
    value_type value_;
    Node *next_;
    Node *prev_;
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  class iterator {
   public:
    explicit iterator() : iterator_(nullptr) {}
    explicit iterator(Node<value_type> *other) : iterator_(other) {}
    iterator &operator=(Node<value_type> *other) {
      iterator_ = other;
      return *this;
    }
    ~iterator() { iterator_ = nullptr; }
    iterator &operator++() {
      iterator_ = iterator_->next_;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      iterator_ = iterator_->next_;
      return tmp;
    }
    iterator &operator--() {
      iterator_ = iterator_->prev_;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      iterator_ = iterator_->prev_;
      return tmp;
    }
    reference operator*() { return iterator_->value_; }
    bool operator==(const iterator &other) {
      return iterator_ == other.iterator_;
    }
    bool operator!=(const iterator &other) {
      return iterator_ != other.iterator_;
    }
    Node<value_type> *getIterator() { return iterator_; }
    void ChangeNextPrev() { std::swap(iterator_->next_, iterator_->prev_); }
    void ChangeIterator(iterator &other) { std::swap(*this, other); }
    value_type getIterValue() const { return iterator_->value_; }

   private:
    Node<value_type> *iterator_;
  };

  class const_iterator {
   public:
    explicit const_iterator() : const_iterator_(nullptr) {}
    explicit const_iterator(Node<value_type> *other) : const_iterator_(other) {}
    const_iterator &operator=(const Node<value_type> *other) {
      const_iterator_ = other.const_iterator_;
      return *this;
    }
    ~const_iterator() { const_iterator_ = nullptr; }
    const_iterator &operator++() {
      const_iterator_ = const_iterator_->next_;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      const_iterator_ = const_iterator_->next_;
      return tmp;
    }
    const_iterator &operator--() {
      const_iterator_ = const_iterator_->prev_;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp = *this;
      const_iterator_ = const_iterator_->prev_;
      return tmp;
    }
    const_reference operator*() const { return const_iterator_->value_; }
    bool operator==(const const_iterator &other) const {
      return const_iterator_ == other.const_iterator_;
    }
    bool operator!=(const const_iterator &other) const {
      return const_iterator_ != other.const_iterator_;
    }
    Node<value_type> *getConstIterator() { return const_iterator_; }

   private:
    Node<value_type> *const_iterator_;
  };

  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  list<T> &operator=(list &&l) noexcept;
  list<T> &operator=(const list &l);
  ~list();
  bool operator!=(const list &other) { return head_ != other.head_; }
  const_reference front() const;
  const_reference back() const;
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other) noexcept;
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse() noexcept;
  void unique();
  void sort();
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  size_type size_;
  Node<value_type> *head_;
  Node<value_type> *tail_;
  Node<value_type> *shadow_node_;
};
}  // namespace containers

#include "s21_list.inc"

#endif  // SRC_S21_LIST_H_
