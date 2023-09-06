#ifndef SIMPLE_NAVIGATOR_ANT_ALGORITHM_H
#define SIMPLE_NAVIGATOR_ANT_ALGORITHM_H

#include <chrono>
#include <random>
#include <vector>

#include "s21_graph.h"

namespace SimpleNavigator {
struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class AntAlgorithm {
  using MatrixDouble = std::vector<std::vector<double>>;
  const int kAlpha = 1;
  const int kBeta = 2;
  const double kPheromons = 0.1;
  const double kDistance = 10;

 public:
  AntAlgorithm() = default;
  ~AntAlgorithm() = default;
  void RunAntAlgoritm(const Graph &graph);

 private:
  bool AllVisited(const std::vector<bool> visited) const;
  size_t FindNextVertex(<std::pair<double, size_t>> &desired_path);
  void FillPheromonMatrix(size_t &size);
  void UpdatePheromonMatrix(const &std::vector<std::vector<size_t>>);
  void FillDistanceMatrix(const Graph &graph);
  std::vector<std::pair<double, size_t>> GetDesireToVisit(
      std::vector<bool> &visited, size_t &vertex);
  MatrixDouble pheromon_matrix_;
  MatrixDouble distance_matrix_;
  TsmResult solution_;
};

};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_ANT_ALGORITHM_H
