#ifndef SIMPLE_NAVIGATOR_GRAPH_H
#define SIMPLE_NAVIGATOR_GRAPH_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace SimpleNavigator {
const int kInfinity = std::numeric_limits<int>::max();

struct TsmResult {
  TsmResult() = default;
  TsmResult(std::vector<int>& other, double d) : vertices(other), distance(d) {}
  TsmResult(const TsmResult& other) { *this = other; };
  ~TsmResult() = default;

  TsmResult& operator=(const TsmResult& other) {
    vertices = other.vertices;
    distance = other.distance;
    return *this;
  };

  bool operator<(const TsmResult& other) const {
    return distance < other.distance;
  }

  bool operator>(const TsmResult& other) const {
    return distance > other.distance;
  }

  void PrintTsmResult() const {
    std::cout << "shortest path: ";
    for (size_t i = 0; i < vertices.size() - 1; ++i) {
      std::cout << vertices[i] << "->";
    }
    std::cout << vertices.back();
    std::cout << "\ndistance: " << distance << "\n";
  }

  std::vector<int> vertices;
  double distance{};
};

class Graph {
 public:
  using AdjacencyMatrix = std::vector<std::vector<int>>;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);
  bool IsEmpty() const noexcept;
  AdjacencyMatrix GetGraphMatrix() const;
  size_t GetSize() const noexcept;

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
