#include "graph_classes/s21_graph.h"

int main() {
  SimpleNavigator::Graph graph;
  graph.LoadGraphFromFile("graph_examples/graph_5");
  graph.print_graph();
  graph.ExportGraphToDot("graph.dot");
  return 0;
}