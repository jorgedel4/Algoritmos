#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
#define um std::unordered_map

struct Node {
  um<char, Node> children;
};

void insert(Node *root, std::string word) {
  Node *current = root;

  for (char letter : word)
    current = &(current->children[letter]);
}

// bool exists(Node root, std::string word) { 
//   Node current = root;

//   for (char letter : word) {
//     if (current.children)
//     current = current.children[letter];
//   }
// }

void DFS(Node root) {
    if (root.children.size() == 0) return;
    for (auto child : root.children) {
        std::cout << child.first << " ";
        DFS(root.children[child.first]);
    }
    std::cout << endl;
} 

int main() {
  int n;
  std::cin >> n;

  std::vector<std::string> words(n);

  for (int i = 0; i < n; ++i)
    std::cin >> words[i];

  // int m;
  // std::cin >> m;

  // std::vector<std::string> queries(m);

  // for(int i = 0; i < m; ++i)
  //     std::cin >> queries[i];

  Node root;

  for (std::string word : words) {
    insert(&root, word);
  }

  // for (auto child : root.children) {
  //   std::cout << child.first << std::endl;

  //   for (auto child2 : root.children[child.first].children) {
  //     std::cout << "\t" << child2.first << std::endl;

  //     for (auto child3 :
  //          root.children[child.first].children[child2.first].children) {
  //       std::cout << "\t\t" << child3.first << std::endl;
  //     }
  //   }
  // }
  Node current = root;
  DFS(current);
  return 0;
}