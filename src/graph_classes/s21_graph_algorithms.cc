#include "s21_graph_algorithms.h"

namespace SimpleNavigator {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int startVertex) const {
  return std::vector<int>();
}

int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
                                                    int vertex1,
                                                    int vertex2) const {
  return 0;
}

GraphAlgorithms::AdjacencyMatrix
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) const {
  return AdjacencyMatrix();
}

GraphAlgorithms::AdjacencyMatrix GraphAlgorithms::GetLeastSpanningTree(
    const Graph& graph) const {
  return AdjacencyMatrix();
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    const Graph& graph) const {
  return TsmResult();
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int startVertex) const {
  return std::vector<int>();
}

};  // namespace SimpleNavigator
