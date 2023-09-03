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
// class Menu {
//  public:
//   void DisplayMenu() {
//     std::cout << "\nMenu:\n";
//     std::cout << "1. Download graph from file\n";
//     std::cout << "2. Breadth First Search\n";
//     std::cout << "3. Depth First Search\n";
//     std::cout << "4. Get Shortest Path Between Two Vertices\n";
//     std::cout << "5. Get Shortest Path Between All Vertices\n";
//     std::cout << "6. Get Least Spanning Tree\n";
//     std::cout << "7. Solve Traveling Salesman Problem\n";
//   }

//   void Option_1(Graph& graph) {
//     std::string file_name{};
//     std::cin >> file_name;
//     try {
//       graph.LoadGraphFromFile(file_name);
//       std::cout << "Graph loaded\n";
//     } catch (std::invalid_argument& e) {
//       std::cout << e.what() << std::endl;
//     }
//   }

//   void Option_2(const Graph& graph, GraphAlgorithms& graph_algo) {
//     int start_vertex{};
//     std::cin >> start_vertex;
//     graph_algo.BreadthFirstSearch(graph, start_vertex);
//   }

//   void Option_3(const Graph& graph, GraphAlgorithms& graph_algo) {
//     int start_vertex{};
//     std::cin >> start_vertex;
//     graph_algo.DepthFirstSearch(graph, start_vertex);
//   }
// };

class ConsoleApp {
 public:
  ConsoleApp() = default;
  ~ConsoleApp() = default;
  void ShowMenu() {
    int menu_number{};
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
    std::string file_name{};
    auto load_file = std::bind(&Graph::LoadGraphFromFile, &graph_, file_name);
    auto depth_search = std::bind(&GraphAlgorithms::DepthFirstSearch,
                                  &graph_algo_, graph_, start_vertex);
    auto breadth_search = std::bind(&GraphAlgorithms::BreadthFirstSearch,
                                    &graph_algo_, start_vertex);
    auto shortest_path_two_vertices =
        std::bind(&GraphAlgorithms::GetShortestPathBetweenVertices,
                  &graph_algo_, graph_, start_vertex, end_vertex);
    auto shortest_path_all_vertices =
        std::bind(&GraphAlgorithms::GetShortestPathsBetweenAllVertices,
                  &graph_algo_, graph_);
    auto least_spanning_tree =
        std::bind(&GraphAlgorithms::GetLeastSpanningTree, &graph_algo_, graph_);
    std::map<int, std::function<void()>> menu_options{
        {1, load_file},
        {2, breadth_search},
        {3, depth_search},
        {4, shortest_path_two_vertices},
        {5, shortest_path_all_vertices},
        {6, least_spanning_tree}};
    // menu_options[1] = std::bind(&Menu::Option_1, &menu, graph_);
    // menu_options[2] = std::bind(&Menu::Option_2, &menu, graph_, graph_algo_);
    // menu_options[3] = std::bind(&Menu::Option_3, &menu, graph_, graph_algo_);
    // menu_options[1] = std::bind(&Graph::LoadGraphFromFile, graph_,
    // file_name);
    // menu_options[2] = std::bind(&GraphAlgorithms::DepthFirstSearch,
    // graph_algo_,
    //                             graph_, start_vertex);
    // menu_options[3] = std::bind(&GraphAlgorithms::BreadthFirstSearch,
    //                             graph_algo_, graph_, start_vertex);
    // menu_options[4] =
    //     std::bind(&GraphAlgorithms::GetShortestPathBetweenVertices,
    //     graph_algo_,
    //               graph_, start_vertex, end_vertex);
    // menu_options[5] =
    //     std::bind(&GraphAlgorithms::GetShortestPathsBetweenAllVertices,
    //               graph_algo_, graph_);
    // menu_options[6] =
    //     std::bind(&GraphAlgorithms::GetLeastSpanningTree, graph_algo_,
    //     graph_);

    auto it = menu_options.find(menu_number);
    if (it != menu_options.end()) {
      it->second();
      graph_.print_graph();
    } else if (menu_number == 'q') {
      std::cout << "Bye\n";
    } else {
      std::cout << "Invalid option\n";
    }
  }

  Graph graph_;
  GraphAlgorithms graph_algo_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_CONSOLE_H
