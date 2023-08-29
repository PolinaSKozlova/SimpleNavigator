#include "s21_graph_algorithms.h"

#include <stack>

namespace SimpleNavigator {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int startVertex) const {
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(graph.GetSize(), false);
  std::stack<int> stack;
  std::cout << "startVertex : " << startVertex << std::endl;
  stack.push(startVertex);
  is_visited[startVertex] = true;
  while (!stack.empty()) {
    int current_vertex = stack.top();
    std::cout << "current_vertex : " << current_vertex << std::endl;
    stack.pop();
    visited.push_back(current_vertex);
    for (int neighbor = 0; neighbor < num_vertices; neighbor++) {
      std::cout << "matrix  [" << current_vertex << "][" << neighbor
                << "] = " << graph.GetGraphMatrix()[current_vertex][neighbor]
                << "  is_visited[neighbor] " << is_visited[neighbor]
                << std::endl;
      if (graph.GetGraphMatrix()[current_vertex][neighbor] != 0 &&
          !is_visited[neighbor]) {
        std::cout << "push " << neighbor << std::endl;
        stack.push(neighbor);
        is_visited[neighbor] = true;
      }
      // if (current_vertex == stack.top()) {
      //   stack.pop();
      // }
    }
  }
  return visited;
}

// int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
//                                                     int vertex1,
//                                                     int vertex2) const {
//   return 0;
// }

// GraphAlgorithms::AdjacencyMatrix
// GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) const {
//   return AdjacencyMatrix();
// }

// GraphAlgorithms::AdjacencyMatrix GraphAlgorithms::GetLeastSpanningTree(
//     const Graph& graph) const {
//   return AdjacencyMatrix();
// }

// TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
//     const Graph& graph) const {
//   return TsmResult();
// }

// std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
//                                                      int startVertex) const
//                                                      {
//   return std::vector<int>();
// }

};  // namespace SimpleNavigator
