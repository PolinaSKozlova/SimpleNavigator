#ifndef SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H
#define SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H

#include <limits>

#include "../containers/s21_queue.h"
#include "../containers/s21_stack.h"
#include "s21_graph.h"

namespace SimpleNavigator {
const int kInfinity = std::numeric_limits<int>::max();
// struct TsmResult {
//   int* vertices;  // массив с искомым маршрутом (с порядком обхода вершин).
//                   // Вместо int* можно использовать std::vector<int>
//   double distance;  // длина этого маршрута
// };

class GraphAlgorithms {
 public:
  using AdjacencyMatrix = std::vector<std::vector<int>>;
  GraphAlgorithms() = default;
  // подумать какие констуркторы нужны
  GraphAlgorithms(const Graph& graph) : graph_(graph){};
  ~GraphAlgorithms() = default;

  std::vector<int> DepthFirstSearch(const Graph& graph, int startVertex) const;
  std::vector<int> BreadthFirstSearch(const Graph& graph,
                                      int startVertex) const;
  int GetShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                     int vertex2) const;
  int GetClosestVertex(const std::vector<int>& distances,
                       const std::vector<bool>& is_visited) const;
  int GetShortestEdge(const Graph& graph, int startVertex) const;
  AdjacencyMatrix GetShortestPathsBetweenAllVertices(const Graph& graph) const;
  AdjacencyMatrix GetLeastSpanningTree(const Graph& graph) const;
  // TsmResult SolveTravelingSalesmanProblem(const Graph& graph) const;
  //

  // extra methods
  void PrintVector(const std::vector<int>& vector) const {
    for (size_t i = 0; i < vector.size() - 1; i++) {
      std::cout << vector.at(i) << " -> ";
    }
    std::cout << vector.back() << std::endl;
  }
  void PrintMatrix(const AdjacencyMatrix m) {
    for (size_t i = 0; i < m.size(); ++i) {
      for (size_t j = 0; j < m[i].size(); ++j) {
        std::cout << m[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  Graph graph_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H