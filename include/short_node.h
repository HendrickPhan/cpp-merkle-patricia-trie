#pragma once
#include <vector>
#include <tuple>
#include "node.h"

class ShortNode : public Node{
public:
  ShortNode(vector<uint8_t> key, Node* value, NodeFlag flag);
  ShortNode();
  ~ShortNode();

  void Unmarshal(vector<uint8_t> hash, vector<uint8_t> data);
  vector<uint8_t> Marshal();
  tuple<vector<uint8_t>, bool> Cache();
  Node* Copy();
  NodeType Type() { return NodeType::SHORT; }

  vector<uint8_t> key;
  Node* value;
  NodeFlag flag;
private:
};
