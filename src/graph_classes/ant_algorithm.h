#ifndef SIMPLE_NAVIGATOR_ANT_ALGORITHM_H
#define SIMPLE_NAVIGATOR_ANT_ALGORITHM_H

#include <vector>

#include "s21_graph.h"

namespace SimpleNavigator {

class AntAlgorithm {
  using MatrixDouble = std::vector<std::vector<double>>;
  const int kAlpha = 1;
  const int kBeta = 2;
  const double kPheromons = 0.1;
  const double kDistance = 10;

 public:
  AntAlgorithm() = default;
  ~AntAlgorithm() = default;
  void RunAntAlgoritm(const Graph& graph);

 private:
  void FillPheromonMatrix();
  MatrixDouble pheromon_matrix_;
  MatrixDouble distance_matrix_;
  TsmResult solution_;
};

};  // namespace SimpleNavigator

#endif  // SIMPLE_NAVIGATOR_ANT_ALGORITHM_H
