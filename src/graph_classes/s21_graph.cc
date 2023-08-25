#include "s21_graph.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace SimpleNavigator {
Graph::Graph(size_t size) : size_(size) { AllocateMemoryForGraphMatrix(); }

Graph::~Graph() { FreeMemoryForGraphMatrix(); }

void Graph::LoadGraphFromFile(std::string filename) {
  std::filesystem::path absolute_path = std::filesystem::absolute(filename);
  std::ifstream fin;
  std::string line;
  fin.open(absolute_path.string());
  if (!fin.is_open()) throw std::invalid_argument("Can't open file");
  getline(fin, line);
  GetSize(line);
  int i = 0;
  while (!fin.eof()) {
    getline(fin, line);
    if (line.empty()) break;
    ReadElementsFromAdjacencyMatrix(line, graph_matrix_[i++]);
  }
  fin.close();
}

// void Graph::ExportGraphToDot(std::string filename) {}

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

void Graph::GetSize(const std::string& size) {
  FreeMemoryForGraphMatrix();
  size_ = std::stoi(size);
  AllocateMemoryForGraphMatrix();
}

void Graph::ReadElementsFromAdjacencyMatrix(const std::string& line,
                                            std::vector<int>& rows) {
  std::istringstream iss(line);
  std::string matrix_line{};
  size_t pos{0};
  while (iss >> matrix_line) {
    std::istringstream sub_iss(matrix_line);
    std::string sub_token;
    getline(sub_iss, sub_token, ' ');
    if (!sub_token.empty()) {
      rows[pos++] = std::stoi(sub_token);
    }
  }
  if (pos != size_) throw std::invalid_argument("Incorrect matrix size");
}

};  // namespace SimpleNavigator