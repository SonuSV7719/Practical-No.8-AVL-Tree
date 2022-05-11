#include<bits/stdc++.h>
using namespace std;

class Node
{
    public:
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int data);
};

Node::Node(int data)
{
    this->data = data;
    this->left = NULL;
    this->right = NULL;
    this->height = 1;
}

class AvlTree
{
    public:
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    int balanceFactor(Node* root);
    int maximum(int a, int b);
    Node* insert(Node* root, int key); 
    int height(Node* node); 
    void preOrder(Node* root);
    Node* search(Node* root, int key);
    Node* delete_ele(Node* root, int key);
    Node* minValueNode(Node* root);
    void inOrder(Node* root);
    void postOrder(Node* root);
};

int AvlTree::maximum(int a, int b)
{
    return (a>b)? a : b;
}

int AvlTree::height(Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int AvlTree::balanceFactor(Node* root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Node* AvlTree::rotateRight(Node* y)
{
    // retrieval
    Node* x = y->left;
    Node* t2 = x->right;
    // reconstruct
    x->right = y;
    y->left = t2;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}

Node* AvlTree::rotateLeft(Node* x)
{
    // retrieval
    Node* y = x->right;
    Node* t2 = y->left;
    // reconstruct
    y->left = x;
    x->right = t2;
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

Node* AvlTree::insert(Node* node, int key)
{
    //check wether the root is initially null or not if null then we will create new node
    if (node == NULL)
        return (new Node(key));
    // check key on left side as node's data is smaller than current data 
    if (key < node->data)
        node->left = insert(node->left, key);
    // check key on right side as node's data is greater than current data 
    else if (key > node->data)
        node->right = insert(node->right, key);
    else 
        return node;
 
    // update height before finding balance factor 
    node->height = 1 + max(height(node->left),
                        height(node->right));
 

    int bf = balanceFactor(node);
 
    // Left Left Case
    if (bf > 1 && key < node->left->data)
        return rotateRight(node);
 
    // Right Right Case
    if (bf < -1 && key > node->right->data)
        return rotateLeft(node);
 
    // Left Right Case
    if (bf > 1 && key > node->left->data)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
 
    // Right Left Case
    if (bf < -1 && key < node->right->data)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* AvlTree::search(Node* root, int key)
{
    if (root ==  NULL || root->data == key) return  root;
    if (key < root->data) 
        return search(root->left, key);
    return search(root->right, key); 
}

void AvlTree::preOrder(Node* root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);

}

void AvlTree::postOrder(Node* root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->data<<" ";

}

void AvlTree::inOrder(Node* root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    cout<<root->data<<" ";
    postOrder(root->right);
    

}

Node* AvlTree::minValueNode(Node* root)
{
    Node* current_node = root;
    if (current_node && current_node->left != NULL)
        current_node = current_node->left;
    return current_node;
}

Node* AvlTree::delete_ele(Node* root, int key)
{
    if (root == NULL) return root;

    //Search key on left side of tree
    if (key < root->data)
        root->left = delete_ele(root->left, key);
    //Search key on right side of tree
    else if (key > root->data)
        root->right = delete_ele(root->right, key);
    
    //if key found after traveresing then delete that node
    else
    {
        //Node with NO child
        if (root->left == NULL && root->right == NULL) return NULL;

        //Node with No child or only one child
        else if (root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        //Node with NO children 
        //first find inorder successor 
        Node* temp = minValueNode(root->right);

        //store value of temp data to root data or copy
        root->data = temp->data;

        //delete inorder successor
        root->right = delete_ele(root->right, temp->data);

        // again check tree is balanced or not
        root->height = 1 + max(height(root->left),
                        height(root->right));
 

    int bf = balanceFactor(root);
 
    // Left Left Case
    if (bf > 1 && key < root->left->data)
        return rotateRight(root);
 
    // Right Right Case
    if (bf < -1 && key > root->right->data)
        return rotateLeft(root);
 
    // Left Right Case
    if (bf > 1 && key > root->left->data)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
 
    // Right Left Case
    if (bf < -1 && key < root->right->data)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    }
    return root;
}

int main()
{
    int n;
    Node* root = NULL;
    AvlTree tree;
    Node* result;

    string yesNo = "y";
    do
    {
        int choice;
        cout<<"**********************Menu**********************"<<endl;
        cout<<"1.Insert\n2.Print inorder\n3.search\n4.Delete Node\n5.Exit"<<endl;
        cout<<"Choice index of given menu to perform that operation: "<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout << "Enter How many elements you want to enter: ";
            cin >> n;
            for (int i = 0; i<n; i++)
            {
                int ele;
                cout << "Enter Element: ";
                cin >> ele;
                root = tree.insert(root, ele);    
            }

            break;
        case 2:
            cout<<"Preorder: ";
            tree.preOrder(root);
            cout<<endl;
            cout<<"Inorder: ";
            tree.inOrder(root);
            cout<<endl;
            cout<<"Postorder: ";
            tree.postOrder(root);
            cout<<endl;
            cout<<endl;
            break;
        case 3:
            int key;
            cout<<"Enter what you want to search: ";
            cin>>key;
            result = tree.search(root, key);
            if (result == NULL)
                cout<<key<< " Not Found!"<<endl<<endl;
            else
                cout<<key<<" Found in AVL TREE"<<endl<<endl;
            break;
        case 4:
            int del;
            cout<<"Enter what you want to delete: ";
            cin>>del;
            root = tree.delete_ele(root, del);
            break;
        case 5:
            yesNo = "n";
            break;
        
        default:
            cout<<"You have entered wrong value option!!"<<endl;
        }

    } while (yesNo != "n");
    


    return 0;
}