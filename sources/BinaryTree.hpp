//#pragma once
#include <iostream>
#include <sstream>

using namespace std;

#include <queue> 
namespace ariel
{
    
// Used to identify the order you wish to traverse on tree
enum Order {POST_ORDER, IN_ORDER, PRE_ORDER};
            //  0           1          2

   
    template<typename T>
    class BinaryTree {
    
    private:
    struct Node {
        T value;
        Node* right;
        Node* left;
        Node(const T& v, Node* L= nullptr, Node* R= nullptr,Node* p=nullptr)
                : value(v), left(L),right(R){
        }
       
    	 // ~Node(){delete left;delete right;}
          T & get_data(){return this->value;}
        



   

    };
    //End class Node

    class iterator {
    private:
     queue<Node*> iterArr; 
         Node* p_currNode;
         unsigned int depth=0;
         
    public:
     iterator(Node* n,Order traverseOrder);
    unsigned int get_depth() const{
        return depth;
    }
        T& operator*() const {
            
            return p_currNode->value;
        }
        T* operator->() const {
            return &(p_currNode->value);
        }
            iterator &operator++(){//prefix
            p_currNode =iterArr.front();
            iterArr.pop();
             return *this;}
            iterator operator++(int){//posfix
            iterator temp = *this;
            p_currNode=iterArr.front();
            iterArr.pop();
             return temp;}
            bool operator==(const iterator &rhs) const{
             return p_currNode==rhs.p_currNode;
    }
            bool operator!=(const iterator &rhs) const{
             return p_currNode!=rhs.p_currNode;
            }
      

    };  // END OF CLASS ITERATOR

  //  bool Contains(T value);
    static void cleanQ(queue<Node*> printQueue);
    static void PlacePreOrder(Node** node,queue<Node*> &printQueue);
    static void PlacePostOrder(Node** node,queue<Node*> &printQueue);
    static void PlaceInOrder(Node** node,queue<Node*> &printQueue);
    T GetNextItem(queue<T> printQueue);
    
    Node* _root;
   // int numNodes;

    public:
     BinaryTree() : _root(nullptr){};
    ~BinaryTree(){
        if(_root!=nullptr){
        delete _root;
        }}
        Node *get_root();
        Node *FindNode(Node *root, T key);
        BinaryTree<T> & add_root(T root);
        BinaryTree<T> & add_left(T val ,T node);
        BinaryTree<T> & add_right(T val ,T node);

       
         void Copy_tree(Node *thistree, const Node *othertree) {
            if (othertree->left != nullptr) {
                thistree->left = new Node(othertree->left->value);
                Copy_tree(thistree->left, othertree->left);
            }
            if (othertree->right != nullptr) {
                thistree->right = new Node(othertree->right->value);
                Copy_tree(thistree->right, othertree->right);
            }
        }  


        BinaryTree &operator=(const BinaryTree<T> bt) {
            if (this == &bt) {
                return *this;
            }
            if (_root != nullptr) {
                delete _root;
            }
            if (bt._root != nullptr) {
                _root = new Node(bt._root->value);
                Copy_tree(_root, bt._root);
            }
            return *this;
        }

        BinaryTree(const BinaryTree &bt) { //copy tree
            if (bt._root != nullptr) {
                this->_root = new Node(bt._root->value);
                Copy_tree(_root, bt._root);
            }
        }
        BinaryTree& operator=(BinaryTree<T>&& bt) noexcept {
            if (_root){ delete _root;}
            _root  = bt._root;
            bt._root = nullptr;
            return *this;
        }

        BinaryTree(BinaryTree &&bt)  noexcept {
            this->_root = bt._root;
            bt._root=nullptr;
        }
        
        iterator begin()
        {
            
            return  begin_inorder();
        }
        iterator end()
        {
            
            return end_inorder();
        }

        iterator end_preorder()
        {
            return iterator(nullptr,PRE_ORDER);
        }
        iterator begin_preorder()
        {
            return iterator(_root,PRE_ORDER);
        }
        iterator end_inorder()
        {
            return iterator(nullptr,IN_ORDER);
        }
        iterator begin_inorder()
        {
            return  iterator(_root,IN_ORDER);

        }
        iterator end_postorder()
        {
            return iterator(nullptr,POST_ORDER);
        }
        iterator begin_postorder()
        {
            return iterator(_root,POST_ORDER);
        }

    //from stackoverfllow
    //print a pretty tree
 static ostream & printSubtree(std::ostream & out,Node* root, const string& prefix)
{
        if (root == NULL)
        {
                return out;
        }

        bool hasLeft = (root->left != NULL);
        bool hasRight = (root->right != NULL);

        if (!hasLeft && !hasRight)
        {
                return out;
        }

        out << prefix;
        out << ((hasLeft  && hasRight) ? "├── " : "");
        out << ((!hasLeft && hasRight) ? "└── " : "");

        if (hasRight)
        {
                bool printStrand = (hasLeft && hasRight && (root->right->right != NULL || root->right->left != NULL));
                string newPrefix = prefix + (printStrand ? "│   " : "    ");
                out << root->right->value << endl;
                printSubtree(out,root->right, newPrefix);
        }

        if (hasLeft)
        {
                out << (hasRight ? prefix : "") << "└── " << root->left->value << endl;
                printSubtree(out,root->left, prefix + "    ");
        }
        return out;
}
      friend std::ostream & operator << (std::ostream & out , const BinaryTree<T> & btree) {
out<<endl;
out<<"The Binary Tree :"<<endl;
        if (btree._root == NULL)
        {
                return out;
        }

        out << btree._root->value << endl;
        printSubtree(out,btree._root, "");
        out << endl;
    
    return out;
}
//tostring T val
static string tostring(T const& t){
    std::ostringstream oss;
    oss<<t;
    return oss.str();

}

    };

///////****Implemntion****/////////



template<typename T>
T BinaryTree<T>::GetNextItem(queue<T> printQueue) {
    T value = printQueue.front();  // Top, peek, front
    printQueue.pop();
    return value;
}
template<typename T> 
void BinaryTree<T>::cleanQ(queue<Node*> printQueue){
    while(!printQueue.empty()){
    printQueue.pop();
    }
}


template<typename T>
void BinaryTree<T>::PlacePreOrder(Node **node,queue<Node*> &printQueue) {
    if (*node == nullptr){
        return;}
    printQueue.push(*node);
    PlacePreOrder(&(*node)->left,printQueue);
    PlacePreOrder(&(*node)->right,printQueue);
}

template<typename T>
void BinaryTree<T>::PlacePostOrder(Node **node,queue<Node*> &printQueue) {
    if (*node == nullptr){
        return;}
        
    PlacePostOrder(&(*node)->left,printQueue);
    PlacePostOrder(&(*node)->right,printQueue);
    printQueue.push(*node);

    cout<<endl;

}

template<typename T>
void BinaryTree<T>::PlaceInOrder(Node **node,queue<Node*> &printQueue) {
    if (*node == nullptr){
        return;}
    PlaceInOrder(&(*node)->left, printQueue);
    printQueue.push(*node);
    PlaceInOrder(&(*node)->right,printQueue);
   
    
}
template<typename T>
BinaryTree<T>::iterator::iterator(Node* n,Order traverseOrder){
    
    if (traverseOrder == IN_ORDER){
     //   cout<<"im a it inOrder "<<endl;
        PlaceInOrder(&n,iterArr);
    }
    else if (traverseOrder == POST_ORDER){
     //   cout<<"im a it post " + tostring(n->value)<<endl;
        PlacePostOrder(&n,iterArr);}
    else if (traverseOrder == PRE_ORDER){
     //    cout<<"im a it pre " <<  tostring(n->value)<<endl;
        PlacePreOrder(&n,iterArr);}
        iterArr.push(nullptr);
        p_currNode=iterArr.front();
       // cout<<(iterArr.size())<<endl;
        iterArr.pop();
      // cout<<(iterArr.size())<<endl;

        
 }


   template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_root(T root)
    {
        if (_root == nullptr){
            _root = new Node(root);
       // numNodes++;
        }
        
                _root->value = root;
            return *this;
        }

 template <typename T>
    typename BinaryTree<T>::Node *BinaryTree<T>::get_root()
    {
        if (this->_root)
        {
            return this->_root;
        }
        throw("there is no root for this tree");
    }

     template <typename T>
     typename BinaryTree<T>::Node* BinaryTree<T>:: FindNode(BinaryTree::Node *root ,T key) {
        if(!root) {return nullptr;}
        if(root->value == key) {return root;}
        // find the key in leftside
        Node* found = FindNode(root->left,key);
        if(found) {return found;}
        // otherwise find in rightside
        return FindNode(root->right,key);
        
    }

   template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(T val, T node)
   {
     Node *n = FindNode(_root, val);
        if (n == nullptr) {
            throw std::invalid_argument(
                    "Error: value is not exist in this tree.\n");
        }
        if (n->left == nullptr) {
            n->left = new Node(node);//new
           // numNodes++;
           
        } else {
            n->left->value = node;//change value
           
            
        }
        return *this;
    }


    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(T val ,T node)
    {
      if (_root == nullptr){throw invalid_argument("there is no root it this tree");}
       Node *n = FindNode(_root, val);
        if (n == nullptr) {
            throw std::invalid_argument(
                    "Error: this value is not exist in this tree.\n");
        }
        if (n->right == nullptr) {
            n->right = new Node{node};
          //  numNodes++;
            
        } else {
            n->right->value = node;
           
        }
        return *this;
    }



}