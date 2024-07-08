#pragma once

#include <vector>
#include <tuple>
#include "node.h"

const int TOTAL_CHILD_NODE = 17;

class FullNode : public Node{
public:
  FullNode();
  ~FullNode();

  void Unmarshal(vector<uint8_t> hash, vector<uint8_t> data);
  vector<uint8_t> Marshal();
  tuple<vector<uint8_t>, bool> Cache();
  Node* Copy();
  NodeType Type() { return FULL; }
  
  Node* children[TOTAL_CHILD_NODE];
  NodeFlag flag;
private:
};
