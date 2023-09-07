#include "annealing_algo.h"

namespace SimpleNavigator {
TsmResult AnnealingAlgorithms::SolveSailsmanProblem(const Graph& graph) const {
  if (graph.IsEmpty()) throw std::invalid_argument("You should load graph!");

  TsmResult result;

  std::vector<int> current_solution = GenerateRandomSolution(graph);
  double current_cost = CalculateCost(current_solution, graph);

  result.vertices = current_solution;
  result.distance = current_cost;

  double temperature = kInitialTemperature;

  while (temperature > kMinTemperature) {
    for (int i = 0; i < kNumIterations; i++) {
      std::vector<int> new_solution = GenerateNextSolution(current_solution);
      double new_cost = CalculateCost(new_solution, graph);

      double delta = new_cost - current_cost;

      if (delta < 0 && std::exp(-delta / temperature) > RandomNumber()) {
        current_solution = new_solution;
        current_cost = new_cost;
      }

      //   double delta = current_cost - new_cost;

      //   if (std::exp(delta / temperature) > RandomNumber()) {
      //     current_solution = new_solution;
      //     current_cost = new_cost;
      //   }

      if (current_cost < result.distance) {
        result.vertices = current_solution;
        result.distance = current_cost;
      }

      temperature *= kCoolingRate;
    }
  }

  if (!result.distance)
    throw std::invalid_argument("In loaded graph path doesn't find!");
  return result;
}

double AnnealingAlgorithms::RandomNumber() const noexcept {
  std::default_random_engine generator(std::random_device{}());
  std::uniform_real_distribution distribution(0.0, 1.0);
  return distribution(generator);
}

int AnnealingAlgorithms::RandomVertex(int max_value) const noexcept {
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution distribution(0, max_value);
  return distribution(generator);
}

std::vector<int> AnnealingAlgorithms::GenerateRandomSolution(
    const Graph& graph) const {
  std::vector<int> start_path;
  size_t vertex{};
  int choice = RandomVertex(graph.GetSize() - 1);
  while (vertex < graph.GetSize()) {
    start_path.push_back(choice);
    ++vertex;
    choice = (choice + 1) % graph.GetSize();
  }
  //   start_path.push_back(start_path.front());
  return start_path;
}

std::vector<int> AnnealingAlgorithms::GenerateNextSolution(
    std::vector<int>& path) const {
  int vertex1 = RandomVertex(path.size() - 1);
  int vertex2 = RandomVertex(path.size() - 1);
  std::swap(path[vertex1], path[vertex2]);
  return path;
}

double AnnealingAlgorithms::CalculateCost(std::vector<int>& current_solution,
                                          const Graph& graph) const {
  double distance{};
  for (size_t k = 0; k < current_solution.size() - 1; ++k) {
    distance +=
        graph.GetGraphMatrix()[current_solution[k]][current_solution[k + 1]];
  }
  distance += graph.GetGraphMatrix()[current_solution[graph.GetSize() - 1]]
                                    [current_solution[0]];
  return distance;
}

};  // namespace SimpleNavigator
