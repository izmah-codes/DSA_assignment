#include <iostream>
using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;
    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;
    int countnodes(Node* temp) {
        if (temp == nullptr) {
            return 0;
        }
        return 1 + countnodes(temp->left) + countnodes(temp->right);
    }

    void clearTreehelper(Node* temp) {
        if (temp == nullptr) {
            return;
        }
        clearTreehelper(temp->left);
        clearTreehelper(temp->right);
        delete temp;
    }

    Node* findNode(Node* temp, char value) {
        if (temp == nullptr) {
            return nullptr;
        }
        if (temp->data == value) {
            return temp;
        }
        Node* found = findNode(temp->left, value);
        if (found != nullptr) {
            return found;
        }
        return findNode(temp->right, value);
    }

    void preorderhelper(Node* temp) {
        if (temp == nullptr) return;
        cout << temp->data << " ";      
        preorderhelper(temp->left);
        preorderhelper(temp->right);
    }

    void inorderhelper(Node* temp) {
        if (temp == nullptr) return;
        inorderhelper(temp->left);
        cout << temp->data << " ";      
        inorderhelper(temp->right);
    }

    void postorderhelper(Node* temp) {
        if (temp == nullptr) return;
        postorderhelper(temp->left);
        postorderhelper(temp->right);
        cout << temp->data << " ";     
    }

    void doubleOrderhelper(Node* temp) {

    if (temp == nullptr) {
        return;
    }
    // 1. Visit current node
    cout << temp->data << " ";

    // 2. Traverse left subtree
    doubleOrderhelper(temp->left);

    // 3. Visit current node again
    cout << temp->data << " ";

    // 4. Traverse right subtree
    doubleOrderhelper(temp->right);
}

public:
    BinaryTree() {
        root = nullptr;
    }

    void createRoot(char value) {
        if (root != nullptr) {
            cout << "Root already exists!" << endl;
            return;
        }
        root = new Node(value);
    }

    void addNode(char parentValue, char value, char side) {
        Node* parent = findNode(root, parentValue);

        if (parent == nullptr) {
            cout << "Parent " << parentValue << " not found!" << endl;
            return;
        }

        if (side == 'L') {
            if (parent->left != nullptr) {
                cout << "Left child of " << parentValue << " is already taken!" << endl;
                return;
            }
            parent->left = new Node(value);
        }
        else if (side == 'R') {
            if (parent->right != nullptr) {
                cout << "Right child of " << parentValue << " is already taken!" << endl;
                return;
            }
            parent->right = new Node(value);
        }
        else {
            cout << "Side must be 'L' or 'R'" << endl;
        }
    }

    void preorder()  { preorderhelper(root);  cout << endl; }
    void inorder()   { inorderhelper(root);   cout << endl; }
    void postorder() { postorderhelper(root); cout << endl; }
    void doubleorder(){doubleOrderhelper(root); cout<<endl;}

    int treeSize() {
        return countnodes(root);
    }

    void clearTree() {
        clearTreehelper(root);
        root = nullptr;
    }


    


};

int main() {
    BinaryTree tree;

    tree.createRoot('A');
    tree.addNode('A', 'B', 'L');
    tree.addNode('A', 'C', 'R');
    tree.addNode('B', 'D', 'L');
    tree.addNode('B', 'E', 'R');
    tree.addNode('C', 'F', 'L');
    tree.addNode('C', 'G', 'R');

    cout << "Total nodes: " << tree.treeSize() << endl;

    cout << "Preorder  : ";
    tree.preorder();

    cout << "Inorder   : ";
    tree.inorder();

    cout << "Postorder : ";
    tree.postorder();

    cout << "Doubleorder : ";
    tree.doubleorder();

    tree.clearTree();
    cout << "Nodes after clearing: " << tree.treeSize() << endl;

    return 0;
}