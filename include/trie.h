/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
#include<vector>
#include<tuple>
#include"node.h"

struct NodeWrapper {
  vector<uint8_t> hash;
  vector<uint8_t> value;
};

// struct CommitReturn{
//   vector<uint8_t> hash;
//   vector<NodeWrapper> nodes;
//   vector<vector<uint8_t>> oldKeys;
// };

class Trie {
public:
  Trie(void);
  ~Trie(void);

  vector<uint8_t> Get(vector<uint8_t> key);
  void Update(vector<uint8_t> key, vector<uint8_t> value);
  vector<uint8_t>Hash();
  tuple<vector<uint8_t>, vector<NodeWrapper>, vector<vector<uint8_t>>> Commit();
  
private:
  tuple<vector<uint8_t>, Node, bool>get(
    origNode Node,
    vector<uint8_t> key,
    uint32_t pos
  )
  void update(vector<uint8_t> key, vector<uint8_t> value);
  tuple<bool, Node> insert(Node node, vector<uint8_t> prefix, vector<uint8_t> key, vector<uint8_t> value);
  Node resolveAndTrack(Node node, vector<uint8_t> prefix);
  Node resolve(Node node, vector<uint8_t> prefix);
  tuple<Node, Node>hashRoot();
} 

