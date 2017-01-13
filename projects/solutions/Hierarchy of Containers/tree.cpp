#ifndef TREE_CPP
#define TREE_CPP


#include "listEl.cpp"
#include<stack>

template<typename T>
class TIterator;


template<typename T>
class BinTree:public ListEl<T>
{
private:
    Element<T>* root;
    int size;
    string dataType;

    void addEl(const T&,Element<T>*&);

    void eraseNode(Element<T>*);

    Element<T>* copyNode(Element<T>*);

    Element<T>* removeEl(Element<T>*,Element<T>*&,bool);

    using Condition = bool (*)(T const&);
    using ConditionI = bool (*)(int);
    using ConditionD = bool (*)(double);
    using ConditionB = bool (*)(bool);
    bool searchRec(Condition f,Element<T>* p) const;
    bool searchRec(ConditionI f,Element<T>* p) const;
    bool searchRec(ConditionD f,Element<T>* p) const;
    bool searchRec(ConditionB f,Element<T>* p) const;

    Element<T>* filterRec(Condition f,Element<T>* p,Element<T>*& parent,bool left);
    Element<T>* filterRec(ConditionI f,Element<T>* p,Element<T>*& parent,bool left);
    Element<T>* filterRec(ConditionD f,Element<T>* p,Element<T>*& parent,bool left);
    Element<T>* filterRec(ConditionB f,Element<T>* p,Element<T>*& parent,bool left);

    Element<T>* balance(vector<T>&,int start,int);
public:


    BinTree(string t = " "):size(0),root(NULL),dataType(t){}
    BinTree(const BinTree& t):size(t.size),dataType(t.dataType)
    {
        root=copyNode(t->root);
    }

    BinTree& operator=(const BinTree& t)
    {
        if(this!=&t)
        {
            eraseNode(root);
            root = copyNode(t->root);
            size = t.size;
            dataType = t.dataType;
        }
    }

    ~BinTree()
    {
        eraseNode(root);
    }

    bool empty() const
    {
        return root==NULL;
    }

    int getSize() const
    {
        return size;
    }

    void add(const T& x);

    T get();

    bool printNode(const Element<T>* t) const;

    void print(ofstream& f) const;

    Element<T>* begin() const
    {
        return root;
    }

    string getType() const
    {
        return "binTree";
    }

     bool member(T const& x) const;

     bool searchCond(Condition f) const
    {
        return searchRec(f,root);
    }

     bool searchCond(ConditionI f) const
    {
        return searchRec(f,root);
    }

     bool searchCond(ConditionD f) const
    {
        return searchRec(f,root);
    }

     bool searchCond(ConditionB f) const
    {
        return searchRec(f,root);
    }

    void filter(Condition f)
    {

        Element<T>* parent = new Element<T>(T(),root);
        root = filterRec(f,root,parent,true);
    }

    void filter(ConditionI f)
    {

        Element<T>* parent = new Element<T>(T(),root);
        root = filterRec(f,root,parent,true);
    }

    void filter(ConditionD f)
    {

        Element<T>* parent = new Element<T>(T(),root);
        root = filterRec(f,root,parent,true);
    }

    void filter(ConditionB f)
    {

        Element<T>* parent = new Element<T>(T(),root);
        root = filterRec(f,root,parent,true);
    }



    void sort();

    string getDataType() const
    {
        return dataType;
    }


};


template<typename T>
void BinTree<T>::addEl(const T& x,Element<T>*& p)
{

    if(p == NULL)
        p = new Element<T>(x);
    else
    {
        if(x<=p->data) addEl(x,p->prev);
        else
        addEl(x,p->next);

    }

}

template<typename T>
void BinTree<T>::eraseNode(Element<T>* p)
{
    if(p!=NULL)
    {
        eraseNode(p->prev);
        eraseNode(p->next);
        delete p;
    }
}

template<typename T>
Element<T>* BinTree<T>::copyNode(Element<T>* p)
{
   Element<T>* copy = NULL;
   if(p!=NULL)
   {
       copy=new Element<T>(p->data,copyNode(p->prev),copyNode(p->next));
   }
   return copy;
}

template<typename T>
Element<T>* BinTree<T>::removeEl(Element<T>* node,Element<T>*& parent,bool left)
{

    if(node == NULL) NULL ;

    if(node->prev == NULL)
    {

        if(left)
        parent->prev = node->next;
        else
        parent->next = node->next;

        delete node;
        return node->next;

    }
    else
    if(node->next == NULL)
    {

        if(left)
        parent->prev = node->prev;
        else
        parent->next = node->prev;

        delete node;
        return node->prev;
    }
    else
    {

        Element<T>* q = node->next;
        if(q->prev==NULL)
        {

            q->prev = node->prev;
            if(left)
                parent->prev = q;
            else
                parent->next = q;

            return q;

        }

        while(q->prev->prev != NULL)
        {

            q=q->prev;
        }


        Element<T>* par = q;
        q=q->prev;

        Element<T>* right = q->next;

        q->prev = node->prev;
        q->next = node->next;
        if(left)
            parent->prev = q;
        else
            parent->next = q;

        node->prev = NULL;
        node->next = right;
        par->prev = node;
        removeEl(node,par,true);

        return q;


    }

}


template<typename T>
bool BinTree<T>::searchRec(Condition f,Element<T>* p) const
{
    if(p==NULL) return false;
    if(f(p->data)) return true;
    return searchRec(f,p->prev)||searchRec(f,p->next);
}


template<typename T>
bool BinTree<T>::searchRec(ConditionI f,Element<T>* p) const
{
    if(p==NULL) return false;
    if(f(p->data)) return true;
    return searchRec(f,p->prev)||searchRec(f,p->next);
}

template<typename T>
bool BinTree<T>::searchRec(ConditionD f,Element<T>* p) const
{
    if(p==NULL) return false;
    if(f(p->data)) return true;
    return searchRec(f,p->prev)||searchRec(f,p->next);
}

template<typename T>
bool BinTree<T>::searchRec(ConditionB f,Element<T>* p) const
{
    if(p==NULL) return false;
    if(f(p->data)) return true;
    return searchRec(f,p->prev)||searchRec(f,p->next);
}



template<typename T>
Element<T>* BinTree<T>::filterRec(Condition f,Element<T>* p,Element<T>*& parent,bool left)
{

    if(p==NULL) return NULL;
    Element<T>* x = p;

    if(f(p->data))
    {

        x = removeEl(p,parent,left);
        return filterRec(f,x,parent,left);

    }
    else
    {
        filterRec(f,p->prev,p,true);
        filterRec(f,p->next,p,false);
        return p;
    }



}


template<typename T>
Element<T>* BinTree<T>::filterRec(ConditionI f,Element<T>* p,Element<T>*& parent,bool left)
{

    if(p==NULL) return NULL;
    Element<T>* x = p;
    if(f(p->data))
    {
        x = removeEl(p,parent,left);
        return filterRec(f,x,parent,left);

    }
    else
    {
        filterRec(f,p->prev,p,true);
        filterRec(f,p->next,p,false);
        return p;
    }


}


template<typename T>
Element<T>* BinTree<T>::filterRec(ConditionD f,Element<T>* p,Element<T>*& parent,bool left)
{

    if(p==NULL) return NULL;
    Element<T>* x = p;
    if(f(p->data))
    {
        x = removeEl(p,parent,left);
        return filterRec(f,x,parent,left);

    }
    else
    {
        filterRec(f,p->prev,p,true);
        filterRec(f,p->next,p,false);
        return p;
    }


}

template<typename T>
Element<T>* BinTree<T>::filterRec(ConditionB f,Element<T>* p,Element<T>*& parent,bool left)
{

    if(p==NULL) return NULL;
    Element<T>* x = p;
    if(f(p->data))
    {
        x = removeEl(p,parent,left);
        return filterRec(f,x,parent,left);

    }
    else
    {
        filterRec(f,p->prev,p,true);
        filterRec(f,p->next,p,false);
        return p;
    }


}



template<typename T>
Element<T>* BinTree<T>::balance(vector<T>& v,int start,int length)
{
    if(length == 0) return NULL;
    if(length == 1) return new Element<T>(v[start]);

    int mid = start+length/2;

    return new Element<T>(v[mid],balance(v,start,length/2),balance(v,mid+1,length/2+(length%2-1)));
}


template<typename T>
void BinTree<T>::add(const T& x)
{
    addEl(x,root);
    size++;
}

template<typename T>
T BinTree<T>::get()
{
    if(root == NULL) return T();
    Element<T>* p = root;

    if(root->prev != NULL)

    while(p->prev->prev!=NULL)
        p=p->prev;

    T x = p->prev->data;
    removeEl(p->prev,p,true);

    return x;
}


template<typename T>
bool BinTree<T>::printNode(const Element<T>* t) const
{
    if(t==NULL)
    {
        return false;
    }


    cout<<t->data<<"-> ";


    if(t->prev==NULL)
        cout<<". ";
    else
        cout<<t->prev->data<<" ";
    if(t->next==NULL)
        cout<<"."<<endl;
    else
        cout<<t->next->data<<endl;

    printNode(t->prev);
    printNode(t->next);


    return true;

}

template<typename T>
void BinTree<T>::sort()
{
    vector<T> v;
    v.resize(size);
    int i =0;
    for(TIterator<T> it(root);it;++it)
    {
        v[i]=*it;
        i++;
    }
    eraseNode(root);
    root = balance(v,0,size);
}



template<typename T>
void BinTree<T>::print(ofstream& f) const
{
    f<<getType()<<" ";
    f<<getDataType()<<" ";
    TIterator<T> i(root);
    while(i)
    {
        f<<*i<<" ";
        ++i;
    }
}

template<typename T>
bool BinTree<T>::member(T const& x) const
{

    Element<T>* p = root;
    while(p!=NULL)
    {

        if(p->data == x) return true;
        if(x < p->data) p=p->prev;
        else
            p=p->next;

    }

    return false;
}




template<typename T>
class TIterator:public ElIterator<T>{
private:
    stack<Element<T>*> s;
public:

    typedef ElIterator<T> P;

    TIterator(Element<T>* e = NULL)
    {
        Element<T>* p = e;
        if(p != NULL)
        {

            while(p->prev!=NULL)
            {
                s.push(p);
                p=p->prev;
            }
        }

        P::it = p;
        P::type = 't';
    }

    void next()
    {
        if(P::it==NULL) return ;
        Element<T>* tmp=P::it;

        if(P::it->next!=NULL)
        {

            Element<T>* tmp=P::it->next;
            s.push(tmp);
            while(tmp->prev!=NULL)
            {
                tmp=tmp->prev;
                s.push(tmp);
            }
            P::it=s.top();
            s.pop();

        }
        else
        {
            if(s.empty()) P::it=NULL;
            else{
            P::it=s.top();
            s.pop();
            }
        }
    }

    TIterator& operator++()
    {
        next();

        return *this;

    }

    TIterator operator++(int i)
    {
        TIterator copy(P::it);
        next();
        return copy;
    }



};




#endif

