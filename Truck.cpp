#include "Truck.h"

int Truck::getCratesNum() const {
    return crates_num;
}

void Truck::setCratesNum(int cratesNum) {
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

    // arriving to position.
    if(state == moving_dest && tb.getLocation() == tb.getDestination()){
        state = parked;
        unload();
        setNextWarehouse();
        setSpeedByDriveTime();
        tb.setDestination(next_warehouse.lock()->getLocation());
    }
    double time = 1;
    // going to the next warehouse.
    if(state == parked && general_time - next_depart >= 0){
        time = general_time - next_depart;
        state = moving_dest;
    }
    if(state == moving_dest){
        drive(time);
    }

}

void Truck::broadcast_status() {
    // Truck Godzilla at (37.14, 10.00), Heading to Lille, Crates: 105
    cout << "Truck " << name << "at ";
    tb.getLocation().print();
    if(state == moving_dest){
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

void Truck::setNextWarehouse() {
    next_warehouse = warehouse_q.front();
    warehouse_q.pop();
    next_arrive = arrive_depart_q.front().first;
    next_depart = arrive_depart_q.front().second;
    arrive_depart_q.pop();
    next_unload = crates_q.front();
    crates_q.pop();
}

const queue<int> &Truck::getCratesQ() const {
    return crates_q;
}

void Truck::setSpeedByDriveTime() {
    double dist = distance(next_warehouse.lock()->getLocation(), warehouse_q.front().lock()->getLocation());
    double t = arrive_depart_q.front().first - next_depart;
    tb.setSpeed(dist / t);
}

