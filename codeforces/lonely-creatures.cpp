#include <bits/stdc++.h>
using namespace std;

using ld = long double;
const ld EPS = 1e-12L;

struct Point {
    ld x, y;
    bool operator<(Point const &o) const {
        if (fabsl(x - o.x) > EPS) return x < o.x;
        return y + EPS < o.y;
    }
};

struct Segment {
    Point a, b;
    int id;
    void normalize() {
        if (a.x > b.x || (fabsl(a.x - b.x) < EPS && a.y > b.y)) swap(a, b);
    }
};

// cross / orient / on-segment helpers
ld cross(ld x1, ld y1, ld x2, ld y2) { return x1*y2 - x2*y1; }
ld orient(const Point &A, const Point &B, const Point &C) {
    return cross(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
}
bool on_segment(const Point &A, const Point &B, const Point &P) {
    return (min(A.x,B.x) - EPS <= P.x && P.x <= max(A.x,B.x) + EPS &&
            min(A.y,B.y) - EPS <= P.y && P.y <= max(A.y,B.y) + EPS);
}

// Return all intersection points between two segments (empty if none).
vector<Point> segment_intersections(const Segment &s1, const Segment &s2) {
    const Point &a = s1.a, &b = s1.b, &c = s2.a, &d = s2.b;
    ld A1 = b.y - a.y, B1 = a.x - b.x, C1 = A1*a.x + B1*a.y;
    ld A2 = d.y - c.y, B2 = c.x - d.x, C2 = A2*c.x + B2*c.y;
    ld det = A1*B2 - A2*B1;
    vector<Point> res;
    if (fabsl(det) < EPS) {
        // Parallel or collinear: collect any endpoints that lie on the other segment
        if (fabsl(orient(a,b,c)) < 1e-10L && on_segment(a,b,c)) res.push_back(c);
        if (fabsl(orient(a,b,d)) < 1e-10L && on_segment(a,b,d)) res.push_back(d);
        if (fabsl(orient(c,d,a)) < 1e-10L && on_segment(c,d,a)) res.push_back(a);
        if (fabsl(orient(c,d,b)) < 1e-10L && on_segment(c,d,b)) res.push_back(b);
        sort(res.begin(), res.end(), [](const Point &p1, const Point &p2){
            if (fabsl(p1.x - p2.x) > EPS) return p1.x < p2.x;
            return p1.y < p2.y;
        });
        // deduplicate within EPS
        vector<Point> uniq;
        for (auto &p : res) {
            if (uniq.empty() || fabsl(uniq.back().x - p.x) > 1e-9L || fabsl(uniq.back().y - p.y) > 1e-9L)
                uniq.push_back(p);
        }
        return uniq;
    } else {
        ld ix = (B2*C1 - B1*C2) / det;
        ld iy = (A1*C2 - A2*C1) / det;
        Point ip{ix, iy};
        if (on_segment(a,b,ip) && on_segment(c,d,ip)) res.push_back(ip);
        return res;
    }
}

// global sweep_x used by status comparator
static ld sweep_x = 0;

// y of a segment at given x (clamped to endpoints if outside)
ld seg_y_at_x(const Segment *s, ld x) {
    if (fabsl(s->a.x - s->b.x) < EPS) {
        // vertical segment -> deterministic: use lower y
        return min(s->a.y, s->b.y);
    }
    ld t = (x - s->a.x) / (s->b.x - s->a.x);
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    return s->a.y + t * (s->b.y - s->a.y);
}

// status comparator: order segments by y at sweep_x, break ties by id
struct SegComp {
    bool operator()(const Segment *s1, const Segment *s2) const {
        ld y1 = seg_y_at_x(s1, sweep_x);
        ld y2 = seg_y_at_x(s2, sweep_x);
        if (fabsl(y1 - y2) > EPS) return y1 < y2;
        return s1->id < s2->id;
    }
};

// event types and event struct
enum EvType { LEFT = 0, INTER = 1, RIGHT = 2 }; // important: INTER between LEFT and RIGHT
struct Event {
    Point p;
    EvType type;
    Segment *s1;
    Segment *s2; // used only for intersection events
};

// comparator for event ordering in set/multiset
struct EventCmp {
    bool operator()(Event const &a, Event const &b) const {
        if (fabsl(a.p.x - b.p.x) > EPS) return a.p.x < b.p.x;
        if (fabsl(a.p.y - b.p.y) > EPS) return a.p.y < b.p.y;
        return a.type < b.type; // LEFT < INTER < RIGHT
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<Segment> segs(n);
    for (int i = 0; i < n; ++i) {
        ld x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segs[i].a = {x1,y1};
        segs[i].b = {x2,y2};
        segs[i].id = i;
        segs[i].normalize();
    }

    multiset<Event, EventCmp> events;
    for (int i = 0; i < n; ++i) {
        events.insert(Event{segs[i].a, LEFT, &segs[i], nullptr});
        events.insert(Event{segs[i].b, RIGHT, &segs[i], nullptr});
    }

    set<Segment*, SegComp> status;
    vector<Point> intersections;

    // scheduled set must distinguish same pair with different intersection points:
    // key = (minid, maxid, rx, ry) where rx/ry are rounded integers of coordinates
    auto round_key = [&](const Point &p)->pair<long long,long long>{
        long long rx = llround((double)p.x * 1e12);
        long long ry = llround((double)p.y * 1e12);
        return {rx, ry};
    };
    set<tuple<int,int,long long,long long>> scheduled;

    auto schedule_intersection_events = [&](Segment *s1, Segment *s2, ld now_x) {
        if (!s1 || !s2) return;
        if (s1->id == s2->id) return;
        vector<Point> ips = segment_intersections(*s1, *s2);
        for (auto &ip : ips) {
            if (ip.x + EPS < now_x) continue; // already to the left
            int a = min(s1->id, s2->id), b = max(s1->id, s2->id);
            auto rk = round_key(ip);
            auto key = make_tuple(a, b, rk.first, rk.second);
            if (scheduled.count(key)) continue;
            scheduled.insert(key);
            events.insert(Event{ip, INTER, s1, s2});
        }
    };

    auto find_in_status = [&](Segment *s) -> set<Segment*,SegComp>::iterator {
        return status.find(s);
    };

    while (!events.empty()) {
        Event ev = *events.begin();
        events.erase(events.begin());
        sweep_x = ev.p.x;

        if (ev.type == LEFT) {
            Segment *s = ev.s1;
            auto it_pair = status.insert(s);
            auto it = it_pair.first;
            Segment *below = nullptr, *above = nullptr;
            if (it != status.begin()) { auto it_prev = it; --it_prev; below = *it_prev; }
            { auto it_next = it; ++it_next; if (it_next != status.end()) above = *it_next; }
            schedule_intersection_events(s, below, sweep_x);
            schedule_intersection_events(s, above, sweep_x);

        } else if (ev.type == RIGHT) {
            Segment *s = ev.s1;
            auto it = find_in_status(s);
            if (it == status.end()) continue;
            Segment *below = nullptr, *above = nullptr;
            if (it != status.begin()) { auto it_prev = it; --it_prev; below = *it_prev; }
            { auto it_next = it; ++it_next; if (it_next != status.end()) above = *it_next; }
            status.erase(it);
            schedule_intersection_events(above, below, sweep_x);

        } else { // INTERSECTION
            Segment *s1 = ev.s1;
            Segment *s2 = ev.s2;
            // if both are present in status, record the intersection
            auto it1 = find_in_status(s1), it2 = find_in_status(s2);
            if (it1 == status.end() || it2 == status.end()) {
                // still record intersections if one of segments has endpoint exactly at event.x
                // but if both missing, skip
                if (it1 == status.end() && it2 == status.end()) continue;
            }
            // verify the point is still a valid intersection (robustness)
            vector<Point> ips = segment_intersections(*s1, *s2);
            bool found = false;
            for (auto &p : ips) {
                if (fabsl(p.x - ev.p.x) <= 1e-9L && fabsl(p.y - ev.p.y) <= 1e-9L) {
                    found = true; break;
                }
            }
            if (!found) continue;

            // record intersection
            intersections.push_back(ev.p);

            // if both present and adjacent, swap and reschedule neighbors (normal BO behaviour)
            if (it1 != status.end() && it2 != status.end()) {
                if (it1 != it2) {
                    auto it_low = it1, it_high = it2;
                    if (SegComp()(*it_high, *it_low)) swap(it_low, it_high); // ensure it_low < it_high
                    // check adjacency
                    auto it_next = it_low; ++it_next;
                    if (it_next == it_high) {
                        // adjacent: perform swap by erase+insert (ensures correct order at current sweep_x)
                        Segment *ls = *it_low, *hs = *it_high;
                        status.erase(it_low);
                        status.erase(it_high);
                        status.insert(hs);
                        status.insert(ls);
                        // find current positions
                        auto pos_h = status.find(hs);
                        auto pos_l = status.find(ls);
                        // neighbors to check
                        Segment *below = nullptr, *above = nullptr;
                        if (pos_h != status.begin()) { auto tmp = pos_h; --tmp; below = *tmp; }
                        { auto tmp = pos_l; ++tmp; if (tmp != status.end()) above = *tmp; }
                        schedule_intersection_events(below, hs, sweep_x);
                        schedule_intersection_events(ls, above, sweep_x);
                    }
                }
            }
            // if not adjacent or one missing in status, we still recorded the intersection
        }
    }

    // unique intersections with EPS
    sort(intersections.begin(), intersections.end(), [](const Point &A, const Point &B){
        if (fabsl(A.x - B.x) > EPS) return A.x < B.x;
        return A.y < B.y;
    });
    vector<Point> uniq;
    for (auto &p : intersections) {
        if (uniq.empty() || fabsl(uniq.back().x - p.x) > 1e-9L || fabsl(uniq.back().y - p.y) > 1e-9L)
            uniq.push_back(p);
    }

    cout.setf(std::ios::fixed);
    cout << setprecision(10);
    cout << uniq.size() << "\n";
    for (auto &p : uniq) cout << (double)p.x << " " << (double)p.y << "\n";
    return 0;
}
