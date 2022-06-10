
#include "StateTrooper.h"

void StateTrooper::getClosestWarehouse() {
    double min_dist = UINT16_MAX;
    weak_ptr<Warehouse> curr_min;
    for (const auto &p: warehouses) {
        if (!p.second) {
            if (min_dist > distance(getLocation(), p.first.lock()->getLocation())) {
                min_dist = distance(getLocation(), p.first.lock()->getLocation());
                tb.setDestination(p.first.lock()->getLocation());
                curr_min = p.first;
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
                        tb.setDestination(p.first.lock()->getLocation());
                        curr_min = p.first;
                    }
                }
            }
        }
    }
}
