#include <iostream>
#include <vector>
#include "utils.h"

using namespace std;

int main() {
  std::string testHexString = "ffff";
  std::vector<uint8_t> testBytes = hexStringToBytes(testHexString);
  std::cout << "Test bytes: " << testBytes.size() << std::endl << bytesToHexString(testBytes) << std::endl;
  std::vector<uint8_t> testInput = {0x01, 0x02, 0x03, 0x04};
  std::vector<uint8_t> testOutput = keccak256(testInput);
  std::cout << "Test output: " << testOutput.size() << std::endl << bytesToHexString(testOutput) << std::endl;
  return 0;
}
