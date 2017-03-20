/* 
 * File:   Order.h
 * Author: jhayes
 *
 */

#ifndef ORDER_H
#define ORDER_H

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include "Pack.h"
#include "Item.h"

using namespace std;

class Order {
public:
    Order();
    virtual ~Order();
    void getOrder();
    void printPlan();
private:
    list<Pack*> packs;
    list<Item*> items;
    int max_items;
    double max_weight;
    string ordering;
    
    void storeOrder();
    void storeItems();
    void packItems();
    void sortItems();
};

#endif /* ORDER_H */

