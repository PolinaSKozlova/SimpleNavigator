#include <gtest/gtest.h>

#include "../graph_classes/s21_graph.h"

TEST(graph_load_from_file, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_5");
  SimpleNavigator::Graph::AdjacencyMatrix expected = {{0, 1, 4, 5, 3},
                                                      {0, 0, 3, 7, 2},
                                                      {4, 2, 0, 1, 4},
                                                      {5, 3, 1, 0, 5},
                                                      {3, 7, 4, 0, 0}};
  SimpleNavigator::Graph::AdjacencyMatrix result = graph.GetGraphMatrix();
  for (size_t i = 0; i < graph.GetSize(); ++i) {
    for (size_t j = 0; j < graph.GetSize(); ++j) {
      EXPECT_EQ(expected[i][j], result[i][j]);
    }
  }
}

TEST(graph_load_from_file, test_2) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_4");
  SimpleNavigator::Graph::AdjacencyMatrix expected = {
      {0, 3, 5, 6}, {3, 0, 1, 7}, {5, 1, 0, 4}, {6, 7, 4, 0}};
  SimpleNavigator::Graph::AdjacencyMatrix result = graph.GetGraphMatrix();
  for (size_t i = 0; i < graph.GetSize(); ++i) {
    for (size_t j = 0; j < graph.GetSize(); ++j) {
      EXPECT_EQ(expected[i][j], result[i][j]);
    }
  }
}

TEST(graph_load_from_file, test_3) {
  SimpleNavigator::Graph graph;
  try {
    graph.LoadGraphFromFile("graph_examples/graph_wrong");
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Incorrect matrix size", std::string(e.what()));
  }
}

TEST(graph_load_from_file, test_4) {
  SimpleNavigator::Graph graph;
  try {
    graph.LoadGraphFromFile("graph_examples/graph_68");
  } catch (std::exception &e) {
    EXPECT_EQ("Can't open file", std::string(e.what()));
  }
}

TEST(graph_export_to_dot, test_1) {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_11");
  graph.ExportGraphToDot("graph.dot");
}

TEST(graph_export_to_dot, test_2) {
  SimpleNavigator::Graph graph;
  try {
    graph.ExportGraphToDot("graph_wrong");
  } catch (std::invalid_argument &e) {
    EXPECT_EQ("Incorrect filename", std::string(e.what()));
  }
}
