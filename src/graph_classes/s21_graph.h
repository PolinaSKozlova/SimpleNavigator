#ifndef SIMPLE_NAVIGATOR_GRAPH_H
#define SIMPLE_NAVIGATOR_GRAPH_H

#include <iostream>
#include <string>
#include <vector>

namespace SimpleNavigator {
class Graph {
 public:
  Graph() = default;
  Graph(size_t size);
  ~Graph();

  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

  void print_graph() {
    for (size_t i = 0; i < size_; ++i) {
      for (size_t j = 0; j < size_; ++j) {
        std::cout << graph_matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  void AllocateMemoryForGraphMatrix();
  void FreeMemoryForGraphMatrix();
  void GetSize(const std::string& size);
  void ReadElementsFromAdjacencyMatrix(const std::string& line,
                                       std::vector<int>& rows);
  size_t size_{};
  std::vector<std::vector<int>> graph_matrix_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_GRAPH_H
