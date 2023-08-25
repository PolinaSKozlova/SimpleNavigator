#ifndef SIMPLE_NAVIGATOR_GRAPH_H
#define SIMPLE_NAVIGATOR_GRAPH_H

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

 private:
  void AllocateMemoryForGraphMatrix();
  void FreeMemoryForGraphMatrix();
  size_t size_{};
  std::vector<std::vector<int>> graph_matrix_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_GRAPH_H
