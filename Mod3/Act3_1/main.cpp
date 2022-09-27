#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    std::unordered_map<char, Node> children;
};

// Time Complexity - O(n), donde n es el numero de palabras
void insert(Node *root, std::string word) {
    Node *current = root;

    for (char letter : word)
        current = &(current->children[letter]);
}

// Time Complexity - O(n), donde n es el numero de palabras
bool exists(Node* root, std::string word) {
    Node* current = root;
    
    for (char letter : word) {
        if (!(current -> children.count(letter))) return false;
        current = &(current -> children[letter]);
    }

    return true;
}

// Time Complexity - O(l), donde l es el total de letras del trie. Ya que se tiene que pasar por todas estas
void DFS(Node root, int tabs) {
    int nChildren = root.children.size();
    if(!nChildren) return;

    for(auto child : root.children) {
        for(int _ = 0; _ < tabs; ++_) cout << " ";
        cout << child.first << endl;
        DFS(root.children[child.first], tabs + 1);
    }
}

int main() {
    int n, m;
    std::cin >> n;

    std::vector<std::string> words(n);

    for (int i = 0; i < n; ++i)
        std::cin >> words[i];

    std::cin >> m;

    std::vector<std::string> queries(m);

    for(int i = 0; i < m; ++i)
        std::cin >> queries[i];

    Node root;

    for (std::string word : words)
        insert(&root, word);

    DFS(root, 0);

    for(string query : queries) {
        cout << exists(&root, query) << endl;
    }

    return 0;
}