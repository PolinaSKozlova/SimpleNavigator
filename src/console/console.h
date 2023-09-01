#ifndef SIMPLE_NAVIGATOR_CONSOLE_H
#define SIMPLE_NAVIGATOR_CONSOLE_H

#include <functional>
#include <iostream>
#include <map>
#include <variant>

#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

namespace SimpleNavigator {
struct ConsoleData {
  std::string filename;
  // указатель на метод класса
};
class ConsoleApp {
 public:
  ConsoleApp() = default;
  ~ConsoleApp() = default;
  void ShowMenu() {
    char menu_number{};
    Graph graph;
    GraphAlgorithms graph_algo;
    while (menu_number != 'q') {
      std::cout << "Menu:\n";
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
  struct LoadGraph {
    std::string filename;
  };
  struct DepthSearch {
    const Graph graph;
    int startVertex;
  };
  struct BreadthSearch {
    const Graph graph;
    int startVertex;
  };
  struct ShortestPathTwo {
    const Graph graph;
    int startVertex;
    int endVertex;
  };
  struct ShortestPathAll {
    const Graph graph;
  };
  struct LeastSpanningTree {
    const Graph graph;
  };
  struct SalesmanProblem {
    const Graph graph;
  };

  struct GraphVisitor {
    void operator()(LoadGraph& file) {
      std::cin >> file.filename;
      graph.LoadGraphFromFile(file.filename);
    }
    std::vector<int> operator()(DepthSearch& search) {
      return graph_algo.DepthFirstSearch(search.graph, search.startVertex);
    }
    std::vector<int> operator()(BreadthSearch& search) {
      return graph_algo.BreadthFirstSearch(search.graph, search.startVertex);
    }
    int operator()(ShortestPathTwo& search) {
      return graph_algo.GetShortestPathBetweenVertices(
          search.graph, search.startVertex, search.endVertex);
    }
    GraphAlgorithms::AdjacencyMatrix operator()(ShortestPathAll& search) {
      return graph_algo.GetShortestPathsBetweenAllVertices(search.graph);
    }
    GraphAlgorithms::AdjacencyMatrix operator()(LeastSpanningTree& search) {
      return graph_algo.GetLeastSpanningTree(search.graph);
    }
    Graph graph;
    GraphAlgorithms graph_algo;
  };

  void DoAlgorithms(const int menu_number) {
    std::variant<LoadGraph, DepthSearch, BreadthSearch, ShortestPathTwo,
                 ShortestPathAll, LeastSpanningTree>
        var;
    // std::map<int, > parametres = {}; map для чтения данных с терминала
    std::visit(GraphVisitor{}, var);
  }

  // Graph graph_;
  // GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
