#ifndef SIMPLE_NAVIGATOR_CONSOLE_H
#define SIMPLE_NAVIGATOR_CONSOLE_H

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
  void DoAlgorithms(const int menu_number) {
    int start_vertex{}, end_vertex{};
    switch (menu_number) {
      case '1': {
        std::string file_name{};
        std::cin >> file_name;
        try {
          graph_.LoadGraphFromFile(file_name);
        } catch (std::invalid_argument &e) {
          std::cout << e.what() << std::endl;
        }
        break;
      }
      case '2':
        if (graph_.IsEmpty()) {
          std::cout << "You should choose the graph\n";
        } else {
          std::cout << "Enter the start vertex: \n";
          std::cin >> start_vertex;
          graph_algo_.PrintVector(
              graph_algo_.BreadthFirstSearch(graph_, start_vertex));
        }
        break;
      case '3':
        if (graph_.IsEmpty()) {
          std::cout << "You should choose the graph\n";
        } else {
          std::cout << "Enter the start vertex: \n";
          std::cin >> start_vertex;
          graph_algo_.PrintVector(
              graph_algo_.DepthFirstSearch(graph_, start_vertex));
        }
        break;
      case '4':
        if (graph_.IsEmpty()) {
          std::cout << "You should choose the graph\n";
        } else {
          std::cout << "Enter two verticies for getting shortest path: \n";
          std::cin >> start_vertex >> end_vertex;
          std::cout << graph_algo_.GetShortestPathBetweenVertices(
                           graph_, start_vertex, end_vertex)
                    << "\n";
        }
        break;
      case '5':
        if (graph_.IsEmpty()) {
          std::cout << "You should choose the graph\n";
        } else {
          graph_algo_.PrintMatrix(
              graph_algo_.GetShortestPathsBetweenAllVertices(graph_));
        }
        break;
      case '6':
        if (graph_.IsEmpty()) {
          std::cout << "You should choose the graph\n";
        } else {
          graph_algo_.PrintMatrix(graph_algo_.GetLeastSpanningTree(graph_));
        }
        break;
      case '7':
        std::cout << menu_number;
        break;
    }
  }

  Graph graph_;
  GraphAlgorithms graph_algo_;

  //   struct LoadGraph {
  //   std::string filename;
  // };
  // struct DepthSearch {
  //   const Graph graph;
  //   int startVertex;
  // };
  // struct BreadthSearch {
  //   const Graph graph;
  //   int startVertex;
  // };
  // struct ShortestPathTwo {
  //   const Graph graph;
  //   int startVertex;
  //   int endVertex;
  // };
  // struct ShortestPathAll {
  //   const Graph graph;
  // };
  // struct LeastSpanningTree {
  //   const Graph graph;
  // };
  // struct SalesmanProblem {
  //   const Graph graph;
  // };

  // struct GraphVisitor {
  //   void operator()(LoadGraph& file) {
  //     std::cin >> file.filename;
  //     graph.LoadGraphFromFile(file.filename);
  //   }
  //   std::vector<int> operator()(DepthSearch& search) {
  //     return graph_algo.DepthFirstSearch(search.graph, search.startVertex);
  //   }
  //   std::vector<int> operator()(BreadthSearch& search) {
  //     return graph_algo.BreadthFirstSearch(search.graph, search.startVertex);
  //   }
  //   int operator()(ShortestPathTwo& search) {
  //     return graph_algo.GetShortestPathBetweenVertices(
  //         search.graph, search.startVertex, search.endVertex);
  //   }
  //   GraphAlgorithms::AdjacencyMatrix operator()(ShortestPathAll& search) {
  //     return graph_algo.GetShortestPathsBetweenAllVertices(search.graph);
  //   }
  //   GraphAlgorithms::AdjacencyMatrix operator()(LeastSpanningTree& search) {
  //     return graph_algo.GetLeastSpanningTree(search.graph);
  //   }
  //   Graph graph;
  //   GraphAlgorithms graph_algo;
  // };

  // void DoAlgorithms(const int menu_number) {
  //   std::variant<LoadGraph, DepthSearch, BreadthSearch, ShortestPathTwo,
  //                ShortestPathAll, LeastSpanningTree>
  //       var;
  //   std::map<int,
  //            std::variant<LoadGraph, DepthSearch, BreadthSearch,
  //                         ShortestPathTwo, ShortestPathAll,
  //                         LeastSpanningTree>>
  //       parametres = {};
  //   // map для чтения данных с терминала
  //   std::visit(GraphVisitor{}, var);
  // }
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
