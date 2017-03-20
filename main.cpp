/* 
 * File:   main.cpp
 * Author: jhayes
 *
 */

#include <cstdlib>
#include "Order.h"

int main(int argc, char** argv) {
    Order order;
    order.getOrder();
    order.printPlan();
}

//TODO free memory
//TODO unit testing