#include "value_node.h"
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

  // Constructor
  ValueNode::ValueNode(vector<uint8_t> _data){
   data = _data;
  }

  ValueNode::ValueNode(){

  };
  // Destructor
  ValueNode::~ValueNode(void){
  }
  
  void ValueNode::Unmarshal(vector<uint8_t> _hash, vector<uint8_t> data) {
    return;
  }

  vector<uint8_t> ValueNode::Marshal() {
    return data;
  }

  tuple<vector<uint8_t>, bool> ValueNode::Cache() {
    return make_tuple(vector<uint8_t>{}, true);
  }
