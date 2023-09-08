#ifndef SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H
#define SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H

#include <limits>
#include <set>

#include "../containers/s21_queue.h"
#include "../containers/s21_stack.h"
#include "annealing_algorithm.h"
#include "ant_algorithm.h"
#include "s21_graph.h"

namespace SimpleNavigator {
const int kInfinity = std::numeric_limits<int>::max();

class GraphAlgorithms {
 public:
  using AdjacencyMatrix = std::vector<std::vector<int>>;
  using VertexSet = std::set<std::pair<int, std::pair<int, int>>>;
  GraphAlgorithms() = default;
  ~GraphAlgorithms() = default;

  std::vector<int> DepthFirstSearch(const Graph& graph, int start_vertex) const;
  std::vector<int> BreadthFirstSearch(const Graph& graph,
                                      int start_vertex) const;
  int GetShortestPathBetweenVertices(const Graph& graph, int vertex1,
                                     int vertex2) const;

  AdjacencyMatrix GetShortestPathsBetweenAllVertices(const Graph& graph) const;
  AdjacencyMatrix GetLeastSpanningTree(const Graph& graph) const;
  TsmResult SolveTravelingSalesmanProblem(const Graph& graph) const;

  // bonus part

  TsmResult SolveSalesmanProblemWithSimulatedAnnealingMethod(
      const Graph& graph) const;

  // extra methods
  void PrintVector(const std::vector<int>& vector) const;
  void PrintMatrix(const AdjacencyMatrix m) const;
  void PrintTsmResult(const TsmResult& result) const;

 private:
  int GetClosestVertex(const std::vector<int>& distances,
                       const std::vector<bool>& is_visited) const;
  bool AllVisited(const std::vector<bool> visited) const;
  bool IsOriented(const Graph& graph) const;
};

};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H