#include "tree.h"
#include <vector>

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  PMNode* root = tree.getRoot();

  if (!root || root->children.empty() || num <= 0)
    return {};

  std::vector<std::vector<char>> all = tree.getAllPerms();

  if (num > static_cast<int>(all.size()))
    return {};

  return all[num - 1];
}

bool findNthPath(PMNode* node, std::vector<char>& path, int target, int& current) {
  path.push_back(node->value);

  if (node->children.empty()) {
    if (current == target)
      return true;
    else {
      current++;
      path.pop_back();
      return false;
    }
  }

  for (int i = 0; i < node->children.size(); ++i) {
    if (findNthPath(node->children[i], path, target, current))
      return true;
  }

  path.pop_back();
  return false;
}


std::vector<char> getPerm2(const PMTree& tree, int num) {
  std::vector<char> result;
  int counter = 1;

  PMNode* root = tree.getRoot();

  if (!root || root->children.empty())
    return {};

  for (int i = 0; root && i < root->children.size(); ++i) {
    if (findNthPath(root->children[i], result, num, counter)) {
      return result;
    }
  }

  return {};
}
