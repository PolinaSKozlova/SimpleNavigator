#ifndef SIMPLE_NAVIGATOR_CONSOLE_H
#define SIMPLE_NAVIGATOR_CONSOLE_H

#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "../graph_classes/annealing_algorithm.h"
#include "../graph_classes/ant_algorithm.h"
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
  ConsoleApp(const ConsoleApp&) = delete;
  ConsoleApp(const ConsoleApp&&) = delete;
  ~ConsoleApp() = default;

  void operator=(const ConsoleApp&) = delete;
  void operator=(const ConsoleApp&&) = delete;

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
    std::cout << "\n========================================================\n";
    std::cout << "\n\tMenu:\n";
    std::cout << "\n========================================================\n";
    std::cout << "\t1. Download graph from file\n";
    std::cout << "\t2. Breadth First Search\n";
    std::cout << "\t3. Depth First Search\n";
    std::cout << "\t4. Get Shortest Path Between Two Vertices\n";
    std::cout << "\t5. Get Shortest Path Between All Vertices\n";
    std::cout << "\t6. Get Least Spanning Tree\n";
    std::cout << "\t7. Solve Traveling Salesman Problem\n";
    std::cout << "\t8. Export graph to dot/gv file\n";
    std::cout << "\t9. Exit\n";
    std::cout << "\n========================================================\n";
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

  void Option_7() const {
    std::cout << "SolveTravelingSalesmanProblem\n";
    try {
      double time{};
      std::cout << "Ant Method:\n";
      time = StartTimer(&GraphAlgorithms::SolveTravelingSalesmanProblem);
      std::cout << "time: " << time << "\n";
      std::cout << "Simulated Annealing Method:\n";
      time = StartTimer(
          &GraphAlgorithms::SolveSalesmanProblemWithSimulatedAnnealingMethod);
      std::cout << "time: " << time << "\n";
      // std::cout << "Dynamic Programming Method:\n";
      // time = StartTimer(
      //     &GraphAlgorithms::SolveSalesmanProblemWithSimulatedAnnealingMethod);
      //  std::cout << "time: " << time << "\n";
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }

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

  double StartTimer(
      std::function<TsmResult(const GraphAlgorithms&, const Graph& graph)> f)
      const {
    const auto start{std::chrono::system_clock::now()};
    f(graph_algo_, graph_).PrintTsmResult();

    const auto finish{std::chrono::system_clock::now()};
    return std::chrono::duration<double>(finish - start).count();
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
