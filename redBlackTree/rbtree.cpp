// rbtree.cpp 
/*
Student name: Pooja Shende

Functions used in this file are
1) RBTree()
2) ~RBTree()
3) void rbInsert(const string& key, const string& value)
4) void rbDelete(const string& key, const string& value)
5) vector<const string*> rbFind(const string& key)
6) void rbPrintTree()
7) Node()
8) Node(const string&, const string&, Node*)
9) ~Node()
10) void postOrderDelete(Node*)
also all the private mutators and accessors to implement delete and insert
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

/*
Desc: Node() is a default constructor of Node class which sets pointers of
parent, left and right to NULL value, also sets color variable to 'B' i.e.
black.
I/P: N/A
O/p: N/A
*/
RBTree::Node::Node()
{
   parent = NULL;
   left = NULL;
   right = NULL;
   color = 'B';
}

/*
Desc: Node() is a parameterized constructor of Node class which sets assigns
nil node to the nodes-parent, left and right, also new or updated key and
value of string type is created by allocating new memory for both of them
using new operator. 
I/P: N/A
O/p: N/A
*/
RBTree::Node::Node(const string& k, const string& v, Node* nil)
{
   key = new string(k);
   value = new string(v);
   parent = nil;
   left = nil;
   right = nil;   
}

/*
Desc: RBTree() is a constructor of RBTree class which creates nil node, and
assigns that node to root.
I/P: N/A
O/p: N/A
*/
RBTree::RBTree()
{
   nil = new Node();
   root = nil;
}

/*
Desc: ~RBTree() is a destructor of RBTree class which deletes all the nodes
present in a red black tree using postorder traversal. So, in this function
postOrderDelete() is called.
I/P: N/A
O/p: N/A
*/
RBTree::~RBTree()
{
   Node * node=root;
   postOrderDelete(node);
   delete nil;
}

/*
Desc: ~Node() is a destructor of Node class which deletes key and value or
satellite data.
I/P: N/A
O/p: N/A
*/
RBTree::Node::~Node()
{
   delete key;
   delete value;
}

/*
Desc: postOrderDelete() is used to delete entire red black tree using
postorder traversal. Traversal is done until all the nodes get deleted.
I/P: N/A
O/p: node of a tree of *node type
*/
void RBTree::postOrderDelete(Node *node)
{

   if(node !=nil)
   {
      postOrderDelete( node->left );
      postOrderDelete( node->right ); 
      delete node;
   }  
}

/*
Desc: reverseInOrderPrint function is used to print all nodes of red black
tree using inorder traversal in reverse manner.
I/P: pointer to the node, and depth of a tree of integer type
O/P: N/A
*/
void RBTree::reverseInOrderPrint(Node *x, int depth) 
{
   if ( x != nil ) 
   {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/*
Desc: This function is used to call reverseInOrderPrint().
I/P: N/A
O/P: N/A
*/
void RBTree::rbPrintTree()
{
   reverseInOrderPrint(root, 0);
}

/*
Desc: constructor of a node is called inside rbInsert() to create a new
node, and this node is then inserted in a tree using rbInsert() which
takes newly created node as a parameter.
I/P: key and value, both of string type
O/P: N/A
*/
void RBTree::rbInsert(const string& key, const string& value)
{
   Node *node = new Node(key, value, nil);
   rbInsert(node);
}

/*
Desc: rbDelete() is used for deletion of a node in a tree. It calls rbDelete()
which takes a node to be deleted as a parameter.
I/P: key and value of string type
O/P: N/A
*/
void RBTree::rbDelete(const string& key, const string& value)
{
   Node *node, *predecessor, *successor, *node1;
   bool predecessorfound=false,successorfound=false;
   while((node = rbTreeSearch(root, key))!=nil)
   {
      if(value == *(node->value))
      {
         rbDelete(node);
         delete node;
      }
      else
      {
         predecessorfound=false;
         node1=node;
         while((predecessor = rbTreePredecessor(node1))!=nil)
         {  if(key==*(predecessor->key))
            {
               if(value == *(predecessor->value))
               {
                  rbDelete(predecessor);
                  predecessorfound=true;
                  delete predecessor;
                  break;
               }
               node1=predecessor;
            }
            else
               break;
         }
         if(!predecessorfound)
         {
            successorfound=false;
            node1=node;
            while((successor = rbTreeSuccessor(node1))!=nil)
            {  if(key==*(successor->key))
               {
                  if(value == *(successor->value))
                  {
                     rbDelete(successor);
                     successorfound=true;
                     delete successor;
                     break;
                  }
                  node1=successor;
               }
               else
                  break;
            }
         }
         if(!successorfound && !predecessorfound)
            break;
      }
   }   
}

/*
Desc: rbFind() is used to find data corresponding to a particular key.
For this, this function traverse entire tree using successor and predecessor.
I/P: key of string type
O/P: vector of type string pointer that contains value 
*/
vector<const string*> RBTree::rbFind(const string& key)
{
   vector<const string*> result;
   Node *node, *predecessor, *successor, *node2;
   node = rbTreeSearch(root, key);
   node2 = node;
   if(node!=nil)
   {
      result.push_back(node->value);
      while((predecessor = rbTreePredecessor(node))!=nil)
      {
         if(key == *(predecessor->key))
         {  
            result.push_back(predecessor->value);
            node = predecessor;
         }
         else if(key != *(predecessor->key))
            break;
      }

      while((successor = rbTreeSuccessor(node2))!=nil)
      {
         if(key == *(successor->key))
         {
            result.push_back(successor->value);
            node2 = successor;
         }
         else if(key != *(successor->key))
            break;
      }
   }
   
   return result;
}

/*
Desc: rbTreeSearch() is used to find a satellite data corresponding to the
key, and for that it traverse the entire tree, including left subtree,
right subtree.
I/P: key of input command, and node of a tree
O/P: nodde of a red black tree of pointer type 
*/
RBTree::Node* RBTree::rbTreeSearch(Node* node, const string& key)
{

   while(node!=nil)
   {
      if(key < *(node->key))
         node = node->left;
      else if(key > *(node->key))
         node = node->right;
      else if(key == *(node->key))
         return node;
   }  
   return node;
}

/*
Desc: rbInsert() is used to insert a new node in a red black tree, by 
comparing it with the value of left or right child, and replaces accordingly.
I/P: newly inserted node of node pointer
O/P: N/A 
*/

void RBTree::rbInsert(Node* node)
{
   Node *x, *y;
   y = nil;
   x = root;
   while(x!=nil)
   {
      y=x;
      if(*(node->key)<*(x->key))
      {
         x=x->left;
      }
      else
      {
         x=x->right;
      }
   } 

   node->parent=y;//assigns y to the parent of newly inserted node
   if(y == nil)
   {
      root = node;
   }
   else if (*(node->key) < *(y->key))
   {
      y->left=node;
   }
   else
   {
      y->right=node;
   }
   node->left = nil;
   node->right = nil;
   node->color = 'R';

   rbInsertFixup(node);

}

/*
Desc: rbInsertFixup() is used to balance a red black tree after the insertion
of new node. 
I/P: newly inserted node
O/P: N/A 
*/

void RBTree::rbInsertFixup(Node *node)
{
   Node *y;
   while (node->parent->color=='R')
   {
      if(node->parent==node->parent->parent->left)
      {
         y=node->parent->parent->right;      
         if(y->color=='R') 
         {
            node->parent->color='B';
            y->color='B';
            node->parent->parent->color='R';
            node=node->parent->parent;
         }
         else if(node==node->parent->right)
         {
            node=node->parent;
            leftRotate(node);
         }
         else
         {
            node->parent->color='B';
            node->parent->parent->color='R';
            rightRotate(node->parent->parent);
         }

      }
      else
      {
         y=node->parent->parent->left;

         if(y->color=='R')
         {
            node->parent->color='B';
            y->color='B';
            node->parent->parent->color='R';
            node=node->parent->parent;
         }
         else if(node==node->parent->left)
         {
            node=node->parent;
            rightRotate(node);
         }
         else
         {
            node->parent->color='B';
            node->parent->parent->color='R';
            leftRotate(node->parent->parent); 
         }  
      }
   }//end while loop

   root->color='B';
}

/*
Desc: After insertion of a new node, if the tree is not balanced then left
rotation of that particular subtree is done.
I/P: node of node pointer type
O/P: N/A
 */
void RBTree::leftRotate(Node *x)
{  
   Node *y;
   y=x->right;
   x->right=y->left;

   if (y->left != nil)
   {
      y->left->parent=x;
   }
   y->parent = x->parent;

   if (x->parent == nil)
   {
      root=y;
   }
   else if(x == x->parent->left) 
   {
      x->parent->left=y;
   }
   else
   {
      x->parent->right=y;
   }
   y->left=x;
   x->parent=y;

}

/*
Desc: After insertion of a new node, if the tree is not balanced then right
rotation of that particular subtree is done.
I/P: node of node pointer
O/P: N/A
 */

void RBTree::rightRotate(Node *x)
{  
   Node *y;
   y=x->left;
   x->left=y->right;

   if (y->right != nil)
   {
      y->right->parent=x;
   }
   y->parent = x->parent;

   if (x->parent == nil)
   {
      root=y;
   }
   else if(x == x->parent->right) 
   {
      x->parent->right=y;
   }
   else
   {
      x->parent->left=y;
   }
   y->right=x;
   x->parent=y;

}

/*
Desc: rbTreeMinimum() returns a node with minimum value by traversing the
left subtree.
I/P: node of node pointer type
O/P: node of node pointer type
*/
RBTree::Node* RBTree::rbTreeMinimum(Node *x)
{
   while(x->left!=nil)
   {
      x=x->left;
   }
   return x;
}

/*
Desc: rbTreeMaximum() returns a node with maximum value by traversing the
right subtree.
I/P: node of node pointer type
O/P: node of node pointer type
*/
RBTree::Node* RBTree::rbTreeMaximum(Node *x)
{

   while(x->right!=nil)
   {
      x=x->right;
   }
   return x;
}

/*
Desc: rbTreeSuccessor() traverse right subtree and returns successor.
I/P: node of node pointer type
O/P: node of node pointer type
*/
RBTree::Node* RBTree::rbTreeSuccessor(Node *x)
{
   Node *y;
   if(x->right!=nil)
      return rbTreeMinimum(x->right);
   y=x->parent;
   while(y!=nil && x==y->right)
   {
      x=y;
      y=y->parent;
   }
   return y;
}

/*
Desc: rbTreeSuccessor() traverse right subtree and returns predecessor.
I/P: node of node pointer type
O/P: node of node pointer type
*/
RBTree::Node* RBTree:: rbTreePredecessor(Node *x)
{
   Node *y;
   if(x->left!=nil)
      return rbTreeMaximum(x->left);
   y=x->parent;
   while(y!=nil && x==y->left)
   {
      x=y;
      y=y->parent;
   }
   return y;

}

/*
Desc: rbDelete() delets a particular node from the tree and calls 
rbTransplant(), rbDeleteFixup() functions.
I/P: node that is to be deleted
O/P: N/A
*/
void RBTree::rbDelete(Node *z)
{  
   Node *y;
   Node *x;
   y=z;
   char original_color=y->color;

   if(z->left==nil)
   {
      x=z->right;
      rbTransplant(z,x);
   }
   else if(z->right==nil)
   {
      x=z->left;
      rbTransplant(z,x);
   }
   else
   {
      y=rbTreeMaximum(z->left);
      original_color=y->color;
      x=y->left;
      if(y->parent==z)
         x->parent=y;
      else
      {
         rbTransplant(y,x);
         y->left=z->left;
         y->left->parent=y;
      }
      rbTransplant(z,y);
      y->right=z->right;
      y->right->parent=y;
      y->color=z->color;
   }
   if(original_color=='B')
      rbDeleteFixup(x);
}

/*
Desc: After deletion of the node, this function is used to fixup or balance
a tree.
I/P: node that is to be deleted
O/P: N/A
*/
void RBTree:: rbDeleteFixup(Node *x)
{
   Node *w;

   {
      while(x!=root && x->color=='B')
      {
         if(x==x->parent->left)
         {
            w=x->parent->right;
            if(w->color=='R')
            {
               w->color='B';
               x->parent->color='R';
               leftRotate(x->parent);//calling left rotate
               w=x->parent->right;
            }
            if((w->left->color=='B') && (w->right->color=='B'))
            {
               w->color='R';
               x=x->parent;
            }
            else if(w->right->color=='B')
            {
               w->left->color='B';
               w->color='R';
               rightRotate(w);//call to rightRotate()
               w=x->parent->right;
            }             
            else
            {
               w->color=x->parent->color;
               x->parent->color='B';
               w->right->color='B';
               leftRotate(x->parent);//call to leftRotate()
               x=root;
            }
         }
         else
         {
            w=x->parent->left;
            if(w->color=='R')
            {
               w->color='B';
               x->parent->color='R';
               rightRotate(x->parent);//call to rightRotate()
               w=x->parent->left;
            }
            if((w->right->color=='B') && (w->left->color=='B'))
               //if right, left children are black then make their parent red
            {
               w->color='R';
               x=x->parent;
            }
            else if(w->left->color=='B')
            {
               w->right->color='B';
               w->color='R';
               leftRotate(w);//call to leftRotate()
               w=x->parent->left;
            }
            else
            {
               w->color=x->parent->color;
               x->parent->color='B';
               w->left->color='B';
               rightRotate(x->parent);//call to rightRotate()
               x=root;
            } 

         } 
      }// while loop ends here
   }
   x->color='B';
}

/*
Desc: After deletion of a node, this function helps in balancing or fixing
red black tree up.s
I/P: two nodes of node pointer type
O/P: N/A
*/
void RBTree:: rbTransplant(Node* u, Node* v)
{
   if(u->parent==nil)
   {
      root=v;
   }
   else if(u==u->parent->left)
   {
      u->parent->left=v;
   }
   else
   {
      u->parent->right=v;
   }
   v->parent=u->parent;
}

