/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 */


#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
#include <chrono>
#include <random>
using std::ifstream;
using std::string;
using std::vector;
using std::default_random_engine;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage
//
// You may add your private helper functions here!
//
   void mergeSortPopulation(int, int);    // sorts poulation using mergesort		 
   void mergeSortCity(int, int);          // sorts city using merge sort
   void mergePopulation(int, int, int);   // to merge subarrays after sorting
   void mergeCity(int, int, int);         // merge subarrays after sorting
   void quickSortPopulation(int, int);    // sorts population using quick sort
   void quickSortCity(int, int);          // sorts city using quick sort
   int partitionPopulation(int, int);     // partitioning of array during sort
   int partitionCity(int, int);           // partitioning of array during sort
   int randomise_partitionPopulation(int,int);// generates random no as pivot
   int randomise_partitionCity(int,int);  // generates random city as pivot
   default_random_engine rand;            // generates random pseudo numbers
};

#endif // CSCI_311_CENSUSDATA_H
