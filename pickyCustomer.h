//Author: Akhil Kondepudi
//Date: 1/15/2022
//Revision History: Creation finished on 1/15/2022 by Akhil Kondepudi

/*Class Invariants:
  This class was created as a certain variation of a specific type of customer. It inherits from the general customer class and
  represnets a customer that has restrictions on some produce that they want. For example, the customer might have it so that it will be unable to get apples
  and pears because they are alergic to them. Only 5 restrictions can be stored at a given time, and the oldest one is overwritten if more are added
  It retains all the functionallity of the original customer class, so if general questions about the class occur, please refer to
  the parent class for answers.
*/

//Interface Invariants:
// constructor
//  -This is how you create a customer object with all the data the it will need to function
//  -Will set mimnimumPrice equal to balance if it exceeds it
//  -by default there are no exclusions in the class, they must be added via the addExclusion method
// copyconstructor
//  -Will create a customer object that has the same data as the customer object inputed.
// overloaded assignment operator
//  -Will create a customer object that has the same data as the customer object inputed.
// addExclusion
//  -adds exclusion to storage in customer
// isExclusion
//  -takes string of the produce name, and returns bool on whether it is restricted or not.

#ifndef P4_PICKYCUSTOMER_H
#define P4_PICKYCUSTOMER_H

#include <iostream>
#include <vector>
#include <memory>
#include "customer.h"
#include "produce.h"

using namespace std;

class PickyCustomer : public Customer {
private:
    string* exclusions;
    int exclusionSize;

public:
    //Preconditions: Input all data that you want stored in the customer object
    //Postconditions: inputed data is stored and exclusionslist is set to a length of 5 and only has empty strings
    PickyCustomer(string Name = "", string Address = "", double Balance = 0, double MinimumPrice = 0);
    // Preconditions: Valid customer object is inputed
    // Postconditions: A duplicate customer object is instantiated
    PickyCustomer(const PickyCustomer& copy);
    // Preconditions: A valid customer object must be inputed
    // Postconditions: A current object becomes a deep copy of the inputed one and object is returned
    PickyCustomer& operator=(const PickyCustomer& copy);
    //Preconditions: None
    //Postconditions: Heap memory is deallocated and object is essentially deleted
    virtual ~PickyCustomer();
    //Preconditions: string must be inputed
    //Postconditions: exclusion is added to list(and replaces oldest value if there are 5 already)
    void addExclusion(string exc);
    //Preconditions: string must be inputed
    //Postconditions: None
    bool isExclusion(string name);

};


#endif //P4_PICKYCUSTOMER_H
