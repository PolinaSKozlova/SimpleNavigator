#include "annealing_algorithm.h"

namespace SimpleNavigator {
TsmResult AnnealingAlgorithms::SolveSailsmanProblem(const Graph& graph) const {
  if (graph.IsEmpty()) throw std::invalid_argument("You should load graph!");

  TsmResult result;

  result.vertices = GenerateRandomSolution(graph.GetSize());
  result.distance = CalculateCost(result.vertices, graph);

  double temperature = kInitialTemperature;

  std::vector<int> new_solution(result.vertices);

  while (temperature > kMinTemperature) {
    for (size_t i = 0; i < 2 * graph.GetSize() * kNumIterations; ++i) {
      new_solution = GenerateNextSolution(new_solution);
      double new_cost = CalculateCost(new_solution, graph);

      auto random_number = []() {
        std::default_random_engine generator(std::random_device{}());
        std::uniform_real_distribution distribution(0.0, 1.0);
        return distribution(generator);
      };

      if (new_cost > 0) {
        if ((new_cost < result.distance || result.distance < 1) ||
            (1 - std::exp((new_cost - result.distance) / temperature)) >
                random_number()) {
          result.vertices = new_solution;
          result.distance = new_cost;
        }
      }

      temperature *= kCoolingRate;
    }
  }

  if (result.distance < 1)
    throw std::invalid_argument("In loaded graph path doesn't find!");
  return result;
}

int AnnealingAlgorithms::RandomVertex(int max_value) const noexcept {
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution distribution(0, max_value);
  return distribution(generator);
}

std::vector<int> AnnealingAlgorithms::GenerateRandomSolution(
    const size_t size) const {
  std::vector<int> start_path;
  size_t vertex{};
  int choice = RandomVertex(size - 1);
  while (vertex < size) {
    start_path.push_back(choice);
    ++vertex;
    choice = (choice + 1) % size;
  }
  start_path.push_back(start_path.front());
  return start_path;
}

std::vector<int> AnnealingAlgorithms::GenerateNextSolution(
    std::vector<int>& path) const {
  path.pop_back();
  int vertex1 = RandomVertex(path.size() - 1);
  int vertex2 = RandomVertex(path.size() - 1);
  std::swap(path[vertex1], path[vertex2]);
  path.push_back(path.front());
  return path;
}

double AnnealingAlgorithms::CalculateCost(
    const std::vector<int>& current_solution, const Graph& graph) const {
  double distance{0};
  if (graph.GetGraphMatrix()[current_solution[current_solution.size() - 2]]
                            [current_solution[0]] != 0) {
    distance +=
        graph.GetGraphMatrix()[current_solution[current_solution.size() - 2]]
                              [current_solution[0]];

  } else {
    return -1.0;
  }
  for (size_t k = 0; k < current_solution.size() - 2; ++k) {
    distance +=
        graph.GetGraphMatrix()[current_solution[k]][current_solution[k + 1]];
    if (graph.GetGraphMatrix()[current_solution[k]][current_solution[k + 1]] ==
        0) {
      return -1.0;
    }
  }
  return distance;
}
};  // namespace SimpleNavigator
