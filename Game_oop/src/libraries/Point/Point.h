#ifndef point_h
#define point_h

#include <algorithm>

template<typename T>
class Point {
private:
    T x_,y_;

public:
    T get_x() const;
    T get_y() const;

    void set_x(T x);
    void set_y(T y);

    Point();
    Point(const T& x, const T& y);
    Point(const Point& other);
    Point(Point&& other);

    Point operator+(const Point& other);
    Point operator-(const Point& other);
    Point operator*(const Point& other);
    Point operator/(const Point& other);

    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);
    Point& operator*=(const Point& other);
    Point& operator/=(const Point& other);

    Point& operator=(const Point& other);

    [[nodiscard]] bool operator==(const Point& other) const;
    [[nodiscard]] bool operator!=(const Point& other) const;
    [[nodiscard]] bool operator<(const Point& other) const;
};

template<typename T>
Point<T> :: Point(const T& x, const T& y) : x_(x), y_(y) {}

template<typename T>
Point<T> :: Point() : Point(0, 0) {}

template<typename T>
Point<T> :: Point(const Point& other) {
    *this = other;
}

template<typename T>
Point<T> :: Point(Point&& other) {
    x_ = std::move(other.x_);
    y_ = std::move(other.y_);
}

template<typename T>
T Point<T> :: get_x() const {
    return x_;
}

template<typename T>
T Point<T> :: get_y() const {
    return y_;
}

template<typename T>
void Point<T> :: set_x(T x) {
    x_ = x;
}

template<typename T>
void Point<T> :: set_y(T y) {
    y_ = y;
}

template<typename T>
Point<T>& Point<T> :: operator=(const Point<T>& other) {
    if(&other != this) {
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

template<typename T>
Point<T> Point<T> :: operator+(const Point<T>& other) {
    Point<T> tmp(*this);
    tmp += other;
    return tmp;
}

template<typename T>
Point<T> Point<T> :: operator-(const Point<T>& other) {
    Point<T> tmp(*this);
    tmp -= other;
    return tmp;
}

template<typename T>
Point<T> Point<T> :: operator*(const Point<T>& other) {
    Point<T> tmp(*this);
    tmp *= other;
    return tmp;
}

template<typename T>
Point<T> Point<T> :: operator/(const Point<T>& other) {
    Point<T> tmp(*this);
    tmp /= other;
    return tmp;
}

template<typename T>
Point<T>& Point<T> :: operator+=(const Point<T>& other)
{
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}

template<typename T>
Point<T>& Point<T> :: operator-=(const Point<T>& other)
{
	x_ -= other.x_;
	y_ -= other.y_;
	return *this;
}

template<typename T>
Point<T>& Point<T> :: operator*=(const Point<T>& other)
{
	x_ *= other.x_;
	y_ *= other.y_;
	return *this;
}

template<typename T>
Point<T>& Point<T> :: operator/=(const Point<T>& other)
{
	x_ /= other.x_;
	y_ /= other.y_;
	return *this;
}

template<typename T>
[[nodiscard]] bool Point<T> :: operator==(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

template<typename T>
[[nodiscard]] bool Point<T> :: operator!=(const Point& other) const {
    return x_ != other.x_ || y_ != other.y_;
}

template<typename T>
[[nodiscard]] bool Point<T> :: operator<(const Point& other) const {
    if(x_ == other.x_) {
        return y_ < other.y_;
    }
    return x_ < other.x_;
}

#endif