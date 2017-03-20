/* 
 * File:   Order.cpp
 * Author: jhayes
 * 
 */

#include "Order.h"

Order::Order() {}

Order::~Order() {}

void Order::getOrder() {
    this->storeOrder();
    this->storeItems();
    this->packItems();
}

void Order::printPlan() {
    for(list<Pack*>::iterator pack = this->packs.begin(); pack != this->packs.end(); pack++) {
        (*pack)->printPack();
        cout << endl;
    }
}

void Order::storeOrder() {
    string line, token;
    double max_weight;
    
    // Store order details
    // TODO catch bad input
    try {
        getline(cin, line);
        istringstream ss(line);
        getline(ss, this->ordering, ',');
        getline(ss, token, ',');
        this->max_items = stoi(token);
        getline(ss, token, ',');
        this->max_weight = stod(token);    
    } catch (const exception& e) {
        cout << "Error: invalid input";
    }
}

void Order::storeItems() {
    string line;
    int id, length, quantity;
    double weight;
    
    // Store item details
    // TODO ensure getline does the right thing at eof
    // TODO catch bad input
    while (getline(cin, line)) {
        if (!line.empty()) {
            sscanf(line.c_str(), "%d,%d,%d,%lf", &id, &length, &quantity, &weight);
            this->items.push_back(new Item(id, length, quantity, weight));
        } else {
            break;
        }
    }
}

void Order::packItems() {
    int pack_num = 0;
    this->sortItems();
    while (!this->items.empty()) {
        pack_num++;
        this->packs.push_back(new Pack(pack_num, this->max_items, this->max_weight));
        this->packs.back()->fillPack(this->items);
    }
}

void Order::sortItems() {
    // TODO enumerate ordering?
    if (this->ordering == "SHORT_TO_LONG") {
        this->items.sort([](Item* a, Item* b) { return a->getLength() < b->getLength(); });
    } else if (this->ordering == "LONG_TO_SHORT") {
        this->items.sort([](Item* a, Item* b) { return a->getLength() > b->getLength(); });
    } else if(this->ordering == "NATURAL") {
        // Leave ordering as is
    } else {
        cout << "Error: invalid ordering";
        exit(EXIT_FAILURE);
    }
}