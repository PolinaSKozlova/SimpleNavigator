#include "s21_graph.h"

namespace SimpleNavigator {
Graph::Graph(size_t size) : size_(size) { AllocateMemoryForGraphMatrix(); }

Graph::~Graph() { FreeMemoryForGraphMatrix(); }

void Graph::LoadGraphFromFile(std::string filename) {}

void Graph::ExportGraphToDot(std::string filename) {}

void Graph::AllocateMemoryForGraphMatrix() {
  graph_matrix_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    graph_matrix_[i].resize(size_);
  }
}

void Graph::FreeMemoryForGraphMatrix() {
  for (size_t i = 0; i < size_; ++i) {
    graph_matrix_[i].clear();
  }
  graph_matrix_.clear();
  size_ = 0;
}

};  // namespace SimpleNavigator