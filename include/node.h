#pragma once
#include <vector>
#include <tuple>
using namespace std;

// Define an enumeration type called Color
enum NodeType {
    FULL, 
    SHORT, 
    VALUE,
    HASH
};


class Node {
    // Data members of class
public:
    // Pure Virtual Function
  virtual void Unmarshal(vector<uint8_t> hash, vector<uint8_t> data) = 0;
  virtual vector<uint8_t> Marshal() = 0;
  virtual tuple<vector<uint8_t>, bool> Cache() = 0;
  virtual Node* Copy() = 0;
  virtual NodeType Type() = 0;
    /* Other members */
};

struct NodeFlag{
  vector<uint8_t> hash;
  bool dirty;
};
