/* 
 * File:   Pack.cpp
 * Author: jhayes
 * 
 * Created on 18 March 2017, 8:27 AM
 */

#include "Pack.h"

Pack::Pack(int pack_id, int max_items, double max_weight) : pack_id{pack_id}, max_items{max_items}, max_weight{max_weight} {
    this->pack_weight = this->pack_item_count = 0;
}

Pack::~Pack() {}

void Pack::printPack() {
    cout << "Pack Number: " << this->pack_id << endl;
    
    for(list<Item*>::iterator item = this->items.begin(); item != this->items.end(); item++) {
        (*item)->printItem();
    }
    
    cout << "Pack Length: " << this->packLength() << ", Pack Weight: " << this->pack_weight << endl;
}

int Pack::packLength() {
    // TODO can get rid of this sort by tracking longest item in fillPack()
    this->items.sort([](Item* a, Item* b) { return a->getLength() > b->getLength(); });
    return this->items.front()->getLength();
}

void Pack::fillPack(list<Item*>& fill_items) {
    while (!fill_items.empty()) {
        Item* item = fill_items.front();
        fill_items.pop_front();
        
        int new_count = this->pack_item_count + item->getCount();
        double new_weight = this->pack_weight + (item->getCount() * item->getWeight());
        
        if (this->max_items < new_count) {
            // Count runs over pack limit
            int fit = this->max_items - this->pack_item_count;
            int remain = item->getCount() - fit;
            this->distributeItems(fill_items, item, fit, remain);
            
            break;
        } else if (this->max_weight < new_weight) {
            // Weight runs over pack limit
            int fit = (int)floor((this->max_weight - this->pack_weight) / item->getWeight());
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