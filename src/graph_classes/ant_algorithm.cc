#include "ant_algorithm.h"

namespace SimpleNavigator {

void AntAlgorithm::RunAntAlgoritm(const Graph &graph) {
  size_t size = graph.GetSize();
  FillPheromonMatrix(size);
  FillDistanceMatrix(graph);

  std::set<TsmResult> solutions;
  // paths.resize(size,std::vector<int>(size));
  size_t ant = 0;
  std::pair<size_t, double> vertex_weight;
  while (ant < size) {
    MatrixDouble phero.resize(size, std::vector<double>(size));
    vertex_weight = std::make_pair(0, 0.0);
    while (vertex_weight.first < size) {
      std::vector<bool> visited(size, false);
      visited[vertex_weight.first] = true;
      std::vector<size_t> path;
      while (!AllVisited(visited)) {
        path.push_back(vertex_weight.first);
        //  to do: pair watch again
        std::vector<std::pair<double, size_t>> desired_path =
            GetDesireToVisit(visited, vertex_weight);
        auto tmp = vertex_weight.first;
        vertex_weight.first = FindNextVertex(desired_path);
        vertex_weight.second +=
            graph.GetGraphMatrix()[tmp][vertex_weight.first];
        visited[vertex_weight.first] = true;
      }
      // возврат в начальную вершину
      for (size_t i = 0; i < path.size() - 1; i++) {
        phero[path[i]][path[i + 1]] = kQ / vertex_weight.second;
      }
      solutions.emplace(path, vertex_weight.second);
      vertex_weight.second = 0.0;
      ++vertex_weight.first;
    }
    UpdatePheromonMatrix(phero);
    phero.clear();
    // обновить феромоны

    //?? вершина  1?
    ant++;
  }
}

bool AntAlgorithm::AllVisited(const std::vector<bool> visited) const {
  for (size_t i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

size_t AntAlgorithm::FindNextVertex(<std::pair<double, size_t>> &desired_path) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  auto generated = distribution(generator);
  size_t next_vertex;
  for (size_t i = 0; i < desired_path.size(); ++i) {
    if (generated < desired_path[i].first &&
        generated > desired_path[i + 1].first) {
      next_vertex = desired_path[i].second;
    }
  }
  return next_vertex;
}

void AntAlgorithm::UpdatePheromonMatrix(const MatrixDouble &phero) {
  // for (size_t i = 0; i < paths.size(); ++i) {
  //   for (size_t j = 0; j < paths[i].size(); ++j) {
  //     pheromon_matrix_[i][paths[i][j]] += kPheromons;
  //   }
  // }
}

void AntAlgorithm::FillPheromonMatrix(size_t &size) {
  pheromon_matrix_.resize(size, std::vector<double>(size));
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      pheromon_matrix_[i][j] = kPheromons;
    }
  }
}

void AntAlgorithm::FillDistanceMatrix(const Graph &graph) {
  distance_matrix_.resize(graph.GetSize(),
                          std::vector<double>(graph.GetSize()));

  for (size_t i = 0; i < graph.GetSize(); ++i) {
    for (size_t j = 0; j < graph.GetSize(); ++j) {
      distance_matrix_[i][j] = graph.GetGraphMatrix()[i][j] / kDistance;
    }
  }
}

std::vector<std::pair<double, size_t>> AntAlgorithm::GetDesireToVisit(
    std::vector<bool> &visited, size_t &vertex) {
  std::vector<std::pair<double, size_t>> result.resize(visited.size());
  double all_desire = 0.0;
  for (size_t i = 0; i < visited.size(); ++i) {
    all_desire += std::pow(pheromon_matrix_[vertex][i], kAlpha) *
                  std::pow(distance_matrix_[vertex][i], kBeta);
  }

  for (size_t i = 0; i < visited.size(); ++i) {
    if (!visited[i]) {
      result[i].first = std::pow(pheromon_matrix_[vertex][i], kAlpha) *
                        std::pow(distance_matrix_[vertex][i], kBeta) /
                        all_desire;
      result[i].second = i;
    }
  }
  result.sort();
  return result;
}

};  // namespace SimpleNavigator