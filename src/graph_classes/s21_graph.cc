#include "s21_graph.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace SimpleNavigator {
Graph::Graph(size_t size) : size_(size) { AllocateMemoryForGraphMatrix(); }

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file_to_read;
  std::string line;
  file_to_read.open(GetAbsolutePath(filename));
  if (!file_to_read.is_open()) throw std::invalid_argument("Can't open file");
  getline(file_to_read, line);
  GetSize(line);
  int i = 0;
  while (!file_to_read.eof()) {
    getline(file_to_read, line);
    if (line.empty()) break;
    ReadElementsFromAdjacencyMatrix(line, graph_matrix_[i++]);
  }
  file_to_read.close();
}

void Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream file_to_write;
  if (!CheckFilename(filename))
    throw std::invalid_argument("Incorrect filename");
  file_to_write.open(GetAbsolutePath(filename));
  file_to_write << "digraph Graph {\n";
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      if (graph_matrix_[i][j] > 0) {
        file_to_write << "\t" << (i + 1) << " -> " << (j + 1)
                      << " [label=" << graph_matrix_[i][j] << "];\n";
      }
    }
  }
  file_to_write << "}";
  file_to_write.close();
}

bool Graph::IsEmpty() const noexcept { return graph_matrix_.empty(); }

Graph::AdjacencyMatrix Graph::GetGraphMatrix() const { return graph_matrix_; }

size_t Graph::GetSize() const noexcept { return size_; }

const std::string Graph::GetAbsolutePath(const std::string& filename) {
  std::filesystem::path absolute_path = std::filesystem::absolute(filename);
  return absolute_path.string();
}

void Graph::AllocateMemoryForGraphMatrix() {
  graph_matrix_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    graph_matrix_[i].resize(size_);
  }
}

void Graph::ClearGraphMatrix() {
  for (size_t i = 0; i < size_; ++i) {
    graph_matrix_[i].clear();
  }
  graph_matrix_.clear();
  size_ = 0;
}

void Graph::GetSize(const std::string& size) {
  ClearGraphMatrix();
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

bool Graph::CheckFilename(const std::string& filename) const noexcept {
  if (std::regex_match(filename, std::regex("[A-Za-z\\d]*.(dot|gv)"))) {
    return true;
  } else {
    return false;
  }
}

};  // namespace SimpleNavigator
