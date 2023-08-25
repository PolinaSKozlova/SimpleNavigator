#ifndef SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H
#define SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H

#include "s21_graph.h"

namespace SimpleNavigator {
class GraphAlgorithms {
 public:
  using AdjacencyMatrix = std::vector<std::vector<int>>;
  GraphAlgorithms() = default;
  // подумать какие констуркторы нужны
  GraphAlgorithms(const Graph& graph) : graph_(graph){};
  ~GraphAlgorithms() = default;

  std::vector<int> DepthFirstSearch(Graph& graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph& graph, int startVertex);

 private:
  Graph graph_;
};
};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_H