//
// Created by Itamar on 08/06/2022.
//

#include "Truck.h"

uint Truck::getCratesNum() const {
    return crates_num;
}

void Truck::setCratesNum(uint cratesNum) {
    crates_num = cratesNum;
}

const queue<weak_ptr<Warehouse>> &Truck::getWarehouseQ() const {
    return warehouse_q;
}



const queue<pair<double, double>> &Truck::getArriveDepartQ() const {
    return arrive_depart_q;
}



void Truck::update() {

}

void Truck::broadcast_status() {

}

void Truck::unload(uint crates) {
    crates_num -= crates;
    curr_warehouse.lock()->setInventory(crates);
}

const weak_ptr<Warehouse> &Truck::getCurrWarehouse() const {
    return curr_warehouse;
}

void Truck::setCurrWarehouse(const weak_ptr<Warehouse> &currWarehouse) {
    curr_warehouse = currWarehouse;
}

const queue<uint> &Truck::getCratesQ() const {
    return crates_q;
}

