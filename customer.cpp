//Author: Akhil Kondepudi
//Date: 1/12/2022
//Revision History: Creation finished on 2/2/2022 by Akhil Kondepudi

/*Implementation Invariants
  Public Functions:
  Constructer
  -the constructor has default values  for error checking, all code will work with default values but will be largely arbitrary
  Copy Constructor
  -copys members from inputed object
  - Uses for loops to parse through the vectors and copy values
  Assignment operator
  -same as the copy constructor, but clears existing values before
  Overloaded addition operators
  -A shortcut way to increase the balance of the customer
  -Makes use of the change balance function
   Overloaded subtraction operators
  -shortcut wat to reduce the balance of the customer
  -Makes use of the change balance function
  info
  -simply returns a sting vector that contains all the data in the fields
  addProduce
  -adds the inputed produce item to produceItems vector
  changeBalance
  -adds value to balance member
  Copy
  -helper function used to copy over data froom inputed customer class
  destroy
  -helper function used to deallocate current heap allocated variables

Overloaded operator choices:
 arithmetic: using pemdas on customer with customer doesn't make sense
 relational: comparing customers doesn't make sense as there are too many ways they can be compared
             defining only one limits what client could do or would be confusing
 logical: doesn't make sense as it doesn't have boolean aspect
 indexing: arguement can be mad for indexing accessing customer's produce items. however
           client has no way of knowing number of produce items, so risks error
 streams: does not make sense
 mixed mode: does not make sense
*/

#include <iostream>
#include <vector>
#include <memory>
#include "customer.h"
#include "produce.h"

using namespace std;

Customer::Customer(string Name, string Address, double Balance, double MinimumPrice) {
	name = Name;
	address = Address;
	balance = Balance;
	minimumPrice = MinimumPrice > Balance ? Balance : MinimumPrice;
    produceItems = new Produce[5];
    maxSize = 5;
    size = 0;
}

Customer::~Customer() {
	destroy();
}

Customer::Customer(const Customer& copy) {
	Copy(copy);
}

Customer& Customer::operator=(const Customer& copy) {
    if(this != &copy){
        destroy();
        Copy(copy);
    }

    return *this;
}

Customer Customer::operator+(double add) const{
    Customer output = Customer(*this);
    output.changeBalance(add);
    return output;
}

Customer operator+(double add, const Customer& c){
    return c + add;
}
Customer& Customer::operator+=(double add){
    changeBalance(add);
    return *this;
}

Customer Customer::operator-(double sub) const{
    Customer output = Customer(*this);
    output.changeBalance(sub * -1);
    return output;
}

Customer operator-(double sub, const Customer& c){
    return c - sub;
}
Customer& Customer::operator-=(double sub){
    changeBalance(sub * -1);
    return *this;
}

unique_ptr<string[]> Customer::info() {
	string balanceString = to_string(balance);
	string minPriceString = to_string(minimumPrice);
	balanceString = balanceString.substr(0, balanceString.find('.') + 3);
	minPriceString = minPriceString.substr(0, minPriceString.find('.') + 3);
    unique_ptr<string[]> output( new string[4]);
    output[0] = name;
    output[1] = address;
    output[2] = balanceString;
    output[3] = minPriceString;
	return output;
}

void Customer::addProduce(Produce p) {
    if (size == maxSize)
    {
        maxSize += 5;
        Produce* temp = new Produce[maxSize];
        for(int i = 0; i < size; i++){
            temp[i] = Produce(produceItems[i]);
        }
        delete[] produceItems;
        produceItems = temp;
        temp = nullptr;

    }
    produceItems[size] = p;
    size++;
}

void Customer::changeBalance(double change) {
	balance = 0 > (balance + change) ? 0 : (balance + change);
}

void Customer::Copy(const Customer &copy){
    name = copy.name;
    address = copy.address;
    balance = copy.balance;
    minimumPrice = copy.minimumPrice;
    size = copy.size;
    maxSize = copy.maxSize;
    produceItems = new Produce[maxSize];
    for(int i = 0; i < size; i++){
        produceItems[i] = Produce(copy.produceItems[i]);
    }
}

void Customer::destroy() {
    delete[] produceItems;
    produceItems = nullptr;
}
