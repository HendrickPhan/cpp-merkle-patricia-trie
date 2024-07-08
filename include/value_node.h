#pragma once
#include <vector>
#include <tuple>
#include "node.h"

class ValueNode : public Node{
public:
  ValueNode(vector<uint8_t> _hash);
  ValueNode();
  ~ValueNode(void);

  void Unmarshal(vector<uint8_t> _hash, vector<uint8_t> data);
  vector<uint8_t> Marshal();
  tuple<vector<uint8_t>, bool> Cache();
  Node* Copy();
  NodeType Type() { return VALUE; }

  vector<uint8_t> data;
private:
};
