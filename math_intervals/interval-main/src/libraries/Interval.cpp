#include "Interval.h"

#include <iostream>

Interval :: Interval(double first, double second) 
{
    start_ = std::min(first, second);
    finish_ = std::max(first, second);
}

double Interval :: len() const {
    return finish_ - start_;
}

bool Interval :: in(double x) const {
    return (start_ < x && x < finish_);
}

std::vector<double> Interval :: split(int n) const {
    if(n <= 0) throw std::invalid_argument("n must be more than zero!");
    std::vector<double> arr(n+1);
    double curr = start_;
    double length = (this->len() / n);
    for(size_t i = 0; i < n + 1; i++) {
        arr[i] = curr;
        curr += length;
    }
    return arr;
}

// смещение происходит относительно центра интервала: (finish - start) / 2

Interval Interval :: operator*(const double& value) {
    Interval tmp(*this);
    double middle = (finish_ - start_) / 2;
    double half_len = this->len() / 2;
    half_len *= value;
    tmp.start_ = middle - half_len;
    tmp.finish_ = middle + half_len;
    return tmp;
}

Interval Interval :: operator/(const double& value) {
    if(value == 0) throw std::invalid_argument("Can't divide by zero!");
    return this->operator*(1 / value);
}

Interval Interval :: operator+(const double& value) {
    Interval tmp(*this);
    tmp.start_ += value;
    tmp.finish_ += value;
    return tmp;
}

Interval Interval :: operator-(const double& value) {
    return this->operator+(-value);
}