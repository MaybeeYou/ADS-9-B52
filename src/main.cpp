// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include "tree.h"

void printVector(const std::vector<char>& vec) {
  for (char c : vec) {
    std::cout << c;
  }
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

  std::cout << "\nGet specific permutations:\n";

  std::cout << "getPerm1 (full traversal):\n";
  for (int i = 1; i <= 6; ++i) {
    auto p = getPerm1(tree, i);
    std::cout << " #" << i << ": ";
    printVector(p);
  }

  std::cout << "\ngetPerm2 (tree nav):\n";
  for (int i = 1; i <= 6; ++i) {
    auto p = getPerm2(tree, i);
    std::cout << " #" << i << ": ";
    printVector(p);
  }
}

void runExperiment() {
  std::vector<char> items = { '1', '2', '3', '4', '5' };
  PMTree tree(items);

  std::cout << "\nPerformance measurements:\n";

  auto start = std::chrono::high_resolution_clock::now();
  auto perms = tree.getAllPerms();
  auto end = std::chrono::high_resolution_clock::now();
  auto dur_all = std::chrono::duration_cast<std::chrono::microseconds>(
    end - start).count();
  std::cout << "getAllPerms(): " << dur_all << " µs\n";

  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= 6; ++i) {
    getPerm1(tree, i);
  }
  end = std::chrono::high_resolution_clock::now();
  auto dur_p1 = std::chrono::duration_cast<std::chrono::microseconds>(
    end - start).count();
  std::cout << "getPerm1():     " << dur_p1 << " µs\n";

  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= 6; ++i) {
    getPerm2(tree, i);
  }
  end = std::chrono::high_resolution_clock::now();
  auto dur_p2 = std::chrono::duration_cast<std::chrono::microseconds>(
    end - start).count();
  std::cout << "getPerm2():     " << dur_p2 << " µs\n";
}

int main() {
  runExample();
  runExperiment();
  return 0;
}
