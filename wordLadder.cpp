#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "wordLadder.hpp"
#include <stack>

// default constructor done for you
WordLadder::WordLadder() = default;

WordLadder::WordLadder(const std::string& inputFile) {
  // we provide a template to demonstrate how to read from a file
  // Constructor that reads words from an input file and builds the word ladder graph
  std::ifstream file(inputFile);
  std::vector<std::string> words {};
  std::string word {};
  while (file >> word) {
    words.push_back(word);
  }
  
  for (auto it = words.begin(); it != words.end(); ++it) {
    // Add vertices to the graph
    addVertex(*it);
    // Check if two words have the same length and differ by only one character
    for (auto jt = it + 1; jt != words.end(); ++jt) {
      if (it->length() == jt->length()) {
        int difcharCount = 0;
        for (size_t i = 0; i < it->length(); ++i) {
          if ((*it)[i] != (*jt)[i]) {
            ++difcharCount;
            if (difcharCount > 1) {
              break;
            }
          }
        }
        // Check if two words have the same length and differ by only one character
        if (difcharCount == 1) {
          addEdge(*it, *jt);
        }
      }
    }
  }
}

// Adds a vertex to the graph
void WordLadder::addVertex(const std::string& word) {
  if (adjList.find(word) == adjList.end()) {
    adjList[word] = std::unordered_set<std::string>();
  }
}

// Adds an edge between two vertices (a and b) in the graph
void WordLadder::addEdge(const std::string& a, const std::string& b) {
  addVertex(a);
  addVertex(b);
  adjList[a].insert(b);
  adjList[b].insert(a);
}

// Check if there is an edge between two vertices in the graph
bool WordLadder::isEdge(const std::string& a, const std::string& b) const {
  auto it = adjList.find(a);
  if (it == adjList.end()) {
    return false;
  } else {
    return it->second.find(b) != it->second.end();
  }
}

// Checks if a vertex exists in the graph
bool WordLadder::isVertex(const std::string& a) const {
  return adjList.find(a) != adjList.end();
}

// Removes a vertex from the graph
void WordLadder::removeVertex(const std::string& a) {
  if (adjList.find(a) == adjList.end()) {
    return;
  }
  // Removes all edges connected to the vertex
  for (const auto& neighbour : adjList[a]) {
    adjList[neighbour].erase(a);
  }
  adjList.erase(a);
}

std::vector<std::string> WordLadder::getShortestPath(const std::string& origin, const std::string& dest) {
  std::unordered_map<std::string, std::string> parentString; // to keep track of the path
  std::queue<std::string> queue; // queue for Breadth-first-search 
  std::unordered_set<std::string> visited; // to show when vertices have been visited

  // pushes the original word to the queue and shows it's been visited
  queue.push(origin); 
  visited.insert(origin); 

  while (!queue.empty()) {
    std::string current = queue.front();
    queue.pop();
    // checks if destination has been found
    if (current == dest) {
      std::vector<std::string> path;
      while (current != origin) {
        path.push_back(current);
        current = parentString[current];
      }
      path.push_back(origin);
      // reverses the path to get the correct order and returns the shortest path (origin to dest)
      std::reverse(path.begin(), path.end()); 
      return path; 
    }
    for (const auto& neighbour : adjList[current]) {
      if (visited.count(neighbour) == 0) {
      // shows neighbour has been visited, sets parent of neighbour to current word and pushes the neighbour to the queue
        visited.insert(neighbour); 
        parentString[neighbour] = current; 
        queue.push(neighbour); 
      }
    }
  }
  // no path found
  return {};
}

std::map<std::string, int> WordLadder::listComponents() {
  std::unordered_set<std::string> visited; // set to mark visited vertices
  std::map<std::string, int> components; // map to store component information

  for (const auto& vertex : adjList) { // iterate over all vertices
    if (visited.count(vertex.first) == 0) { // if vertex is not visited
      std::stack<std::string> stack;
      stack.push(vertex.first); // push the vertex onto the stack
      visited.insert(vertex.first); // mark vertex as visited
      int count = 0; // counter for the component size
      while (!stack.empty()) {
        std::string current = stack.top();
        stack.pop();
        count++;
        for (const auto& neighbour : adjList[current]) {
          if (visited.count(neighbour) == 0) { // if neighbour is not visited
            visited.insert(neighbour); // mark neighbour as visited
            stack.push(neighbour); // push the neighbour onto the stack for further exploration
          }
        }
      }
      components[vertex.first] = count; // store the component size in the map
    }
  }
  return components; // return the map with component information
}








