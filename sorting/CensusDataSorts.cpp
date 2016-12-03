/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "CensusData.h"

/*
I/P: type of sort which is of integer type
Desc: This function is used for sorting records using insertion sort according
to type of data. If type of sort is 0, then data is sorted according to 
population, and if type of sort is 1, then data is sorted according to city.
O/P: NA
*/
void CensusData::insertionSort(int typeOfSort) 
{ 
   Record* key;
   int i;
   if(typeOfSort == 0)
   {
      for (int j=1; j<=getSize()-1; j++)
      {
         key = data.at(j);
         i = j-1;
         while(i>-1 && data.at(i)->population > key->population)
         {
	   data.at(i+1) = data.at(i);
	   i=i-1;	 		
         }
         data.at(i+1) = key;
      }
   }

   else if(typeOfSort == 1)
   {
      for(int j=1; j<=getSize()-1; j++)
      {
         key = data.at(j);
         i = j-1;
         while(i>-1 && (*(data.at(i)->city)).compare(*(key->city))>0)
         {
	    data.at(i+1) = data.at(i);
	    i=i-1;	 		
         }
         data.at(i+1) = key;       
      }
   }
}

/*
I/P: type of sort which is of integer type
Desc: This function is used for sorting records using merge sort according
to type of data. If type of sort is 0, then data is sorted according to 
population, and if type of sort is 1, then data is sorted according to city.
O/P: NA
*/
void CensusData::mergeSort(int typeOfSort) 
{
   int start = 0;
   int end = (data.size())-1;
   if(typeOfSort == 0)
      mergeSortPopulation(start, end);
   else if(typeOfSort == 1)
      mergeSortCity(start, end);
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function include two recursive calls to divide the array
from start to middle element, and from middle+1 element to the last element.
Then mergePopulation() gets called to sort and merge sorted subarrays according
to population. 
O/P: NA
*/
void CensusData::mergeSortPopulation(int start, int end)
{
  int mid;
  if(start < end)
    {
      mid = (start+end)/2;
      mergeSortPopulation(start, mid);
      mergeSortPopulation(mid+1, end);
      mergePopulation(start, mid, end);
    }
}

/*
I/P: start and last indices of array which is of integer type
Desc: This function sorts records of different files according to the
population. Two left and right arrays are created and then elements in
those arrays get sorted by comparing and merging.
O/P: NA 
*/
void CensusData::mergePopulation(int start, int mid, int end)
{
   int n1, n2, i, j, k;
   n1 = mid-start+1;
   n2 = end-mid;
   vector <Record*> leftArray, rightArray;
  
   for(i=0; i<n1; i++)
   {
      leftArray.push_back(data[start+i]);
   }
   for(j=1; j<=n2; j++)
   {
      rightArray.push_back(data[mid+j]);
   }

   i = 0;
   j = 0;
   k=start;

   while(i<n1 && j<n2)
   {
      if(leftArray.at(i)->population <= rightArray.at(j)->population)
      {
         data.at(k) = leftArray.at(i);
         i++;
         k++;
      }
      else
      {
         data.at(k) = rightArray.at(j);
         j++;
	 k++;  
      }
   }
   
   if(i<n1)
   {
      while(i<n1)
      {
         data.at(k) = leftArray.at(i);
         i++;
         k++; 
      }
   }
   else if(j<n2)
   {
      while(j<n2)
      {
         data.at(k) = rightArray.at(j);
         j++;
         k++;  
      }
   }
  
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function include two recursive calls to divide the array
from start to middle element, and from middle+1 element to the last element.
Then mergeCity() gets called to sort and merge sorted subarrays according to
city. 
O/P: NA
*/
void CensusData::mergeSortCity(int start, int end)
{
   int mid;
   if(start < end)
   {
      mid = (start+end)/2;
      mergeSortCity(start, mid);
      mergeSortCity(mid+1, end);
      mergeCity(start, mid, end);
   }
}

/*
I/P: start and last indices of array which is of integer type
Desc: This function sorts records of different files according to the
city name. Two left and right arrays are created and then records in
those arrays get sorted by comparing alphabates of strings and merging.
O/P: NA 
*/
void CensusData::mergeCity(int start, int mid, int end)
{
   int n1, n2, i, j, k;
   n1 = mid-start+1;
   n2 = end-mid;
   vector <Record*> leftArray, rightArray;
  
   for(i=0; i<n1; i++)
   {
      leftArray.push_back(data[start+i]);
   }
   for(j=1; j<=n2; j++)
   {
      rightArray.push_back(data[mid+j]);
   }
 
   i = 0;
   j = 0;
   k=start;
   while(i<n1 && j<n2)
   {
      if(*(leftArray.at(i)->city) <= *(rightArray.at(j)->city))
      {
         data.at(k) = leftArray.at(i);
         i++;
	 k++;
      }
      else
      {
         data.at(k) = rightArray.at(j);
         j++;
	 k++;  
      }
   }

   if(i<n1)
   {
      while(i<n1)
      {
         data.at(k) = leftArray.at(i);
         i++;
         k++; 
      }
   }
   else if(j<n2)
   {
      while(j<n2)
      {
         data.at(k) = rightArray.at(j);
         j++;
         k++;  
      }
   }
}

/*
I/P: type of sort which is of integer type
Desc: This function is used for sorting records using quick sort according
to type of data. If type of sort is 0, then data is sorted according to 
population, and if type of sort is 1, then data is sorted according to city.
seed functionality is obtained to generate random number.
O/P: NA
*/
void CensusData::quickSort(int typeOfSort)
{
   int start = 0;
   int end = (data.size())-1;
   // seed functionality is referred from the link below:
   // http://www.cplusplus.com/reference/random/generate_canonical/
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   rand.seed(seed);
   if(typeOfSort == 0)
      quickSortPopulation(start, end);
   else if(typeOfSort == 1)
      quickSortCity(start, end);
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function include two recursive calls to sort those subarrays
further. Initially randomise_partitionPopulation() is called to generate
index of random number then recursive calls are invoked.
O/P: NA
*/
void CensusData::quickSortPopulation(int start, int end)
{
   int sortedElement;
   if(start < end)
   {
      sortedElement = randomise_partitionPopulation(start, end);
      quickSortPopulation(start, sortedElement-1);  
      quickSortPopulation(sortedElement+1, end);
   }
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function generates random number using a class named
uniform_int_distribution. It produces random number on uniformly distributed
interval from start element to end element which we are passing as parameters. 
O/P: index of randomly generated number which is of integer type.
*/
int CensusData::randomise_partitionPopulation(int start,int end)
{
   
   std::uniform_int_distribution<int> range(start,end);   
   int i=range(rand);
   Record *temp;
   temp=data[end];
   data[end]=data[i];
   data[i]=temp;
   return partitionPopulation(start, end);
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function compares population of each record from start to end,
and if the value of previous record is greater than next record, it swaps
those two values. Using such functionality, all the data gets sorted. 
O/P: index of sorted element which is of integer type.
*/
int CensusData::partitionPopulation(int start, int end)
{
   int i, j;
   Record* pivot;
   pivot = data.at(end);
   i = start-1;
   for(j=start; j<end; j++)
   {
      if(data.at(j)->population <= pivot->population)
      {
         i++;
         std::swap(data.at(i),data.at(j));
      }
   }
   std::swap(data.at(i+1), data.at(end));
   return i+1;
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function include two recursive calls to sort those subarrays
further. Initially randomise_partitionCity() is called to generate index of
random number then recursive calls are invoked.
O/P: NA
*/
void CensusData::quickSortCity(int start, int end)
{
   int sortedElement;
   if(start < end)
   {
      sortedElement = randomise_partitionCity(start, end);
      quickSortCity(start, sortedElement-1);  
      quickSortCity(sortedElement+1, end);
   }
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function generates random number using a class named
uniform_int_distribution. It produces random number on uniformly distributed
interval from start element to end element which we are passing as parameters. 
O/P: index of randomly generated number which is of integer type.
*/
int CensusData::randomise_partitionCity(int start,int end)
{
   std::uniform_int_distribution<int> range(start,end);   
   int i=range(rand);
   Record *temp;
   temp=data[end];
   data[end]=data[i];
   data[i]=temp;
   return partitionCity(start, end);
}

/*
I/P: start and end indices of arrays which is of integer type.
Desc: This function compares strings of city of each record from start to end,
and if the value of previous record is greater than next record, it swaps
those two values. Using such functionality, all the data gets sorted. 
O/P: index of sorted element which is of integer type.
*/
int CensusData::partitionCity(int start, int end)
{
   int i, j;
   Record* pivot;
   pivot = data.at(end);
   i = start-1;
   for(j=start; j<end; j++)
   {
      if(*(data.at(j)->city) <= *(pivot->city))
      {
         i++;
         std::swap(data.at(i),data.at(j));
      }
   }
   std::swap(data.at(i+1), data.at(end));
   return i+1;
}
