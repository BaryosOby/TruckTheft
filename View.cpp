#include "View.h"


Point View::normalize(const Point &p) const {
    int x = p.x / (100 * size);
    int y = p.y / (100 * size);
    Point r(x, y);
    return r;
}

map<Point, string> &View::objects_in_range() {
    double range_x = size * zoom + pan.x * zoom * 100;
    return ;
}

const Point &View::getPan() const {
    return pan;
}

void View::setPan(const Point &p) {
    View::pan = p;
}

double View::getZoom() const {
    return zoom;
}

void View::setZoom(double zm) {
    View::zoom = zm;
}

int View::getSize() const {
    return size;
}

void View::setSize(int sze) {
    View::size = sze;
}

View::View():pan(DEF_PAN, DEF_PAN), zoom(DEF_SCALE), size(DEF_SIZE) {
}

void View::pushObj(const shared_ptr<Sim_obj> &sp) {
    objects.push_back(sp);
}

void View::clear() {
    objects.clear();
}

void View::show() const {

}

