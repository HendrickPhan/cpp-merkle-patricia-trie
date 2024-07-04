/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
extern "C"
{
#include "KeccakHash.h"
}
#include "utils.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;


// Function to convert a byte array to a hexadecimal string
string bytesToHexString(vector<uint8_t> bytes) {
    stringstream ss;
    ss << hex << setfill('0');
    for (uint32_t i = 0; i < bytes.size(); i++) {
        ss << setw(2) << static_cast<unsigned int>(bytes[i]);
    }
    return ss.str();
}

// Function to convert a hexadecimal string to a byte array
vector<uint8_t> hexStringToBytes(string hexString) {
    vector<uint8_t> bytes;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        string byteString = hexString.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}


void keccak_256(
   const unsigned char* input,
    unsigned int inputByteLen,
    unsigned char* output)
  {
   // Ethereum started using Keccak and called it SHA3 before it was finalised.
    // Standard SHA3-256 (the FIPS accepted version) uses padding 0x06, but
    // Ethereum's "Keccak-256" uses padding 0x01.
    // All other constants are copied from Keccak_HashInitialize_SHA3_256 in
    // KeccakHash.h.
    Keccak_HashInstance hi;
    Keccak_HashInitialize(&hi, 1088, 512, 256, 0x01);
    Keccak_HashUpdate(
      &hi, input, inputByteLen * std::numeric_limits<unsigned char>::digits);
    Keccak_HashFinal(&hi, output);
}

vector<uint8_t> keccak256(vector<uint8_t> input) {
    vector<uint8_t> output(32);
    keccak_256(input.data(), input.size(), output.data());
    return output;
}
