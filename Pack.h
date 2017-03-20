/* 
 * File:   Pack.h
 * Author: jhayes
 *
 * Pack class declaration. An object that contains a list of item objects
 * sorted as per order, and limited by weight and number of items. Also
 * possesses ident.
 */

#ifndef PACK_H
#define PACK_H

#include <list>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "Item.h"

using namespace std;

class Pack {
public:
    Pack(int pack_id, int max_items, double max_weight);
    virtual ~Pack();
    void printPack();
    void fillPack(list<Item*>& items);
private:
    int pack_id;
    int pack_item_count;
    int max_items;
    int pack_length;
    double max_weight;
    double pack_weight;
    list<Item*> items;
    
    void incrementMetrics(int add_count, double add_weight);
    void distributeItems(list<Item*>& fill_items, Item* item, int fit, int remain);
};

#endif /* PACK_H */

