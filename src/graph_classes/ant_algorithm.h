#ifndef SIMPLE_NAVIGATOR_ANT_ALGORITHM_H
#define SIMPLE_NAVIGATOR_ANT_ALGORITHM_H

#include <chrono>
#include <random>
#include <set>
#include <vector>

#include "s21_graph.h"

namespace SimpleNavigator {

class AntAlgorithm {
  const int kAlpha = 3;
  const int kBeta = 3;
  const double kQ = 3;
  const double kEvaporation = 0.1;
  const double kPheromons = 0.2;
  const double kDistance = 10.0;
  const int kNumIterations = 100;

 public:
  void RunAntAlgoritm(const Graph &graph);
  TsmResult GetSolution() { return solution_; }
  using MatrixDouble = std::vector<std::vector<double>>;
  using WeightToVertex = std::pair<double, int>;

 private:
  bool AllVisited(const std::vector<bool> &visited) const;
  int FindNextVertex(const std::vector<WeightToVertex> &desired_path);
  void FillPheromonMatrix(int size);
  void UpdatePheromonMatrix(const MatrixDouble &phero);
  void FillDistanceMatrix(const Graph &graph);
  std::vector<WeightToVertex> GetDesireToVisit(const std::vector<bool> &visited,
                                               int vertex);

  MatrixDouble pheromon_matrix_;
  MatrixDouble distance_matrix_;
  TsmResult solution_;
};

};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_ANT_ALGORITHM_H
