// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <algorithm>
#include <iostream>
#include <vector>

struct PMNode {
  char value;
  std::vector<PMNode*> children;

  explicit PMNode(char val) : value(val) {}
};

class PMTree {
 private:
  PMNode* root;

  std::vector<char> remove(const std::vector<char>* list, char item) {
    std::vector<char> res;
    int n = list->size();
    for (int i = 0; i < n; ++i) {
      if ((*list)[i] != item)
        res.push_back((*list)[i]);
    }
    return res;
  }

  void build(PMNode* node, std::vector<char> remaining) {
    int n = remaining.size();
    for (int i = 0; i < n; ++i) {
      char c = remaining[i];
      PMNode* child = new PMNode(c);
      node->children.push_back(child);
      build(child, remove(&remaining, c));
    }
  }

  void clear(PMNode* node) {
    if (!node) return;
    int n = node->children.size();
    for (int i = 0; i < n; ++i) {
      clear(node->children[i]);
      delete node->children[i];
    }
  }

  void collect(PMNode* node, std::vector<char>& path,
    std::vector<std::vector<char>>& result) const {
    path.push_back(node->value);

    if (node->children.empty()) {
      result.push_back(path);
    } else {
      int n = node->children.size();
      for (int i = 0; i < n; ++i) {
        collect(node->children[i], path, result);
      }
    }

    path.pop_back();
  }

 public:
   explicit PMTree(const std::vector<char>& chars) : root(new PMNode('*')) {
     if (chars.empty()) return;

     std::vector<char> sorted = chars;
     std::sort(sorted.begin(), sorted.end());

     int n = sorted.size();
     for (int i = 0; i < n; ++i) {
       PMNode* child = new PMNode(sorted[i]);
       root->children.push_back(child);
       build(child, remove(&sorted, sorted[i]));
     }
   }

   ~PMTree() {
     clear(root);
     delete root;
   }

  std::vector<std::vector<char>> getAllPerms() const {
     std::vector<std::vector<char>> result;
     std::vector<char> path;

     int n = root->children.size();
     for (int i = 0; i < n; ++i) {
       collect(root->children[i], path, result);
     }

     return result;
  }

PMNode* getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const  PMTree& tree, int num);
bool findNthPath(PMNode* node, std::vector<char>& path,
  int target, int& current);



#endif  // INCLUDE_TREE_H_
