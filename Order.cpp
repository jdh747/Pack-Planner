/* 
 * File:   Order.cpp
 * Author: jhayes
 * 
 */

#include "Order.h"

Order::Order() {}

Order::~Order() {
    // Free dynamically allocated pack objects
    for(list<Pack*>::iterator pack = this->packs.begin(); pack != this->packs.end(); pack++) {
        delete *pack;
    }
}

void Order::getOrder() {
    this->storeOrder();
    this->packItems();
}

void Order::printPlan() {
    // Iterate over packs, printing details including: pack id, list of items
    // and their details, length of largest item in pack, and combined pack weight
    for(list<Pack*>::iterator pack = this->packs.begin(); pack != this->packs.end(); pack++) {
        (*pack)->printPack();
        cout << endl;
    }
}

void Order::storeOrder() {
    // Note: implicitly stoi and stod strip trailing non-numeric characters. 
    // Additional error checking would be required to reject inputs with 
    // this characteristic
    string line, token;
    
    try {
        // Store order details
        getline(cin, line);
        istringstream ss(line);
        getline(ss, this->sort, ',');
        getline(ss, token, ',');
        this->max_items = stoi(token);
        getline(ss, token);
        this->max_weight = stod(token);
        if (!ss.eof()) {
            throw;
        }
        
        // Store item details
        while (getline(cin, line)) {
            if (!line.empty()) {
                istringstream ss(line);
                getline(ss, token, ',');
                int id = stoi(token);
                getline(ss, token, ',');
                int length = stoi(token);
                getline(ss, token, ',');
                int quantity = stoi(token);
                getline(ss, token);
                double weight = stod(token);
                this->items.push_back(new Item(id, length, quantity, weight));
                if (!ss.eof()) {
                    throw;
                }
            } else {
                break;
            }
        }
    } catch (const exception& e) {
        cout << "Error: invalid input";
    }
}

void Order::packItems() {
    // Sort items by length as per order, then iterate over items to arrange
    // into a list of Pack objects that meet weight and quantity restrictions
    int pack_num = 0;
    this->sortItems();
    while (!this->items.empty()) {
        pack_num++;
        this->packs.push_back(new Pack(pack_num, this->max_items, this->max_weight));
        this->packs.back()->fillPack(this->items);
    }
}

void Order::sortItems() {
    // Sort stored list of items depending on ordering given with order: item
    // length ascending or descending, or in the order given (natural)
    if (this->sort == "SHORT_TO_LONG") {
        this->items.sort([](Item* a, Item* b) { return a->getLength() < b->getLength(); });
    } else if (this->sort == "LONG_TO_SHORT") {
        this->items.sort([](Item* a, Item* b) { return a->getLength() > b->getLength(); });
    } else if(this->sort == "NATURAL") {
        // Leave ordering as is
    } else {
        cout << "Error: invalid ordering";
        exit(EXIT_FAILURE);
    }
}