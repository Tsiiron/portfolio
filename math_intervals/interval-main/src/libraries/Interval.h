#ifndef meteor_blast
#define meteor_blast

#include <vector>

class Interval {
private:
    double start_;
    double finish_;

public:
    explicit Interval(double first, double second);

    double len() const;
    bool in(double x) const;
    std::vector<double> split(int n) const;

    Interval operator*(const double& value);
    Interval operator/(const double& value);
    Interval operator+(const double& value);
    Interval operator-(const double& value);
};

#endif