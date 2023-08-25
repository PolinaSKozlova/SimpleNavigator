#ifndef SIMPLE_NAVIGATOR_S21_STACK_H_
#define SIMPLE_NAVIGATOR_S21_STACK_H_

#include "s21_list.h"

namespace containers {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  explicit stack() : list() {}
  explicit stack(std::initializer_list<value_type> const &items) {
    for (const auto &element : items) {
      push(element);
    }
  }
  stack(const stack &s) { list = s.list; }
  stack(stack &&s) { swap(s); }
  ~stack() { list.clear(); }
  stack &operator=(const stack &s) {
    if (!empty) {
      list.clear();
    }
    list = s.list;
    return *this;
  }
  stack &operator=(stack &&s) {
    list.swap(s.list);
    return *this;
  }
  const_reference top() const { return list.back(); }
  void push(const_reference value) { list.push_back(value); }
  void pop() { list.pop_back(); }
  void swap(stack &other) { list.swap(other.list); }
  bool empty() const { return list.empty(); }
  size_type size() const { return list.size(); }
  template <typename... Args>
  void emplace_front(Args &&...args) {
    (push(args), ...);
  }

 private:
  s21::list<value_type> list{};
};

}  // namespace containers

#endif  // SIMPLE_NAVIGATOR_S21_STACK_H_