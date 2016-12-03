/*
Author: Pooja Shende
Programming Assignment # 3
Assignment description: Create a hashtable, and implement functions of
hashtables. Also, deasign and implement hash function.
There are seven functions used to implement hash function including
constructor. 
1) print() is used to print hash table in standard format.
2) processFile() is used to insert element into hash table, and statistics are
updated.
3) remove() is used to delete elementt from the hash table, and statistics are
updated.
4) search() is used to check wheather a particular element is present in a
hash table or not.
5) output() is used to print the hash table into a file.
6) printStats() is used to print the statistics of hash table.
7) Hash() is a constructor, used to initialize statistics to zero.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "hash.h"

using namespace std;

/*
i/p: NA
Description: Hash() is a constructor, used to initialize statistics of hash
table to zero.
o/p: NA
*/
Hash :: Hash()
{
   collisions = 0;
   longestList = 0;
   avgLength = 0;
   totalElements = 0; 
   nonEmptyLists = 0;
}

/*
i/p: NA
Description: print() is used to print hash table in standard format.
Hash table is printed on console.
o/p: NA
*/
void Hash :: print()
{
   list<string>::iterator itr;
   for(int i=0; i<HASH_TABLE_SIZE; i++)
   {
      cout << i << ":\t";
      for(itr=hashTable[i].begin(); itr!=hashTable[i].end(); ++itr)
      {
         cout << *itr << ", ";
      }
      cout << endl;
   }
}

/*
i/p: element of string type, that is to be inserted in hash table
Description: This function is used to process an input file. It inserts
an element into hash table using push_back(). It also calculates statistics
such that number of collisions, average list length, length of longest list.
o/p: NA
*/
void Hash :: processFile(string fileName)
{
   string word;
   int key;
   unsigned int listSize;
   
   ifstream inputFile(fileName.c_str());
   if(inputFile.is_open())
   {
      while(getline(inputFile, word))
      {
         totalElements = totalElements+1;
         key = hf(word);
         if(hashTable[key].empty() == false)
            collisions = collisions+1;
         if(hashTable[key].empty() == true)
            nonEmptyLists = nonEmptyLists + 1;
         hashTable[key].push_back(word);
         listSize = hashTable[key].size();
         if(listSize > longestList)
            longestList = listSize;
         currentAvgListLen = (double)totalElements/nonEmptyLists;
         avgLength = (currentAvgListLen + avgLength) / 2.0;
      }
      inputFile.close();
   }
}

/*
i/p: element of string type which is to be deleted or removed from hash table.
Description: remove() is used to delete a particular element from the hash
table using erase(). It also updates average list length.
o/p: NA
*/
void Hash :: remove(string deleteWord)
{ 
   int key;
   list<string>::iterator itr;
   key = hf(deleteWord);
   for(itr=hashTable[key].begin(); itr!=hashTable[key].end(); ++itr)
   {
      if(deleteWord == *itr)
      { 
         hashTable[key].erase(itr);
         totalElements = totalElements -1;
         if(hashTable[key].empty()==true)
            nonEmptyLists = nonEmptyLists - 1;
         currentAvgListLen = (double)totalElements/nonEmptyLists;
         avgLength = (currentAvgListLen + avgLength) / 2.0;
         break;
      } 
   }
}

/*
i/p: element to be searched
Description: This function is used to search a particular element.
o/p: boolean type - returns true if the element to be searched is present
in a hash table otherwise, returns false.
*/
bool Hash :: search(string searchString)
{
   int key;
   list<string>::iterator itr;
   key = hf(searchString);
   for(itr=hashTable[key].begin(); itr!=hashTable[key].end(); ++itr)
   {
      if(searchString == *itr)
         return true;
   }
   return false;
}

/*
i/p: name of a file which is of string type
Description: output() is used to print hash table to a specified file. And
its printing format is same as that of print().
o/p: NA
*/
void Hash :: output(string outFile )
{
   ofstream outputFile;
   outputFile.open(outFile);
   list<string>::iterator itr;
   for(int i=0; i<HASH_TABLE_SIZE; i++)
   {
      outputFile << i << ":";
      for(itr=hashTable[i].begin(); itr!=hashTable[i].end(); ++itr)
      {
         outputFile << "\t" << *itr << "," << " ";
      }
      outputFile << endl;
   }  
}

/*
i/p: NA
Description: printStats() is used to print the statistics of hash table.
o/p: NA
*/
void Hash :: printStats( )
{
   cout << "Total Collisions = " << collisions << endl;
   cout << "Longest List Ever = " << longestList << endl;
   cout << "Average List Length Over Time = " << avgLength << endl;
   cout << "Load Factor = " << (double)totalElements/HASH_TABLE_SIZE << endl;
}















