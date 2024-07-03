/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
#include <vector>

using namespace std;

vector<uint8_t> HexToCompact(vector<uint8_t> input);
vector<uint8_t> CompactToHex(vector<uint8_t> input);
vector<uint8_t> KeyBytesToHex(vector<uint8_t> input);
vector<uint8_t> HexToKeyBytes(vector<uint8_t> input);
int PrefixLen(vector<uint8_t> a, vector<uint8_t> b);
bool HasTerm(vector<uint8_t> b);

