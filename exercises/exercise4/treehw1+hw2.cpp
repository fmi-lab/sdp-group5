#include <iostream>
#include <assert.h>
#include <string.h>
#include <fstream>
#include <algorithm> 
#include <vector>


using namespace std;

template <class T>
using mapFn = T(*)(const T&);

template <class T>
struct Node
{
	Node<T> *left, *right;
	T data;

	Node(const T& d, Node<T> *l, Node<T> *r) :
		left(l), right(r), data(d)
	{
		makeID();
	}
	Node() :left(NULL), right(NULL)
	{
		makeID();
	}

	int getID() const
	{
		return id;
	}

private:
	int id;

	void makeID()
	{
		static int maxID = 0;
		maxID++;
		id = maxID;

	}

};

template <class T>
class BTree
{
private:
	Node<T> *root;
	void simplePrint(Node<T> *subTreeRoot) const;
	bool add(const T& data, const char *trace, Node<T>*&);
	void deleteAll(Node<T> *subTreeRoot);
	bool member(const T&, Node<T> *subTreeRoot) const;
	void map(mapFn<T>, Node<T> *subTreeRoot);

	void dottyPrint(Node<T> *subTreeRoot, ostream& out) const;

	void serialize(Node<T>*, ostream&) const;
	Node<T>* parseTree(istream &in);


	static Node<T>* copyTree(const Node<T> *subTreeRoot);

	void insertBOT(Node<T>*&subTreeRoot, const T& x);

	Node<T>* insertedBOT(Node<T>*subTreeRoot, const T& x);

	void deleteElement(Node<T> *&subTreeRoot, const T&x);

	T minelement(Node<T> *subTreeRoot) const;
	/// Howework
	string findTrace(const T& x, Node<T> *node) const;
	T& findByIndex(int i, Node<T> *node);
	int count(Node<T> *node) const;
	void level(Node<T> *node, int k, vector<T> &res) const;
	/// Homework2
	int turnDataToCount(Node<T> *node);
	void isBOT(Node<T> *node, vector<T> &arr) const;
	static Node<T>* deleted(const T&, Node<T> *node);
public:
	BTree();
	BTree(const BTree<T> &other);

	BTree<T>& operator = (const BTree<T> &other);

	BTree<T>& add(const T& data, const char *trace);

	void deleteElement(const T&x);

	void deserialize(istream&);

	void simplePrint() const;
	void dottyPrint(ostream&);
	//bool isEmpty();
	bool member(const T&) const;

	void map(mapFn<T>);

	void serialize(ostream&)const;

	BTree<T>& insertBOT(const T& x);

	BTree<T> insertedBOT(const T& x);

	T minelement()const;
	/// Homework
	string findTrace(const T& x) const;
	int count() const;
	T& BTree<T>::operator[](int i);
	vector<T> level(int k) const;
	/// Homework2
	void turnDataToCount();
	bool isBOT() const;
	BTree<T> deletedBOT(const T& x) const;
	~BTree();

};

template<class T>
void BTree<T>::deleteElement(Node<T> *&subTreeRoot, const T&x)
{
	//триене от празно дърво
	if (subTreeRoot == NULL)
		return;

	//триене от листо
	if (subTreeRoot->data == x &&
		subTreeRoot->left == NULL &&
		subTreeRoot->right == NULL)

	{
		delete subTreeRoot;
		subTreeRoot = NULL;
		return;
	}

	//триене от лявото поддърво
	if (x < subTreeRoot->data)
	{
		deleteElement(subTreeRoot->left, x);
		return;
	}

	//триене от дясното поддърво
	if (x > subTreeRoot->data)
	{
		deleteElement(subTreeRoot->right, x);
		return;
	}

	//вече сме сигурни, че трием корена!
	//освен това сме сигурни, че корена има ПОНЕ ЕДИН
	//наследник

	//триене на корен само с 1 наследник
	if (subTreeRoot->right == NULL)
	{
		Node<T> *tmp = subTreeRoot;
		subTreeRoot = subTreeRoot->left;
		delete tmp;
		return;
	}

	//триене на корен само с 1 наследник
	//този случй може да не се разглежда
	if (subTreeRoot->left == NULL)
	{
		Node<T> *tmp = subTreeRoot;
		subTreeRoot = subTreeRoot->right;
		delete tmp;
		return;
	}


	//триене на корена
	//вече сме сигурни, че корена има точно два наследника
	T minel = minelement(subTreeRoot->right);
	subTreeRoot->data = minel;
	deleteElement(subTreeRoot->right, minel);


}

template<class T>
void BTree<T>::deleteElement(const T&x)
{
	deleteElement(root, x);
}

template<class T>
T BTree<T>::minelement(Node<T> *subTreeRoot) const
{
	assert(subTreeRoot != NULL);
	Node<T> *current = subTreeRoot;

	while (current->left != NULL)
	{
		current = current->left;
	}

	return current->data;

}


template<class T>
T BTree<T>::minelement() const
{
	return minelement(root);

}

template<class T>
BTree<T> BTree<T>::insertedBOT(const T& x)
{
	BTree<T> result;
	result.root = insertedBOT(root, x);

	return result;
}


template<class T>
Node<T>* BTree<T>::insertedBOT(Node<T>*subTreeRoot, const T& x)
{
	if (subTreeRoot == NULL)
	{
		return new Node<T>(x, NULL, NULL);
	}

	if (x > subTreeRoot->data)
	{
		return new Node<T>(subTreeRoot->data,
			copyTree(subTreeRoot->left),
			insertedBOT(subTreeRoot->right, x));

	}

	return new Node<T>(subTreeRoot->data,
		insertedBOT(subTreeRoot->left, x),
		copyTree(subTreeRoot->right));

}


template<class T>
void BTree<T>::insertBOT(Node<T>* &subTreeRoot, const T& x)
{

	if (subTreeRoot == NULL)
	{
		subTreeRoot = new Node<T>(x, NULL, NULL);
		return;
	}

	if (x <= subTreeRoot->data)
	{
		insertBOT(subTreeRoot->left, x);
	}
	else {
		insertBOT(subTreeRoot->right, x);
	}

}


template<class T>
BTree<T>& BTree<T>::insertBOT(const T& x)
{
	insertBOT(root, x);
	return *this;
}

template<class T>
BTree<T>& BTree<T>::operator = (const BTree<T> &other)
{
	if (this == &other)
		return *this;

	deleteAll(root);
	root = copyTree(other.root);

	return *this;
}


template<class T>
Node<T>* BTree<T>::copyTree(const Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return NULL;

	return new Node<T>(subTreeRoot->data,
		copyTree(subTreeRoot->left),
		copyTree(subTreeRoot->right));
}

template<class T>
BTree<T>::BTree(const BTree<T> &other)
{
	root = copyTree(other.root);
}


template<class T>
void BTree<T>::serialize(Node<T> *subTreeRoot, ostream &out) const
{
	if (subTreeRoot == NULL)
	{
		out << "null ";
		return;
	}

	out << subTreeRoot->data << " ";

	serialize(subTreeRoot->left, out);
	serialize(subTreeRoot->right, out);

}

template<class T>
void BTree<T>::serialize(ostream &out) const
{
	serialize(root, out);
	cout << endl;
}



template<class T>
void BTree<T>::dottyPrint(ostream &out)
{
	dottyPrint(root, out);
}



template<class T>
void BTree<T>::dottyPrint(Node<T> *subTreeRoot, ostream& out) const
{
	if (subTreeRoot == NULL)
		return;

	out << subTreeRoot->getID()
		<< "[label=\""
		<< subTreeRoot->data
		<< "\"];" << endl;

	if (subTreeRoot->left != NULL)
		out << subTreeRoot->getID()
		<< "->"
		<< subTreeRoot->left->getID()
		<< endl;

	if (subTreeRoot->right != NULL)
		out << subTreeRoot->getID()
		<< "->"
		<< subTreeRoot->right->getID()
		<< endl;

	dottyPrint(subTreeRoot->left, out);
	dottyPrint(subTreeRoot->right, out);
}



template<class T>
void BTree<T>::map(mapFn<T> f, Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;

	subTreeRoot->data = f(subTreeRoot->data);
	map(f, subTreeRoot->left);
	map(f, subTreeRoot->right);
}

template<class T>
void BTree<T>::map(mapFn<T>f)
{
	map(f, root);
}


template<class T>
bool BTree<T>::member(const T& x) const
{
	return member(x, root);
}


template<class T>
bool BTree<T>::member(const T& x, Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return false;


	return subTreeRoot->data == x ||
		member(x, subTreeRoot->left) ||
		member(x, subTreeRoot->right);


}


template<class T>
void BTree<T>::deleteAll(Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;

	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BTree<T>::~BTree()
{
	deleteAll(root);
	root = NULL;

}


template <class T>
BTree<T>& BTree<T>::add(const T& x, const char *trace)
{
	add(x, trace, root);
	return *this;
}


template <class T>
bool BTree<T>::add(const T& x, const char *trace, Node<T>* &subTreeRoot)
{
	if (subTreeRoot == NULL)
	{
		assert(strlen(trace) == 0);
		subTreeRoot = new Node<T>(x, NULL, NULL);
		return true;
	}

	assert(strlen(trace)>0);

	if (trace[0] == 'L')
		return add(x, trace + 1, subTreeRoot->left);

	assert(trace[0] == 'R');
	return add(x, trace + 1, subTreeRoot->right);

	return true;

}

template <class T>
BTree<T>::BTree() :root(NULL) {}

template <class T>
void BTree<T>::simplePrint() const
{
	simplePrint(root);
	cout << endl;
}

template <class T>
void BTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return;

	simplePrint(subTreeRoot->left);
	cout << subTreeRoot->data << " ";
	simplePrint(subTreeRoot->right);
}

void removeWhite(istream &in)
{
	while (in.peek() <= 32)
		in.get();
}

template <class T>
Node<T>* BTree<T>::parseTree(istream &in)
{

	removeWhite(in);

	if (in.peek() == 'n')
	{
		string dummy;
		in >> dummy;
		assert(dummy == "null");
		return NULL;
	}

	T data;
	in >> data;

	return new Node<T>(data,
		parseTree(in),
		parseTree(in));


}


template <class T>
void BTree<T>::deserialize(istream &in)
{
	deleteAll(root);

	root = parseTree(in);


}

/// !!!!!!!!!!!!!!!!!!!!!!!!!! H O M E W O R K !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
template<class T>
string BTree<T>::findTrace(const T& x) const
{
	return findTrace(x, root);
}

template<class T>
int BTree<T>::count() const {
	return count(root);
}

template<class T>
T& BTree<T>::operator[](int i) {
	/* if (root == nullptr ) {
	*	 throw exception("Empty tree");
	* }
	* if (i < 0 i >= count(root)){
	*   throw out_of_range("Invalid index i ");
	* }
	*/
	return findByIndex(i, root);
}

template<class T>
vector<T> BTree<T>::level(int k) const {
	vector<T> res;
	level(root, k, res);
	return res;
}


template<class T>
string BTree<T>::findTrace(const T &x, Node<T>* node) const
{
	if (node == nullptr) {
		return "_";
	}
	if (node->data == x) {
		return "";
	}
	string left = findTrace(x, node->left);
	string right = findTrace(x, node->right);
	if (left != "_") {
		return "L" + left;
	}
	else if (right != "_") {
		return "R" + right;
	}
	return "_";

}

template<class T>
T& BTree<T>::findByIndex(int i, Node<T>* node) {
	if (i == 0) {
		return node->data;
	}
	int cntLeft = count(node->left);
	if (node->left != nullptr && i <= cntLeft) {
		findByIndex(i - 1, node->left);
	}
	else if (node->right != nullptr) {
		findByIndex(i - cntLeft - 1, node->right);
	}
}

template<class T>
int BTree<T>::count(Node<T>* node) const {
	if (node == nullptr) {
		return 0;
	}
	return 1 + count(node->left) + count(node->right);
}

template<class T>
void BTree<T>::level(Node<T>* node, int k, vector<T>& res) const {
	if (node == nullptr) {
		return;
	}
	if (k == 0) {
		res.push_back(node->data);
		return;
	}
	level(node->left, k - 1, res);
	level(node->right, k - 1, res);
}

/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! E N D !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/// !!!!!!!!!!!!!!!!!!!!!!! H O M E W O R K 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!
template<class T>
void BTree<T>::turnDataToCount()
{
	turnDataToCount(root);
}

template<class T>
bool BTree<T>::isBOT() const
{
	vector<T> arr; 
	isBOT(root, arr);

	return is_sorted(arr.begin(), arr.end());
}

template<class T>
BTree<T> BTree<T>::deletedBOT(const T& x) const
{
	BTree<T> res = *this;
	res.deleteElement(x);
	return res;
}

template<class T>
int BTree<T>::turnDataToCount(Node<T>* node)
{
	if (node == nullptr) {
		return 0;
	}
	return node->data = (1 + turnDataToCount(node->left) + turnDataToCount(node->right));
}

template<class T>
void BTree<T>::isBOT(Node<T>* node, vector<T>& arr) const {
	if (node == nullptr) {
		return;
	}
	isBOT(node->left, arr);
	arr.push_back(node->data);
	isBOT(node->right, arr);
}



/// !!!!!!!!!!!!!!!!!!!!!!! E N D !!!!!!!!!!!!!!!!!!!!!!!!!!!!

void testMember()
{
	BTree<int> t;

	t.add(10, "").add(12, "L").add(14, "R").add(15, "LR");

	assert(t.member(12) == true);
	assert(t.member(18) == false);
	assert(t.member(15) == true);
}


int plusOne(const int& i)
{
	return i + 1;
}

void testAssignment()
{
	BTree<int> t;

	t.add(10, "").add(12, "L").add(14, "R").add(15, "LR");
	t.simplePrint();

	BTree<int> t1 = t;

	t1.map(plusOne);

	t1 = t;

	assert(t1.member(10) &&
		t1.member(12) &&
		t1.member(14) &&
		t1.member(15));


}

void testMinEl()
{
	BTree<int> t;

	t.insertBOT(59)
		.insertBOT(23)
		.insertBOT(68)
		.insertBOT(190)
		.insertBOT(41)
		.insertBOT(67);

	assert(t.minelement() == 23);
}

int main()
{

	/*testMember();
	testAssignment();
	testMinEl();*/

	BTree<int> t;
	t.insertBOT(10).insertBOT(15).insertBOT(5).insertBOT(100);
	std::cout << std::endl << std::boolalpha << t.isBOT() << std::endl;

	/*
	std::cout << std::endl << std::boolalpha << t.isBOT() << std::endl;
	t.turnDataToCount();
	t.simplePrint();
	std::cout << std::boolalpha << t.isBOT() << std::endl; */
	/*t.insertBOT(56)
		.insertBOT(23)
		.insertBOT(68)
		.insertBOT(190)
		.insertBOT(41)
		.insertBOT(60)
		.insertBOT(65)
		.insertBOT(59);


	cerr << "digraph G{" << endl;
	t.dottyPrint(cerr);

	BTree<int> t1 = t;
	t1.deleteElement(56);

	t1.dottyPrint(cerr);

	cerr << "}";

	t1.simplePrint();*/

	return 0;
}




