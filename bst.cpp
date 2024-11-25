#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;
    node(int val){
    data=val;
    left=nullptr;
    right=nullptr;
}
};

node* root = nullptr;
//insertion
node* insertNode(int data) {
    node* newNode = new node(data);
    if (!root) {
        root = newNode;
        return root;
    }

    node* current = root;
    while (true) {
        if (data < current->data) {
            if (!current->left) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else if (data > current->data) {
            if (!current->right) {
                current->right = newNode;
                break;
            }
            current = current->right;
        } else {
            cout << "Value already exists in the tree.\n";
            break; // Avoid duplicates
        }
    }
    return root;
}

void inorder(node* root) {
    if (!root) return;
    stack<node*> s;
    node* current = root;

    while (!s.empty() || current != nullptr) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preorder(node* root) {
    if (!root) return;
    stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node* current = s.top();
        s.pop();
        cout << current->data << " ";

        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

void postorder(node* root) {
    if (!root) return;
    stack<node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

node* searchNode(int value) {
    node* current = root;
    while (current) {
        if (value == current->data) return current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

void deleteNode(int value) {
    if (!root) return;

    node* nodeToDelete = nullptr;
    node* parent = nullptr;
    node* current = root;

    while (current) {
        if (current->data == value) {
            nodeToDelete = current;
            break;
        }
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (!nodeToDelete) {
        cout << "Value not found in the tree.\n";
        return;
    }

    // Case 1: leaf node
    if (!nodeToDelete->left && !nodeToDelete->right) {
        if (!parent) {
            root = nullptr;
        } else if (parent->left == nodeToDelete) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete nodeToDelete;
    }

    // Case 2: one child
    else if (nodeToDelete->left && !nodeToDelete->right) {
        if (!parent) {
            root = nodeToDelete->left; 
        } else if (parent->left == nodeToDelete) {
            parent->left = nodeToDelete->left;
        } else {
            parent->right = nodeToDelete->left;
        }
        delete nodeToDelete;
    } else if (!nodeToDelete->left && nodeToDelete->right) {
        if (!parent) {
            root = nodeToDelete->right; 
        } else if (parent->left == nodeToDelete) {
            parent->left = nodeToDelete->right;
        } else {
            parent->right = nodeToDelete->right;
        }
        delete nodeToDelete;
    }

    // Case 3: two children
    else {
        node* nextNode = nodeToDelete->right;   
        node* parentOfNext = nullptr;

        while (nextNode->left) {
            parentOfNext = nextNode;
            nextNode = nextNode->left;
        }

        nodeToDelete->data = nextNode->data;
        if (!parentOfNext) {
            nodeToDelete->right = nextNode->right;
        } else {
            parentOfNext->left = nextNode->right;
        }
        delete nextNode;
    }
}

int main() {
    int choice, value;

    do {
        cout << "Binary Search Tree Operations"<<endl;
        cout << "1. Insert"<<endl;
        cout << "2. In-order Traversal"<<endl;
        cout << "3. Pre-order Traversal"<<endl;
        cout << "4. Post-order Traversal"<<endl;
        cout << "5. Search"<<endl;
        cout << "6. Delete"<<endl;
        cout << "7. Exit"<<endl;
        cout << "Enter your choice: "<<endl;
        cin >> choice;

        switch (choice) {
            case 1://for input
                cout << "Enter value to insert: ";
                cin >> value;
                insertNode(value);
                break;
            case 2://inorder
                cout << "In-order Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3://preorder
                cout << "Pre-order Traversal: ";
                preorder(root);
                cout << endl;
                break;
            case 4://postorder
                cout << "Post-order Traversal: ";
                postorder(root);
                cout << endl;
                break;
            case 5://for search
                cout << "Enter value to search: ";
                cin >> value;
                if (searchNode(value))
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value not found in the tree.\n";
                break;
            case 6://to delete
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(value);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
