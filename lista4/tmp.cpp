#include<bits/stdc++.h>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;

vector<float> Timing(5, 0.0);
int m = 100;

long long maxElements = 0;
long long curElements = 0;
long long compares = 0;
long long inserts = 0;
long long deletes = 0;
long long finds = 0;
long long mins = 0;
long long maxs = 0;
long long successors = 0;
long long inorders = 0;


//ToDo : wypisz czas wywolania funkcji i porownania dla kadego rodzaju drzewa :((((

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
		compares++;
        if(t == NULL)
        {
			compares--;
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

    void successor(node* t)
    {
        if(t)
		{
			if(t->right)
			{
				node* n = findMin(t->right);
				cout<<n->data;
			}
			
		}
		cout<<"\n";
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
        else if(x < t->data){
			t->left = remove(x, t->left);
			compares++;
		}
        else if(x > t->data){
			t->right = remove(x, t->right);
			compares+=2;
		}
        else if(t->left && t->right)
        {
			compares+=3;
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
        else if(x < t->data){
			compares++;
			return find(t->left, x);
		}
            
        else if(x > t->data){
			compares+=2;
			return find(t->right, x);
		}
        else{
			compares+=2;
			return t;
		}
            
    }

public:

    BST() {
        root = NULL;
    }

    void insert(string x) {
        root = insert(x, root);
    }

    node* remove(string x) {
		deletes++;
		node* a = find(root, x);
        if(a != NULL){
            curElements--;
			root = remove(x, root);
		}
    }

    void display() {
        inorder(root);
    }

    void min() {
        auto a = findMin(root);
        if(a != NULL)
        {
            cout<<a->data;
        }
        cout<<"\n";
    }

    void max() {

        node* a = findMax(root);
        if(a != NULL)
        {
            cout<<a->data;
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
        successor(find(root, x));
    }
};

//RB Tree           
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


class RBTree {
private:

    struct Node {
        string data; 
        Node *parent;
        Node *left;
        Node *right;
        int color;
    };
    
	Node* root;
	Node* TNULL;

	void initializeNULLNode(Node* node, Node* parent) {
		node->data = "";
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	void inOrderHelper(Node* node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			cout<<node->data<<" ";
			inOrderHelper(node->right);
		} 
	}

	Node* searchTreeHelper(Node* node, string key) {
		compares++;
		if (node == TNULL || key == node->data) {
			return node;
		}
		compares++;
		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void fixDelete(Node* x) {
		Node* s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					} 

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			} 
		}
		x->color = 0;
	}


	void rbTransplant(Node* u, Node* v){
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->left){
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(Node* node, string key) {
		Node* z = TNULL;
		Node* x, *y;
		while (node != TNULL){
			compares++;
			if (node->data == key) {
				z = node;
			}
			compares++;
			if (compares++ > -1 && node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right, false);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			fixDelete(x);
		}
	}
	
	void fixInsert(Node* k){
		Node* u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right;

				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

public:

    

	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
		
	}

	void inorder() {
		inOrderHelper(this->root);
	}

	Node* searchTree(string k, bool w) {
		Node* node = searchTreeHelper(this->root, k);
		if(w)
		{
			if(node != TNULL) cout<<1<<"\n";
			else cout<<0<<"\n";
		}
		
		return node;
	}

	Node* minimum(Node* node, bool w) {
		if(root != TNULL)
		{
			while (node->left != TNULL) {
				node = node->left;
			}
			if(w)cout<<node->data<<"\n";
			return node;
		}
		else if(w)cout<<"\n";
		
	}

	Node* maximum(Node* node, bool w) {
		if(root != TNULL)
		{
			while (node->right != TNULL) {
				node = node->right;
			}
			if(w)cout<<node->data<<"\n";
			return node;
		}
		else if(w)cout<<"\n";
	}

	Node* successor(Node* x) {
		if (x->right != TNULL) {
			return minimum(x->right, false);
		}

		Node* y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
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
		if (y->right != TNULL) {
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

	void insert(string key) {
		Node* node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;
		Node* y = nullptr;
		Node* x = this->root;

		while (x != TNULL) {
			y = x;
			compares++;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			compares++;
			y->left = node;
		} else {
			compares++;
			y->right = node;
		}

		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}

	Node* getRoot(){
		return this->root;
	}

	void deleteNode(string data) {
		Node* node = searchTree(data, false);
		deletes++;
		if(node) {
			deleteNodeHelper(this->root, data);
			curElements--;
		}
		
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
		compares++;
		if (node == nullptr || key == node->data) {
			return node;
		}
		compares++;
		if (key.compare(node->data) < 0) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void deleteNodeHelper(Node* node, string key) {
		Node* x = nullptr;
		Node* t, *s;
		
		while (node != nullptr){
			compares++;
			if (node->data == key) {
				x = node;
			}
			compares++;
			if (node->data.compare(key) <=0) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (x == nullptr) {
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
        Node* x = maximum(s, false);
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

	Node* minimum(Node* node, bool w) {
        if(root){
            while (node->left != nullptr) {
                node = node->left;
            }
            if(w)cout<<node->data<<"\n";
            return node;
        }
        else if(w)cout<<"\n";
	}

	Node* maximum(Node* node, bool w) {
        if(root)
        {
            while (node->right != nullptr) {
			    node = node->right;
		    }
            if(w)cout<<node->data<<"\n";
		    return node;
        }
		else if(w)cout<<"\n";
	}

	Node* successor(Node* x) {
		
		if (x->right != nullptr) {
			return minimum(x->right, false);
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
			compares++;
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
		deletes++;
		Node* node = searchTree(data);
		if(node){
			deleteNodeHelper(this->root, data);
			curElements--;
		}
	}

};

vector<string> loadFromFile(string fileName, int start, int end)
{
    vector<string> out;
	fileName = "lotr.txt";
    ifstream myFile (fileName);
    string line;
	if(fileName == "aspell_wordlist.txt")
	{
		int num = 0;
		if(myFile.is_open())
		{
			while(getline(myFile, line))
			{
				bool ok = true;
				for(int i = 0; i < line.size(); i++)
				{
					if(!isalpha(line[i]))
					{
						ok = false;
						break;
					}
				}
				
				if(line.size() > 0 && ok)
				{
                    num++;
                    if(num > start && num<= end)
					    out.push_back(line);
					
				}
			}
		}
	}
    else if(myFile.is_open())
    {
		int num = 0;
        while(getline(myFile, line, ' '))
        {
			bool ok = true;
				for(int i = 0; i < line.size(); i++)
				{
					if(!isalpha(line[i]))
					{
						ok = false;
						break;
					}
				}
				
				if(line.size() > 0 && ok)
				{
                    num++;
                    if(num > start && num<= end)
					    out.push_back(line);
					
				}
        }
    }
    else
    {
        cout<<"nieprawidlowa nazwa pliku\n";
    }
    random_shuffle(out.begin(), out.end());
    return out;
}
vector<vector<float>> resoults(69, vector<float>(6, 0.0));
void coutTime(int num)
{
    int index = (num/1000) -1;
    resoults[index][0] += (Timing[0]*1000000/inserts)/m;
    resoults[index][1] += (Timing[1]*1000000/deletes)/m;
    resoults[index][2] += (Timing[2]*1000000/finds)/m;
    resoults[index][3] += (Timing[3]*1000000/mins)/m;
    resoults[index][4] += (Timing[4]*1000000/maxs)/m;
    resoults[index][5] += (Timing[5]*1000000/successors)/m;
    Timing[0] = 0.0;
    Timing[1] = 0.0;
    Timing[2] = 0.0;
    Timing[3] = 0.0;
    Timing[4] = 0.0;
    Timing[5] = 0.0;
    inserts = 0;
    deletes = 0;
    finds = 0;
    mins= 0;
    maxs = 0;
    successors = 0;
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
    srand(time(0));
	using namespace std::chrono;
	vector<string> fromFile;
	
	//0 - insert
	//1 - delete
	//2 - find
	//3 - min
	//4 - max
	//5 - successor
	//6 - inorder
	//all in ms
	
    
    // Binary-Search Tree
    string comand = "";
    cin>>comand;
    vector<string> instructions;
    while(comand != "end")
    {
        instructions.push_back(comand);
        cin>>comand;
    }
    //for(int i = 0; i < instructions.size(); i++)cerr<<instructions[i]<<" ";
    for(int rep = 0; rep < m; rep++)
    {
		int curNum = 0;
    	int step = 1000;
        cerr<<rep<<"\n";
        if(type == "bst")
        {
            BST tree;
            string intent = "";

            for(int i = 0; i < instructions.size(); i++)
            {
                intent =instructions[i];
                if(intent == "end")break;
                
                if(intent == "load")
                {
                    if(curNum > 0)coutTime(curNum);
                    string fileName = "";
                    i++;
                    fileName = instructions[i];
                    fromFile = loadFromFile(fileName, curNum, curNum+step);
                    curNum+=step;
                    
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    for(string i : fromFile)
                    {
                        tree.insert(i);
                        inserts++;
                        curElements++;
                    }
                    if(curElements > maxElements)maxElements = curElements;
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[0] += timePass.count()*1000;
                }
                if(intent == "delete")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.remove(param);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[1] += timePass.count()*1000;
                }
                if(intent == "find")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    finds++;
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.search(param);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[2] += timePass.count()*1000;
                }
                if(intent == "min")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    tree.min();
                    mins++;
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[3] += timePass.count()*1000;
                }
                if(intent == "max")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    tree.max();
                    maxs++;
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[4] += timePass.count()*1000;
                }
                if(intent == "successor")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.successor(param);
                    successors++;
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[5] += timePass.count()*1000;
                }
            }
        }
        // Red-Black Tree
        else if(type == "rbt")
        {
            RBTree tree;
            string intent = "";
            for(int i = 0; i < instructions.size(); i++)
            {
                intent =instructions[i];
                if(intent == "load")
                {
                    if(curNum > 0)coutTime(curNum);
                    string fileName = "";
                    i++;
                    fileName = instructions[i];
                    fromFile = loadFromFile(fileName, curNum, curNum+step);
                    curNum+=step;
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    for(string i : fromFile)
                    {
                        tree.insert(i);
                        inserts++;
                        curElements++;
                    }
                    if(curElements > maxElements)maxElements = curElements;
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[0] += timePass.count()*1000;
                    
                }
                if(intent == "delete")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.deleteNode(param);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[1] += timePass.count()*1000;
                }
                if(intent == "find")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    finds++;
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.searchTree(param, true);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[2] += timePass.count()*1000;
                }
                if(intent == "min")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    mins++;
                    tree.minimum(tree.getRoot(), true);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[3] += timePass.count()*1000;
                }
                if(intent == "max")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    maxs++;
                    tree.maximum(tree.getRoot(), true);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[4] += timePass.count()*1000;
                }
                if(intent == "successor")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    successors++;
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.successor(tree.searchTree(param, false));
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[5] += timePass.count()*1000;
                }
            }  
        }
        //Splay Tree
        else if(type == "splay")
        {
            SplayTree tree;
            string intent = "";
            for(int i = 0; i < instructions.size(); i++)
            {
                intent =instructions[i];
                if(intent == "load")
                {
                    
                    if(curNum > 0)coutTime(curNum);
                    string fileName = "";
                    i++;
                    fileName = instructions[i];
                    fromFile = loadFromFile(fileName, curNum, curNum+step);
                    curNum+=step;
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    for(string i : fromFile)
                    {
                        tree.insert(i);
                        inserts++;
                        curElements++;
                    }
                    if(curElements > maxElements) maxElements = curElements;
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[0] += timePass.count()*1000;
                }
                if(intent == "delete")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.deleteNode(param);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[1] += timePass.count()*1000;
                }
                if(intent == "find")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    finds++;
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    if(tree.searchTree(param))cout<<1<<"\n";
                    else cout<<0<<"\n";
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[2] += timePass.count()*1000;
                }
                if(intent == "min")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    mins++;
                    tree.minimum(tree.getRoot(), true);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[3] += timePass.count()*1000;
                }
                if(intent == "max")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    maxs++;
                    tree.maximum(tree.getRoot(), true);
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[4] += timePass.count()*1000;
                }
                if(intent == "successor")
                {
                    high_resolution_clock::time_point tStart = high_resolution_clock::now();
                    successors++;
                    int r = rand()%fromFile.size();
                    string param = fromFile[r];
                    tree.successor(tree.searchTree(param));
                    high_resolution_clock::time_point tEnd = high_resolution_clock::now();

                    duration<double> timePass = duration_cast<duration<double>>(tEnd - tStart);
                    Timing[5] += timePass.count()*1000;
                }
            }
        }
        else
        {
            cout<<"nieprawidlowy typ drzewa, nie rozpoznano typu "<<type<<"\n";
        }
    }
    for(int i = 0; i < resoults.size(); i++)
    {
		cerr<<(i+1)*1000<<";";
        for(int j = 0; j < resoults[i].size(); j++)
        {
            cerr<<(int)resoults[i][j]<<";";
        }
        cerr<<"\n";
    }
    return 0;
}