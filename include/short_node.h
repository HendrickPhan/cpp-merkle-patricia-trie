#pragma once
#include <vector>
#include <tuple>
#include "node.h"

class ShortNode : public Node{
public:
  ShortNode();
  ~ShortNode();

  void Unmarshal(vector<uint8_t> hash, vector<uint8_t> data);
  vector<uint8_t> Marshal();
  tuple<vector<uint8_t>, bool> Cache();
  
  vector<uint8_t> key;
  Node* value;
  NodeFlag flag;
private:
};
