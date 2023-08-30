#include "s21_graph_algorithms.h"

#include <queue>
#include <stack>

namespace SimpleNavigator {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int startVertex) const {
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(graph.GetSize(), false);
  std::stack<int> stack;
  stack.push(startVertex - 1);
  is_visited[startVertex - 1] = true;
  visited.push_back(startVertex);
  while (!stack.empty()) {
    int current_vertex = stack.top();
    stack.pop();
    if (!is_visited[current_vertex]) {
      is_visited[current_vertex] = true;
      visited.push_back(current_vertex + 1);
    }
    for (int neighbor = num_vertices - 1; neighbor >= 0; --neighbor) {
      if (graph.GetGraphMatrix()[current_vertex][neighbor] != 0 &&
          !is_visited[neighbor]) {
        stack.push(neighbor);
      }
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

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int startVertex) const {
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(graph.GetSize(), false);

  std::queue<int> queue;
  queue.push(startVertex - 1);
  is_visited[startVertex - 1] = true;

  while (!queue.empty()) {
    int current_vertex = queue.front();
    visited.push_back(current_vertex + 1);
    queue.pop();
    for (int neighbor = 0; neighbor < num_vertices; neighbor++) {
      if (graph.GetGraphMatrix()[current_vertex][neighbor] != 0 &&
          !is_visited[neighbor]) {
        queue.push(neighbor);
        is_visited[neighbor] = true;
      }
    }
  }
  return visited;
}

};  // namespace SimpleNavigator
