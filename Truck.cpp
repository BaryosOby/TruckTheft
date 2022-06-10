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


void Truck::update(double general_time) {
    // track is done
    if(warehouse_q.empty()){
        state = stopped;
    }

    // arriving to destination.
    if(state == moving && tb.getLocation() == tb.getDestination()){
        state = parked;
        unload();
        next_warehouse = warehouse_q.front();
        warehouse_q.pop();
        next_arrive = arrive_depart_q.front().first;
        next_depart = arrive_depart_q.front().second;
        arrive_depart_q.pop();
        next_unload = crates_q.front();
        crates_q.pop();
        setSpeedByDriveTime();
        tb.setDestination(next_warehouse.lock()->getLocation());
    }
    double time = 1;
    // going to the next warehouse.
    if(state == parked && general_time - next_depart >= 0){
        time = general_time - next_depart;
        state = moving;
    }
    if(state == moving){
        drive(time);
    }

}

void Truck::broadcast_status() {
    // Truck Godzilla at (37.14, 10.00), Heading to Lille, Crates: 105
    cout << "Truck " << name << "at ";
    tb.getLocation().print();
    if(state == moving){
        cout << ", Heading to " << next_warehouse.lock()->getName();
    }
    cout << ", Crates: " << crates_num << endl;
}

void Truck::unload() {
    crates_num -= next_unload;
    next_warehouse.lock()->setInventory(next_unload);
}

const weak_ptr<Warehouse> &Truck::getCurrWarehouse() const {
    return next_warehouse;
}

void Truck::setCurrWarehouse(const weak_ptr<Warehouse> &currWarehouse) {
    next_warehouse = currWarehouse;
}

const queue<uint> &Truck::getCratesQ() const {
    return crates_q;
}

void Truck::setSpeedByDriveTime() {
    double dist = distance(next_warehouse.lock()->getLocation(), warehouse_q.front().lock()->getLocation());
    double t = arrive_depart_q.front().first - next_depart;
    tb.setSpeed(dist / t);
}

