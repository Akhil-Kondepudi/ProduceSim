//Author: Akhil Kondepudi
//Date: 1/15/2022
//Revision History: Creation finished on 1/15/2022 by Akhil Kondepudi

/*Implementation Invariants
  Public Functions:
  Constructer
  - the constructor has default values  for error checking, all code will work with default values but will be largely arbitrary
  - Classification list has size set to 5, but this is arbitrary as size can be increased when strings are added
  CopyConstructor
  - calls parent copy constructor and duplicates the includeClassifications heap array
  addClassification
  -string inputed is added to exclusion list. increases size of array if the size is not big enough
  isSameClassification
  -parses the includeClassification array to check if inputed value is in it, returns true or false depending on that.
*/

#include <iostream>
#include <vector>
#include <memory>
#include "customer.h"
#include "produce.h"
#include "segmentCustomer.h"

using namespace std;

SegmentCustomer::SegmentCustomer(string Name, string Address, double Balance, double MinimumPrice) : Customer(Name, Address, Balance, MinimumPrice){
    includeClassifications = new string[5];
    arrSize = 0;
    arrMaxSize = 5;
}

SegmentCustomer::SegmentCustomer(const SegmentCustomer &copy) : Customer(copy) {
    includeClassifications = new string[copy.arrMaxSize];
    arrSize = copy.arrSize;
    arrMaxSize = copy.arrMaxSize;
    for(int i = 0; i < arrSize; i++) {
        includeClassifications[i] = copy.includeClassifications[i];
    }
}

SegmentCustomer& SegmentCustomer::operator=(const SegmentCustomer &copy){
    if(this != &copy){
        Customer::operator=(copy);
        delete[] includeClassifications;
        includeClassifications = new string[copy.arrMaxSize];
        arrSize = copy.arrSize;
        arrMaxSize = copy.arrMaxSize;
        for(int i = 0; i < arrSize; i++) {
            includeClassifications[i] = copy.includeClassifications[i];
        }
    }
}


SegmentCustomer::~SegmentCustomer(){
    delete[] includeClassifications;
    includeClassifications = nullptr;
}

void SegmentCustomer::addClassification(string clasif){
    if (arrSize == arrMaxSize)
    {
        string *temp = new string[arrMaxSize + 5];
        arrMaxSize += 5;
        for (int x = 0; x < arrSize; x++) {
            temp[x] = (includeClassifications[x]);
        }
        delete[] includeClassifications;
        includeClassifications = temp;
        temp = nullptr;
    }
    includeClassifications[arrSize] = clasif;
    arrSize++;
}

bool SegmentCustomer::isSameClassification(string clasif){
    for (int i = 0; i < arrSize; i++){
        if (clasif == includeClassifications[i]){
            return true;
        }
    }
    return false;
}

