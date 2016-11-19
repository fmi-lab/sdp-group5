#include <iostream>
#include <cassert>
#include <cstring>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <iomanip>

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
	Node() :left(nullptr), right(nullptr)
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


#define OPER_PRINT 0
#define OPER_TRAV 1

template <class T>
using waiting = pair<int, Node<T>*>;

template <class T>
class BTree
{

public:
	class LeftRightRootIterator
	{

	public:

		LeftRightRootIterator(Node<T> *root)
		{
			if (root != nullptr)
			{
				operations.push(waiting<T>(OPER_TRAV, root));
				unwind();
			}
		}

		void unwind();

		T operator * ()
		{

			assert(!operations.empty());
			assert(operations.top().first == OPER_PRINT);
			assert(operations.top().second != nullptr);

			//сигурни сме, че на върха на стека
			//стои число "за печатане"

			return operations.top().second->data;

		}

		LeftRightRootIterator& operator ++ ()
		{

			assert(!operations.empty());
			operations.pop();
			unwind();
			return *this;
		}

		bool operator != (const LeftRightRootIterator &other)
		{

			if (operations.empty())
				return !other.operations.empty();

			if (other.operations.empty())
				return !operations.empty();

			//и двете са непразни

			return operations.top() != other.operations.top();
		}

	private:
		stack<waiting<T>> operations;


	};

public:


	LeftRightRootIterator end()
	{
		return LeftRightRootIterator(nullptr);
	}

	LeftRightRootIterator begin()
	{

		return LeftRightRootIterator(root);
	}

	const LeftRightRootIterator end() const
	{
		return LeftRightRootIterator(nullptr);
	}

	const LeftRightRootIterator begin() const
	{

		return LeftRightRootIterator(root);
	}
	enum class Operations : char {
		add = '+', substitute = '-', multiply = '*', divide = '/'
	};
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

	/*
	//преподлогаме, че имеме T::operator +
	//n - колко елемента ОСТАВА да сумираме
	int firstHalfHelper (Node<int> *subTreeRoot, int &n)
	{

	if (n == 0)
	return 0;
	if (subTreeRoot == nullptr)
	return 0;
	int part1 = firstHalfHelper (subTreeRoot->left,n);
	if (n == 0)
	return part1;
	part1 += subTreeRoot->data;
	n--;
	return part1 + firstHalfHelper (subTreeRoot->right,n);
	}*/
	/// Homework1
	string findTrace(const T& x, Node<T> *node) const;
	T& findByIndex(int i, Node<T> *node);
	int count(Node<T> *node) const;
	void level(Node<T> *node, int k, vector<T> &res) const;
	void prettiestPrint(Node<T> *node, int indent) const;
	void prettyPrint(Node<T> *node, int indent) const;
	/// Homework2
	int turnDataToCount(Node<T> *node);
	void isBOT(Node<T> *node, vector<T> &arr) const;
	int calculate(Node<T> *node) const;

public:
	BTree();
	BTree(const BTree<T> &other);

	/*
	ако разглеждаме елементи на ДНД като
	редица от числа, подредени в нарастващ ред,
	да се намери сумата на първата половината на редицата

	T firstHalfSum ();
	T secondHalfSum ();
	*/


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

	~BTree();


	/// Homework
	string findTrace(const T& x) const;
	int count() const;
	T& BTree<T>::operator[](int i);
	vector<T> level(int k) const;
	void prettiestPrint() const;
	void prettyPrint() const;
	/// Homework2
	void turnDataToCount();
	bool isBOT() const;
	BTree<T> deletedBOT(const T& x) const;
	int calculate() const;
};

template<class T>
void BTree<T>::LeftRightRootIterator::unwind()
{

	if (operations.empty())
		return;

	waiting<T> topOperation = operations.top();
	Node<T>* topNode = topOperation.second;

	while (!operations.empty() && topOperation.first != OPER_PRINT)
	{

		operations.pop();
		operations.push(waiting<T>(OPER_PRINT, topNode));
		if (topNode->right != nullptr)
			operations.push(waiting<T>(OPER_TRAV, topNode->right));
		if (topNode->left != nullptr)
			operations.push(waiting<T>(OPER_TRAV, topNode->left));
	
		topOperation = operations.top();
		topNode = topOperation.second;

	}

	//стекът е или празен или на върха му има операция PRINT
}


template<class T>
void BTree<T>::deleteElement(Node<T> *&subTreeRoot, const T&x)
{
	//триене от празно дърво
	if (subTreeRoot == nullptr)
		return;

	//триене от листо
	if (subTreeRoot->data == x &&
		subTreeRoot->left == nullptr &&
		subTreeRoot->right == nullptr)

	{
		delete subTreeRoot;
		subTreeRoot = nullptr;
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
	if (subTreeRoot->right == nullptr)
	{
		Node<T> *tmp = subTreeRoot;
		subTreeRoot = subTreeRoot->left;
		delete tmp;
		return;
	}

	//триене на корен само с 1 наследник
	//този случй може да не се разглежда
	if (subTreeRoot->left == nullptr)
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
	assert(subTreeRoot != nullptr);
	Node<T> *current = subTreeRoot;

	while (current->left != nullptr)
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
	if (subTreeRoot == nullptr)
	{
		return new Node<T>(x, nullptr, nullptr);
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

	if (subTreeRoot == nullptr)
	{
		subTreeRoot = new Node<T>(x, nullptr, nullptr);
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
	if (subTreeRoot == nullptr)
		return nullptr;

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
	if (subTreeRoot == nullptr)
	{
		out << "nullptr ";
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
	if (subTreeRoot == nullptr)
		return;

	out << subTreeRoot->getID()
		<< "[label=\""
		<< subTreeRoot->data
		<< "\"];" << endl;

	if (subTreeRoot->left != nullptr)
		out << subTreeRoot->getID()
		<< "->"
		<< subTreeRoot->left->getID()
		<< endl;

	if (subTreeRoot->right != nullptr)
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
	if (subTreeRoot == nullptr)
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
	if (subTreeRoot == nullptr)
		return false;


	return subTreeRoot->data == x ||
		member(x, subTreeRoot->left) ||
		member(x, subTreeRoot->right);


}


template<class T>
void BTree<T>::deleteAll(Node<T> *subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return;

	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BTree<T>::~BTree()
{
	deleteAll(root);
	root = nullptr;

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
	if (subTreeRoot == nullptr)
	{
		assert(strlen(trace) == 0);
		subTreeRoot = new Node<T>(x, nullptr, nullptr);
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
BTree<T>::BTree() :root(nullptr) {}

template <class T>
void BTree<T>::simplePrint() const
{
	simplePrint(root);
	cout << endl;
}



template <class T>
void BTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	stack<waiting<T>> operations;

	operations.push(waiting<T>(OPER_TRAV, subTreeRoot));

	cout << "{";

	while (!operations.empty())
	{
		waiting<T> topOperation = operations.top();
		Node<T>* topNode = topOperation.second;
		operations.pop();

		if (topOperation.first == OPER_PRINT)
		{
			cout << topNode->data << " ";
		}
		else if (topNode != nullptr) {
			operations.push(waiting<T>(OPER_TRAV, topNode->right));
			operations.push(waiting<T>(OPER_PRINT, topNode));
			operations.push(waiting<T>(OPER_TRAV, topNode->left));
		}
	}

	cout << "}\n";
}

/*
template <class T>
void BTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
if (subTreeRoot == nullptr)
return;
simplePrint (subTreeRoot->left);
cout << subTreeRoot->data << " ";
simplePrint (subTreeRoot->right);
}
*/

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
		assert(dummy == "nullptr");
		return nullptr;
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
void BTree<T>::prettyPrint() const {
	prettyPrint(root, 0);
}

template<class T>
void BTree<T>::prettiestPrint() const {
	prettiestPrint(root, 0);
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

template <class T>
void BTree<T>::prettyPrint(Node<T> *node, int indent) const {
	if (!node) {
		return;
	}

	if (node->right) {
		prettyPrint(node->right, indent + 4);
	}
	if (indent) {
		cout << setw(indent) << ' ';
	}
	/// Optional
	if (node->right) {
		cout << " \n" << setw(indent) << ' ';
	}
	cout << node->data << "\n ";
	if (node->left) {
		/// Optional
		cout << setw(indent) << ' ' << " \n";
		prettyPrint(node->left, indent + 4);
	}
}

template <class T> 
void BTree<T>::prettiestPrint(Node<T> *node, int indent) const {
  if (!node) {
    return;
  }

  if (node->right) {
    prettiestPrint(node->right, indent + 4);
  }
  if (indent) {
    cout << setw(indent) << ' ';
  }
  if (node->right) {
    cout << " /\n" << setw(indent) << ' ';
  }
  cout << node->data << "\n ";
  if (node->left) {
    cout << setw(indent) << ' ' << " \\\n";
    prettiestPrint(node->left, indent + 4);
  }
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

template<>
int BTree<char>::calculate() const
{
	assert(root != nullptr);
	return calculate(root);
}

template<>
int BTree<char>::calculate(Node<char>* node) const
{
	if (node->left && node->right) {
		int leftRes = calculate(node->left);
		int rightRes = calculate(node->right);
		assert(node->data == '+' || node->data == '-' || node->data == '*' || node->data == '/');
		switch (static_cast<Operations>(node->data)) {
			case Operations::add: return leftRes + rightRes;
			case Operations::substitute: return leftRes - rightRes;
			case Operations::multiply: return leftRes * rightRes;
			case Operations::divide: return leftRes / rightRes;
		}
	}
	assert(!node->left && !node->right);
	assert(isdigit(node->data));
	return node->data - '0';
}

int calculate(const BTree<char>& exprTree) {
	using op = BTree<char>::Operations;
	stack<int> st;
	assert(exprTree.count() != 0);
	for (auto it = exprTree.begin(); it != exprTree.end(); ++it) {
		if (isdigit(*it)) {
			st.push(*it - '0');
		}
		else {
			char oper = *it;
			assert(oper == '+' || oper == '-' || oper == '*' || oper == '/');
			int rhs = st.top();
			st.pop();
			int lhs = st.top();
			st.pop();
			switch (static_cast<op>(oper)) {
			case op::add: st.push(lhs + rhs); break;
			case op::substitute: st.push(lhs - rhs); break;
			case op::multiply: st.push(lhs*rhs); break;
			case op::divide: st.push(lhs / rhs); break;
			}
		}
	}
	return st.top();
}

int calculate(const BTree<string>& exprTree) {
	using op = BTree<string>::Operations;
	stack<int> st;
	assert(exprTree.count() != 0);
	for (auto it = exprTree.begin(); it != exprTree.end(); ++it) {
		if (isdigit((*it)[0])) {
			st.push(stoi(*it));
		}
		else {
			assert((*it).length() == 1);
			char oper = (*it)[0];
			assert(oper == '+' || oper == '-' || oper == '*' || oper == '/');
			int rhs = st.top();
			st.pop();
			int lhs = st.top();
			st.pop();
			switch (static_cast<op>(oper)) {
			case op::add: st.push(lhs + rhs); break;
			case op::substitute: st.push(lhs - rhs); break;
			case op::multiply: st.push(lhs*rhs); break;
			case op::divide: st.push(lhs / rhs); break;
			}
		}
	}
	return st.top();
}
/// !!!!!!!!!!!!!!!!!!!!!!! E N D !!!!!!!!!!!!!!!!!!!!!!!!!!!!
void testIterator()
{
	BTree<int> t;

	t.insertBOT(59)
		.insertBOT(23)
		.insertBOT(68)
		.insertBOT(190)
		.insertBOT(41)
		.insertBOT(67);


	for (auto it = t.begin(); it != t.end(); ++it) {
			std::cout << *it << " ";
	}

	//assert(count == 6);

}



 /* int main() {
	BTree<char> t;
	t.add('+', "")
		.add('*', "L")
		.add('2', "LL")
		.add('3', "LR")
		.add('+', "R")
		.add('5', "RL")
		.add('0', "RR");
	t.prettyPrint();
	cout << endl << "Char expression tree result : " << t.calculate() << endl;
	cout << "Char expression tree result : " << calculate(t) << endl << endl;

	BTree<string> tStr;
	tStr.add("+", "")
		.add("*", "L")
		.add("2", "LL")
		.add("3", "LR")
		.add("+", "R")
		.add("15", "RL")
		.add("0", "RR");
	tStr.prettyPrint();
	cout << endl << "String expression tree result : " << calculate(tStr) << endl;
	cout << endl;
	BTree<int> t2;
	t2.insertBOT(59)
		.insertBOT(23)
		.insertBOT(68)
		.insertBOT(190)
		.insertBOT(17)
		.insertBOT(67);
	t2.prettiestPrint();
	cout << endl;
}*/

