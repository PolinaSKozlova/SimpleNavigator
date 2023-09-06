#ifndef SIMPLE_NAVIGATOR_GRAPH_H
#define SIMPLE_NAVIGATOR_GRAPH_H

#include <iostream>
#include <string>
#include <vector>

namespace SimpleNavigator {
struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class Graph {
 public:
  using AdjacencyMatrix = std::vector<std::vector<int>>;
  Graph() = default;
  ~Graph() = default;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
  bool IsEmpty() const noexcept;
  AdjacencyMatrix GetGraphMatrix() const;
  size_t GetSize() const noexcept;

  // extra methods
  void print_graph() const {
    for (size_t i = 0; i < size_; ++i) {
      for (size_t j = 0; j < size_; ++j) {
        std::cout << graph_matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  const std::string GetAbsolutePath(const std::string& filename);
  void AllocateMemoryForGraphMatrix();
  void ClearGraphMatrix();
  void GetSize(const std::string& size);
  void ReadElementsFromAdjacencyMatrix(const std::string& line,
                                       std::vector<int>& rows);
  bool CheckFilename(const std::string& filename) const noexcept;
  size_t size_{};
  AdjacencyMatrix graph_matrix_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_GRAPH_H
