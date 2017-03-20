/* 
 * File:   Order.h
 * Author: jhayes
 *
 * Order class declaration. A class that fulfills orders outlined by std input.
 * Abstracts std input read (order and items), sorting, packing, and printing
 * processes. Storing ordered lists of items and packs, in addition to order
 * details.
 */

#ifndef ORDER_H
#define ORDER_H

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
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
    string sort;
    
    void storeOrder();
    void packItems();
    void sortItems();
};

#endif /* ORDER_H */

