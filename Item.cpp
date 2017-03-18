/* 
 * File:   Item.cpp
 * Author: jhayes
 * 
 * Created on 18 March 2017, 8:20 AM
 */

#include "Item.h"

Item::Item(int id, int length, int quantity, double weight) : item_id{id}, item_length{length}, item_quantity{quantity}, piece_weight{weight} {}

Item::Item(const Item& obj) {
    this->item_id = obj.item_id;
    this->item_length = obj.item_length;
    this->item_quantity = obj.item_quantity;
    this->piece_weight = obj.piece_weight;
}

Item::~Item() {
}

void Item::printItem() {
    cout << this->item_id << ", " << this->item_length << ", " << this->item_quantity << ", " << this->piece_weight << endl;
}

int Item::getLength() {
    return this->item_length;
}

double Item::getWeight() {
    return this->piece_weight;
}

int Item::getCount() {
    return this->item_quantity;
}

void Item::setQuantity(int quantity) {
    this->item_quantity = quantity;
}