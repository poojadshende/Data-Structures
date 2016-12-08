/*
Author name: Pooja Shende

Functions used in this file are
1) main()
2) RBapp()- Construstor of RBapp class
3) mainLoop()- To process a file
4) processCommand()- It reads ans process a command
5) processInsert()- to insert into red black tree
6) processPrint()- to print red black tree
7) processFind()- find and print all occurences of tree
8) processDelete()- delete from the tree
*/

#include<iostream>
#include "rbapp.h"

using namespace std;
/*
Desc: mainLoop()function is called in main() and object of RBapp is
instantiated.
I/P: N/A
O/P: integer
*/
int main()
{
   RBapp myRBapp;
   myRBapp.mainLoop();
   return 0;
}

/*
Desc: This is a constructor of RBapp class which sets flag value of done
variable to false.
I/P: N/A
O/P: N/A
*/
RBapp::RBapp()
{
   done = false;
}

/*
Desc: This function calls processCommand() till the end of the file.
I/P: N/A
O/P: N/A
*/
void RBapp::mainLoop()
{
   while(!cin.eof() && !done)
      processCommand();
}

/*
Desc: processCommand() reads file and calls different functions of
tree such as insertion, deletion and find, depending upon input command.
I/P: N/A
O/P: N/A
*/
void RBapp::processCommand()
{
   string inputCommand;
   size_t found;
   getline(cin, inputCommand);
   if(inputCommand == "quit")
   {
      done = true;
      return;
   }
   found = inputCommand.find("insert ");
   if (found!=string::npos)
   { 
      inputCommand.erase(0,7);
      processInsert(inputCommand);
      return;
   }

   found = inputCommand.find("find ");
   if (found!=string::npos)
   { 
      inputCommand.erase(0,5);
      processFind(inputCommand);
      return;
   }

   found = inputCommand.find("delete ");
   if (found!=string::npos)
   { 
      inputCommand.erase(0,7);
      processDelete(inputCommand);
   }

   found = inputCommand.find("print");
   if (found!=string::npos)
   { 
      processPrint();
      return;
   }
}

/*
Desc: processInsert() function separates key and value from input command
and passes both these as parameters to the rbInsert().
I/P: input command of string type
O/P: N/A
*/
void RBapp::processInsert(string& inputCommand)
{ 
   string key, value;
   size_t found = inputCommand.find(' ');
   key = inputCommand.substr(0,found);
   inputCommand.erase(0,key.length()+1);
   value = inputCommand;
   myRBT.rbInsert(key, value);
}

/*
Desc: processPrint() function is used to call rbPrintTree() which
red black tree.
I/P: N/A
O/P: N/A
*/
void RBapp::processPrint()
{
   myRBT.rbPrintTree();
}

/*
Desc: processFind() is used to call rbFind(). It takes input command as
parameter. It also prints key and value of i/p command.
I/P: key of type string
O/P: N/A
*/
void RBapp::processFind(string& inputCommand)
{
   vector<const string*> result;
   vector<const string*>::iterator itr;
   result = myRBT.rbFind(inputCommand);
   for(itr=result.begin(); itr!=result.end(); ++itr)
   {
      cout << inputCommand << " " << **itr << endl;
   }
}

/*
Desc: processDelete() function separates key and satellite data from
i/p command, and passes both these values to rbDelete() function to delete
corresponding key and data pair from red black tree.
I/P: input command of string type
O/P: N/A
*/
void RBapp::processDelete(string& inputCommand)
{
   string key, value;
   size_t found = inputCommand.find(' ');
   key = inputCommand.substr(0,found);
   inputCommand.erase(0,key.length()+1);
   value = inputCommand;
   myRBT.rbDelete(key, value);
}
