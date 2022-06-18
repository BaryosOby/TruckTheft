#include <iostream>
#include "Controller.h"


int main() {
//    auto v = View();
//    string s = "AAA";
//    string s1 = "BBB";
//    string s2 = "CCC";
//    string s3 = "DDD";
//    string s5 = "EEE";
//    auto r1 = make_shared<Truck>(Truck(s, 0, 0));
//    auto r2 = make_shared<Truck>(Truck(s1, 15, 25.2));
//    auto r3 = make_shared<Truck>(Truck(s2, 18, 5.2));
//    auto r4 = make_shared<Truck>(Truck(s3, 0.5, 0.5));
//    auto r5 = make_shared<Truck>(Truck(s5, 49.99, 5.2));
//    v.pushObj(r1);
//    v.pushObj(r2);
//    v.pushObj(r3);
//    v.pushObj(r4);
//    v.pushObj(r5);
//    //v.setPan(Point(2.5,3.5));
//    //v.setZoom(2.5);
//    map<pair<double,double>, string> map = v.objects_in_range();
//    v.show();

    Controller c;
    fstream dep;
    string dep_name = "depot.dat";
//    dep.open(dep_name, ios_base::in);
    c.parseWarehouse(dep_name, dep);
    string trk_name = "Godzilla.txt";
    fstream god;
//    dep.open(dep_name);
    c.parseTruck(trk_name, god);
    shared_ptr<View> v = make_shared<View>(View());
    Model::getInstance().attach(v);
//    Model::getInstance().broadcast_status();
    Point p(-10, -10);
    v->setPan(p);
    v->show();


    return 0;
}
