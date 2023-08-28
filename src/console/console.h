#ifndef SIMPLE_NAVIGATOR_CONSOLE_H
#define SIMPLE_NAVIGATOR_CONSOLE_H

#include <functional>
#include <iostream>
#include <map>

#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

namespace SimpleNavigator {
class ConsoleApp {
 public:
  ConsoleApp() = default;
  ~ConsoleApp() = default;
  void ShowMenu() {
    char ch;
    while (ch != 'q') {
      std::cout << "Menu:\n";
      std::cout << "1. Depth First Search\n";
      std::cout << "2. Breadth First Search\n";
      std::cout << "3. Get Shortest Path Between Two Vertices\n";
      std::cout << "4. Get Shortest Path Between All Vertices\n";
      std::cout << "5. Get Least Spanning Tree\n";
      std::cout << "5. Solve Traveling Salesman Problem\n";
      std::cout << "7. Get Shortest Paths Between All Vertices\n";
      std::cin >> ch;
    }
  }

 private:
  const std::map<
      char, std::function<void(const Graph& graph, int vertex1, int vertex2)>>
      menu_methods_;
  Graph graph_;
  GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
