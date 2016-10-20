#include <iostream>
#include <algorithm>
#include "vector.h"

int main() {
  /// Test constructors, copy and move operations
  std::cout << "Constructors, copy and move operations:\n\n";
  sdplib::vector<int> v1{1, 22, 13, 4, 5}, v2{100, 40, 231, 3, 42};
  sdplib::printVector(v1);
  sdplib::printVector(v2);
  sdplib::vector<int> v3 = v1;
  sdplib::printVector(v3);
  v3 = v2;
  sdplib::printVector(v3);
  sdplib::vector<int> v4( 10, 77 );
  sdplib::printVector(v4);
  sdplib::vector<int> v5 = std::move(v3);
  sdplib::printVector(v5);
  std::cout << "\n------------------------------------------------------------\n";
  /// Test push_back and pop_back
  std::cout << "\npush_back and pop_back:\n\n";
  v1.push_back(100);
  sdplib::printVector(v1);
  v1.pop_back();
  sdplib::printVector(v1);
  std::cout << "\n------------------------------------------------------------\n";
  /// Test insert and erase
  std::cout << "\ninsert and erase:\n\n";
  sdplib::vector<int>::iterator iter = v1.insert(v1.begin() + 3, 404);
  sdplib::printVector(v1);
  v1.erase(iter);
  sdplib::printVector(v1);
  std::cout << "\n------------------------------------------------------------\n";
  /// Test reserve and resize
  std::cout << "\nreserve and resize:\n\n";
  v1.reserve(100);
  sdplib::printVector(v1);
  v1.resize(15);
  sdplib::printVector(v1);
  v1.resize(20);
  sdplib::printVector(v1);
  v1.resize(5);
  sdplib::printVector(v1);
  std::cout << "\n------------------------------------------------------------\n";
  /// Test operator[], at, front and back
  std::cout << "\n[], at, front and back:\n\n";
  sdplib::printVector(v1);
  v1[3] = 123;
  sdplib::printVector(v1);
  v1.at(3) = 4444;
  sdplib::printVector(v1);
  try {
	  v1.at(50);
  }
  catch (std::out_of_range exc) {
	  std::cout << exc.what() << std::endl; /// vector<T>::at(): index is out of range
  }
  std::cout << "front: " << v1.front() << std::endl;
  std::cout << "back: " << v1.back() << std::endl;
  sdplib::printVector(v1);
  std::cout << "\n------------------------------------------------------------\n";

  /// Test clear
  std::cout << "\nclear:\n\n";
  v1.clear();
  sdplib::printVector(v1);
  std::cout << "\n------------------------------------------------------------\n";

  /// Test standart library algorithms
  std::cout << "\nstd algorithms:\n\n";
  sdplib::printVector(v2);

  std::cout << "\nstd::reverse: \n";
  std::reverse(v2.begin(), v2.end());
  sdplib::printVector(v2);

  std::cout << "\nstd::sort:\n";
  std::sort(v2.begin(), v2.end());
  sdplib::printVector(v2);

  std::cout << "\nstd::find:\n";
  sdplib::vector<int>::iterator iter2 = std::find(v2.begin(), v2.end(), 42);
  if (iter2 != v2.end()) {
	  std::cout << "Found: " << *iter2 << " in v2\n";
  }
  else {
	  std::cout << "Didn't Found: " << 42 << " in v2\n";
  }
  auto iter3 = std::find(v2.begin(), v2.end(), 120); ///You can also use auto here
  if (iter3 != v2.end()) {
	  std::cout << "Found: " << *iter3 << " in v2\n";
  }
  else {
	  std::cout << "Didn't Found: " << 120 << " in v2\n\n";
  }
  std::cout << "\n------------------------------------------------------------\n\n";
  return 0;
}