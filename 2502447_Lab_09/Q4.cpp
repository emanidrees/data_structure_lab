#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int medicineID;
    int expiryDate;

    Node* left;
    Node* right;

    Node(string n, int id, int date)
    {
        name = n;
        medicineID = id;
        expiryDate = date;

        left = NULL;
        right = NULL;
    }
};

class MinHeap
{
public:
    Node* root;

    MinHeap()
    {
        root = NULL;
    }

    void swapMedicine(Node* a, Node* b)
    {
        swap(a->name, b->name);
        swap(a->medicineID, b->medicineID);
        swap(a->expiryDate, b->expiryDate);
    }

    
    void insert(string name, int id, int date)
    {
        Node* newNode = new Node(name, id, date);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left == NULL)
            {
                temp->left = newNode;
                break;
            }
            else
                q.push(temp->left);

            if (temp->right == NULL)
            {
                temp->right = newNode;
                break;
            }
            else
                q.push(temp->right);
        }

        heapifyUp(newNode);
    }

    
    void heapifyUp(Node* newNode)
    {
        Node* parent = NULL;

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left == newNode || temp->right == newNode)
            {
                parent = temp;
                break;
            }

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }

        if (parent != NULL &&
            newNode->expiryDate < parent->expiryDate)
        {
            swapMedicine(newNode, parent);
            heapifyUp(parent);
        }
    }

   
    void display()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!";
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            cout << temp->name << " ("
                 << temp->medicineID << ", "
                 << temp->expiryDate << ")  ";

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }
    }

   
    void nearestExpiry()
    {
        if (root != NULL)
        {
            cout << "\nMedicine with nearest expiry: ";
            cout << root->name;
            cout << " | ID: " << root->medicineID;
            cout << " | Expiry: " << root->expiryDate;
        }
    }

    
    void deleteRoot()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!";
            return;
        }

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }

        queue<Node*> q;
        q.push(root);

        Node* last = root;
        Node* lastParent = NULL;

       
        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left != NULL)
            {
                lastParent = temp;
                last = temp->left;
                q.push(temp->left);
            }

            if (temp->right != NULL)
            {
                lastParent = temp;
                last = temp->right;
                q.push(temp->right);
            }
        }

       
        root->name = last->name;
        root->medicineID = last->medicineID;
        root->expiryDate = last->expiryDate;

        if (lastParent->right == last)
            lastParent->right = NULL;
        else
            lastParent->left = NULL;

        delete last;

        heapifyDown(root);
    }

 
    void heapifyDown(Node* temp)
    {
        Node* smallest = temp;

        if (temp->left != NULL &&
            temp->left->expiryDate < smallest->expiryDate)
        {
            smallest = temp->left;
        }

        if (temp->right != NULL &&
            temp->right->expiryDate < smallest->expiryDate)
        {
            smallest = temp->right;
        }

        if (smallest != temp)
        {
            swapMedicine(temp, smallest);
            heapifyDown(smallest);
        }
    }
};

int main()
{
    MinHeap h;

    
    h.insert("Panadol", 101, 20271215);
    h.insert("Brufen", 102, 20261130);
    h.insert("Augmentin", 103, 20280310);
    h.insert("Calpol", 104, 20261005);
    h.insert("Disprin", 105, 20270920);
    h.insert("Rigix", 106, 20261225);

    cout << "Hospital Medicine Heap:\n";
    h.display();

    
    h.nearestExpiry();

    
    cout << "\n\nDeleting medicine with nearest expiry...";

    h.deleteRoot();

    cout << "\n\nUpdated Medicine Heap:\n";
    h.display();

   
    h.nearestExpiry();

    return 0;
}

