#include<bits/stdc++.h>
using namespace std;


//BST Tree
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
class BST {
    
    struct node {
        string data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(string x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x.compare(t->data) < 0)
            t->left = insert(x, t->left);
        else
            t->right = insert(x, t->right);
        return t;
    }

    node* successor(node* t, node* n)
    {
        if(n->right != NULL)
            return findMin(n->right);
        node* p = NULL;
        while(t != NULL)
        {
            if(n->data.compare(t->data) < 0)
            {
                p = t;
                t = t->left;
            }
            else if(n->data.compare(t->data) > 0)
                t = t->right;
            else
                break;
        }

        return p;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(string x, node* t) {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x.compare(t->data) < 0)
            t->left = remove(x, t->left);
        else if(x.compare(t->data) > 0)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    node* find(node* t, string x) {
        if(t == NULL)
            return NULL;
        else if(x.compare(t->data) < 0)
            return find(t->left, x);
        else if(x.compare(t->data) > 0)
            return find(t->right, x);
        else
            return t;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(string x) {
        root = insert(x, root);
    }

    void remove(string x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << "\n";
    }

    void min() {
        auto a = findMin(root);
        if(a != NULL)
        {
            cout<<"Min: "<<a->data;
        }
        cout<<"\n";
    }

    void max() {

        node* a = findMax(root);
        if(a != NULL)
        {
            cout<<"Max: "<<a->data;
        }
        cout<<"\n";
        
    }

    void search(string x) {
        node* a = find(root, x);
        if(a != NULL)
            cout<<1<<"\n";
        else
            cout<<0<<"\n";
    }

    void successor(string x) {
        node* a = successor(root, find(root, x));
        if(root != NULL)
        {
            cout<<root->data;
        }
        cout<<"\n";
    }
};

//RB Tree           
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class RB_TREE {

    struct node {
    string data{};
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    string color;
    };

    node* root;

    public:
        RB_TREE() : root(nullptr) {}

        node* GetRoot(){ return root; }

         void InsertNode(string stuff) {
           if(root == nullptr){
               root = new node();
               root->data = stuff;
               root->parent = nullptr;
               root->color = "BLACK";
           }
           else {
               auto linker = GetRoot();
               node* newnode = new node();
               newnode->data = stuff;

               while(linker != nullptr){
                   if(linker->data.compare(stuff) > 0){
                       if(linker->left == nullptr){
                           linker->left = newnode;
                           newnode->color = "RED";
                           newnode->parent = linker;
                           cout << "Element inserted.\n"; break; }
                       else { linker = linker->left; }
                   } else {
                       if(linker->right == nullptr){
                           linker->right = newnode;
                           newnode->color = "RED";
                           newnode->parent = linker;
                           cout << "Element inserted.\n"; break; }
                       else {  linker = linker->right; }
                   }
               }
            RB_Insert_Fixup(newnode);
           }
        }

        void RB_Insert_Fixup(node* z) {
            while(z->parent->color == "RED") {
                auto grandparent = z->parent->parent;
                auto uncle = GetRoot();
                if(z->parent == grandparent->left) {
                    if(grandparent->right) { uncle = grandparent->right; }
                    if(uncle->color == "RED"){
                        z->parent->color = "BLACK";
                        uncle->color = "BLACK";
                        grandparent->color = "RED";
                        if(grandparent->data != root->data){ z = grandparent; }
                        else { break; }
                    }
                    else if(z == grandparent->left->right) {
                       LeftRotate(z->parent);
                    }
                    else {
                        z->parent->color = "BLACK";
                        grandparent->color = "RED";
                        RightRotate(grandparent);
                        if(grandparent->data != root->data){ z = grandparent; }
                        else { break; }
                    }
                }
                else {
                    if(grandparent->left) { uncle = grandparent->left; }
                    if(uncle->color == "RED"){
                        z->parent->color = "BLACK";
                        uncle->color = "BLACK";
                        grandparent->color = "RED";
                        if(grandparent->data != root->data){ z = grandparent; }
                        else { break; }
                    }
                    else if(z == grandparent->right->left){
                        RightRotate(z->parent);
                    }
                    else {
                        z->parent->color = "BLACK";
                        grandparent->color = "RED";
                        LeftRotate(grandparent);
                        if(grandparent->data != root->data){ z = grandparent; }
                        else { break; }
                    }
                }
            }
            root->color = "BLACK";
        }


        void RemoveNode(node* parent, node* curr, string stuff) {
            if(curr == nullptr) { return; }
            if(curr->data.compare(stuff) == 0) {
                //CASE -- 1
                if(curr->left == nullptr && curr->right == nullptr) {
                    if(parent->data.compare(curr->data) == 0){ root = nullptr; }
                    else if(parent->right == curr) {
                        RB_Delete_Fixup(curr);
                        parent->right = nullptr;
                    } 
                    else { 
                        RB_Delete_Fixup(curr);
                        parent->left = nullptr;
                    }
                }
                //CASE -- 2
                else if(curr->left != nullptr && curr->right == nullptr) {
                    string swap = curr->data;
                    curr->data = curr->left->data;
                    curr->left->data = swap;
                    RemoveNode(curr, curr->right, stuff);
                }
                else if(curr->left == nullptr && curr->right != nullptr) {
                    string swap = curr->data;
                    curr->data = curr->right->data;
                    curr->right->data = swap;
                    RemoveNode(curr, curr->right, stuff);
                }
                //CASE -- 3
                else {
                    bool flag = false;
                    node* temp = curr->right;
                    while(temp->left) { flag = true; parent = temp; temp = temp->left; }
                    if(!flag) { parent = curr; }
                    string swap = curr->data;
                    curr->data = temp->data;
                    temp->data = swap;
                    RemoveNode(parent, temp, swap);
                }
            }
        }

        void Remove(string stuff) {
            auto temp = root;
            auto parent = temp;
            bool flag = false;
            if(!temp) { RemoveNode(nullptr, nullptr, stuff); }

            while(temp) {
                if(stuff.compare(temp->data) == 0) { flag = true; RemoveNode(parent, temp, stuff); break; }
                else if(stuff < temp->data) { parent = temp ; temp = temp->left; }
                else { parent = temp ; temp = temp->right; }
            }

            if(!flag) { cout << "\nElement doesn't exist in the table"; }
        }

        void RB_Delete_Fixup(node* z) { 
            while(z->data != root->data && z->color == "BLACK") {
                auto sibling = GetRoot();
                if(z->parent->left == z) {
                    if(z->parent->right){ sibling = z->parent->right; }
                    if(sibling) {
                        //CASE -- 1
                        if(sibling->color == "RED") {
                            sibling->color = "BLACK";
                            z->parent->color = "RED";
                            LeftRotate(z->parent);
                            sibling = z->parent->right;
                        }
                         //CASE -- 2
                        if(sibling->left == nullptr && sibling->right == nullptr) {
                            sibling->color = "RED";
                            z = z->parent;
                        }
                        else if(sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                            sibling->color = "RED";
                            z = z->parent;
                        }
                        //CASE -- 3
                        else if(sibling->right->color == "BLACK") {
                            sibling->left->color = "BLACK";
                            sibling->color = "RED";
                            RightRotate(sibling);
                            sibling = z->parent->right;
                        } else {
                            sibling->color = z->parent->color;
                            z->parent->color = "BLACK";
                            if(sibling->right){ sibling->right->color = "BLACK"; }
                            LeftRotate(z->parent);
                            z = root;
                        }
                    } 
                } else {
                    if(z->parent->right == z){
                        if(z->parent->left){ sibling = z->parent->left; }
                        if(sibling) {
                            //CASE -- 1
                            if(sibling->color == "RED"){
                                sibling->color = "BLACK";
                                z->parent->color = "RED";
                                RightRotate(z->parent);
                                sibling = z->parent->left;
                            }
                            //CASE -- 2
                             if(sibling->left == nullptr && sibling->right == nullptr) {
                                sibling->color = "RED";
                                z = z->parent;
                            }
                            else if(sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                                sibling->color = "RED";
                                z = z->parent;
                            }
                            //CASE -- 3 
                            else if(sibling->left->color == "BLACK") {
                                sibling->right->color = "BLACK";
                                sibling->color = "RED";
                                RightRotate(sibling);
                                sibling = z->parent->left;
                            } else {
                                sibling->color = z->parent->color;
                                z->parent->color = "BLACK";
                                if(sibling->left){ sibling->left->color = "BLACK"; }
                                LeftRotate(z->parent);
                                z = root;
                            }
                        } 
                    }

                }
            }
            z->color = "BLACK";
        }

        node* TreeSearch(string stuff) {
            auto temp = GetRoot();
            if(temp == nullptr) { return nullptr; }

            while(temp) {
                if(stuff.compare(temp->data) == 0){ return temp; }
                else if(stuff.compare(temp->data) < 0){ temp = temp->left; }
                else { temp = temp->right; }
            }
            return nullptr;
        }

         void LeftRotate(node* x) {
            node* nw_node = new node();
            if(x->right->left) { nw_node->right = x->right->left; }
            nw_node->left = x->left;
            nw_node->data = x->data;
            nw_node->color = x->color;
            x->data = x->right->data;

            x->left = nw_node;
            if(nw_node->left){ nw_node->left->parent = nw_node; }
            if(nw_node->right){ nw_node->right->parent = nw_node; }
            nw_node->parent = x;

            if(x->right->right){ x->right = x->right->right; }
            else { x->right = nullptr; }

            if(x->right){ x->right->parent = x; }
        }

        void RightRotate(node* x) {
            node* nw_node = new node();
            if(x->left->right){ nw_node->left = x->left->right; }
            nw_node->right = x->right;
            nw_node->data = x->data;
            nw_node->color = x->color;

            x->data = x->left->data;
            x->color = x->left->color;

            x->right = nw_node;
            if(nw_node->left){ nw_node->left->parent = nw_node; }
            if(nw_node->right){ nw_node->right->parent = nw_node; }
            nw_node->parent = x;

            if(x->left->left){ x->left = x->left->left; }
            else { x->left = nullptr; }

            if(x->left){ x->left->parent = x; }
        }

        void InorderTraversal(node* temp) {
            if(!temp){ return; }
            
            InorderTraversal(temp->left);
            cout <<temp->data<<" ";
            InorderTraversal(temp->right);
        }
 };

//splay Tree
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class SplayTree
{

    struct Node
    {
        string key;
        Node* parent;
        Node* left;
        Node* right;
        
        Node(string key)
        {
            this -> key = key;
            this -> parent = NULL;
            this -> left = NULL;
            this -> right = NULL;
        }
    };

    Node *root;
    
    void zig(Node *x)
    {
        Node *p = x -> parent;
        if (p -> left == x)
        {
            Node *A = x -> left;
            Node *B = x -> right;
            Node *C = p -> right;
            
            x -> parent = NULL;
            x -> right = p;
            
            p -> parent = x;
            p -> left = B;
            
            if (B != NULL) B -> parent = p;
        }
        else
        {
            Node *A = p -> left;
            Node *B = x -> left;
            Node *C = x -> right;
            
            x -> parent = NULL;
            x -> left = p;
            
            p -> parent = x;
            p -> right = B;
            
            if (B != NULL) B -> parent = p;
        }
    }

    void zig_zig(Node *x)
    {
        Node *p = x -> parent;
        Node *g = p -> parent;
        if (p -> left == x)
        {
            Node *A = x -> left;
            Node *B = x -> right;
            Node *C = p -> right;
            Node *D = g -> right;
            
            x -> parent = g -> parent;
            x -> right = p;
            
            p -> parent = x;
            p -> left = B;
            p -> right = g;
            
            g -> parent = p;
            g -> left = C;
            
            
            if (x -> parent != NULL)
            {
                if (x -> parent -> left == g) x -> parent -> left = x;
                else x -> parent -> right = x;
            }
            
            if (B != NULL) B -> parent = p;
            
            if (C != NULL) C -> parent = g;
        }
        else
        {
            Node *A = g -> left;
            Node *B = p -> left;
            Node *C = x -> left;
            Node *D = x -> right;
            
            x -> parent = g -> parent;
            x -> left = p;
            
            p -> parent = x;
            p -> left = g;
            p -> right = C;
            
            g -> parent = p;
            g -> right = B;
            
            if (x -> parent != NULL)
            {
                if (x -> parent -> left == g) x -> parent -> left = x;
                else x -> parent -> right = x;
            }
            
            if (B != NULL) B -> parent = g;
            
            if (C != NULL) C -> parent = p;
        }
    }

    void zig_zag(Node *x)
    {
        Node *p = x -> parent;
        Node *g = p -> parent;
        if (p -> right == x)
        {
            Node *A = p -> left;
            Node *B = x -> left;
            Node *C = x -> right;
            Node *D = g -> right;
            
            x -> parent = g -> parent;
            x -> left = p;
            x -> right = g;
            
            p -> parent = x;
            p -> right = B;
            
            g -> parent = x;
            g -> left = C;
            
            if (x -> parent != NULL)
            {
                if (x -> parent -> left == g) x -> parent -> left = x;
                else x -> parent -> right = x;
            }
            
            if (B != NULL) B -> parent = p;
            
            if (C != NULL) C -> parent = g;
        }
        else
        {
            Node *A = g -> left;
            Node *B = x -> left;
            Node *C = x -> right;
            Node *D = p -> right;
            
            x -> parent = g -> parent;
            x -> left = g;
            x -> right = p;
            
            p -> parent = x;
            p -> left = C;
            
            g -> parent = x;
            g -> right = B;
            
            if (x -> parent != NULL)
            {
                if (x -> parent -> left == g) x -> parent -> left = x;
                else x -> parent -> right = x;
            }
            
            if (B != NULL) B -> parent = g;
            
            if (C != NULL) C -> parent = p;
        }
    }
    
    void splay(Node *x)
    {
        while (x -> parent != NULL)
        {
            Node *p = x -> parent;
            Node *g = p -> parent;
            if (g == NULL) zig(x);
            else if (g -> left == p && p -> left == x) zig_zig(x);
            else if (g -> right == p && p -> right == x) zig_zig(x);
            else zig_zag(x);
        }
        this -> root = x;
    }
    
public:

    SplayTree()
    {
        this -> root = NULL;
    }


    SplayTree(Node *rt)
    {
        this -> root = rt;
    }


    Node* find(string x)
    {
        Node *ret = NULL;
        Node *curr = this -> root;
        Node *prev = NULL;
        while (curr != NULL)
        {
            prev = curr;    
            if (x.compare(curr -> key) < 0) curr = curr -> left;
            else if (x.compare(curr -> key) > 0) curr = curr -> right;
            else
            {
                ret = curr;
                break;
            }
        }
        if (ret != NULL) splay(ret);
        else if (prev != NULL) splay(prev);
        return ret;
    }


    void insert(string x)
    {
        if (root == NULL)
        {
            root = new Node(x);
            return;
        }
        Node *curr = this -> root;
        while (curr != NULL)
        {
            if (x.compare(curr -> key) < 0)
            {
                if (curr -> left == NULL)
                {
                    Node *newNode = new Node(x);
                    curr -> left = newNode;
                    newNode -> parent = curr;
                    splay(newNode);
                    return;
                }
                else curr = curr -> left;
            }
            else if (x.compare(curr -> key) > 0)
            {
                if (curr -> right == NULL)
                {
                    Node *newNode = new Node(x);
                    curr -> right = newNode;
                    newNode -> parent = curr;
                    splay(newNode);
                    return;
                }
                else curr = curr -> right;
            }
            else
            {
                splay(curr);
                return;
            }
        }
    }


    Node* subtree_max(Node *subRoot)
    {
        Node *curr = subRoot;
        while (curr -> right != NULL) curr = curr -> right;
        return curr;
    }

    
    Node* subtree_min(Node *subRoot)
    {
        Node *curr = subRoot;
        while (curr -> left != NULL) curr = curr -> left;
        return curr;
    }
};

vector<string> loadFromFile(string fileName)
{
    vector<string> out;
    ifstream myFile (fileName);
    string line;
    if(myFile.is_open())
    {
        while(getline(myFile, line, ' '))
        {
            while(!isalpha(line[0]))
            {
                line = line.substr(1, line.length());
            }
            while(!isalpha(line[line.length()-1]))
            {
                line = line.substr(0, line.length()-1);
            }
            out.push_back(line);
        }
    }
    else
    {
        cout<<"nieprawidlowa nazwa pliku\n";
    }
    return out;
}

// main
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


int main()
{
    string type = "";
    cout<<"podaj typ drzewa:\n";
    cin>>type;

    if(type == "bst")
    {
        BST tree;
        string intent = "";
        while(intent != "end")
        {
            cout<<">";
            cin>>intent;
            cout<<"\n";
            if(intent == "insert")
            {
                string param;
                cin>>param;
                tree.insert(param);
            }
            if(intent == "load")
            {
                string fileName = "";
                cin>>fileName;
                vector<string> fromFile;
                fromFile = loadFromFile(fileName);
                for(string i : fromFile)
                {
                    tree.insert(i);
                }
            }
            if(intent == "delete")
            {
                string param;
                cin>>param;
                tree.remove(param);
            }
            if(intent == "find")
            {
                string param;
                cin>>param;
                tree.search(param);
            }
            if(intent == "min")
            {
                tree.min();
            }
            if(intent == "max")
            {
                tree.max();
            }
            if(intent == "successor")
            {
                
            }
            if(intent == "inorder")
            {
                tree.display();
            }
        }
    }
    else if(type == "rbt")
    {
        RB_TREE tree;
        string intent = "";
        while(intent != "end")
        {
            
        }
    }
    else if(type == "splay")
    {
        SplayTree tree;
        string intent = "";
        while(intent != "end")
        {
            
        }
    }
    else
    {
        cout<<"nieprawidlowy typ drzewa, nie rozpoznano typu "<<type<<"\n";
    }
    return 0;
}