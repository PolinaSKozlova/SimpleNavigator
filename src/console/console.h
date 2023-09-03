#ifndef SIMPLE_NAVIGATOR_CONSOLE_H
#define SIMPLE_NAVIGATOR_CONSOLE_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <variant>

#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

namespace SimpleNavigator {
class ConsoleApp {
 public:
  ConsoleApp() = default;
  ~ConsoleApp() = default;
  void ShowMenu() {
    char menu_number{};
    Graph graph;
    GraphAlgorithms graph_algo;
    while (menu_number != 'q') {
      std::cout << "\nMenu:\n";
      std::cout << "1. Download graph from file\n";
      std::cout << "2. Breadth First Search\n";
      std::cout << "3. Depth First Search\n";
      std::cout << "4. Get Shortest Path Between Two Vertices\n";
      std::cout << "5. Get Shortest Path Between All Vertices\n";
      std::cout << "6. Get Least Spanning Tree\n";
      std::cout << "7. Solve Traveling Salesman Problem\n";
      std::cin >> menu_number;
      DoAlgorithms(menu_number);
    }
  }

 private:
  void DoAlgorithms(const int menu_number) {
    std::system("clear");
    int start_vertex{}, end_vertex{};
    switch (menu_number) {
      case '1': {
        std::string file_name{};
        std::cin >> file_name;
        try {
          graph_.LoadGraphFromFile(file_name);
          std::cout << "Graph loaded\n";
        } catch (std::invalid_argument& e) {
          std::cout << e.what() << std::endl;
        }
        break;
      }
      case '2':
        if (CheckGraph(start_vertex))
          graph_algo_.PrintVector(
              graph_algo_.BreadthFirstSearch(graph_, start_vertex));
        break;
      case '3':
        if (CheckGraph(start_vertex))
          graph_algo_.PrintVector(
              graph_algo_.DepthFirstSearch(graph_, start_vertex));
        break;
      case '4':
        if (CheckGraph()) {
          std::cout << "Enter two verticies for getting shortest path: \n";
          std::cin >> start_vertex >> end_vertex;
          std::cout << graph_algo_.GetShortestPathBetweenVertices(
                           graph_, start_vertex, end_vertex)
                    << "\n";
        }
        break;
      case '5':
        if (CheckGraph())
          graph_algo_.PrintMatrix(
              graph_algo_.GetShortestPathsBetweenAllVertices(graph_));
        break;
      case '6':
        if (CheckGraph())
          graph_algo_.PrintMatrix(graph_algo_.GetLeastSpanningTree(graph_));
        break;
      case '7':
        break;
    }
  }

  bool CheckGraph() {
    if (graph_.IsEmpty()) {
      std::cout << "You should choose the graph\n";
      return false;
    }
    return true;
  }

  bool CheckGraph(int& vertex) {
    if (graph_.IsEmpty()) {
      std::cout << "You should choose the graph\n";
      return false;
    } else {
      std::cout << "Enter the start vertex: \n";
      std::cin >> vertex;
      return true;
    }
  }

  Graph graph_;
  GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
