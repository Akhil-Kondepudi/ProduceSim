//Author: Akhil Kondepudi
//Date: 3-2-2022
//Revision History: Created the file -Akhil Kondepudi

#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include "customer.h"
#include "segmentCustomer.h"
#include "pickyCustomer.h"
#include "delivery.h"
#include "produce.h"

using namespace std;

const string filename = "C:\\Users\\junnu\\Desktop\\C# Projects\\P4\\ProduceListTabDelimited-1.txt";
static string names[] = { "Celery Root", "Parsely", "Pear", "Cilantro", "Orange", "Apple", "Crimini", "Potato", "Sage", "Spinach", "Kiwi" };
const int namesSize = 11;
static string classific[] = { "fruit", "vegetable", "fungi", "herb" };
const int classificSize = 4;
const string currDate = "1-10-2022-1200";
const int listMaxSize = 40;
const int numClass = 3;
const int maxIntAdditionSubtraction = 5;
const double maxDoubleAdditionSubtraction = 10.0;

static void welcomeMessage();
static void goodbyeMessage();
static void populateProduce(vector<Produce> produceList);
static shared_ptr<SegmentCustomer> randSegmentCustomer();
static shared_ptr<PickyCustomer> randPickyCustomer();
static shared_ptr<Customer> randCustomer();
static void testAddProduce(Produce p);
static void testSubProduce(Produce p);
static void testAddCustomer(shared_ptr<Customer> c);
static void testSubCustomer(shared_ptr<Customer> c);
static void testCustomerCopy(Customer c);
static void testDeliveryCopy(Delivery d);
static void theWorks(Delivery d);


int main() {
    welcomeMessage();
    vector<shared_ptr<Customer>> custList;
    vector<Delivery> deliList;
    vector<Produce> ProdList;
    populateProduce(ProdList);
    for(int i = 0; i < ProdList.size(); i++){
        testAddProduce(ProdList[i]);
        testSubProduce(ProdList[i]);
    }
    int upper = rand() % listMaxSize;
    int num;
    for (int i = 0; i < upper; i++){
        num = rand() % numClass;
        if (num % numClass == 0){
            custList.push_back(randCustomer());
        }
        else if (num % numClass == 1){
            custList.push_back(randPickyCustomer());
        }
        else{
            custList.push_back(randSegmentCustomer());
        }
    }
    for(int i = 0; i < upper; i++){
        testAddCustomer(custList[i]);
        testSubCustomer(custList[i]);
        testCustomerCopy(*custList[i]);
    }
    for(int i = 0; i < upper; i++){
        deliList.push_back(Delivery(custList[i].get(), filename));
    }
    for(int i = 0; i < upper; i++){
        testDeliveryCopy(deliList[i]);
        theWorks(deliList[i]);
    }

    goodbyeMessage();
    return 0;
}

static void welcomeMessage()
{
    cout << "Welcome to the Driver Demo" << endl;
}

static void goodbyeMessage()
{
    cout << "The program has ended." << endl;
}

static shared_ptr<Customer> randCustomer()
{
    shared_ptr<Customer> output (new Customer("", "", (rand() % 10000 + 100) / 100.00, (rand() % 10000 + 100) / 100.00));
    return output;
}

static shared_ptr<PickyCustomer> randPickyCustomer()
{
    shared_ptr<PickyCustomer> pc (new PickyCustomer("", "", (rand() % 10000 + 100) / 100.00, (rand() % 10000 + 100) / 100.00));
    int upper = rand() % 10;
    for (int x = 0; x < upper; x++)
    {
        pc->addExclusion(names[rand() % namesSize]);
    }
    return pc;
}

static shared_ptr<SegmentCustomer> randSegmentCustomer()
{
    shared_ptr<SegmentCustomer> sc (new SegmentCustomer("", "", (rand() % 10000 + 100) / 100.00, (rand() % 10000 + 100) / 100.00));
    int upper = rand() % 4;
    for (int i = 0; i < upper; i++)
    {
        sc->addClassification(classific[rand() % classificSize]);
    }
    return sc;
}

static void theWorks(Delivery d)
{
    int size = rand() % namesSize;
    string* wanted = new string[size];
    for(int i = 0; i < size; i++){
        wanted[i] = names[rand() % namesSize];
    }
    Produce* ptr = new Produce[0];
    d.ForcastDelivery(wanted, size);
    d.FillBox(ptr, 0, currDate);
    d.DeliverBox(currDate);
}

static void populateProduce(vector<Produce> produceList){
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
                }
                else {
                    cnt = round(stod(item[1]));
                    cost = stod(item[3]);
                }
                produceList.push_back(Produce(item[0], cnt, cost, item[2], item[4], item[5], harvdate, item[5], expiredate));
            }
        }
    }
}

static void testAddProduce(Produce p){
    bool test = (rand() % 2) == 0; //for random testing of object
    if(test){
        int randVal = rand() % maxIntAdditionSubtraction;
        p += randVal;
        Produce c = randVal + p;
        Produce p = p + randVal;
        p++;
        ++p;
    }
}

static void testSubProduce(Produce p){
    bool test = (rand() % 2) == 0; //for random testing of object
    if(test){
        int randVal = rand() % maxIntAdditionSubtraction;
        p -= randVal;
        Produce c = randVal - p;
        Produce p = p - randVal;
        p--;
        --p;
    }
}

static void testAddCustomer(shared_ptr<Customer> c){
    bool test = (rand() % 2) == 0; //for random testing of object
    if(test){
        int randVal = rand() % maxIntAdditionSubtraction;
        *c += randVal;
        Customer p = *c + randVal;
        Customer d = randVal + p;
    }
}

static void testSubCustomer(shared_ptr<Customer> c){
    bool test = (rand() % 2) == 0; //for random testing of object
    if(test){
        int randVal = rand() % maxIntAdditionSubtraction;
        *c -= randVal;
        Customer p = *c - randVal;
        Customer d = randVal - p;
    }
}

static void testCustomerCopy(Customer c){
    bool test = (rand() % 2) == 0; //for random testing of object
    if(test){
        Customer copy = Customer(c);
        Customer copy2 = c;
    }
}
static void testDeliveryCopy(Delivery d){
    bool test = (rand() % 2) == 0; //for random testing of object
    if(test){
        Delivery copy = Delivery(d);
        Delivery copy2 = d;
    }
}