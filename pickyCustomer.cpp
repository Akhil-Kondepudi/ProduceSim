//Author: Akhil Kondepudi
//Date: 1/15/2022
//Revision History: Creation finished on 1/15/2022 by Akhil Kondepudi

/*Implementation Invariants
  Public Functions:
  Constructer
  - the constructor has default values  for error checking, all code will work with default values but will be largely arbitrary
  - exclusionlist is set to a length of 5 with only empty strings because only five values should be stored. The empty strings are so that
    the length of it can be parsed without throwing errors
  copyconstructor
  - creates deap copy of heap allocated members, and carries over the rest
  addExclusion
  -string inputed is added to exclusion list. modulues of size is used to garuntee size and also to replace oldest value
  isExclusion
  -parses the exclusionlist to check if inputed value is in it, returns true or false depending on that.
*/

#include <iostream>
#include <vector>
#include <memory>
#include "customer.h"
#include "produce.h"
#include "pickyCustomer.h"

using namespace std;

PickyCustomer::PickyCustomer(string Name, string Address, double Balance, double MinimumPrice)  : Customer(Name, Address, Balance, MinimumPrice) {
    exclusions = new string[] { "", "", "", "", ""};
    exclusionSize = 0;
}


PickyCustomer::PickyCustomer(const PickyCustomer &copy) : Customer(copy) {
    exclusions = new string[] { "", "", "", "", ""};
    for(int i = 0; i < 5; i++){
        exclusions[i] = copy.exclusions[i];
    }
    exclusionSize = copy.exclusionSize;
}

PickyCustomer& PickyCustomer::operator=(const PickyCustomer &copy){
    if(this != &copy){
        Customer::operator=(copy);
        delete[] exclusions;
        exclusions = new string[] { "", "", "", "", ""};
        for(int i = 0; i < 5; i++){
            exclusions[i] = copy.exclusions[i];
        }
        exclusionSize = copy.exclusionSize;
    }
}

PickyCustomer::~PickyCustomer(){
    delete[] exclusions;
    exclusions = nullptr;
}

void PickyCustomer::addExclusion(string exc) {
    exclusions[exclusionSize % 5] = exc;
    exclusionSize++;
}

bool PickyCustomer::isExclusion(string name){
    for (int i = 0; i < 5; i++){
        if (exclusions[i] == name) {
            return true;
        }
    }
    return false;
}

