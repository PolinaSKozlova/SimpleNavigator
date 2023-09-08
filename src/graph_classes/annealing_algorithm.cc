#include "annealing_algorithm.h"

namespace SimpleNavigator {
TsmResult AnnealingAlgorithms::SolveSailsmanProblem(const Graph& graph) const {
  if (graph.IsEmpty()) throw std::invalid_argument("You should load graph!");

  TsmResult result;

  std::vector<int> current_solution = GenerateRandomSolution(graph.GetSize());
  double current_cost = CalculateCost(current_solution, graph);

  result.vertices = current_solution;
  result.distance = current_cost;

  double temperature = kInitialTemperature;

  while (temperature > kMinTemperature) {
    for (size_t i = 0; i < 2 * graph.GetSize() * kNumIterations; ++i) {
      std::vector<int> new_solution = GenerateNextSolution(current_solution);
      double new_cost = CalculateCost(new_solution, graph);

      double delta = current_cost - new_cost;

      auto random_number = []() {
        std::default_random_engine generator(std::random_device{}());
        std::uniform_real_distribution distribution(0.0, 1.0);
        return distribution(generator);
      };

      if (new_cost > 0 && std::exp(delta / temperature) > random_number()) {
        current_solution = new_solution;
        current_cost = new_cost;
      }

      if (current_cost < result.distance) {
        result.vertices = current_solution;
        result.distance = current_cost;
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
  for (size_t k = 0; k < current_solution.size() - 1; ++k) {
    if (graph.GetGraphMatrix()[current_solution[k]][current_solution[k + 1]] ==
        0)
      return -1;
    distance +=
        graph.GetGraphMatrix()[current_solution[k]][current_solution[k + 1]];
  }
  return distance;
}

};  // namespace SimpleNavigator
