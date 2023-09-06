#include "s21_graph_algorithms.h"

#include <queue>
#include <set>
#include <stack>

namespace SimpleNavigator {
std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) const {
  if (graph.IsEmpty()) {
    throw std::invalid_argument("Sorry! There is no graph!");
  }
  if (start_vertex < 1 || start_vertex > (int)graph.GetSize()) {
    throw std::invalid_argument("Invalid start vertex!");
  }
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(num_vertices, false);
  containers::stack<int> stack;
  stack.push(start_vertex - 1);
  is_visited[start_vertex - 1] = true;
  visited.push_back(start_vertex);
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
  if (graph.IsEmpty()) {
    throw std::invalid_argument("Sorry! There is no graph!");
  }
  if (vertex1 < 1 || vertex1 > (int)graph.GetSize() || vertex2 < 1 ||
      vertex2 > (int)graph.GetSize()) {
    throw std::invalid_argument("Invalid start or end vertex!");
  }
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

  if (distance[vertex2 - 1] == kInfinity) {
    return -1;
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
  if (graph.IsEmpty()) {
    throw std::invalid_argument("Sorry! There is no graph!");
  }
  int num_vertices = graph.GetSize();
  GraphAlgorithms::AdjacencyMatrix shortest_paths;
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
  if (graph.IsEmpty()) {
    throw std::invalid_argument("Sorry! There is no graph!");
  }

  if (IsOriented(graph)) {
    throw std::invalid_argument(
        "Minimum spanning tree can't be found for a directed graph!");
  }
  int num_vertices = graph.GetSize();
  GraphAlgorithms::AdjacencyMatrix mst;
  mst.resize(num_vertices, std::vector<int>(num_vertices));
  std::vector<bool> visited(num_vertices, false);
  GraphAlgorithms::VertexSet from_to;
  for (int i = 0; i < num_vertices; i++) {
    for (int j = 0; j < num_vertices; j++) {
      if (graph.GetGraphMatrix()[i][j] != 0) {
        from_to.insert(
            std::make_pair(graph.GetGraphMatrix()[i][j], std::make_pair(i, j)));
      }
    }
  }

  auto min_value = *from_to.begin();
  mst[min_value.second.first][min_value.second.second] = min_value.first;
  mst[min_value.second.second][min_value.second.first] = min_value.first;
  visited[min_value.second.first] = true;
  visited[min_value.second.second] = true;
  auto it = from_to.erase(from_to.begin());

  while (!AllVisited(visited)) {
    if (((visited[it->second.first]) && (!visited[it->second.second])) ||
        ((!visited[it->second.first]) && (visited[it->second.second]))) {
      mst[it->second.first][it->second.second] = it->first;
      mst[it->second.second][it->second.first] = it->first;
      visited[it->second.first] = true;
      visited[it->second.second] = true;
      from_to.erase(it);
      it = from_to.begin();
    } else {
      ++it;
    }
  }

  return mst;
}

bool GraphAlgorithms::IsOriented(const Graph& graph) const {
  for (size_t i = 0; i < graph.GetSize(); i++) {
    for (size_t j = 0; j < graph.GetSize(); j++) {
      if (graph.GetGraphMatrix()[i][j] != graph.GetGraphMatrix()[j][i]) {
        return true;
      }
    }
  }
  return false;
}

bool GraphAlgorithms::AllVisited(const std::vector<bool> visited) const {
  for (size_t i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

// TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
//     const Graph& graph) const {
//   return TsmResult();
// }

TsmResult GraphAlgorithms::SolveSalesmanProblemWithDynamicMethod(
    const Graph& graph) const {
  return TsmResult();
}

void GraphAlgorithms::PrintVector(const std::vector<int>& vector) const {
  for (size_t i = 0; i < vector.size() - 1; i++) {
    std::cout << vector.at(i) << " -> ";
  }
  std::cout << vector.back() << std::endl;
}

void GraphAlgorithms::PrintMatrix(const AdjacencyMatrix m) const {
  for (size_t i = 0; i < m.size(); ++i) {
    for (size_t j = 0; j < m[i].size(); ++j) {
      std::cout << m[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) const {
  if (graph.IsEmpty()) {
    throw std::invalid_argument("Sorry! There is no graph!");
  }
  if (start_vertex < 1 || start_vertex > (int)graph.GetSize()) {
    throw std::invalid_argument("Invalid start vertex!");
  }
  std::vector<int> visited;
  int num_vertices = graph.GetSize();
  std::vector<bool> is_visited(graph.GetSize(), false);
  containers::queue<int> queue;
  queue.push(start_vertex - 1);
  is_visited[start_vertex - 1] = true;

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
