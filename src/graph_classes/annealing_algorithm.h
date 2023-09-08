#ifndef SIMPLE_NAVIGATOR_ANNEALING_ALGORITHMS_H
#define SIMPLE_NAVIGATOR_ANNEALING_ALGORITHMS_H

#include <random>
#include <vector>

#include "s21_graph.h"

namespace SimpleNavigator {
class AnnealingAlgorithms {
  const double kInitialTemperature = 1000.0;
  const double kCoolingRate = 0.99;
  const double kMinTemperature = 0.01;
  const int kNumIterations = 100;

 public:
  AnnealingAlgorithms() = default;
  ~AnnealingAlgorithms() = default;
  TsmResult SolveSailsmanProblem(const Graph& graph) const;

 private:
  int RandomVertex(int max_value) const noexcept;
  std::vector<int> GenerateRandomSolution(const size_t size) const;
  std::vector<int> GenerateNextSolution(std::vector<int>& path) const;
  double CalculateCost(const std::vector<int>& current_solution,
                       const Graph& graph) const;
};

};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_ANNEALING_ALGORITHMS_H