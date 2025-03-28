#include<iostream>

using namespace std;

const int N = 1000;

struct treeNode { 
    int data;
    treeNode* firstChild;
    treeNode* nextSibling;
    treeNode(int val):data(val), firstChild(nullptr), nextSibling(nullptr) {}
};

class Tree {
    public:
    treeNode* root;
    treeNode* nodeList[N];
    bool isChild[N];

    Tree():root(nullptr) { 
        for(int i = 0; i < N; i++) {
            nodeList[i] = nullptr;
            isChild[i] = false;
        }
    }

    void updateRoot() {
        for(int i = 0; i < N; i++) {
            if(nodeList[i] != nullptr && !isChild[i]) { 
                root = nodeList[i];
                return;
            }
        }
    }

    void addChild(int parent, int child) {
        if(!nodeList[parent]) nodeList[parent] = new treeNode(parent);
        if(!nodeList[child]) nodeList[child] = new treeNode(child);
        treeNode* parentNode = nodeList[parent];
        treeNode* childNode = nodeList[child];

        if(parentNode->firstChild == nullptr) { 
            parentNode->firstChild = childNode;
        }
        else { 
            treeNode* tmp = parentNode->firstChild;
            while(tmp->nextSibling != nullptr) {
                tmp = tmp->nextSibling;
            }
            tmp->nextSibling = childNode;
        }
        isChild[child] = true;
    }

    int getHeight(treeNode* node) { 
        if(node == nullptr) { 
            return 0;
        }
        int maxChildHeight = 0;
        treeNode* child = node->firstChild;
        while(child != nullptr) {
            maxChildHeight = max(maxChildHeight, getHeight(child));
            child = child->nextSibling;
        }
        return maxChildHeight + 1;
    }

    void preorder(treeNode* node) {
        if(node == nullptr) {
            return;
        }
        cout << node->data << " ";
        treeNode* child = node->firstChild;
        while(child != nullptr) {
            preorder(child);
            child = child->nextSibling;
        }
    }

    void postorder(treeNode* node) {
        if (node == nullptr) {
            return;
        }
        treeNode* child = node->firstChild;
        while (child != nullptr) {
            postorder(child);
            child = child->nextSibling;
        }
        cout << node->data << " ";
    }

    bool isBinaryTree(treeNode* node) {
        if(node == nullptr) {
            return true;
        }
        int childCount = 0;
        treeNode* child = node->firstChild;
        while(child != nullptr){
            childCount++;
            if(childCount > 2) {
                return false;
            }
            child = child->nextSibling;
        }
        child = node->firstChild;
        while(child != nullptr) {
            if(!isBinaryTree(child)) {
                return false;
            }
            child = child->nextSibling;
        }
        return true;
    }

    void inorder(treeNode* node) {
        if (node == nullptr) {
            return;
        }
        treeNode* leftChild = node->firstChild;
        treeNode* rightChild = (leftChild) ? leftChild->nextSibling : nullptr;
        inorder(leftChild);
        cout << node->data << " ";
        inorder(rightChild);
    }

    void process() {
        if (root == nullptr) {
            return;
        }
        cout << getHeight(root) - 1 << endl;
        preorder(root);
        cout << endl;
        postorder(root);
        cout << endl;
        if (isBinaryTree(root)) {
            inorder(root);
            cout << endl;
        } else {
            cout << "NOT BINARY TREE" << endl;
        }
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    Tree tree;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        tree.addChild(u, v);
    }
    tree.updateRoot(); 
    tree.process();
    return 0;
}
