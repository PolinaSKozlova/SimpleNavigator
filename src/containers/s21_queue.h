#ifndef SIMPLE_NAVIGATOR_S21_QUEUE_H_
#define SIMPLE_NAVIGATOR_S21_QUEUE_H_

#include "s21_list.h"

namespace containers {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() : list(){};
  explicit queue(std::initializer_list<value_type> const &items) {
    for (value_type element : items) {
      push(element);
    }
  }
  queue(const queue &q) : list(q.list) {}
  queue(queue &&q) : list() { swap(q); }
  ~queue() { list.clear(); }
  queue operator=(const queue &q) {
    list = q.list;
    return *this;
  }
  queue operator=(queue &&q) {
    list = q.list;
    q.list.clear();
    return *this;
  }
  const_reference front() const { return list.front(); }
  const_reference back() const { return list.back(); }
  void push(const_reference value) { list.push_back(value); }
  void pop() {
    if (!empty()) {
      list.pop_front();
    }
  }
  void swap(queue &other) { list.swap(other.list); }
  bool empty() const { return list.empty(); }
  size_type size() const { return list.size(); }
  template <typename... Args>
  void emplace_back(Args &&...args) {
    (push(args), ...);
  }

 private:
  s21::list<value_type> list{};
};
}  // namespace containers

#endif  // SIMPLE_NAVIGATOR_S21_QUEUE_H_