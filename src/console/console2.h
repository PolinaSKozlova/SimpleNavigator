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
    while (menu_number != 8) {
      DisplayMenu();
      std::cin >> menu_number;
      DoAlgorithms(menu_number);
    }
  }

 private:
  void DoAlgorithms(const int menu_number) {
    std::system("clear");
    std::map<int, std::function<void()>> menu_options;
    menu_options[1] = std::bind(&ConsoleApp::Option_1, this);
    menu_options[2] = std::bind(&ConsoleApp::Option_2, this);
    menu_options[3] = std::bind(&ConsoleApp::Option_3, this);
    menu_options[4] = std::bind(&ConsoleApp::Option_4, this);
    menu_options[5] = std::bind(&ConsoleApp::Option_5, this);
    menu_options[6] = std::bind(&ConsoleApp::Option_6, this);

    try {
      auto it = menu_options.find(menu_number);
      if (menu_number == 8) {
        std::cout << "Bye\n";
      } else if (it != menu_options.end()) {
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
    std::string file_name{};
    std::cin >> file_name;
    try {
      graph_.LoadGraphFromFile(file_name);
      std::cout << "Graph loaded\n";
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }

  void Option_2() {
    int start_vertex{};
    std::cin >> start_vertex;
    graph_algo_.PrintVector(
        graph_algo_.BreadthFirstSearch(graph_, start_vertex));
  }

  void Option_3() {
    int start_vertex{};
    std::cin >> start_vertex;
    graph_algo_.PrintVector(graph_algo_.DepthFirstSearch(graph_, start_vertex));
  }

  void Option_4() {
    int start_vertex{};
    int end_vertex{};
    std::cout << "Enter the start and the end vertices: \n";
    std::cin >> start_vertex >> end_vertex;
    std::cout << graph_algo_.GetShortestPathBetweenVertices(
        graph_, start_vertex, end_vertex);
  }

  void Option_5() {
    graph_algo_.PrintMatrix(
        graph_algo_.GetShortestPathsBetweenAllVertices(graph_));
  }

  void Option_6() {
    graph_algo_.PrintMatrix(graph_algo_.GetLeastSpanningTree(graph_));
  }

  Graph graph_;
  GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
