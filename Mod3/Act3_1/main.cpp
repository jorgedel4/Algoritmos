#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    std::unordered_map<char, Node> children;
};

void insert(Node *root, std::string word) {
    Node *current = root;

    for (char letter : word)
        current = &(current->children[letter]);
}

bool exists(Node* root, std::string word) {
    Node* current = root;
    
    for (char letter : word) {
        if (!(current -> children.count(letter))) return false;
        current = &(current -> children[letter]);
    }

    return true;
}

void DFS(Node root, int spaces) {
    if (root.children.size() == 0) {
        for (int i = 0; i < spaces; i++)
            std::cout << " ";
        return;
    }

    //for (it = root.children.cend(); it != root.children.cbegin(); it++)
    for (auto child : root.children)
    {
        std::cout << child.first;
        DFS(root.children[child.first], spaces + 1);
    }

    std::cout << endl;
}

int main() {
    int n, m;
    std::cin >> n;

    std::vector<std::string> words(n);

    // for (int i = n - 1; i >= 0; --i)
    //     std::cin >> words[i];

    for (int i = 0; i < n; ++i)
        std::cin >> words[i];

    // for (int i = n - 1; i >= 0; --i)
    //     std::cin >> words[i];

    // std::cin >> m;

    // std::vector<std::string> queries(m);

    // for(int i = 0; i < m; ++i)
    //     std::cin >> queries[i];

    Node root;

    for (std::string word : words)
        insert(&root, word);

    Node current = root;
    //DFS(current, 0);

    for (auto child : root.children) {
        cout << child.first << endl;
        for(auto child2 : root.children[child.first].children){
            cout << "\t" << child2.first << endl;
            for(auto child3 : root.children[child.first].children[child2.first].children) {
                cout << "\t\t" << child3.first << endl;
            }
        }
    }

    return 0;
}