#include"doublylinkedlist.h"


/*
I/P: NA
Desc: Constructor of a doubly linked list is used to initialize
      a new node. In this, head i.e. first node, tail i.e. last
      node, and current node are initialized to NULL.
O/P: NA
*/
DoublyLinkedList :: DoublyLinkedList()
{
	head = NULL;
	tail = NULL;
	current = NULL;
}

/*
I/P: NA
Desc: In the destructor of a doubly linked list all the nodes present
      in the dll are removed. We delete all the nodes by traversing entire
      dll. We take head node in a temporary node, we delete that temp node,
      and point next pointer of the head to the next node.
O/P: NA
*/
DoublyLinkedList :: ~DoublyLinkedList()
{
	while(head != NULL)
	{
	  Node* n = head;
	  head = head->next;
	  delete n;
	}
}

/*
I/P: NA
Desc: Constructor of a node is used to initialize node variables.
      Therefore, in this, next, prev and data are initialized to NULL.
O/P: NA
*/
DoublyLinkedList :: Node :: Node()
{
	next = NULL;
	prev = NULL;
	data = NULL;
}

/*
I/P: NA
Desc: When we delete a node, destructor of a node is also called. In
      this, previous and next node pointers are made NULL, and deletion
      of data is also done.
O/P: NA
*/
DoublyLinkedList :: Node :: ~Node()
{	
	prev=NULL;
	next=NULL;
	delete prev;
	delete next;
	delete data;
}

/*
I/P: next and prev node pointers, and data of string pointer type
Desc: This is a parameterized constructor of node in which next, prev
      node pointers, and data is passed as parameters. We are set values
      to the next, prev and data which we are passing through parametrs
      to create object.
O/P: NA
*/
DoublyLinkedList :: Node :: Node(Node *nextVal, Node *prevVal, string *dataVal)
{
	next = nextVal;
	prev = prevVal;
	data = new string(*dataVal);
}

/*
I/P: NA
Desc: empty() checks whether dll is empty or not. If the head is NULL i.e.
      dll is empty, then this function will return true value else false.
O/P: boolean value of true or false
*/
bool DoublyLinkedList :: empty()
{
	if (head == NULL)
	  return true;
	else
	  return false;
}

/*
I/P: NA
Desc: This function shows that current song is the first song in the list.
      So we set current pointer to the first node i.e. head.
O/P: NA
*/
void DoublyLinkedList :: begin()
{
	current = head;
}

/*
I/P: NA
Desc: This function shows that current song is the last song in the list.
      So we set current pointer to the last node i.e. tail.
O/P: NA
*/
void DoublyLinkedList :: end()
{
	current = tail;
}

/*
I/P: NA
Desc: prev() checks whether the previous node is present in dll.
      If it is present then this function will return true boolean
      value else false value. And current pointer is set to its 
      previous node.
O/P: boolean value true or false
*/
bool DoublyLinkedList :: prev()
{
	if (current->prev == NULL)
	{
	  return false;
	}
	else
	{
	  current = current->prev;
	  return true;
	}
	
}

/*
I/P: NA
Desc: next() checks whether the next node is present in dll.
      If it is present then this function will return true boolean
      value else false value. And current pointer is set to its 
      next node.
O/P: boolean
*/
bool DoublyLinkedList :: next()
{
	if (current->next == NULL)
	{
	  return false;
	}
	else
	{
	  current = current->next;
	  return true;
	}
			
}

/*
I/P: NA
Desc: This function is returning data of current node as well as printing
      the same i.e. current node value.
O/P: current data of string type
*/
const string& DoublyLinkedList :: getData()
{
	string* tempCurrent;
	tempCurrent = current->data;
	cout<< *tempCurrent << endl;
	return *tempCurrent;
}

/*
I/P: node data which we want to append in the dll.
Desc: This function inserts a node at the end of the list.If head is NULL
      then newly inserted node will be only one nodein the list otherwise 
      newly inserted node will be the last node in the list, and in that
      case, we will set next of the newly node to NULL. And it will again 
      be a current node.
O/P: NA
*/
void DoublyLinkedList :: append(string &inputLine)
{
	if (head == NULL)
	{	
  	  head = new Node(NULL, NULL, &inputLine);
	  tail = head;
	  current = head;
	}
	else
	{
	  tail->next = new Node(NULL, tail, &inputLine);
	  tail = tail->next;
	  current = tail;
	  
	}
}

/*
I/P: node data which we want to insert before current node in the dll.
Desc: This function inserts a node before the current node. If head is NULL
      newly inserted node is the only one in the list so it is head, tail and
      current node. If prev of a current node is NULL then newly inserted node
      becomes head and current node.  
O/P: NA
*/
void DoublyLinkedList :: insertBefore(string &str1)
{
	Node *nodeBefore;
	if (head == NULL)
	{	
  	  head = new Node(NULL, NULL, &str1);
	  tail = head;
	  current = head;
	}
	else if (current->prev == NULL)
	{
	  nodeBefore = new Node(head, NULL, &str1);
	  head->prev = nodeBefore;
	  head = nodeBefore;
	  current = nodeBefore;
	}
	else
	{
	  nodeBefore = new Node(current, current->prev, &str1);
	  nodeBefore->prev->next = nodeBefore;
	  current->prev = nodeBefore;
	  current = nodeBefore;  
	}
}

/*
I/P: node data which we want to insert after current node in the dll.
Desc: This function inserts a node after the current node. If head is NULL
      newly inserted node is the only one in the list so it is head, tail and
      current node. If next of a current node is NULL then newly inserted node
      becomes tail and current node.  
O/P: NA
*/
void DoublyLinkedList :: insertAfter(string &str2)
{
	Node *nodeAfter;
	if (head == NULL)
	{	
  	  head = new Node(NULL, NULL, &str2);
	  tail = head;
	  current = head;
	}
	else if (current->next == NULL)
	{
	  nodeAfter = new Node(NULL, tail, &str2);
	  tail->next = nodeAfter;
	  tail = nodeAfter;
	  current = nodeAfter;
	}
	else
	{
	  nodeAfter = new Node(current->next, current, &str2);
	  current->next->prev = nodeAfter;
	  current->next = nodeAfter;
	  current = nodeAfter;  
	}
}

/*
I/P: data of a node which we want to find in dll of string type
Desc: If a node to find is present in dll then this function will
      return true value else false. For that we traverse entire tree.
      And node which we found will be current node.
O/P: boolean value of true or false
*/
bool DoublyLinkedList :: find(string &str3)
{	
	Node *tempNode;
	for(tempNode=head; tempNode!=NULL; tempNode=tempNode->next)
	{
	  if(*tempNode->data == str3)
	  {
		current = tempNode;
		return true;
	  }
		
 	}

	return false;
	
	
}

/*
I/P: string which we want to delete
Desc: This function removes first occurence of the song, and current
      node will be the next node in the list if it is present else it
      will be the previous node. If the node is not found then current
      position of a node will not be changed.
O/P: NA
*/
void DoublyLinkedList :: remove(string &str4)
{
	if (find(str4))
	{
	  Node *deleteNode = current;
	  if(deleteNode->prev == NULL && deleteNode->next == NULL)
	  {
		current = NULL;
		head = NULL;
		tail = NULL;
		delete deleteNode;
	  }


	  else if(deleteNode->prev == NULL)
	  {
		deleteNode->next->prev = NULL;
		head = deleteNode->next;
		current = head;
		delete deleteNode;
	  }

	  else if(deleteNode->prev != NULL && deleteNode->next != NULL)
	  {
		deleteNode->prev->next = deleteNode->next;
		current = deleteNode->next;
		current->prev = deleteNode->prev;
		delete deleteNode;
	  }

	  else if(deleteNode->next == NULL)
	  {
		deleteNode->prev->next = NULL;
		tail = deleteNode->prev;
		current = tail;
		delete deleteNode;
	  }
	}
}



