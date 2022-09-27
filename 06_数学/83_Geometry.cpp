using Point = std::complex<double>;
 
#define x real
#define y imag
 
double dot(const Point &a, const Point &b) {
    return (std::conj(a) * b).x();
}
 
double cross(const Point &a, const Point &b) {
    return (std::conj(a) * b).y();
}

struct Line {
    Point a;
    Point b;
    Line(const Point &a, const Point &b) : a(a), b(b) {}
};
 
Point rotate(const Point &a) {
    return Point(-a.y(), a.x());
}
 
int sgn(const Point &a) {
    return a.y() > 0 || (a.y() == 0 && a.x() > 0) ? 1 : -1;
}
 
bool onLeft(const Point &a, const Line &l) {
    return cross(l.b - l.a, a - l.a) > 0;
}

Point intersection(const Line &l1, const Line &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

std::vector<Point> hp(std::vector<Line> lines) {
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
         
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
         
        return cross(d1, d2) > 0;
    });
     
    std::deque<Line> ls;
    std::deque<Point> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
         
        while (!ps.empty() && !onLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }
         
        while (!ps.empty() && !onLeft(ps[0], l)) {
            ps.pop_front();
            ls.pop_front();
        }
         
        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                 
                if (!onLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
         
        ps.push_back(intersection(ls.back(), l));
        ls.push_back(l);
    }
     
    while (!ps.empty() && !onLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.push_back(intersection(ls[0], ls.back()));
     
    return std::vector<Point>(ps.begin(), ps.end());
}