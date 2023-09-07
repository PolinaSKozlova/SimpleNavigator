#include "console/console.h"
#include "graph_classes/s21_graph.h"
#include "graph_classes/s21_graph_algorithms.h"

int main() {
  // SimpleNavigator::ConsoleApp console_app;
  // console_app.ShowMenu();
  SimpleNavigator::Graph graph;
  try {
    // graph.LoadGraphFromFile(
    //     "/Users/verenach/A2_SimpleNavigator_v1.0-1/src/graph_examples/"
    //     "graph_7_non_or");
    graph.LoadGraphFromFile(
        "/Users/verenach/A2_SimpleNavigator_v1.0-1/src/graph_examples/"
        "graph_or_6");
  } catch (std::invalid_argument &e) {
    std::cout << "load graph error " << e.what() << std::endl;
  }
  try {
    graph.ExportGraphToDot("graph_or.dot");
  } catch (std::invalid_argument &e) {
    std::cout << "export graph error " << e.what() << std::endl;
  }

  SimpleNavigator::GraphAlgorithms graph_algorithms;
  // graph_algorithms.PrintTsmResult(
  //     graph_algorithms.SolveSalesmanProblemWithSimulatedAnnealingMethod(graph));
  try {
    graph_algorithms.SolveSalesmanProblemWithSimulatedAnnealingMethod(graph)
        .printTsmResult();
  } catch (std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
