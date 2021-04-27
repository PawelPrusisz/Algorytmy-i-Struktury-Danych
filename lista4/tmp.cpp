#include<bits/stdc++.h>

using namespace std;

//ToDo : successor BST
//ToDo : "First" < "a" ????
//ToDo : RBT testing
//ToDo : splay testing
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
        else if(x < t->data)
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
            cout<<n->data<<" "<<t->data<<" ";
            if(n->data.compare(t->data) < 0)
            {
                p = t;
                t = t->left;
                cout<<1<<"\n";
            }
            else if(n->data.compare(t->data) > 0)
            {
                t = t->right;
                cout<<1<<"\n";
            }
                
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
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
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
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
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
               cout << "Element inserted.\n";
           }
           else {
               auto linker = GetRoot();
               node* newnode = new node();
               newnode->data = stuff;

               while(linker != nullptr){
                   if(linker->data.compare(stuff) < 0){
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
                        if(grandparent->data.compare(root->data) != 0){ z = grandparent; }
                        else { break; }
                    }
                    else if(z == grandparent->left->right) {
                       LeftRotate(z->parent);
                    }
                    else {
                        z->parent->color = "BLACK";
                        grandparent->color = "RED";
                        RightRotate(grandparent);
                        if(grandparent->data.compare(root->data) != 0){ z = grandparent; }
                        else { break; }
                    }
                }
                else {
                    if(grandparent->left) { uncle = grandparent->left; }
                    if(uncle->color == "RED"){
                        z->parent->color = "BLACK";
                        uncle->color = "BLACK";
                        grandparent->color = "RED";
                        if(grandparent->data.compare(root->data) != 0){ z = grandparent; }
                        else { break; }
                    }
                    else if(z == grandparent->right->left){
                        RightRotate(z->parent);
                    }
                    else {
                        z->parent->color = "BLACK";
                        grandparent->color = "RED";
                        LeftRotate(grandparent);
                        if(grandparent->data.compare(root->data) != 0){ z = grandparent; }
                        else { break; }
                    }
                }
            }
            root->color = "BLACK";
        }


        void RemoveNode(node* parent, node* curr, string stuff) {
            if(curr == nullptr) { return; }
            cout<<"b";
            if(curr->data.compare(stuff) == 0) {
                //CASE -- 1
                if(curr->left == nullptr && curr->right == nullptr) {
                    cout<<"1";
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
                    cout<<"2.1";
                    string swap = curr->data;
                    curr->data = curr->left->data;
                    curr->left->data = swap;
                    RemoveNode(curr, curr->right, stuff);
                }
                else if(curr->left == nullptr && curr->right != nullptr) {
                    cout<<"2.2";
                    string swap = curr->data;
                    curr->data = curr->right->data;
                    curr->right->data = swap;
                    RemoveNode(curr, curr->right, stuff);
                }
                //CASE -- 3
                else {
                    cout<<"3";
                    bool flag = false;
                    node* temp = curr->right;
                    while(temp->left) { flag = true; parent = temp; temp = temp->left; }
                    if(!flag) { parent = curr; }
                    string swap = curr->data;
                    curr->data = temp->data;
                    temp->data = swap;
                    RemoveNode(parent, temp, swap);
                }
                cout<<"c";
            }
        }

        void Remove(string stuff) {
            node* temp = root;
            node* parent = temp;
            bool flag = false;
            if(!temp) { RemoveNode(nullptr, nullptr, stuff); }
            cout<<"debug\n\n";
            while(temp) {
                cout<<"a";
                string a;
                cin>>a;
                if(stuff.compare(temp->data) == 0) { 
                    flag = true;
                    RemoveNode(parent, temp, stuff);
                    break;
                }
                else if(stuff.compare(temp->data) < 0) {
                    parent = temp;
                    temp = temp->left;
                }
                else { parent = temp ; temp = temp->right; }
            }
            cout<<"\n";
            if(!flag) { cout << "\nElement doesn't exist in the table"; }
        }

        void RB_Delete_Fixup(node* z) { 
            while(z->data.compare(root->data) !=0 && z->color == "BLACK") {
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
            cout << temp->data << "<" << temp->color << "> ";
            InorderTraversal(temp->right);
        }

        void InorderTraversal() {
            node* temp = root;
            if(!temp){ return; }
            
            InorderTraversal(temp->left);
            cout<< temp->data << "<" << temp->color << "> ";
            InorderTraversal(temp->right);
        }

        void Minimum(node* temp) {
            if(!temp->left)cout << temp->data << "<" << temp->color << ">\n";
            else Minimum(temp->left);
        }
        void Minimum() {
            if(root){
                node* temp = root;
                if(!temp->left)cout << temp->data << "<" << temp->color << ">\n";
                else Minimum(temp->left);
            }
            else cout<<"\n";
        }

        void Maximum(node* temp) {
            if(!temp->right)cout << temp->data << "<" << temp->color << ">\n";
            else Maximum(temp->left);
        }
        void Maximum() {
            if(root){
                node* temp = root;
                if(!temp->right)cout << temp->data << "<" << temp->color << ">\n";
                else Maximum(temp->left);
            }
            else cout<<"\n";
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

class SplayTree {
private:

    struct Node {
        string data;
        Node *parent;
        Node *left;
        Node *right;
    };

	Node* root;

	void inOrderHelper(Node* node) {
		if (node != nullptr) {
			inOrderHelper(node->left);
			cout<<node->data<<" ";
			inOrderHelper(node->right);
		} 
	}

	Node* searchTreeHelper(Node* node, string key) {
		if (node == nullptr || key == node->data) {
			return node;
		}

		if (key.compare(node->data) < 0) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void deleteNodeHelper(Node* node, string key) {
		Node* x = nullptr;
		Node* t, *s;
		while (node != nullptr){
			if (node->data == key) {
				x = node;
			}

			if (node->data.compare(key) <=0) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (x == nullptr) {
			cout<<"Couldnt find key in the tree"<<endl;
			return;
		}
		split(x, s, t);
		if (s->left){
			s->left->parent = nullptr;
		}
		root = join(s->left, t);
		delete(s);
		s = nullptr;
	}

	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void splay(Node* x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig rotation
					rightRotate(x->parent);
				} else {
					// zag rotation
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig rotation
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag rotation
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag rotation
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				// zag-zig rotation
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

    Node* join(Node* s, Node* t) {
        if(!s){
            return t;
        }
        if(!t){
            return s;
        }
        Node* x = maximum(s);
        splay(x);
        x->right = t;
        t->parent = x;
        return x;
    }

	void split(Node* &x, Node* &s, Node* &t) {
		splay(x);
		if (x->right) {
			t = x->right;
			t->parent = nullptr;
		} else {
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	} 

public:
	SplayTree() {
		root = nullptr;
	}

	void inorder() {
		inOrderHelper(this->root);
	}

	Node* searchTree(string k) {
		Node* x = searchTreeHelper(this->root, k);
		if (x) {
			splay(x);
		}
		return x;
	}

	Node* minimum(Node* node) {
        if(root){
            while (node->left != nullptr) {
                node = node->left;
            }
            cout<<node->data<<"\n";
            return node;
        }
        else cout<<"\n";
	}

	Node* maximum(Node* node) {
        if(root)
        {
            while (node->right != nullptr) {
			    node = node->right;
		    }
            cout<<node->data<<"\n";
		    return node;
        }
		else cout<<"\n";
	}

	Node* successor(Node* x) {
		
		if (x->right != nullptr) {
			return minimum(x->right);
		}

		Node* y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void insert(string key) {
		Node* node = new Node;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->data = key;
		Node* y = nullptr;
		Node* x = this->root;

		while (x != nullptr) {
			y = x;
			if (node->data.compare(x->data) < 0) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data.compare(y->data) < 0) {
			y->left = node;
		} else {
			y->right = node;
		}

		splay(node);
	}

	Node* getRoot(){
		return this->root;
	}

	void deleteNode(string data) {
		deleteNodeHelper(this->root, data);
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
    cin>>type;
    int n;
    cin>>n;
    // Binary-Search Tree
    if(type == "bst")
    {
        BST tree;
        string intent = "";

        for(int i = 0; i < n; i++)
        {
            cin>>intent;
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
                string param;
                cin>>param;
                tree.successor(param);
            }
            if(intent == "inorder")
            {
                tree.display();
            }
        }
    }
    // Red-Black Tree
    else if(type == "rbt")
    {
        RB_TREE tree;
        string intent = "";
        for(int i = 0; i < n; i++)
        {
            cin>>intent;
            if(intent == "insert")
            {
                string param;
                cin>>param;
                tree.InsertNode(param);
            }
            if(intent == "load")
            {
                string fileName = "";
                cin>>fileName;
                vector<string> fromFile;
                fromFile = loadFromFile(fileName);
                for(string i : fromFile)
                {
                    tree.InsertNode(i);
                }
            }
            if(intent == "delete")
            {
                string param;
                cin>>param;
                tree.Remove(param);
            }
            if(intent == "find")
            {
                string param;
                cin>>param;
                tree.TreeSearch(param);
            }
            if(intent == "min")
            {
                tree.Minimum();
            }
            if(intent == "max")
            {
                tree.Maximum();
            }
            if(intent == "successor")
            {
                //TODO: successor
                //string param;
                //cin>>param;
                //tree.successor(param);
            }
            if(intent == "inorder")
            {
                tree.InorderTraversal();
                cout<<"\n";
            }
        }
    }
    //Splay Tree
    else if(type == "splay")
    {
        SplayTree tree;
        string intent = "";
        for(int i = 0; i < n; i++)
        {
            cin>>intent;
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
                tree.deleteNode(param);
            }
            if(intent == "find")
            {
                string param;
                cin>>param;
                if(tree.searchTree(param))cout<<1<<"\n";
                else cout<<0<<"\n";
            }
            if(intent == "min")
            {
                tree.minimum(tree.getRoot());
            }
            if(intent == "max")
            {
                tree.maximum(tree.getRoot());
            }
            if(intent == "successor")
            {
                string param;
                cin>>param;
                tree.successor(tree.searchTree(param));
            }
            if(intent == "inorder")
            {
                tree.inorder();
                cout<<"\n";
            }
        }
    }
    else
    {
        cout<<"nieprawidlowy typ drzewa, nie rozpoznano typu "<<type<<"\n";
    }
    return 0;
}