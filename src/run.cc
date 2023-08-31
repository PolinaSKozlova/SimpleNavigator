#include "graph_classes/s21_graph.h"
#include "graph_classes/s21_graph_algorithms.h"

int main() {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_6");
  graph.print_graph();
  // graph.ExportGraphToDot("graph.dot");

  SimpleNavigator::GraphAlgorithms graph_algorithms;
  // graph_algorithms.DepthFirstSearch(graph, 1);
  // graph_algorithms.PrintVector(graph_algorithms.DepthFirstSearch(graph, 1));
  // graph_algorithms.BreadthFirstSearch(graph, 1);
  // graph_algorithms.PrintVector(graph_algorithms.BreadthFirstSearch(graph,
  // 1)); std::cout << "shortest way "
  //            << graph_algorithms.GetShortestPathBetweenVertices(graph, 1, 7)
  //            << std::endl;

  SimpleNavigator::GraphAlgorithms::AdjacencyMatrix graph_matrix =
      graph_algorithms.GetShortestPathsBetweenAllVertices(graph);
  std::cout << " shortest_paths after FW" << std::endl;
  graph_algorithms.PrintMatrix(graph_matrix);

  return 0;
}