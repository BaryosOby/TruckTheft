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

//update after givven 'go' command
void Truck::update(double general_time) {
    double prev_depart = next_depart;
    // track is done
    if (warehouse_q.empty()) {
        state = stopped;
    }

    // arriving to position.
    if (state == moving_dest && tb.getLocation() == tb.getDestination()) {
        state = parked;
        unload();
        setSpeedByDriveTime();
        setNextWarehouse();
        tb.setDestination(next_warehouse.lock()->getInitLocation());
    }
    double time = 1;
    // going to the next warehouse.
    if (state == parked &&  prev_depart - general_time >= 0) { // change here
        time = general_time + 1 - prev_depart;
        state = moving_dest;
    }
    if (state == moving_dest) {
        if (general_time == 0) {
            double dist = distance(tb.getLocation(), next_warehouse.lock()->getInitLocation());
            double t = next_arrive;
            tb.setSpeed(dist / t);
        }
        if(next_arrive - general_time >= 0 && next_arrive - general_time < 1) time = (1 - abs(general_time - next_arrive)); //added here
        drive(time);
    }

}
//print status
void Truck::broadcast_status() {
    // Truck Godzilla at (37.14, 10.00), Heading to Lille, Crates: 105
    cout << "Truck " << name << " at ";
    tb.getLocation().print();
    if (state == moving_dest) {
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
//set next details for truck
void Truck::setNextWarehouse() {
    next_warehouse = warehouse_q.front();
    warehouse_q.pop();
    next_arrive = arrive_depart_q.front().first;
    next_depart = arrive_depart_q.front().second;
    arrive_depart_q.pop();
    next_unload = crates_q.front();
    crates_q.pop();
    tb.setDestination(next_warehouse.lock()->getInitLocation());
}

const queue<int> &Truck::getCratesQ() const {
    return crates_q;
}
//set speed according to arrive time for next destination
void Truck::setSpeedByDriveTime() {
    double dist = distance(next_warehouse.lock()->getInitLocation(), warehouse_q.front().lock()->getInitLocation());
    double t = arrive_depart_q.front().first - next_depart;
    tb.setSpeed(dist / t);
}

