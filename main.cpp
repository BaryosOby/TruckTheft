#include <iostream>
#include "View.h"


int main() {
    auto v = View();
    string s = "AAA";
    string s1 = "BBB";
    string s2 = "CCC";
    string s3 = "DDD";
    string s5 = "EEE";
    auto r1 = make_shared<Truck>(Truck(s, 0, 0));
    auto r2 = make_shared<Truck>(Truck(s1, 1500, 2520));
    auto r3 = make_shared<Truck>(Truck(s2, 18000, 520));
    auto r4 = make_shared<Truck>(Truck(s3, 5001, 4700));
    auto r5 = make_shared<Truck>(Truck(s5, 4999, 520));
    v.pushObj(r1);
    v.pushObj(r2);
    v.pushObj(r3);
    v.pushObj(r4);
    v.pushObj(r5);
//    v.setPan(Point(2.5,3));
//    v.setZoom(2.5);
    map<pair<double,double>, string> map = v.objects_in_range();
    v.show();

    return 0;
}
