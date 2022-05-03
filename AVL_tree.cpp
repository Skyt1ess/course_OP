#include <iostream>

using namespace std;

class AVL_Tree {
private:
    struct Node {
        int val;
        int height = 0;
        Node* left = NULL;
        Node* right = NULL;
    };
    Node* root = NULL;

    int height(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return node->height;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    int getBalanceFactor(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    Node* push(int val, Node* node) {
        if (node == NULL) {
            node = new Node();
            node->val = val;
            node->height = 1;
            return node;
        } else
        if (val > node->val) {
            node->right = push(val, node->right);
        } else {
            node->left = push(val, node->left);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (val < node->left->val) {
                return rightRotate(node);
            } else
            if (val > node->left->val) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (val > node->right->val) {
                return leftRotate(node);
            } else if (val < node->right->val) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }


    Node* nodeWithMimumValue(Node* node) {
        Node* current = node;
        while (current->left != NULL) {
            current = current->left;
        }

        return current;
    }

    Node* remove(int val, Node* node) {
        if (node == NULL) {
            return node;
        }

        if (val < node->val) {
            node->left = remove(val, node->left);
        }
        else
        if (val > node->val) {
            node->right = remove(val, node->right);
        }
        else {
            if ((node->left == NULL) || (node->right == NULL)) {
                Node *temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else
                *node = *temp;
                delete temp;
            } else {
                Node *temp = nodeWithMimumValue(node->right);
                node->val = temp->val;
                node->right = remove(temp->val, node->right);
            }
        }

        if (node == NULL) {
            return node;
        }


        node->height = 1 + max(height(node->left),
        height(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    void print(Node* node, int cnt) {
        if (node == NULL) {
            return;
        }
        print(node->left, cnt + 1);
        for (int i = 0; i <= cnt; i++) {
            cout << "  ";
        }
        cout << node->val << endl;
        print(node->right, ++cnt);
    }

    Node* find(int val, Node* node) {
        if (node == NULL) {
            return node;
        }

        if (val > node->val) {
            return find(val, node->right);
        }
        if (val < node->val) {
            return find(val, node->left);
        }

        return node;
    }


public:
    void push(int val) {
        root = push(val, root);
    }
    bool remove(int val) {
        root = remove(val, root);
    }
    bool find(int val) {
        Node* res = find(val, root);
        if (res == NULL) {
            return false;
        } else {
            return true;
        }
    }
    void print() {
        print(root, 0);
    }
};

int main() {
    AVL_Tree tree;
    tree.push(3);
    tree.push(2);
    tree.push(4);
    tree.push(6);
    tree.push(5);
    tree.push(1);
    tree.push(2);
    tree.push(8);
    tree.push(0);
    tree.push(0);
    tree.push(9);
    tree.push(9);
    tree.push(10);
    tree.print();

    if (tree.find(5)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    tree.remove(10);
    tree.remove(9);
    tree.remove(9);
    tree.remove(5);
    cout << "After removing: " << endl;
    tree.print();
}
