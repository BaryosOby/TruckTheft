
#include "StateTrooper.h"

void StateTrooper::getClosestWarehouse() {
    double min_dist = UINT16_MAX;
    weak_ptr<Warehouse> curr_min;
    int count = 0;
    for (const auto &p: warehouses) {
        if (!p.second) {
            if (min_dist > distance(getLocation(), p.first.lock()->getLocation())) {
                min_dist = distance(getLocation(), p.first.lock()->getLocation());
                curr_min = p.first;
                warehouse_idx = count;
            } else if (min_dist == distance(getLocation(), p.first.lock()->getLocation())) {
                string w1 = curr_min.lock()->getName();
                string w2 = p.first.lock()->getName();
                unsigned int length = min(w1.size(), w2.size());
                for (int i = 0; i < length; ++i) {
                    if (w1[i] == w2[i]) continue;
                    else if (w1[i] < w2[i]) {
                        break;
                    } else {
                        min_dist = distance(getLocation(), p.first.lock()->getLocation());
                        curr_min = p.first;
                        warehouse_idx = count;
                        break;
                    }
                }
            }
        }
        count++;
    }
    if(min_dist == UINT16_MAX){
        tb.setDestination(init_location);
    }
    else{
        tb.setDestination(curr_min.lock()->getLocation());
    }

}

void StateTrooper::update(double general_time) {
    if(state == moving_dest){
        double time_to_arrive;
        double d = distance(tb.getLocation(), tb.getDestination());
        time_to_arrive = d / tb.getSpeed();
        if(time_to_arrive <= 1){
            drive(time_to_arrive);
            if(warehouses[warehouse_idx].first.lock()->getLocation() == tb.getDestination()){
                warehouses[warehouse_idx].second = true;
            }
            getClosestWarehouse();
        }
        else{
            drive();
        }
    }
    if(state == moving_course){
        drive();
    }
}

void StateTrooper::broadcast_status() {
    cout << "State Trooper " << name << " at ";
    tb.getLocation().print();
    if(state == moving_dest){
        cout << ", Heading to " << warehouses[warehouse_idx].first.lock()->getName();
    }
    else if(state == moving_course){
        cout << ", Heading on course " << setprecision(2) << tb.getCourse() << " degrees";
    }
    cout << ", speed " << setprecision(2) << tb.getSpeed() << " km/h" << endl;
}
