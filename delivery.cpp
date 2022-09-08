//Author: Akhil Kondepudi
//Date: 1/12/2022
//Revision History: Creation finished on 2/2/2022 by Akhil Kondepu

/*Implementation Invariants
  Public Functions:
  Copy Constructor
  - Uses for loops to parse through the vectors and copy values
  Assignment operator
  -same as the copy constructor, but clears existing values before hand
  Copy
  -Helper function that is used to create a deep copy of object
  -shallow copy of pointer to customer is INTENTIONAL as we cannat create a seperate customer out of nowhere
  destroy
  -helper function that is used to destroy the object
  Replace Item
  -works by searching the deliveryBox for a produce item that shares the name and then replacing it wiht the inputed prodduce item
  -Uses check valid to make sure produce item is ok to be inputed
  DeliverBox
  -First checks if any items need to be replaced by any of the items in storage using checkValid
  -Once finished making sure everything in the deliveryBox is ok, it sends all the produce Items to the customer and reduces their balance by th appropriate amount
  ShareOrder
  -simply parses through the deliveryBox vector to return a string vector containing all the information about each produce item in there
  FillBox
  -Has an optional input in case the client wants to increase the storage, Fills the outgoing deliveryBox with the produce items that were requested in Forcast Delivery
  -will basically do nothing to deliveryBox if client hasnt called Forcast delivery yet (this is intentional)
  ForcastDelivery
  -simply uses a for loop to fill wanted items with all the the things in the inputed vector
  RemoveVal
  -helper function to remove a value from array without leaving an empty space

Overloaded operator choices:
 arithmetic: using pemdas on Delivery with Delivery doesn't make sense, as well as using numbers with delivery
 relational: comparing delivery doesn't make sense as there are too many ways they can be compared
             defining only one limits what client could do or would be confusing
 logical: doesn't make sense as it doesn't have boolean aspect
 indexing: does not make sense, unkown what client would be indexing to.
 streams: does not make sense
 mixed mode: does not make sense
 */
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <cmath>
#include "customer.h"
#include "delivery.h"
#include "produce.h"

using namespace std;


Delivery::Delivery(Customer* c,const Produce* initialList, int size) {
    totalCost = 0;
    customer = c;
    produceList = new Produce[size + 5];
    prodListMaxSize = size + 5;
    for (int i = 0; i < size; i++) {
        produceList[i] = Produce(initialList[i]);
    }
    prodListSize = size;
}

Delivery::Delivery(Customer* c, string filename){
    customer = c;
    totalCost = 0;
    ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()) {
        string line;
        string tempstr;
        string item[7];
        string date[3];
        string datestr;
        string harvdate;
        string expiredate;
        bool firstline = true;
        int cnt;
        int iterator;
        double cost;
        while (getline(myfile, line)) {
            if (firstline) {
                firstline = false;
            } else {
                stringstream s(line);
                iterator = 0;
                while (getline(s, tempstr, '\t')) {
                    item[iterator] = tempstr;
                    iterator++;
                }
                iterator = 0;
                datestr = item[6];
                stringstream d(datestr);
                while (getline(d, tempstr, '/')) {
                    date[iterator] = tempstr;
                    iterator++;
                }
                harvdate = date[0] + "-" + date[1] + "-" + date[2] + "-1200";
                expiredate = date[0] + "-" + to_string(stoi(date[1]) + 7) + "-" + date[2] + "-1200";
                if (stod(item[1]) < 1) {
                    cnt = 1;
                    cost = (1 / stod(item[1])) * stod(item[3]);
                } else {
                    cnt = round(stod(item[1]));
                    cost = stod(item[3]);
                }
                if(prodListMaxSize == prodListSize) {
                    Produce *temp = new Produce[prodListSize + 5];
                    prodListMaxSize += 5;
                    for (int x = 0; x < prodListSize; x++) {
                        temp[x] = Produce(produceList[x]);
                    }
                    delete[] produceList;
                    produceList = temp;
                    temp = nullptr;
                }
                produceList[prodListSize] = Produce(item[0], cnt, cost, item[2], item[4], item[5], harvdate, item[5], expiredate);
                prodListSize++;
            }
        }
    }
    myfile.close();
}

Delivery::~Delivery() {
    destroy();
}

void Delivery::Copy(const Delivery &copy){
    totalCost = copy.totalCost;
    customer = copy.customer;
    prodListSize = copy.prodListSize;
    deliveryBoxListSize- copy.deliveryBoxListSize;
    wantedItemsSize = copy.wantedItemsSize;
    prodListMaxSize = copy.prodListMaxSize;
    deliveryBoxListMaxSize = copy.deliveryBoxListMaxSize;
    wantedItemsMaxSize = copy.wantedItemsMaxSize;
    produceList = new Produce[prodListMaxSize];
    deliveryBox = new Produce[deliveryBoxListMaxSize];
    wantedItems = new string[wantedItemsMaxSize];
    for(int i = 0; i < prodListSize; i++){
        produceList[i] = Produce(copy.produceList[i]);
    }
    for(int i = 0; i < deliveryBoxListSize; i++){
        deliveryBox[i] = Produce(copy.deliveryBox[i]);
    }
    for(int i = 0; i < wantedItemsSize; i++){
        wantedItems[i] = (copy.wantedItems[i]);
    }
}

void Delivery::destroy() {
    delete[] produceList;
    produceList = nullptr;
    delete[] deliveryBox;
    deliveryBox = nullptr;
    delete[] wantedItems;
    wantedItems = nullptr;
    customer = nullptr;
}

Delivery::Delivery(const Delivery& copy) {
    Copy(copy);
}

Delivery::Delivery(Delivery &&delivery) noexcept{
    totalCost = delivery.totalCost;
    customer = delivery.customer;
    produceList = delivery.produceList;
    prodListSize = delivery.prodListSize;
    prodListMaxSize = delivery.prodListMaxSize;
    deliveryBox = delivery.deliveryBox;
    deliveryBoxListSize = delivery.deliveryBoxListSize;
    deliveryBoxListMaxSize = delivery.deliveryBoxListMaxSize;
    wantedItems = delivery.wantedItems;
    wantedItemsSize = delivery.wantedItemsSize;
    wantedItemsMaxSize = delivery.wantedItemsMaxSize;
    delivery.customer = nullptr;
    delivery.produceList = nullptr;
    delivery.deliveryBox = nullptr;
    delivery.wantedItems = nullptr;
}

Delivery& Delivery::operator=(Delivery&& delivery){
    swap(totalCost, delivery.totalCost);
    swap(customer, delivery.customer);
    swap(produceList, delivery.produceList);
    swap(prodListSize, delivery.prodListSize);
    swap(prodListMaxSize, delivery.prodListMaxSize);
    swap(deliveryBox, delivery.deliveryBox);
    swap(deliveryBoxListSize, delivery.deliveryBoxListSize);
    swap(deliveryBoxListMaxSize, delivery.deliveryBoxListMaxSize);
    swap(wantedItems, delivery.wantedItems);
    swap(wantedItemsSize, delivery.wantedItemsSize);
    swap(wantedItemsMaxSize, delivery.wantedItemsMaxSize);
    return *this;
}

Delivery& Delivery::operator=(const Delivery& copy) {
    if(this != &copy){
        destroy();
        Copy(copy);
    }

    return *this;
}


bool Delivery::ReplaceItem(string itemName, Produce replaced, string testtime) {
    int i = 0;
    while (i < deliveryBoxListSize && checkValid(replaced, testtime)) {
        if (deliveryBox[i].info()[0] == itemName) {
            totalCost -= stoi(deliveryBox[i].info()[1]) * stod(deliveryBox[i].info()[3]);
            totalCost += stoi(replaced.info()[1]) * stod(replaced.info()[3]);
            deliveryBox[i] = replaced;
            return true;
        }
        i++;
    }
    return false;
}

void Delivery::DeliverBox(string testtime) {
    if (PickyCustomer* ptr = dynamic_cast<PickyCustomer*> (customer)){
        pickyDeliverBox(ptr, testtime);
    }
    else if (SegmentCustomer* ptr = dynamic_cast<SegmentCustomer*> (customer)){
        segDeliverBox(ptr, testtime);
    }
    else{
        normDeliverBox(testtime);
    }
}

void Delivery::pickyDeliverBox(PickyCustomer *pc, string testtime) {
    bool replaced;
    Produce p;
    int index;
    for (int i = 0; i < deliveryBoxListSize; i++) {
        if (!checkValid(deliveryBox[i], testtime) || (pc->isExclusion(deliveryBox[i].info()[0]))) {
            replaced = false;
            p = Produce();
            for (int x = 0; x < prodListSize; x++) {
                if (checkValid(produceList[x],testtime) && !(pc->isExclusion(deliveryBox[i].info()[0]))) {
                    replaced = true;
                    if (produceList[x].info(testtime)[6] < p.info(testtime)[6]) {
                        p = produceList[x];
                        index = x;
                    }
                }
            }
            if (replaced) {
                ReplaceItem(deliveryBox[i].info()[0], p, testtime);
                removeVal(produceList, index, true);
            }
            else{
                totalCost -= stoi(deliveryBox[i].info()[1]) * stod(deliveryBox[i].info()[3]);
                removeVal(deliveryBox, i, false);
            }
            i--;
        }
    }
    bool found;
    while (totalCost < stod(pc->info()[3])){
        found = false;
        p = Produce();
        for (int x = 0; x < prodListSize; x++){
            if (checkValid(produceList[x], testtime) && !(pc->isExclusion(produceList[x].info()[0]))) {
                found = true;
                if (produceList[x].info(testtime)[6] < p.info(testtime)[6]) {
                    p = produceList[x];
                    index = x;
                }
            }
        }
        if (!found){
            break;
        }
        if(deliveryBoxListMaxSize == deliveryBoxListSize) {
            Produce *temp = new Produce[deliveryBoxListSize + 5];
            deliveryBoxListMaxSize += 5;
            for (int x = 0; x < deliveryBoxListSize; x++) {
                temp[x] = Produce(deliveryBox[x]);
            }
            delete[] deliveryBox;
            deliveryBox = temp;
            temp = nullptr;
        }
        deliveryBox[deliveryBoxListSize] = Produce(p);
        deliveryBoxListSize++;
        totalCost += stoi(p.info()[1]) * stod(p.info()[3]);
        removeVal(produceList, index, true);
    }

    if (stod(pc->info()[2]) < totalCost) {
        pc->changeBalance(-1 * stod(pc->info()[2]));
    }
    else {
        pc->changeBalance(-1 * totalCost);
    }
    totalCost = 0;
    int size = deliveryBoxListSize;
    for (int x = 0; x < size; size--){
        pc->addProduce(deliveryBox[0]);
        removeVal(deliveryBox, 0, false);
    }
    deliveryBoxListSize = 0;
}

void Delivery::segDeliverBox(SegmentCustomer *sc, string testtime) {
    bool replaced;
    Produce p;
    int index;
    for (int i = 0; i < deliveryBoxListSize; i++) {
        if (!checkValid(deliveryBox[i], testtime)  || !sc->isSameClassification(deliveryBox[i].info()[4])) {
            replaced = false;
            p = Produce();
            for (int x = 0; x < prodListSize; x++) {
                if (checkValid(produceList[x],testtime) && sc->isSameClassification(deliveryBox[i].info()[4])) {
                    replaced = true;
                    if (produceList[x].info(testtime)[6] < p.info(testtime)[6]) {
                        p = produceList[x];
                        index = x;
                    }
                }
            }
            if (replaced) {
                ReplaceItem(deliveryBox[i].info()[0], p, testtime);
                removeVal(produceList, index, true);
            }
            else{
                totalCost -= stoi(deliveryBox[i].info()[1]) * stod(deliveryBox[i].info()[3]);
                removeVal(deliveryBox, i, false);
            }
            i--;
        }
    }
    bool found;
    while (totalCost < stod(sc->info()[3])){
        found = false;
        p = Produce();
        for (int x = 0; x < prodListSize; x++){
            if (checkValid(produceList[x], testtime)  && sc->isSameClassification(produceList[x].info()[4])) {
                found = true;
                if (produceList[x].info(testtime)[6] < p.info(testtime)[6]) {
                    p = produceList[x];
                    index = x;
                }
            }
        }
        if (!found){
            break;
        }
        if(deliveryBoxListMaxSize == deliveryBoxListSize) {
            Produce *temp = new Produce[deliveryBoxListSize + 5];
            deliveryBoxListMaxSize += 5;
            for (int x = 0; x < deliveryBoxListSize; x++) {
                temp[x] = Produce(deliveryBox[x]);
            }
            delete[] deliveryBox;
            deliveryBox = temp;
            temp = nullptr;
        }
        deliveryBox[deliveryBoxListSize] = Produce(p);
        deliveryBoxListSize++;
        totalCost += stoi(p.info()[1]) * stod(p.info()[3]);
        removeVal(produceList, index, true);
    }

    if (stod(sc->info()[2]) < totalCost) {
        sc->changeBalance(-1 * stod(sc->info()[2]));
    }
    else {
        sc->changeBalance(-1 * totalCost);
    }
    totalCost = 0;
    int size = deliveryBoxListSize;
    for (int x = 0; x < size; size--){
        sc->addProduce(deliveryBox[0]);
        removeVal(deliveryBox, 0, false);
    }
    deliveryBoxListSize = 0;
}

void Delivery::normDeliverBox(string testtime) {
    bool replaced;
    Produce p;
    int index;
    for (int i = 0; i < deliveryBoxListSize; i++) {
        if (!checkValid(deliveryBox[i], testtime)) {
            replaced = false;
            p = Produce();
            for (int x = 0; x < prodListSize; x++) {
                if (checkValid(produceList[x],testtime)) {
                    replaced = true;
                    if (produceList[x].info(testtime)[6] < p.info(testtime)[6]) {
                        p = produceList[x];
                        index = x;
                    }
                }
            }
            if (replaced) {
                ReplaceItem(deliveryBox[i].info()[0], p, testtime);
                removeVal(produceList, index, true);
            }
            else{
                totalCost -= stoi(deliveryBox[i].info()[1]) * stod(deliveryBox[i].info()[3]);
                removeVal(deliveryBox, i, false);
            }
            i--;
        }
    }
    bool found;
    while (totalCost < stod(customer->info()[3])){
        found = false;
        p = Produce();
        for (int x = 0; x < prodListSize; x++){
            if (checkValid(produceList[x], testtime)) {
                found = true;
                if (produceList[x].info(testtime)[6] < p.info(testtime)[6]) {
                    p = produceList[x];
                    index = x;
                }
            }
        }
        if (!found){
            break;
        }
        if(deliveryBoxListMaxSize == deliveryBoxListSize) {
            Produce *temp = new Produce[deliveryBoxListSize + 5];
            deliveryBoxListMaxSize += 5;
            for (int x = 0; x < deliveryBoxListSize; x++) {
                temp[x] = Produce(deliveryBox[x]);
            }
            delete[] deliveryBox;
            deliveryBox = temp;
            temp = nullptr;
        }
        deliveryBox[deliveryBoxListSize] = Produce(p);
        deliveryBoxListSize++;
        totalCost += stoi(p.info()[1]) * stod(p.info()[3]);
        removeVal(produceList, index, true);
    }

    if (stod(customer->info()[2]) < totalCost) {
        customer->changeBalance(-1 * stod(customer->info()[2]));
    }
    else {
        customer->changeBalance(-1 * totalCost);
    }
    totalCost = 0;
    int size = deliveryBoxListSize;
    for (int x = 0; x < size; size--){
        customer->addProduce(deliveryBox[0]);
        removeVal(deliveryBox, 0, false);
    }
    deliveryBoxListSize = 0;
}


unique_ptr<string[]> Delivery::ShareOrder() {
    unique_ptr<string[]> output( new string[deliveryBoxListSize]);
    unique_ptr<string[]>  produceInfo;
    for (int i = 0; i < deliveryBoxListSize; i++) {
        produceInfo = deliveryBox[i].info();
        output[i] = (produceInfo[0] + " " + produceInfo[1] + " " + produceInfo[2]
            + " " + produceInfo[3] + "$ " + produceInfo[4]);
    }
    return output;
}

void Delivery::FillBox(const Produce* items, int size, string testtime) {
    for (int i = 0; i < size; i++) {
        if(prodListMaxSize == prodListSize) {
            Produce *temp = new Produce[prodListSize + 5];
            prodListMaxSize += 5;
            for (int x = 0; x < prodListSize; x++) {
                temp[x] = Produce(produceList[x]);
            }
            delete[] produceList;
            produceList = temp;
            temp = nullptr;
        }
        produceList[prodListSize] = Produce(items[i]);
        prodListSize++;
    }

    for (int i = 0; i < wantedItemsSize; i++) {
        for (int x = 0; x < prodListSize; x++) {
            if (wantedItems[i] == produceList[x].info()[0] && totalCost <= stod(customer->info()[3]) && checkValid(produceList[x], testtime)) {
                totalCost += stoi(produceList[x].info()[1]) * stod(produceList[x].info()[3]);

                if(deliveryBoxListMaxSize == deliveryBoxListSize) {
                    Produce *temp = new Produce[deliveryBoxListSize + 5];
                    deliveryBoxListMaxSize += 5;
                    for (int x = 0; x < deliveryBoxListSize; x++) {
                        temp[x] = Produce(deliveryBox[x]);
                    }
                    delete[] deliveryBox;
                    deliveryBox = temp;
                    temp = nullptr;
                }
                deliveryBox[deliveryBoxListSize] = Produce(produceList[x]);
                deliveryBoxListSize++;
                removeVal(produceList, x, true);
                x--;
            }
        }
    }
}


void Delivery::ForcastDelivery(const string* produceNames, int size) {
    for (int i = 0; i < size; i++) {
        if(wantedItemsMaxSize == wantedItemsSize) {
            string* temp = new string[wantedItemsSize + 5];
            wantedItemsMaxSize += 5;
            for (int x = 0; x < wantedItemsSize; x++) {
                temp[x] = (wantedItems[x]);
            }
            delete[] wantedItems;
            wantedItems = temp;
            temp = nullptr;
        }

        wantedItems[i] = (produceNames[i]);
        wantedItemsSize++;
    }
}


bool Delivery::checkValid(Produce p, string testtime) {
    bool val = !(p.checkSpoiled(testtime) || p.checkExpired(testtime));
    return val;
}

void Delivery::removeVal(Produce* arr, int index, bool isprodList){
    int size;
    int maxSize;
    if (isprodList){
        size = prodListSize;
        maxSize = prodListMaxSize;
    }
    else{
        size = deliveryBoxListSize;
        maxSize = deliveryBoxListMaxSize;
    }
    Produce* temp = new Produce[maxSize];
    int newIndex = 0;
    for (int i = 0; i < size; i++){
        if (i == index){
        }
        else{
            temp[newIndex] = Produce(arr[i]);
            newIndex++;
        }
    }
    if (isprodList){
        prodListSize--;
        delete[] produceList;
        produceList = temp;
        temp = nullptr;
    }
    else{
        deliveryBoxListSize--;
        delete[] deliveryBox;
        deliveryBox = temp;
        temp = nullptr;
    }
}
