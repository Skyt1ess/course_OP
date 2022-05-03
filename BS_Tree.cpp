#include <iostream>

using namespace std;

class BS_Tree {
private:
    struct Node {
        int val;
        Node* left = NULL;
        Node* right = NULL;
    };
    Node* head = NULL;

    void push(int val, Node*& node) {
        if (node == NULL) {
            node = new Node;
            node->val = val;
        } else
        if (val > node->val) {
            push(val, node->right);
        } else {
            push(val, node->left);
        }
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

    Node* find_parent(Node* child, Node* node) {
        if (node->left && node->left == child ||
            node->right && node->right == child) {
                return node;
            }
        if (child->val > node->val) {
            return find_parent(child, node->right);
        } else {
            return find_parent(child, node->left);
        }


    }
public:
    void push(int val) {
        push(val, head);
    }
    bool remove(int val) {

        Node* del = find(val, head);
        if (del == NULL) {
            cout << "No value" << endl;
            return false;
        }

        Node* tmp = new Node();
        if (del != head) {
            tmp = find_parent(del, head);
        } else {
            tmp->left = del;
        }

        if (del->left == NULL && del->right == NULL) {
                if (tmp->left == del) {
                    tmp->left = NULL;
                } else {
                    tmp->right = NULL;
                }
            delete del;
        } else
        if (del->left == NULL) {
                if (tmp->left == del) {
                    tmp->left = del->right;
                } else {
                    tmp->right = del->right;
                }
            delete del;
        } else
        if (del->right == NULL) {
                if (tmp->left == del) {
                    tmp->left = del->left;
                } else {
                    tmp->right = del->left;
                }
            delete del;
        } else {
            tmp = del->right;
            while (tmp->left) {
                tmp = tmp->left;
            }
            int data = tmp->val;
            remove(data);
            del->val = data;
        }




    }
    bool find(int val) {
        Node* res = find(val, head);
        if (res == NULL) {
            return false;
        } else {
            return true;
        }
    }
    void print() {
        print(head, 0);
    }
};

int main() {
    BS_Tree tree;
    tree.push(3);
    tree.push(2);
    tree.push(4);
    tree.push(6);
    tree.print();
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

    tree.remove(3);
    cout << "After removing: " << endl;
    tree.print();
}
