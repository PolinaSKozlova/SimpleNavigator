#include "s21_graph_algorithms.h"

#include <queue>
#include <stack>

namespace SimpleNavigator {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int startVertex) const {
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(num_vertices, false);
  containers::stack<int> stack;
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

int GraphAlgorithms::GetShortestPathBetweenVertices(const Graph& graph,
                                                    int vertex1,
                                                    int vertex2) const {
  int num_vertices = graph.GetSize();
  std::vector<int> distance(num_vertices, kInfinity);
  std::vector<bool> is_visited(num_vertices, false);

  distance[vertex1 - 1] = 0;

  for (int i = 0; i < num_vertices - 1; i++) {
    int next_v = GetClosestVertex(distance, is_visited);
    if (next_v == -1) {
      break;
    }

    is_visited[next_v] = true;

    for (int v = 0; v < num_vertices; v++) {
      if (!is_visited[v] && graph.GetGraphMatrix()[next_v][v] != 0) {
        int weight = graph.GetGraphMatrix()[next_v][v];
        if (distance[next_v] + weight < distance[v]) {
          distance[v] = distance[next_v] + weight;
        }
      }
    }
  }
  return distance[vertex2 - 1];
}

int GraphAlgorithms::GetClosestVertex(
    const std::vector<int>& distances,
    const std::vector<bool>& is_visited) const {
  int closest_vertex = -1;
  int min_distance = kInfinity;
  for (size_t i = 0; i < distances.size(); i++) {
    if (!is_visited[i] && distances[i] < min_distance) {
      closest_vertex = i;
      min_distance = distances[i];
    }
  }
  return closest_vertex;
}

GraphAlgorithms::AdjacencyMatrix
GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph& graph) const {
  int num_vertices = graph.GetSize();
  GraphAlgorithms::AdjacencyMatrix shortest_paths;
  // shortest_paths.resize(num_vertices, std::vector<int>(num_vertices));
  shortest_paths = graph.GetGraphMatrix();

  for (int k = 0; k < num_vertices; k++) {
    for (int i = 0; i < num_vertices; i++) {
      for (int j = 0; j < num_vertices; j++) {
        if (shortest_paths[i][k] && shortest_paths[k][j] && i != j) {
          if (shortest_paths[i][k] + shortest_paths[k][j] <
                  shortest_paths[i][j] ||
              shortest_paths[i][j] == 0) {
            shortest_paths[i][j] = shortest_paths[i][k] + shortest_paths[k][j];
          }
        }
      }
    }
  }

  return shortest_paths;
}

GraphAlgorithms::AdjacencyMatrix GraphAlgorithms::GetLeastSpanningTree(
    const Graph& graph) const {
  int num_vertices = graph.GetSize();
  GraphAlgorithms::AdjacencyMatrix mst;
  mst.resize(num_vertices, std::vector<int>(num_vertices));
  std::vector<int> vertex(num_vertices, kInfinity);
  std::vector<bool> is_visited(num_vertices, false);

  vertex[0] = 0;

  for (int i = 0; i < num_vertices - 1; i++) {
    int closest_vertex = GetClosestVertex(vertex, is_visited);
    if (closest_vertex == -1) {
      break;
    }

    is_visited[closest_vertex] = true;

    for (int v = 0; v < num_vertices; v++) {
      if (!is_visited[v] && graph.GetGraphMatrix()[closest_vertex][v] != 0 &&
          graph.GetGraphMatrix()[closest_vertex][v] < vertex[v]) {
        mst[closest_vertex][v] = graph.GetGraphMatrix()[closest_vertex][v];
        mst[v][closest_vertex] = graph.GetGraphMatrix()[closest_vertex][v];
        vertex[v] = graph.GetGraphMatrix()[closest_vertex][v];
      }
    }
  }

  return mst;
}

// TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
//     const Graph& graph) const {
//   return TsmResult();
// }

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int startVertex) const {
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(graph.GetSize(), false);
  // std::queue<int> queue;
  containers::queue<int> queue;
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
