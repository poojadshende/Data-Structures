 
#include <string>
#include "hash.h"

using std::string;

/*
i/p: an element to be inserted in a hash table which is of string type
Description: hf() is a hash function used to calculate a value of a key or
a slot of a table to which element to be inserted hashes.
o/p: key or slot of a hash table to which element hashes to.
*/

/*
A hash function is called a good hash function when a hash table contains
less number of collisions and list length of munimum size. To achieve this,
even distribution accross hash table is required, however we do not know
probability distribution of keys.Hash function calculates a value of a key by
dividing a result by size of a hash table. Prime numbers seem good for general
purpose uniform hashing, and for repeating over sets. So, by selecting prime 
number which is not too close to an exact power of 2 will minimize collisions
and satisfy the rule described above.

Referred from http://stackoverflow.com/questions/8317508/hash-function-for-a-string
*/
int Hash::hf(string word)
{
   int result = 0;
   for( int i = 0; (unsigned int)i < word.length(); i++)
   {
      result = ((result * 373) + word[i])%HASH_TABLE_SIZE;
   }
   return result;
}

