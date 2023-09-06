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
  const int kExit = 9;
  const std::map<int, std::function<void()>> menu_options_{
      {1, std::bind(&ConsoleApp::Option_1, this)},
      {2, std::bind(&ConsoleApp::Option_2, this)},
      {3, std::bind(&ConsoleApp::Option_3, this)},
      {4, std::bind(&ConsoleApp::Option_4, this)},
      {5, std::bind(&ConsoleApp::Option_5, this)},
      {6, std::bind(&ConsoleApp::Option_6, this)},
      {7, std::bind(&ConsoleApp::Option_7, this)},
      {8, std::bind(&ConsoleApp::Option_8, this)},
      {9, std::bind(&ConsoleApp::Option_9, this)}};

 public:
  ConsoleApp() = default;
  ~ConsoleApp() = default;

  void ShowMenu() {
    int menu_number{};
    while (menu_number != kExit) {
      DisplayMenu();
      std::cin >> menu_number;
      DoAlgorithms(menu_number);
      ClearInput();
    }
  }

 private:
  void DoAlgorithms(const int menu_number) {
    std::system("clear");
    try {
      auto it = menu_options_.find(menu_number);
      if (it != menu_options_.end()) {
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
    std::cout << "8. Export graph to dot/gv file\n";
    std::cout << "9. Exit\n";
  }

  void Option_1() {
    std::cout << "Enter graph filename\n";
    try {
      LoadOrExportGraph(&Graph::LoadGraphFromFile);
      std::cout << "Graph loaded\n";
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }

  void Option_2() const { DoSearch(&GraphAlgorithms::BreadthFirstSearch); }

  void Option_3() const { DoSearch(&GraphAlgorithms::DepthFirstSearch); }

  void Option_4() const {
    DoSearch(&GraphAlgorithms::GetShortestPathBetweenVertices);
  }

  void Option_5() const {
    graph_algo_.PrintMatrix(
        graph_algo_.GetShortestPathsBetweenAllVertices(graph_));
  }

  void Option_6() const {
    graph_algo_.PrintMatrix(graph_algo_.GetLeastSpanningTree(graph_));
  }

  void Option_7() const { std::cout << "SolveTravelingSalesmanProblem\n"; }

  void Option_8() {
    std::cout << "Enter filename to export\n";
    try {
      LoadOrExportGraph(&Graph::ExportGraphToDot);
      std::cout << "Graph exported\n";
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }

  void Option_9() { std::cout << "Bye\n"; }

  void DoSearch(
      std::function<std::vector<int>(const GraphAlgorithms&, const Graph& graph,
                                     int start_vertex)>
          f) const {
    int start_vertex{};
    std::cout << "Enter the vertex: \n";
    if (std::cin >> start_vertex) {
      graph_algo_.PrintVector(f(graph_algo_, graph_, start_vertex));
    } else {
      ClearInput();
      std::cout << "Incorrect input\n";
    }
  }
  void DoSearch(std::function<int(const GraphAlgorithms&, const Graph& graph,
                                  int start_vertex, int end_vertex)>
                    f) const {
    int start_vertex{}, end_vertex{};
    std::cout << "Enter the start and the end vertices: \n";
    if (std::cin >> start_vertex >> end_vertex) {
      std::cout << f(graph_algo_, graph_, start_vertex, end_vertex);
    } else {
      ClearInput();
      std::cout << "Incorrect input\n";
    }
  }

  void LoadOrExportGraph(
      std::function<void(Graph&, const std::string& filename)> f) {
    std::string file_name{};
    if (std::cin >> file_name) {
      f(graph_, file_name);
    } else {
      ClearInput();
    }
  }

  void ClearInput() const {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  Graph graph_;
  GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
