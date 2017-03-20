/* 
 * File:   Item.h
 * Author: jhayes
 *
 */

#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Item {
public:
    Item(int id, int length, int quantity, double weight);
    Item(const Item& obj);
    virtual ~Item();
    void printItem();
    int getLength();
    int getCount();
    double getWeight();
    void setQuantity(int quantity);
private:
    int item_id;
    int item_length;
    int item_quantity;
    double piece_weight;
};

#endif /* ITEM_H */

