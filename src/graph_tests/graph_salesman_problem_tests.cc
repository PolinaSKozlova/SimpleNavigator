#include <gtest/gtest.h>

#include <vector>

#include "../graph_classes/annealing_algorithm.h"
#include "../graph_classes/ant_algorithm.h"
#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

TEST(ant_algorithm, test_1) {}

TEST(ant_algorithm, test_2) {}

TEST(ant_algorithm, test_3) {}

TEST(annealing_algorithm, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_4");
  SimpleNavigator::AnnealingAlgorithms best_path;
  best_path.SolveSailsmanProblem(graph);
  EXPECT_EQ(14, best_path.SolveSailsmanProblem(graph).distance);
}

TEST(annealing_algorithm, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_5");
  SimpleNavigator::AnnealingAlgorithms best_path;
  best_path.SolveSailsmanProblem(graph);
  EXPECT_EQ(13, best_path.SolveSailsmanProblem(graph).distance);
}

TEST(annealing_algorithm, test_3) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_6_or");
  SimpleNavigator::AnnealingAlgorithms best_path;
  try {
    best_path.SolveSailsmanProblem(graph);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("In loaded graph path doesn't find!", std::string(e.what()));
  }
}
