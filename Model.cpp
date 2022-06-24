#include "Model.h"
//cot'r
Model::Model() : time(0) {
    string name = "Frankfurt";
    auto frank = make_shared<Warehouse>(name, 40, 10, 100000);
    objs.push_back(frank);
    warehouses.push_back(frank);
}
//return true if object exist
bool Model::findObj(Sim_obj &obj) const {
    for (const auto &ob : objs) {
        if (ob->getName() == obj.getName()) {
            return true;
        }
    }
    return false;
}
// singleton kind of use
Model &Model::getInstance() {
    static Model mod;
    return mod;
}
// update all objets by getting 'go' command
void Model::update() {
    for (const auto &ob : objs) {
        ob->update(time);
    }
    time++;
}
// push object to general data structure and for its unique vector
void Model::pushObj(const shared_ptr<Sim_obj> &obj) {

    if (findObj(*obj)) {
        return;
    }

    objs.push_back(obj);
    if (view.lock() != nullptr) {
        view.lock()->pushObj(obj);
    }

    if (typeid(*obj) == typeid(Truck)) {
        trucks.push_back(dynamic_pointer_cast<Truck>(obj));
    }

    if (typeid(*obj) == typeid(Chopper)) {
        choppers.push_back(dynamic_pointer_cast<Chopper>(obj));
    }

    if (typeid(*obj) == typeid(StateTrooper)) {
        auto trop = dynamic_pointer_cast<StateTrooper>(obj);
        troops.push_back(trop);
        for (auto &w : warehouses) {
            trop->pushWarehouse(w);
        }
    }

    if (typeid(*obj) == typeid(Warehouse)) {
        warehouses.push_back(dynamic_pointer_cast<Warehouse>(obj));
    }
}
//after init attach objects to view
void Model::attach(shared_ptr<View> &v) {
    view = v;
    for (const auto &ob : objs) {
        view.lock()->pushObj(ob);
    }
}
//find trooper
bool Model::findTroop(const Truck &t) const {
    for (const auto &troop : troops) {
        if (t.check_radius(troop.lock()->getLocation(), 0.1)) {
            return true;
        }
    }
    return false;
}

//print all objects status
void Model::broadcast_status() const {
    for (const auto &ob : objs) {
        ob->broadcast_status();
    }
}

double Model::getTime() const {
    return time;
}
// chopper try to attack given truck
void Model::attackByName(const string &chop_name, const string &truck_name) {
    auto chop = dynamic_pointer_cast<Chopper>(getVehicleByName(chop_name));
    auto truck = dynamic_pointer_cast<Truck>(getVehicleByName(truck_name));
    if (chop == nullptr) {
        throw invalidNameException(chop_name);
    }
    if (chop == nullptr) {
        throw invalidNameException(truck_name);
    }
    if (chop->check_radius(truck->getLocation(), chop->getAttackRadius())) {
        if (findTroop(*truck)) {
            chop->setAttackRadius(-0.01);
        } else {
            chop->setAttackRadius(0.01);
            truck->setState(off_road);
            truck->setCratesNum(0);
        }
        chop->setState(stopped);
    }
}

// find vehicle by name
shared_ptr<Vehicle> Model::getVehicleByName(const string &name) {
    for (const auto &ob : objs) {
        if (ob->getName() == name) {
            return dynamic_pointer_cast<Vehicle>(ob);
        }
    }
    return shared_ptr<Vehicle>();
}

// find warehouse by name
weak_ptr<Warehouse> Model::getWareByName(const string &name) { //TODO combine with getV
    for (const auto &ob : warehouses) {
        if (ob.lock()->getName() == name) {
            return ob;
        }
    }
    return weak_ptr<Warehouse>();
}
