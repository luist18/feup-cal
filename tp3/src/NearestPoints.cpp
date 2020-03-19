/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
    this->dmin = dmin;
    this->p1 = p1;
    this->p2 = p2;
}

Result::Result() {
    this->dmin = MAX_DOUBLE;
    this->p1 = Point(0, 0);
    this->p2 = Point(0, 0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right) {
    std::sort(v.begin() + left, v.begin() + right + 1,
              [](Point p, Point q) { return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right) {
    std::sort(v.begin() + left, v.begin() + right + 1,
              [](Point p, Point q) { return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
    Result res;

    for (int i = 0; i < vp.size() - 1; i++) {
        for (int j = i + 1; j < vp.size(); j++) {
            Point p1 = vp[i];
            Point p2 = vp[j];
            double distance = p1.distance(p2);

            if (distance < res.dmin)
                res = Result(distance, p1, p2);
        }
    }

    return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
    Result res;
    sortByX(vp, 0, vp.size() - 1);
    res = nearestPoints_BF(vp);
    return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res) {
    double distance;
    for (int i = left; i < right; i++) {
        for (int j = i + 1; j <= right; j++) {
            if (vp[j].y - vp[i].y > res.dmin)
                break;
            else if ((distance = vp[i].distance(vp[j])) < res.dmin)
                res = Result(distance, vp[i], vp[j]);
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
    // Base case of two points
    if (right == left + 1)
        return Result(vp[left].distance(vp[right]), vp[left], vp[right]);

    // Base case of a single point: no solution, so distance is MAX_DOUBLE
    if (right == left)
        return Result(MAX_DOUBLE, vp[left], vp[right]);

    // Divide in halves (left and right) and solve them recursively,
    // possibly in parallel (in case numThreads > 1)

    Result resleft, resright, min;

    if (numThreads > 1) {
        std::thread t([&]() { resleft = np_DC(vp, left, (left + right) / 2, numThreads / 2); });
        resright = np_DC(vp, (left + right) / 2 + 1, right, numThreads);
        t.join();
    } else {
        resleft = np_DC(vp, left, (left + right) / 2, numThreads);
        resright = np_DC(vp, (left + right) / 2 + 1, right, numThreads);
    }

    // Select the best solution from left and right
    if (resleft.dmin < resright.dmin)
        min = resleft;
    else
        min = resright;

    int ixMed = (right + left) / 2;

    double medium = (vp[ixMed].x + vp[ixMed + 1].x) / 2;
    int i = left;
    for (; vp[i].x < medium - min.dmin; i++);
    left = i;

    for (; i < vp.size() && vp[i].x < medium + min.dmin; i++);
    right = i;

    // Order points in strip area by Y coordinate
    sortByY(vp, left, right);

    // Calculate nearest points in strip area (using npByY function)
    npByY(vp, left, right, min);

    // Reorder points in strip area back by X coordinate
    sortByX(vp, left, right);

    return min;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;

void setNumThreads(int num) {
    numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
    sortByX(vp, 0, vp.size() - 1);
    return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
    sortByX(vp, 0, vp.size() - 1);
    return np_DC(vp, 0, vp.size() - 1, numThreads);
}

double getDistance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
