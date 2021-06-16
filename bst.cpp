#include <iostream>
#include <queue>
using namespace std;

// tree node structure
struct node {
    node(int key);
    int key;
    struct node *left=NULL;
    struct node *right=NULL;
};

// basic bst class, unbalanced
class Bst {
public:
    Bst();
    void insert(int key);
    void del(int key);
    void print();
    struct node* find(int key);
    int max();
    int min();
private: 
    struct node *root=NULL;
    struct node* insert(struct node *root, int key);
    struct node* del(struct node *root, int key);
};

// basic test code
int main() {
    Bst b = Bst();
    b.insert(10);
    b.insert(15);
    b.insert(5);
    b.insert(11);
    b.insert(6);
    b.insert(4);
    b.del(10);
    b.print();
    return 0;
}

// insert function
void Bst::insert(int key) {
    root = insert(root, key);
}

// insert helper
struct node* Bst::insert(struct node *root, int key) {
    if (root==NULL) return new node(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }

    return root;
}

// delete function
void Bst::del(int key) {
    root = del(root, key);
}

// delete helper
struct node* Bst::del(struct node *root, int key) {
	if (root==NULL) return root;
    
    if (key < root->key) {
        root->left = del(root->left, key);
    } else if (key > root->key) {
        root->right = del(root->right, key);
    } else {
        // found node to delete
        // CASE 1, node is leaf, delete
        if (root->left==NULL && root->right==NULL) return NULL;

        // CASE 2, node has one child, swap with child
        if (root->left==NULL) {
            struct node *newRoot = root->right;
            root = NULL;
            return newRoot;
        } else if (root->right==NULL) {
            struct node *newRoot = root->left;
            root = NULL;
            return newRoot;
        }

        // CASE 3, swap with inorder successor and call del again
        struct node *succ  = root->right;
        while (succ->left!=NULL) succ = succ->left;
        
        root->key = succ->key;
        root->right = del(root->right, succ->key);
    }

    return root;
}

// find
struct node* Bst::find(int key) {    
    struct node *curr = root;

    while (curr!=NULL) {
        if (curr->key == key) return curr;

        curr = (key < curr->key) ? curr->left : curr->right;
    }

    return NULL;
} 

// max
int Bst::max() {
    struct node *curr = root;
    while (curr->right!=NULL) curr = curr->right;
    return curr->key; 
}

// min
int Bst::min() {
    struct node *curr = root;
    while (curr->left!=NULL) curr = curr->left;
    return curr->key; 
}

// bfs print
void Bst::print() {
    queue<struct node*> nodes;
    nodes.push(root);

    while (nodes.size()>0) {
        struct node *curr = nodes.front();
        nodes.pop();
        cout << curr->key;
        
        if (curr->left!=NULL) nodes.push(curr->left);
        if (curr->right!=NULL) nodes.push(curr->right);
    }
}

// constructor sets key
node::node(int key) {
    this->key = key;
}

// no arg constructor
Bst::Bst() {}