#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>

void printVector(const std::vector<char>& vec) {
  for (char c : vec)
    std::cout << c;
  std::cout << std::endl;
}

void runExample() {
  std::vector<char> items = { '1', '2', '3' };
  PMTree tree(items);

  std::cout << "All permutations:" << std::endl;
  auto all_perms = tree.getAllPerms();
  for (const auto& perm : all_perms) {
    printVector(perm);
  }

  std::cout << "\nGetting specific permutations:\n";
  std::cout << "Method getPerm1 (full traversal):\n";
  for (int i = 1; i <= 6; ++i) {
    auto perm = getPerm1(tree, i);
    std::cout << "Permutation #" << i << ": ";
    printVector(perm);
  }

  std::cout << "\nMethod getPerm2 (tree navigation):\n";
  for (int i = 1; i <= 6; ++i) {
    auto perm = getPerm2(tree, i);
    std::cout << "Permutation #" << i << ": ";
    printVector(perm);
  }
}

void runExperiment() {
  std::vector<char> items = { '1', '2', '3', '4', '5' };
  PMTree tree(items);

  std::cout << "\nPerformance measurements:\n";

  auto start = std::chrono::high_resolution_clock::now();
  auto perms = tree.getAllPerms();  
  auto end = std::chrono::high_resolution_clock::now();
  auto duration_all = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time for getAllPerms(): " << duration_all.count() << " µs\n";


  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= 6; ++i) {
    getPerm1(tree, i);  
  }
  end = std::chrono::high_resolution_clock::now();
  auto duration_p1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time for getPerm1():     " << duration_p1.count() << " µs\n";

  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= 6; ++i) {
    getPerm2(tree, i);
  }
  end = std::chrono::high_resolution_clock::now();
  auto duration_p2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time for getPerm2():     " << duration_p2.count() << " µs\n";
}

int main() {
  runExample();     
  runExperiment();   

  return 0;
}
