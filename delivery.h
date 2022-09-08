#pragma once
//Author: Akhil Kondepudi
//Date: 1/12/2022
//Revision History: Creation finished on 2/2/2022 by Akhil Kondepu

//Interface Invariants:
// Delivery constructor
//  -This is how you create a delivery object with all the data the it will need to function
//  -By giving the pointer to customer, you are allowing for the modification of customer
//  -if customer is deleted while being used in delivery, then delivery WILL error.
//  -This will only work if the Preconditions are followef explicitly
// Delivery destructor
//  -destroys the delivery object
// Delivery copy constructor
//  -Creates a delivery object with the exact same data as the inputed delivery object
//  -Only works if a valid delivery object is inputed
// Overoaded assignment operator
//  -Creates a delivery object with the exact same data as the inputed delivery object
//  -Only works if a valid delivery object is inputed
// ReplaceItem
//  -takes in the name of the produce item you want to replace and replaces it with the inputed produce item
//  -will return false and not perform replacement if unable to find name or inputed produce item expired or spoiled
// DeliverBox
//  -Will deliver all the items currently stored in the class to the client, will replace any spoiled or expired
//   produce items with anything that the object has in storage that is not expired
//  -will also reduce the clients balance by the amount that the delivery cost if the delivery costs more than the clients balance
//   then it will give the extra stuff to the client for free
// ShareOrder
//  -will share info of each produce item set to be delivered in the for of a string vector
// FillBox
//  -will fill the box to be delivered with items in storage based on what the forcast delivery was/wanted
//  -Also takes in a array of Produce items that the client wants to add to storage if desired
//  -size of array MUST also be inputed or values will not be added to storage
// ForcastDelivery
//  -Takes in a vector of strings that is the name of the produce items that the client wants added to the delivery
//

/*Class Invariants:
  This class was created as a way for a delivery service to keep track of the current deliveries.
  It allows for current storage availabel for delivery to be updated and based and that and what items
  that the customer wants (which is gotten from ForcastDelivery) can fill up the delivery up to the customers
  minimum spending amount. The object also supports deep copying incase there are any duplicate orders that the
  customre wants to happen again. Items can be replaced based on the item name. If the amount in the delivery box actually
  exceeds the amount of balance that the customer has, then the extra will be given to the customer for free, as it is impossible to
  know if it is possible to be above the miminmum Price but below the balance with the costs of all the produce items.
*/



#ifndef DELIVERY_H
#define DELIVERY_H
#include <iostream>
#include <vector>
#include <memory>
#include "customer.h"
#include "pickyCustomer.h"
#include "segmentCustomer.h"
#include "produce.h"

using namespace std;

class Delivery {
private:
	double totalCost;
	Customer* customer;
	Produce* produceList = {};
    int prodListSize = 0;
    int prodListMaxSize = 0;
	Produce* deliveryBox = {};
    int deliveryBoxListSize = 0;
    int deliveryBoxListMaxSize = 0;
    string* wantedItems = {};
    int wantedItemsSize = 0;
    int wantedItemsMaxSize = 0;


    // Preconditions: Valid Produce object inputed, optionally testtime for test date.
    // Postconditions: returns true if produce is usable
	bool checkValid(Produce p, string testtime = "");
    // Preconditions: produce array, index of item wanting to be removed, and bool of if its the produceList array must be inputed
    // Postconditions: removes the value at the given index of the given array and reduces respective size variable by 1
    void removeVal(Produce* arr, int index, bool isprodList);
    // Preconditions: Valid Delivery object is inputed
    // Postconditions: A copy of delivery data is copied over
    void Copy(const Delivery &copy);
    // Preconditions: None
    // Postconditions: Object is essentially destroyed
    void destroy();
    // Preconditions: None
    // Postconditions: array containg information about current items in delivery box are transfered to customer if valid
    //                 else they items are replaced and other items fill box until minimum price has been passed
    void normDeliverBox(string testTime = "");
    // Preconditions: Customer must be a PickyCustomer
    // Postconditions: array containg information about current items in delivery box are transfered to customer if valid
    //                 else they items are replaced and other items fill box until minimum price has been passed
    void pickyDeliverBox(PickyCustomer* pc, string testtime = "");
    // Preconditions: Customer must be a SegmentedCustomer
    // Postconditions: array containg information about current items in delivery box are transfered to customer if valid
    //                 else they items are replaced and other items fill box until minimum price has been passed
    void segDeliverBox(SegmentCustomer* sc, string testtime = "");
public:
	// Preconditions: Valid pointer to customer object, array containing storage of produce items, and size of said array must be inputed
	// Postconditions: Delivery object is instianitated holding inputed data
	Delivery(Customer* c, const Produce* initialList, int size);
    // Preconditions: Valid customer object and filename of file holding produce information in specific format inputed
    // Postconditions: Delivery object is instianitated holding inputed data
    Delivery(Customer* c, string filename);
    // Preconditions: None
	// Postconditions: Object is esentially destroyed
	~Delivery();
	// Preconditions: Valid Delivery object must be inputed
	// Postconditions: A copy of the inputed delivery object is instantiated
	Delivery(const Delivery& copy);
    // Preconditions: Valid Delivery object must be inputed
    // Postconditions: A copy of the inputed delivery object is instantiated, move semantics so imputed object is destroyed
    Delivery(Delivery&& delivery) noexcept;
	// Preconditions: Valid delivery object must be inputed
	// Postconditions: Current object becomes a copy of the inputed delivery object
	Delivery& operator=(const Delivery& copy);
    // Preconditions: Valid delivery object must be inputed
    // Postconditions: Current object becomes a copy of the inputed delivery object, move semantics so imputed object is destroyed
    Delivery& operator=(Delivery&& delivery);
	// Preconditions: name of produce item and produce item must be inputed
	// Postconditions: produce item with name in the delivery box is replaced with inputed produce object. if replacing failed return 0;
	bool ReplaceItem(string itemName, Produce replaced, string testtime = "");
	// Preconditions: None
	// Postconditions: All the items in deleviveryBox are sent to customer and total cost is reset to 0
	void DeliverBox(string testtime = "");
	// Preconditions: None
	// Postconditions: Vector containg information about current items in delivery box are returned
    unique_ptr<string[]> ShareOrder();
	// Preconditions: Optionally input array of produce items, and the size of the array, if wanted to add them to storage
	// Postconditions: deliveryBox is filled by items dorm produceList based on validity and names from ForcastDelivery
	void FillBox(const Produce* items = {}, int size = 0, string testtime = "");
	// Preconditions: array of desired produce item names must be inputed as well as array size
	// Postconditions: fills wantedItems with inputed names.
	void ForcastDelivery(const string* produceNames, int size);
};

#endif

