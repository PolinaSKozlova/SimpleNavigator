#ifndef SIMPLE_NAVIGATOR_GRAPH_H
#define SIMPLE_NAVIGATOR_GRAPH_H

#include <iostream>
#include <string>
#include <vector>

namespace SimpleNavigator {
struct TsmResult {
  std::vector<int> vertices;
  double distance;

  TsmResult() = default;
  TsmResult(std::vector<int> other, double d) : vertices(other), distance(d) {}
  TsmResult(const TsmResult& o) : vertices(o.vertices), distance(o.distance) {}
  void operator=(const TsmResult& o) {
    vertices = o.vertices;
    distance = o.distance;
  }

  bool operator<(const TsmResult& o) const { return distance < o.distance; }

  bool operator>(const TsmResult& o) const { return distance > o.distance; }
};
class Graph {
 public:
  using AdjacencyMatrix = std::vector<std::vector<int>>;
  // подумать какие констуркторы нужны
  Graph() = default;
  explicit Graph(size_t size);
  ~Graph() = default;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
  bool IsEmpty() const noexcept;
  AdjacencyMatrix GetGraphMatrix() const;
  size_t GetSize() const noexcept;

  // extra methods
  void print_graph() {
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
