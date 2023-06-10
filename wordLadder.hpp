#ifndef WORD_LADDER_HPP_
#define WORD_LADDER_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>

class WordLadder {
 private:
 // put whatever member variables you want to represent the graph here
  std::unordered_map<std::string, std::unordered_set<std::string>> adjList;

  /*
  Each vertex will have a pair, first will be boolean representing whether its its avalid word or not, and second will be the actual adjacency list
  */

 public:
  WordLadder(); // default constructor
  explicit WordLadder(const std::string& filename); // constructor that reads in a file and builds the graph
  void addVertex(const std::string& a); // adds a vertex to the graph
  void addEdge(const std::string& a, const std::string& b); // adds an edge between two vertices in the graph
  bool isEdge(const std::string& a, const std::string& b) const; // checks if there is an edge between two vertices in the graph
  bool isVertex(const std::string& a) const; // checks if a vertex exists in the graph
  void removeVertex(const std::string& a); // removes a vertex from the graph
  std::vector<std::string> getShortestPath(const std::string& origin, const std::string& dest); // finds the shortest path between two vertices in the graph
  std::map<std::string, int> listComponents(); // finds all connected components in the graph

 private:
  // you can add any additional helper functions you might need.

};

#endif


