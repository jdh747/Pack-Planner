/* 
 * File:   main.cpp
 * Author: jhayes
 *
 * Created on 18 March 2017, 8:47 PM
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