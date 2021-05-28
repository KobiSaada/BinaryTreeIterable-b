//#pragma once
#include <iostream>
#include <sstream>

using namespace std;

#include <queue> // stl library
#include <stack> 
namespace ariel
{
    
// Used to identify the order you wish to traverse the tree
enum Order {POST_ORDER, IN_ORDER, PRE_ORDER};
            //  0           1          2

   
    template<typename T>
    class BinaryTree {
    
     

    private:
    struct Node {
        T value;
        Node *parent;;
        Node* right;
        Node* left;
        Node(const T& v, Node* L= nullptr, Node* R= nullptr,Node* p=nullptr)
                : value(v), left(L),right(R),parent(p) {
        }
       
    	  ~Node(){delete left;delete right;}
          T & get_data(){return this->value;}
          Node(const Node& other)//copy constractur
:left(nullptr),
 right(nullptr),
 value(other.value)
{
    if (other.left != nullptr )
    {
        left = new Node(*other.left);
    }
    if (other.right != nullptr)
    {
        right = new Node(*other.right);
    }
}

Node& operator=(const Node& other)
{
    value = other.value;

    Node * l = left;
    left = new Node(*other.left);
    delete l;

    Node * r= right;
    right = new Node(*other.right);
    delete r;

    return *this;
}

        // Node(Node&other){ CopyHelper(this,*other); }


          Node(Node &&other) noexcept {
                value = other.value;
                right = other.right;
                other.right = nullptr;
                left = other.left;
                other.left = nullptr;
            }

         
     void CopyHelper(Node* &thisTree,Node * otherTree) {
    if (!otherTree) {
        thisTree = nullptr;
        return;
    }

    thisTree = new Node(otherTree->value);
   // thisTree ->value = otherTree->value;
    CopyHelper(thisTree ->left, otherTree->left);
    CopyHelper(thisTree ->right, otherTree->right);
}
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
            iterator &operator++();
            const iterator operator++(int);
            bool operator==(const iterator &rhs) const;
            bool operator!=(const iterator &rhs) const;
      

    };  // END OF CLASS ITERATOR

    bool Contains(T value);
    static void cleanQ(queue<Node*> printQueue);
    static void PlacePreOrder(Node** node,queue<Node*> &printQueue);
    static void PlacePostOrder(Node** node,queue<Node*> &printQueue);
    static void PlaceInOrder(Node** node,queue<Node*> &printQueue);
    T GetNextItem(queue<T> printQueue);
    Node* _root;
    int numNodes;

    public:
     BinaryTree() : _root(nullptr){};
    ~BinaryTree(){delete _root;};
    

        BinaryTree(BinaryTree &other)  noexcept {
            numNodes = other.numNodes ;
            _root = new Node(other._root->value);
            other._root = nullptr;
        }


        BinaryTree &operator=(const BinaryTree &&otherBST) noexcept {
    if (this != &otherBST) {
        if (_root) {
            stack <Node*> nodeStack;
            nodeStack.push(_root);

            Node *currentNode = nullptr;
            while (!nodeStack.empty()) {
                currentNode = nodeStack.top();
                nodeStack.pop();

                if (currentNode->right) {
                    nodeStack.push(currentNode->right);
                }
                if (currentNode->left) {
                    nodeStack.push(currentNode->left);
                }

                delete currentNode;
                currentNode = nullptr;
            }
            cout << _root << endl; // This is where it seems like root is not being deleted correctly/nullptr'd.
        }

        _root = move(otherBST.root);
        otherBST.root = nullptr;
    }
    else {
        cout << "ERROR: Cannot assign to self." << endl;
    }

    return *this;
}

        Node *get_root();
        Node *FindNode(Node *n, T nodeValue);
        BinaryTree<T> & add_root(T root);
        BinaryTree<T> & add_left(T node, T l);
        BinaryTree<T> & add_right(T node, T r);
     
    
        
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
        //num of childs of some node
       int numOfChilds(Node* current) const {
        int num = 0;
        if(current->left && current->right) {num = 2; return num;}
        if(current->left || current->right) {num = 1; return num;}
        return num;
    }

static void print_queue(queue<Node*> q)//print queue
{
    int i=0;
  while (!q.empty())
  {
      cout<<i<<endl;
    tostring((q.front())->value);
    q.pop();
  }
  i++;
  std::cout << std::endl;
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
    while(!printQueue.empty())
    printQueue.pop();
}


template<typename T>
void BinaryTree<T>::PlacePreOrder(Node **node,queue<Node*> &printQueue) {
    if (*node == nullptr)
        return;
    printQueue.push(*node);
    PlacePreOrder(&(*node)->left,printQueue);
    PlacePreOrder(&(*node)->right,printQueue);
}

template<typename T>
void BinaryTree<T>::PlacePostOrder(Node **node,queue<Node*> &printQueue) {
    if (*node == nullptr)
        return;
        
    PlacePostOrder(&(*node)->left,printQueue);
    PlacePostOrder(&(*node)->right,printQueue);
    printQueue.push(*node);

    cout<<endl;

}

template<typename T>
void BinaryTree<T>::PlaceInOrder(Node **node,queue<Node*> &printQueue) {
    if (*node == nullptr)
        return;
    PlaceInOrder(&(*node)->left, printQueue);
    printQueue.push(*node);
    PlaceInOrder(&(*node)->right,printQueue);
   
    
}
template<typename T>
BinaryTree<T>::iterator::iterator(Node* n,Order traverseOrder){
     // cleanQ(iterArr);
  
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
        if (_root == nullptr){_root = new Node(root);}
            else{_root->value = root;}
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
            n->left = new Node(node);
           
        } else {
            n->left->value = node;
            
        }
        return *this;
    }


    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(T val, T node)
    {
      if (_root == nullptr){throw invalid_argument("there is no root it this tree");}
       Node *n = FindNode(_root, val);
        if (n == nullptr) {
            throw std::invalid_argument(
                    "Error: this value is not exist in this tree.\n");
        }
        if (n->right == nullptr) {
            n->right = new Node{node};
            
        } else {
            n->right->value = node;
           
        }
        return *this;
    }
    template<class T>
bool BinaryTree<T>::Contains(T value) {
    Node* curr = _root;

    while(curr != nullptr) {
        if (value == curr->value) {
            return true;
        }
        else if (value < curr->value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return false;
}
template<typename T>
    bool ariel::BinaryTree<T>::iterator::operator==(
            const ariel::BinaryTree<T>::iterator &rhs) const {
        return p_currNode==rhs.p_currNode;
    }

    template<typename T>
    bool ariel::BinaryTree<T>::iterator::operator!=(
            const ariel::BinaryTree<T>::iterator &rhs) const {
        return p_currNode!=rhs.p_currNode;;
    }

    template<typename T>
    const typename BinaryTree<T>::iterator BinaryTree<T>::iterator::operator++(int) {
        iterator temp = *this;
        p_currNode=iterArr.front();
        iterArr.pop();
        return temp;
    }

    template<typename T>
    typename BinaryTree<T>::iterator &BinaryTree<T>::iterator::operator++() {
        p_currNode =iterArr.front();
        iterArr.pop();
        return *this;
    }



}