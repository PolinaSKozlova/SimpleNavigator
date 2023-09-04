#ifndef SIMPLE_NAVIGATOR_CONSOLE_H
#define SIMPLE_NAVIGATOR_CONSOLE_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

namespace SimpleNavigator {
class ConsoleApp {
 public:
  ConsoleApp() = default;
  ~ConsoleApp() = default;
  void ShowMenu() {
    int menu_number{};
    while (menu_number != kExit) {
      DisplayMenu();
      std::cin >> menu_number;
      DoAlgorithms(menu_number);
    }
  }

 private:
  const int kExit = 8;
  const std::map<int, std::function<void()>> menu_options_{
      {1, std::bind(&ConsoleApp::Option_1, this)},
      {2, std::bind(&ConsoleApp::Option_2, this)},
      {3, std::bind(&ConsoleApp::Option_3, this)},
      {4, std::bind(&ConsoleApp::Option_4, this)},
      {5, std::bind(&ConsoleApp::Option_5, this)},
      {6, std::bind(&ConsoleApp::Option_6, this)}};

  void DoAlgorithms(const int menu_number) {
    std::system("clear");
    try {
      auto it = menu_options_.find(menu_number);
      if (menu_number == kExit) {
        std::cout << "Bye\n";
      } else if (it != menu_options_.end()) {
        it->second();
      } else {
        std::cout << "Invalid option\n";
      }
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }

  void DisplayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Download graph from file\n";
    std::cout << "2. Breadth First Search\n";
    std::cout << "3. Depth First Search\n";
    std::cout << "4. Get Shortest Path Between Two Vertices\n";
    std::cout << "5. Get Shortest Path Between All Vertices\n";
    std::cout << "6. Get Least Spanning Tree\n";
    std::cout << "7. Solve Traveling Salesman Problem\n";
    std::cout << "8. Exit\n";
  }

  void Option_1() {
    std::cout << "Enter graph filename\n";
    std::string file_name{};
    std::cin >> file_name;
    try {
      graph_.LoadGraphFromFile(file_name);
      std::cout << "Graph loaded\n";
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }

  void Option_2() const {
    int start_vertex{};
    if (std::cin >> start_vertex) {
      graph_algo_.PrintVector(
          graph_algo_.BreadthFirstSearch(graph_, start_vertex));
    } else {
      std::cout << "Incorrect input\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  void Option_3() const {
    int start_vertex{};
    if (std::cin >> start_vertex) {
      graph_algo_.PrintVector(
          graph_algo_.DepthFirstSearch(graph_, start_vertex));
    } else {
      std::cout << "Incorrect input\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  void Option_4() const {
    int start_vertex{};
    int end_vertex{};
    std::cout << "Enter the start and the end vertices: \n";
    if (std::cin >> start_vertex >> end_vertex) {
      std::cout << graph_algo_.GetShortestPathBetweenVertices(
          graph_, start_vertex, end_vertex);
    } else {
      std::cout << "Incorrect input\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  void Option_5() const {
    graph_algo_.PrintMatrix(
        graph_algo_.GetShortestPathsBetweenAllVertices(graph_));
  }

  void Option_6() const {
    graph_algo_.PrintMatrix(graph_algo_.GetLeastSpanningTree(graph_));
  }

  Graph graph_;
  GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
