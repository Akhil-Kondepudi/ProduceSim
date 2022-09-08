//Author: Akhil Kondepudi
//Date: 1/12/2022
//Revision History: Creation finished on 1/12/2022 by Akhil Kondepudi
//                  Converted code to work in c++  on 1/26/2022 by Akhil Kondepudi

//Interface Invariants:
// Produce constructor
//  -This is how you create a produce object with all the data the it will need to function
//  -This will only work if the Preconditions are followed explicitly
//  -does not have safety checks for illogical inputs(like negative quantity). It is up to client to proplerly input if they want proper utility
// Produce null constructor:
//  -Creates a produce object filled with useless information, should only be used when initializing arrays of produce items
// Produce copy constructor
//  -Creates a Produce object with the exact same data as the inputed Produce object
//  -Only works if a valid Produce object is inputed
// Produce overloaded assignment operator
//  -Creates a Produce object with the exact same data as the inputed Produce object
//  -Only works if a valid Produce object is inputed
// addition assignment operators
//  -acts as a shortcut way to increase quantity of produce item
// subtraction assignment operators
//  -acts as a shortcut way to decrease quantity of produce item
// checkSpoiled
//  -This is how to check if the current produce item is spoiled, which occurs if the current time is passed the expiration date
//  -This does allow for an input of a custom time. HOWEVER, this custom time is only intended for class testing. It is not advised for client use
//  -Keep note that once an item is spoiled, it is impossible for it to be marked as unspoiled ever again
// setSpoiled
//  -This is for if the client would like to manually set the item as spoiled for unforseen reasons
// checkExpired
//  -This is how to check if the current produce item is expired, which occurs based on improper storing conditions for certain lengths of time
//  -This does allow for an input of a custom time. HOWEVER, this custom time is only intended for class testing. It is not advised for client use
//  -Keep note that once an item is expired, it is impossible for it to be marked as not expired ever again
// moveStorage
//  -Will change the storage location to new inputed location, and by default will change storage time to system time
//  -This does allow for an input of a custom time. HOWEVER, this custom time is only intended for class testing. It is not advised for client use
//  -Will check if the item will have expired before moving locations due to improper storing conditions.
// blackoutOccur
//  -Should be called on item in event of blackout in order to determine if item is expired because of it.
// info
//  -returns a vector of strings that contains the basic info about the produce object
// changeAmount
//  -setter for the amount field
// changeCost
//  -setter for the cost field

//Class Invariants:
//This class was created as a way for grocery stores to keep track of their produce items.
//After initilizing an instance of the produce object with appropriate data, the object should be able to act as a virtual
//representation of the actual produce item. Using this object, the client shoulf be able to efficiantly do things like manage
//their inventory and check on the quality of the produce item (like if it is spoiled). The client can easily change the quantity
//or the cost of the item in case of senarios like one quantity being sold or the price changing due to a sale. The class will
//by default update data using system time so functions can be called efficiently and easily. This class will work effectlively only
//if preconditions for constructor and methods are strictly followed. If not, the data will likeely be faulty or errors will be thrown.
//Due to the intended usage of this class, there is no default constructor available, as an empty produce object is nonsensical in the
//context of an actual grocery store.
#ifndef PRODUCE_H
#define PRODUCE_H
#include <iostream>
#include <vector>

using namespace std;

class Produce {
private:
    class Time {
    public:
        //Precondition: None
        //Postconditions: Will initialize the time object with all of the values set to 0
        Time();
        //Precondition: valid Time object is inputed
        //Postcondition: will initialize time object with same data as inputed time object
        Time(const Time& copy);
        int year;
        int month;
        int day;
        int hour;
        int minute;
    };

    //variables that hold the data about the class
    string name;
    string unit;
    string classification;
    int quantity;
    double cost;
    string storage;
    Time storageDate;
    string storageRec;
    Time expireDate;
    bool spoiled;
    bool expired;

    //Precondition: time is given in format of "month-date-year-military time" all as numbers
      //Postcondition: will return struct of time with data based on input
    Time convertTime(string date) const;
    //Precondition: two filled out time structs must be inputed (no empty fields)
    //Postcondition: will return time difference between the inputed times in minutes
    int compareTime(Time first, Time second) const;
    //Precondition: None
    //Postcondition: Returns time struct based on current system time.
    Time currentTime() const;


public:
    //Preconditions: All the parameters must be inputed in the proper format. Specifically:
    // the name of the produce item as a string
    // the amount of the item
    // the cost of one unit of the item as double. (if one unit costs $3.50, then input 3.50)
    // the units the item is being stored as, like oz or lb. (if the unit is the item itself, input "cnt")
    // the classification of the item, specifically whether it is a "fruit", "vegetable", "fungus", or "herb"
    // the location the item is currently being stored, specifically in either "refrigerator", "dark" (as in dark place), or "counter" (as in counter top)
    // the date and time in which the item started being stored at the given location, given in the format of "month-date-year-military time" all as numbers
    // the location that the item should be stored in, specifically in either "refrigerator", "dark" (as in dark place), or "counter" (as in counter top)
    // the expiration date of the item, given in the format of "month-date-year-military time" all as numbers
    //Postconditions: A produce object will be initialized that holds all the data that has been inputed
    Produce(string Name, int Qty, double Cost, string Unit, string classific, string store, string storeDate, string storeRec, string expireDt);
    //Preconditions: None
    //Postconditions: Produce object with null data will be initialized
    Produce();
    //Preconditions: A valid Produce object must be inputed
    //Postconditions: A Produce object will be created with a copy of all the data that was in the inputed Produce object.
    Produce(const Produce& copy);
    //Preconditions: A valid Produce object must be inputed
    //Postconditions: A Produce object will be created with a copy of all the data that was in the inputed Produce object.
    Produce& operator=(const Produce& copy);
    //Preconditions: valid int is used
    //Postconditions: int is added to quantity
    Produce operator+(int add) const;
    //Preconditions: valid int is used
    //Postconditions: int is added to quantity and
    friend Produce operator+(int add, const Produce& p);
    //Preconditions: valid int is used
    //Postconditions: int is added to quantity
    Produce& operator+=(int add);
    //Preconditions: None
    //Postconditions: quantity is incremented by 1;
    Produce& operator++();
    //Preconditions: None
    //Postconditions: quantity is incremented by 1;
    Produce operator++(int);
    //Preconditions: valid int is used
    //Postconditions: int is subtracted from quantity, will reset to 0 if it goes negative
    Produce operator-(int sub) const;
    //Preconditions: valid int is used
    //Postconditions: int is subtracted from quantity, will reset to 0 if it goes negative
    friend Produce operator-(int sub, const Produce& p);
    //Preconditions: valid int is used
    //Postconditions: int is subtracted from quantity, will reset to 0 if it goes negative
    Produce& operator-=(int sub);
    //Preconditions: None
    //Postconditions: quantity is decrimented by 1, resets to 0 if negative
    Produce& operator--();
    //Preconditions: None
    //Postconditions: quantity is decrimented by 1, resets to 0 if negative
    Produce operator--(int);
    //Precondition: If customized current time is wanted, input time in format of "month-date-year-military time" all as numbers.
    //Otherwise, will default to the system time.
    //Postcondition: marks item as spoiled if should be marked as spoiled, and returns true if item is spoiled
    bool checkSpoiled(string tempTime = "");
    //Precondition: None
    //Postcondition: will set spoiled to true, esentiallly marking the item as spoiled
    void setSpoiled();
    //Precondition: If customized current time is wanted, input time in format of "month-date-year-military time" all as numbers.
      //Otherwise, will default to the system time.
      //Postcondition: marks item as expired if should be marked as expired, and returns true if item is expired
    bool checkExpired(string tempTime = "");
    //Precondition: Input the storage location that the item is being moved to, specifically in either "refrigerator",
    //"dark" (as in dark place), or "counter" (as in counter top).
    //If customized current time is wanted, input time in format of "month-date-year-military time" all as numbers.
    //Otherwise, will default to the system time.
    //Postcondition: will set expired to true if appropriate, and change storage and storageDate as given
    void moveStorage(string location, string tempTime = "");
    //Precondition: None
    //Postcondition: will set expired to true if appropriate (if storage requirement is "refrigerator")
    void blackoutOccur();
    //Precondition: None
    //Postcondition: Simply returns a vector of strings that has info of the Produce item in the order of:
    //               "name, quantity, unit, cost, storage location"
    unique_ptr<string[]> info(string testtime = "") const;
    //Precondition: proper intger must be inputed
    //Postcondition: sets amount equal to the inputed integer
    void changeAmount(int newAmnt);
    //Precondition: proper double must be inputed
    //Postccndition: sets the cost equal to unputed double
    void changeCost(double newCost);


};

#endif

