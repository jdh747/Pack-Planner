/* 
 * File:   Pack.cpp
 * Author: jhayes
 * 
 */

#include "Pack.h"

Pack::Pack(int pack_id, int max_items, double max_weight) : pack_id{pack_id}, max_items{max_items}, max_weight{max_weight} {
    this->pack_weight = this->pack_item_count = this->pack_length = 0;
}

Pack::~Pack() {
    // Free dynamically allocated item objects
    for(list<Item*>::iterator item = this->items.begin(); item != this->items.end(); item++) {
        delete *item;
    }
}

void Pack::printPack() {
    cout << "Pack Number: " << this->pack_id << endl;
    
    // Print each item in pack. Includes item: id, length, quantity, and weight
    for(list<Item*>::iterator item = this->items.begin(); item != this->items.end(); item++) {
        (*item)->printItem();
    }
    
    // Print length of largest item in pack and combined weight of all items
    auto packLength = [this]() { return (*max_element(this->items.begin(), this->items.end(), [](Item* a, Item* b) { return a->getLength() < b->getLength(); }))->getLength(); };
    cout << "Pack Length: " << packLength() << ", Pack Weight: " << this->pack_weight << endl;
}

void Pack::fillPack(list<Item*>& fill_items) {
    // Iterate over list of items, popping items off and adding them to packs
    // until list is empty, or pack exceeds weight or count requirements
    while (!fill_items.empty()) {
        // Pop next item off order list for addition to current pack, or
        // splitting of item quantity over this pack and the next
        Item* item = fill_items.front();
        fill_items.pop_front();
        
        // Utilities for computing item quantity that fills weight restriction,
        // and determines whether pack count is exceeded given a count of the
        // current item
        auto weightFitCalc = [this, item]() { return (int)floor((this->max_weight - this->pack_weight) / item->getWeight()); };
        auto weightOver = [this, item](int count) { return this->max_weight < this->pack_weight + (count * item->getWeight()); };
        
        bool over_count = this->max_items < this->pack_item_count + item->getCount();
        bool over_weight = weightOver(item->getCount());
        
        if (over_count || over_weight) {
            // Count or weight runs over pack limit
            int fit = over_count ? this->max_items - this->pack_item_count : weightFitCalc();
            
            // Fitting to count still exceeds weight limit
            fit = weightOver(fit) ? weightFitCalc() : fit;
            
            // Distribute item quantity between this and next pack
            int remain = item->getCount() - fit;
            this->distributeItems(fill_items, item, fit, remain);
            break;
        } else {
            // All items fit in pack
            this->items.push_back(item);
            this->incrementMetrics(item->getCount(), item->getCount() * item->getWeight());
        }
    }
}

void Pack::incrementMetrics(int add_count, double add_weight) {
    this->pack_item_count += add_count;
    this->pack_weight += add_weight;
}

void Pack::distributeItems(list<Item*>& fill_items, Item* item, int fit, int remain) {
    // Fill available space in current pack
    this->items.push_back(new Item(*item));
    this->items.back()->setQuantity(fit);
    this->incrementMetrics(fit, fit * item->getWeight());

    // Add remaining items back to fill order
    item->setQuantity(remain);
    fill_items.push_front(item);
}