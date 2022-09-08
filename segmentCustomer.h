//Author: Akhil Kondepudi
//Date: 1/15/2022
//Revision History: Creation finished on 1/15/2022 by Akhil Kondepudi

/*Class Invariants:
  This class was created as a certain variation of a specific type of customer. It inherits from the general customer class and
  represnets a customer that only wants specific classifications of produce. This means that they want ony fruit, or they only want fungus and
  vegtable produce. It retains all the functionallity of the original customer class, so if general questions about the class occur, please refer to
  the parent class for answers.
*/

//Interface Invariants:
// constructor
//  -This is how you create a customer object with all the data the it will need to function
//  -Will set mimnimumPrice equal to balance if it exceeds it
//  -by default there are no classifications in the class, they must be added via the addClassification method
// copy constructor
//  -used to make a duplicate of the object. is a deep copy
// overloaded assignment operator
//  -used to make a duplicate of the object. is a deep copy
// addClassification
//  -adds Classification to storage in customer
// isSameClassification
//  -takes string of the produce classification, and returns bool on whether it is included or not.


#ifndef P4_SEGMENTCUSTOMER_H
#define P4_SEGMENTCUSTOMER_H

#include <iostream>
#include <vector>
#include <memory>
#include "customer.h"
#include "produce.h"

using namespace std;

class SegmentCustomer : public Customer {
private:
    string* includeClassifications;
    int arrSize;
    int arrMaxSize;
public:
    //Preconditions: Input all data that you want stored in the customer object
    //Postconditions: inputed data is stored and includeClassifications is set to empty array
    SegmentCustomer(string Name = "", string Address = "", double Balance = 0, double MinimumPrice = 0);
    // Preconditions: Valid customer object is inputed
    // Postconditions: A duplicate customer object is instantiated
    SegmentCustomer(const SegmentCustomer& copy);
    // Preconditions: A valid customer object must be inputed
    // Postconditions: A current object becomes a deep copy of the inputed one and object is returned
    SegmentCustomer& operator=(const SegmentCustomer& copy);
    //Preconditions: None
    //Postconditions: Heap memory is deallocated and object is essentially deleted
    virtual ~SegmentCustomer();
    //Preconditions: string must be inputed
    //Postconditions: string is added to includeClassifications, if it is not big enough, its size is increased
    void addClassification(string clasif);
    //Preconditions: string is inputed
    //Postconditions: none
    bool isSameClassification(string clasif);
};


#endif //P4_SEGMENTCUSTOMER_H
