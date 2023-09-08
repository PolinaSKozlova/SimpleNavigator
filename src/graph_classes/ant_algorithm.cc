#include "ant_algorithm.h"

#include <algorithm>

#include "s21_graph.h"

namespace SimpleNavigator {

void AntAlgorithm::RunAntAlgoritm(const Graph &graph) {
  int size = static_cast<int>(graph.GetSize());
  FillPheromonMatrix(size);
  FillDistanceMatrix(graph);

  std::set<TsmResult> solutions;
  std::vector<int> path;
  int ant = 0;
  int no_path = 0;

  while (ant < size) {
    MatrixDouble phero;
    int started_here = 0;
    WeightToVertex vertex_weight = std::make_pair(0.0, started_here);
    phero.resize(size, std::vector<double>(size));

    while (vertex_weight.second < size) {
      path.resize(0);
      std::vector<bool> visited(size, false);
      visited[vertex_weight.second] = true;

      started_here = vertex_weight.second;
      path.push_back(vertex_weight.second);
      while (!AllVisited(visited)) {
        std::vector<WeightToVertex> desired_path =
            GetDesireToVisit(visited, vertex_weight.second);

        auto tmp = vertex_weight.second;
        vertex_weight.second = FindNextVertex(desired_path);
        if (vertex_weight.second == -1) {
          vertex_weight.second = started_here;

          no_path++;
          if (no_path == size + 1) {
            throw std::invalid_argument("Sorry! There is no path!");
          }
          break;
        }
        vertex_weight.first +=
            graph.GetGraphMatrix()[tmp][vertex_weight.second];
        path.push_back(vertex_weight.second);
        visited[vertex_weight.second] = true;
      }
      if (graph.GetGraphMatrix()[vertex_weight.second][started_here] == 0) {
        vertex_weight.second = started_here;
        no_path++;
        if (no_path == size + 1) {
          throw std::invalid_argument("Sorry! There is no path!");
        }
        break;
      }
      path.push_back(started_here);
      vertex_weight.first +=
          graph.GetGraphMatrix()[vertex_weight.second][started_here];
      vertex_weight.second = started_here;
      for (size_t i = 0; i < path.size() - 1; i++) {
        phero[path[i]][path[i + 1]] = kQ / vertex_weight.first;
      }

      solutions.emplace(path, vertex_weight.first);
      vertex_weight.first = 0.0;
      vertex_weight.second += 1;
    }
    UpdatePheromonMatrix(phero);
    //==========================================================================
    std::cout << "updated pheromon matrix" << std::endl;
    for (size_t i = 0; i < pheromon_matrix_.size(); ++i) {
      for (size_t j = 0; j < pheromon_matrix_[i].size(); ++j) {
        std::cout << pheromon_matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
    //==========================================================================
    phero.clear();
    ant++;
    std::cout << "ant: " << ant << std::endl;
    std::cout << "no path: " << no_path << std::endl;
    std::cout << "solutions: " << solutions.size() << std::endl;
    std::cout << std::endl;
  }

  if (!solutions.empty()) solution_ = *solutions.begin();
}

bool AntAlgorithm::AllVisited(const std::vector<bool> &visited) const {
  for (size_t i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

int AntAlgorithm::FindNextVertex(
    const std::vector<AntAlgorithm::WeightToVertex> &desired_path) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  auto generated = distribution(generator);
  int next_vertex = -1;
  for (size_t i = 0; i < desired_path.size(); ++i) {
    if (generated < desired_path[i].first &&
        generated > desired_path[i + 1].first) {
      next_vertex = desired_path[i].second;
    }
  }

  return next_vertex;
}

void AntAlgorithm::UpdatePheromonMatrix(const MatrixDouble &phero) {
  for (size_t i = 0; i < pheromon_matrix_.size(); ++i) {
    for (size_t j = 0; j < pheromon_matrix_[i].size(); ++j) {
      pheromon_matrix_[i][j] *= (1 - kEvaporation);
      pheromon_matrix_[i][j] += phero[i][j];
    }
  }
}

void AntAlgorithm::FillPheromonMatrix(int size) {
  pheromon_matrix_.resize(size, std::vector<double>(size));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
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

std::vector<AntAlgorithm::WeightToVertex> AntAlgorithm::GetDesireToVisit(
    std::vector<bool> &visited, int vertex) {
  std::vector<AntAlgorithm::WeightToVertex> result;

  result.resize(visited.size());
  double all_desire = 0.0;
  for (size_t i = 0; i < visited.size(); ++i) {
    if (!visited[i]) {
      all_desire += std::pow(pheromon_matrix_[vertex][i], kAlpha) *
                    std::pow(distance_matrix_[vertex][i], kBeta);
    }
  }

  for (size_t i = 0; i < visited.size(); ++i) {
    if (!visited[i]) {
      result[i].first = std::pow(pheromon_matrix_[vertex][i], kAlpha) *
                        std::pow(distance_matrix_[vertex][i], kBeta) /
                        all_desire;
      result[i].second = i;
    }
  }

  std::sort(result.begin(), result.end());

  for (size_t i = result.size() - 2; i > 0; --i) {
    result.at(i).first = result.at(i).first + result.at(i + 1).first;
  }

  return result;
}

};  // namespace SimpleNavigator