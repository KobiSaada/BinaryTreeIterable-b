#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "BinaryTree.hpp"
using namespace ariel;

int main() {
  BinaryTree<int> tree_of_ints;
  int c ;
  std::cout<<"enter a num for the root: " <<std::endl;
  std::cin>>c;
  tree_of_ints.add_root(c);
  int l,r;
  std::cout<<"enter a num for left and right child first left :" <<std::endl;
  std::cin>>l;
  std::cin>>r;
  tree_of_ints.add_left(c,l);
  tree_of_ints.add_right(c,r);
  
   std::cout<<"how do u want to travers on tree press 1 for inorder 2 for postorder 3 for preorder :" << std::endl;
   int choose;
   std::cin>>choose;
   switch (choose)
   {
   case 1:
       for (auto it=tree_of_ints.begin_inorder(); it!=tree_of_ints.end_inorder(); ++it) {
    std::cout << (*it) <<std::endl;
    break;
  }  
     
     case 2 :
      for (auto it=tree_of_ints.begin_postorder(); it!=tree_of_ints.end_postorder(); ++it) {
    std::cout << (*it)  ;
    break;
  }  
    case 3 :
    for (auto it=tree_of_ints.begin_preorder(); it!=tree_of_ints.end_preorder(); ++it) {
    std::cout << (*it)  ;
    break;
  }  
   default:
     break;
   }
   std::cout <<std::endl;
std::cout<<"if u wnat to show the tree press 1 othernum for exit: "<<std::endl;
int s;
std::cin>>s;
switch (s)
{
case 1:
  std::cout<<tree_of_ints<<std::endl;
  break;
default:
  break;
}

   return 0;
}
