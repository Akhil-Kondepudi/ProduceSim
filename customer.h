//Author: Akhil Kondepudi
//Date: 1/12/2022

//Interface Invariants:
// Customer constructor
//  -This is how you create a customer object with all the data the it will need to function
//  -Will set mimnimumPrice equal to balance if it exceeds it
// Customer copy constructor
//  -Creates a customer object with the exact same data as the inputed customer object
//  -Only works if a valid customer object is inputed
// Overoaded assignment operator
//  -Creates a customer object with the exact same data as the inputed customer object
//  -Only works if a valid customer object is inputed
// Overloaded addition operator
//  -A shortcut way to increase the balance of the customer
// Overloaded subtraction operator
//  -shortcut wat to reduce the balance of the customer
//  -balance cannot go below 0.
// info
//  -returns a string vector that contains the basic data about the customer to the client
// addProduce
//  -adds the inputed produce object to a vector that the customer holds
// changeBalance
//  -changes balance based on the inputed double

/*Class Invariants:
This class was created as a way for a delivery service to keep track of their customers
Each customer object basically acts as a virtual representation of the customer, and will basic information
about the customer like their name, and how much money they have in their account. The client can query for
information about the customer but as of right now, they can only modify the balance. The constructor allows for
the construction of a customer with no information stored in it, but it is HIGHLY ADIVESED that the client would
fill out these fields when constructing the object
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <memory>
#include <vector>
#include "produce.h"

using namespace std;

class Customer {
private:
	string name;
	string address;
	double balance;
	double minimumPrice;
    int maxSize;
    int size;
    Produce* produceItems;
    // Preconditions: Valid customer object is inputed
    // Postconditions: A copy customer data is copied over
    void Copy(const Customer &copy);
    // Preconditions: None
    // Postconditions: Object is essentially destroyed
    void destroy();

public:
	// Preconditions: None, Although input of fields is highly advised
	// Postconditions: fields are initialized with data proveided, or empty strings and 0s if no data is provided
    Customer(string Name = "", string Address = "", double Balance = 0, double MinimumPrice = 0);
	// Preconditions: None
	// Postconditions: object data is deleted
	virtual ~Customer();
	// Preconditions: Valid customer object is inputed
	// Postconditions: A duplicate customer object is instantiated
	Customer(const Customer& copy);
	// Preconditions: A valid customer object must be inputed
	// Postconditions: A current object becomes a deep copy of the inputed one and object is returned
	Customer& operator=(const Customer& copy);
    // Preconditions: valid double is used
    // Postcondtions: balance is increased by inputed amount
    Customer operator+(double add) const;
    // Preconditions: valid double is used
    // Postcondtions: balance is increased by inputed amount
    friend Customer operator+(double add, const Customer& p);
    // Preconditions: valid double is used
    // Postcondtions: balance is increased by inputed amount
    Customer& operator+=(double add);
    // Preconditions: valid double is used
    // Postcondtions: balance is decreased by inputed amount
    Customer operator-(double sub) const;
    // Preconditions: valid double is used
    // Postcondtions: balance is decreased by inputed amount
    friend Customer operator-(double sub, const Customer& c);
    // Preconditions: valid double is used
    // Postcondtions: balance is decreased by inputed amount
    Customer& operator-=(double sub);
	// Preconditions: None
	// Postconditions: A unique pointer to an array about information of the customer is returned
    unique_ptr<string[]> info();
	// Preconditions: Produce object must be inputed
	// Postconditions: Produce object is added to the clients posession
	void addProduce(Produce p);
	// Preconditions: valid double is inputed
	// Postconditions: inputed double is added to the balance, whether negative or positive
	void changeBalance(double change);
	

};

#endif
