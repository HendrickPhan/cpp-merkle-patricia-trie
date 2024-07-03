#pragma once
#include <vector>
#include <tuple>
#include "node.h"

using namespace std;

class HashNode : public Node{
public:
  HashNode(vector<uint8_t> _hash);
  HashNode();
  ~HashNode();

  void Unmarshal(vector<uint8_t> _hash, vector<uint8_t> data);
  vector<uint8_t> Marshal();
  tuple<vector<uint8_t>, bool> Cache();
  
  vector<uint8_t> hash;
private:
};
