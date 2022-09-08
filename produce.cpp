//Author: Akhil Kondepudi
//Date: 1/12/2022
//Revision History: Creation finished on 1/12/2022 by Akhil Kondepudi
//                  Converted code to work in c++  on 1/26/2022 by Akhil Kondepudi


//Implementation Invariants
//Public functions
// checkSpoiled
//  -I first check if the spoiled field is marked as true, because if it is then going through the rest of the function is
//   not only a waste of time, but has the posibility of setting spoiled from true to false which should be impossible
//  -if spoiled is false, then the code checks if it should be true based on the time difference using the compareTime private method
//   to compare the current time to the expiration date
// checkExpired
//  -first I establish what the function should be using as the current time and compare that with the storage time using the
//   compareTime private method to figure out how long the item has been stored at its current location
//  -I used if statements considering the time passed, the current storage location, and the location the item should be stored,
//   in order to determine if the item should be expired based on the given rules for expiration.
//  -method is designed so that expired can be set to true, but once set to true can never become false again.
// assignment operators
//  -implemented as a shortcut way for client to change quantity.
//  -makes use of change amount function extensively, otherwise pretty self explanatory
// moveStorage
//  -Uses checkExpired to check if item is expired before moving locations because expiration is storage dependant
//  -only partially complete as it needs functionality to accomodate expiration if moving from bewtween two places that both don't match storage requirement
// blackoutOccur
//  -a simple bit of code built to accomodate blackouts to user specification
//  -current specification is that all items that require refrigeration are immediately expired
// changeAmount
//  -sets the value of quantity if inputed value is positive, else it doesnt change the value
// changeCost
//  -sets the value of cost if inputed value is positive, else it doesnt change the value
//  -does not nead to check for sigfig on the double as the info function already accounts for it
//
//Private functions
// convertTime
//  -converts a string structured in the specific format of  "month-date-year-military time" in numbers to the time struct for time comparisons
//  -works using string manipulation so inputed string must be in that format to work
// compareTime
//  -works essentailly by converting each time field value to its minute equivilant and then subtracting based on that value
//  -due to implementation, does not account for leap years. funtionality for leap years does not need to be added for another 2 years.
// currentTime
//  -finds the current time of the system using methods from time.h and string manipulationand to create a time struct with that data

/*

Overloaded operator choices:
 arithmetic: using pemdas on Produce with Produce doesn't make sense
 relational: comparing delivery doesn't make sense as there are too many ways they can be compared
             defining only one limits what client could do or would be confusing
 logical: doesn't make sense as it doesn't have boolean aspect
 indexing: does not make sense, unkown what client would be indexing to.
 streams: does not make sense
 mixed mode: does not make sense

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <time.h>
#include "produce.h"

using namespace std;

Produce::Time::Time() {
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
}

Produce::Time::Time(const Time& copy) {
    year = copy.year;
    month = copy.month;
    day = copy.day;
    hour = copy.hour;
    minute = copy.minute;
}


Produce::Produce(string Name, int Qty, double Cost, string Unit, string classific, string store, string storeDt, string storeRec, string expireDt) {
    name = Name;
    quantity = Qty;
    cost = Cost;
    unit = Unit;
    classification = classific;
    storage = store;
    storageDate = convertTime(storeDt);
    storageRec = storeRec;
    expireDate = convertTime(expireDt);
    spoiled = false;
    expired = false;
}

Produce::Produce() {
    name = "";
    quantity = 0;
    cost = 0;
    unit = "";
    classification = "";
    storage = "";
    storageDate = currentTime();
    storageRec = "";
    expireDate = convertTime("12-0-2400-1200");
    spoiled = true;
    expired = true;
}

Produce::Produce(const Produce& copy) {
    name = copy.name;
    quantity = copy.quantity;
    cost = copy.cost;
    unit = copy.unit;
    classification = copy.classification;
    storage = copy.storage;
    storageDate = Time(copy.storageDate);
    storageRec = copy.storageRec;
    expireDate = Time(copy.expireDate);
    spoiled = copy.spoiled;
    expired = copy.expired;
}

Produce& Produce::operator=(const Produce& copy){
    if(this != &copy){
        name = copy.name;
        quantity = copy.quantity;
        cost = copy.cost;
        unit = copy.unit;
        classification = copy.classification;
        storage = copy.storage;
        storageDate = Time(copy.storageDate);
        storageRec = copy.storageRec;
        expireDate = Time(copy.expireDate);
        spoiled = copy.spoiled;
        expired = copy.expired;
    }
}

Produce Produce::operator+(int add) const{
    Produce output = Produce(*this);
    output.changeAmount(quantity + add);
    return output;
}

Produce operator+(int add, const Produce& p){
    return p + add;
}

Produce& Produce::operator+=(int add){
    quantity += add;
    return *this;
}

Produce& Produce::operator++() {
    changeAmount(quantity + 1);
    return *this;
}

Produce Produce::operator++(int) {
    Produce output = *this;
    ++output;
    return output;
}

Produce Produce::operator-(int sub) const{
    Produce output = Produce(*this);
    output.changeAmount(quantity - sub);
    return output;
}

Produce operator-(int sub, const Produce& p){
    return p + sub;
}

Produce& Produce::operator-=(int sub){
    changeAmount(quantity - sub);
    return *this;
}

Produce& Produce::operator--() {
    changeAmount(quantity - 1);
    return *this;
}

Produce Produce::operator--(int) {
    Produce output = *this;
    --output;
    return output;
}

bool Produce::checkSpoiled(string tempTime) {
    if (spoiled) {
        return spoiled;
    }
    Time currTime = tempTime == "" ? currentTime() : convertTime(tempTime);
    spoiled = compareTime(expireDate, currTime) < 0;
    return spoiled;
}

void Produce::setSpoiled() {
    spoiled = true;
}

bool Produce::checkExpired(string tempTime) {
    Time currTime = tempTime == "" ? currentTime() : convertTime(tempTime);
    int timePassed = compareTime(currTime, storageDate);
    if (timePassed > 60 && storage != "refrigerator" && storageRec == "refrigerator") {
        expired = true;
    }
    if (timePassed > 1440 && storage != "dark" && storageRec == "dark") {
        expired = true;
    }
    return expired;
}

void Produce::moveStorage(string location, string tempTime) {
    Time currTime = tempTime == "" ? currentTime() : convertTime(tempTime);
    checkExpired(tempTime);
    storage = location;
    storageDate = currTime;
}

void Produce::blackoutOccur() {
    expired = storageRec == "refrigerator" ? true : expired;
}

Produce::Time Produce::convertTime(string date) const{
    int iterator = 0;
    string times[4];
    string tempStr;
    stringstream s(date);
    while (getline(s, tempStr, '-')) {
        times[iterator] = tempStr;
        iterator++;
    }

    Time temp;
    temp.month = stoi(times[0]);
    temp.day = stoi(times[1]);
    temp.year = stoi(times[2]);
    temp.hour = stoi(times[3].substr(0, 2));
    temp.minute = stoi(times[3].substr(2, 2));
    return temp;
}

int Produce::compareTime(Time first, Time second) const {
    int daysInMonth[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    int minuteDiff = (first.year - second.year) * 525600;
    int firstDays = daysInMonth[first.month - 1] + first.day;
    int secondDays = daysInMonth[second.month - 1] + second.day;
    minuteDiff += (firstDays - secondDays) * 1440;
    minuteDiff += (first.hour * 60 + first.minute) - (second.hour * 60 + second.minute);
    return minuteDiff;
}


Produce::Time Produce::currentTime() const {
    int iterator = 0;
    string strList[6];
    string monthList[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    time_t curTime = time(NULL);
    string str = ctime(&curTime);
    string tempStr;
    stringstream s(str);
    while (getline(s, tempStr, ' ')) {
        strList[iterator] = tempStr;
        iterator++;
    }
    for (int x = 0; x < 12; x++) {
        if (strList[1] == monthList[x]) {
            iterator = x;
        }
    }

    Time temp;
    temp.day = stoi(strList[2]);
    temp.month = iterator + 1;
    temp.year = stoi(strList[4]);
    temp.hour = stoi(strList[3].substr(0, 2));
    temp.minute = stoi(strList[3].substr(3, 2));

    return temp;
}

unique_ptr<string[]> Produce::info(string testtime) const {
    Time currTime = testtime == "" ? currentTime() : convertTime(testtime);
    unique_ptr<string[]> output( new string[7]);
    string costString = to_string(cost);
    costString = costString.substr(0, costString.find('.') + 3);
    output[0] = name;
    output[1] = to_string(quantity);
    output[2] = unit;
    output[3] = costString;
    output[4] = classification;
    output[5] = storage;
    output[6] = to_string(compareTime(expireDate, currTime));
    return output;
}

void Produce::changeAmount(int newAmnt) {
    quantity = newAmnt > 0 ? newAmnt : 0;
}

void Produce::changeCost(double newCost) {
    cost = newCost > 0 ? newCost : 0;
}




