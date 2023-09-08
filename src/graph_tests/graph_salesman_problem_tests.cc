#include <gtest/gtest.h>

#include <vector>

#include "../graph_classes/annealing_algorithm.h"
#include "../graph_classes/ant_algorithm.h"
#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

TEST(ant_algorithm, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_4");
  SimpleNavigator::GraphAlgorithms best_path;
  SimpleNavigator::TsmResult res =
      best_path.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(graph.GetSize() + 1, res.vertices.size());
}

TEST(ant_algorithm, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_5");
  SimpleNavigator::GraphAlgorithms best_path;
  SimpleNavigator::TsmResult res =
      best_path.SolveTravelingSalesmanProblem(graph);
  EXPECT_EQ(graph.GetSize() + 1, res.vertices.size());
}

TEST(ant_algorithm, test_3) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_6_or");
  SimpleNavigator::AntAlgorithm best_path;
  try {
    best_path.RunAntAlgoritm(graph);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no path!", std::string(e.what()));
  }
}

TEST(ant_algorithm, test_4) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::AntAlgorithm best_path;
  try {
    best_path.RunAntAlgoritm(graph);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no graph!", std::string(e.what()));
  }
}

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

TEST(annealing_algorithm, test_4) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::AnnealingAlgorithms best_path;
  try {
    best_path.SolveSailsmanProblem(graph);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("You should load graph!", std::string(e.what()));
  }
}
