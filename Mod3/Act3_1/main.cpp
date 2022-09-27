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

// void DFS2(Node root, int spaces) {
//     if (root.children.size() == 0) {
//         for (int i = 0; i < spaces; i++)
//             std::cout << " ";
//         return;
//     }

//     for(int x = 0; x < auxV.size(); ++x){
//         cout << auxV[x];
//         DFS(root.children[auxV[x]], spaces + 1);
//     }

//     std::cout << endl;
// }

void DFS(Node root, int tabs) {
    int nChildren = root.children.size();
    if(!nChildren) return;
    vector<char> children;

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

    DFS(root, 0);

    return 0;
}