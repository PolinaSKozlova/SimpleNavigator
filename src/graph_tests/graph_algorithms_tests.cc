#include <gtest/gtest.h>

#include <vector>

#include "../graph_classes/s21_graph.h"
#include "../graph_classes/s21_graph_algorithms.h"

TEST(BFS, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_4");
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  std::vector<int> result{1, 2, 3, 4};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 1), result);
  std::vector<int> result2{2, 1, 3, 4};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 2), result2);
  std::vector<int> result3{3, 1, 2, 4};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 3), result3);
  std::vector<int> result4{4, 1, 2, 3};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 4), result4);
}

TEST(BFS, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_10");
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  std::vector<int> result{6, 1, 4, 5, 7, 8, 9, 10, 2, 3};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 6), result);
  std::vector<int> result2{2, 1, 5, 8, 10, 3, 4, 6, 9, 7};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 2), result2);
  std::vector<int> result3{5, 1, 2, 3, 4, 6, 8, 9, 10, 7};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 5), result3);
  std::vector<int> result4{7, 3, 4, 6, 8, 1, 5, 9, 10, 2};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 7), result4);
  std::vector<int> result5{10, 2, 3, 4, 5, 6, 8, 1, 7, 9};
  EXPECT_EQ(graph_algorithms.BreadthFirstSearch(graph, 7), result4);
}

TEST(BFS, test_3) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  try {
    graph_algorithms.BreadthFirstSearch(graph, 1);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no graph!", std::string(e.what()));
  }
}

TEST(DFS, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_4");
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  std::vector<int> result{1, 2, 3, 4};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 1), result);
  std::vector<int> result2{2, 1, 3, 4};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 2), result2);
  std::vector<int> result3{3, 1, 2, 4};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 3), result3);
  std::vector<int> result4{4, 1, 2, 3};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 4), result4);
}

TEST(DFS, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_10");
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  std::vector<int> result{1, 2, 5, 3, 4, 6, 7, 8, 9, 10};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 1), result);
  std::vector<int> result2{9, 1, 2, 5, 3, 4, 6, 7, 8, 10};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 9), result2);
  std::vector<int> result3{4, 1, 2, 5, 3, 7, 6, 8, 9, 10};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 4), result3);
  std::vector<int> result4{7, 3, 1, 2, 5, 4, 6, 8, 9, 10};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 7), result4);
  std::vector<int> result5{8, 1, 2, 5, 3, 4, 6, 7, 9, 10};
  EXPECT_EQ(graph_algorithms.DepthFirstSearch(graph, 8), result5);
}

TEST(DFS, test_3) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  try {
    graph_algorithms.DepthFirstSearch(graph, 1);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no graph!", std::string(e.what()));
  }
}

TEST(shortest_path, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_10");
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 1, 10), 32);
  EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 9, 2), 33);
  EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 4, 2), 32);
  EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 7, 10), 98);
  EXPECT_EQ(graph_algorithms.GetShortestPathBetweenVertices(graph, 3, 8), 23);
}

TEST(shortest_path, test_2) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  try {
    graph_algorithms.GetShortestPathBetweenVertices(graph, 1, 10);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no graph!", std::string(e.what()));
  }
}

TEST(shortest_path_between_all, test_1) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  try {
    graph_algorithms.GetShortestPathsBetweenAllVertices(graph);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no graph!", std::string(e.what()));
  }
}

TEST(shortest_path_between_all, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_10");
  SimpleNavigator::GraphAlgorithms::AdjacencyMatrix result{
      {0, 29, 20, 20, 16, 31, 101, 12, 4, 32},
      {29, 0, 42, 32, 28, 44, 111, 21, 33, 41},
      {20, 42, 0, 15, 14, 27, 81, 23, 23, 27},
      {20, 32, 15, 0, 4, 12, 92, 12, 24, 13},
      {16, 28, 14, 4, 0, 16, 95, 9, 20, 16},
      {31, 44, 27, 12, 16, 0, 95, 24, 35, 3},
      {101, 111, 81, 92, 95, 95, 0, 90, 104, 98},
      {12, 21, 23, 12, 9, 24, 90, 0, 15, 25},
      {4, 33, 23, 24, 20, 35, 104, 15, 0, 36},
      {32, 41, 27, 13, 16, 3, 98, 25, 36, 0}};
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  EXPECT_EQ(graph_algorithms.GetShortestPathsBetweenAllVertices(graph), result);
}

TEST(minimal_spanning_tree, test_1) {
  SimpleNavigator::Graph graph;
  SimpleNavigator::GraphAlgorithms graph_algorithms;
  try {
    graph_algorithms.GetLeastSpanningTree(graph);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Sorry! There is no graph!", std::string(e.what()));
  }
}

TEST(minimal_spanning_tree, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_10");
  SimpleNavigator::GraphAlgorithms::AdjacencyMatrix result{
      {0, 0, 0, 0, 0, 0, 0, 12, 4, 0},  {0, 0, 0, 0, 0, 0, 0, 21, 0, 0},
      {0, 0, 0, 0, 14, 0, 81, 0, 0, 0}, {0, 0, 0, 0, 4, 12, 0, 0, 0, 0},
      {0, 0, 14, 4, 0, 0, 0, 9, 0, 0},  {0, 0, 0, 12, 0, 0, 0, 0, 0, 3},
      {0, 0, 81, 0, 0, 0, 0, 0, 0, 0},  {12, 21, 0, 0, 9, 0, 0, 0, 0, 0},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0},   {0, 0, 0, 0, 0, 3, 0, 0, 0, 0}};

  SimpleNavigator::GraphAlgorithms graph_algorithms;
  EXPECT_EQ(graph_algorithms.GetLeastSpanningTree(graph), result);
}
