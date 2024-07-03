/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
#include <vector>

using namespace std;

string bytesToHexString(vector<uint8_t> bytes);
vector<uint8_t> hexStringToBytes(string hexString);
vector<uint8_t> keccak256(vector<uint8_t> input);

