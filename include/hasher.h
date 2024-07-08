#pragma once
#include <vector>
#include <tuple>
#include "node.h"
#include "short_node.h"
#include "full_node.h"

using namespace std;

tuple<Node*, Node*> hashNode(Node*);
tuple<Node*, Node*> hashShortNodeChildren(ShortNode* node);
tuple<Node*, Node*> hashFullNodeChildren(FullNode* node);
Node* shortNodeToHash(ShortNode* node);
Node* fullNodeToHash(FullNode* node);
Node* hashData(vector<uint8_t> data);

