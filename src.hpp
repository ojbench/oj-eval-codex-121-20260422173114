// Implementation of sjtu::complex per problem statement
#ifndef SRC_HPP_SJTU_COMPLEX
#define SRC_HPP_SJTU_COMPLEX

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
    divided_by_zero() = default;
    ~divided_by_zero() override = default;
    const char* what() const noexcept override {
        return "complex divided by zero!";
    }
};

inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

class complex {
private:
    double a, b; // a + bi
public:
    // Constructors
    complex() : a(0.0), b(0.0) {}
    complex(double ra) : a(ra), b(0.0) {}
    complex(double ra, double rb) : a(ra), b(rb) {}

    // Accessors returning references
    double &real() { return a; }
    double &imag() { return b; }
    const double &real() const { return a; }
    const double &imag() const { return b; }

    // Unary operators
    complex operator-() const { return complex(-a, -b); }
    complex operator~() const { return complex(a, -b); }

    // Arithmetic operators
    complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); }
    complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); }
    complex operator*(const complex &rhs) const {
        return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
    }
    complex operator/(const complex &rhs) const {
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double denom = rhs.a * rhs.a + rhs.b * rhs.b;
        return complex((a * rhs.a + b * rhs.b) / denom, (b * rhs.a - a * rhs.b) / denom);
    }

    complex &operator+=(const complex &rhs) { a += rhs.a; b += rhs.b; return *this; }
    complex &operator-=(const complex &rhs) { a -= rhs.a; b -= rhs.b; return *this; }
    complex &operator*=(const complex &rhs) {
        double na = a * rhs.a - b * rhs.b;
        double nb = a * rhs.b + b * rhs.a;
        a = na; b = nb;
        return *this;
    }
    complex &operator/=(const complex &rhs) {
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double denom = rhs.a * rhs.a + rhs.b * rhs.b;
        double na = (a * rhs.a + b * rhs.b) / denom;
        double nb = (b * rhs.a - a * rhs.b) / denom;
        a = na; b = nb;
        return *this;
    }

    bool operator==(const complex &rhs) const {
        return std::fabs(a - rhs.a) < 1e-6 && std::fabs(b - rhs.b) < 1e-6;
    }

    explicit operator bool() const {
        return !(sign(a) == 0 && sign(b) == 0);
    }

    friend std::ostream &operator<<(std::ostream &os, const complex &x) {
        double ra = (std::fabs(x.a) < 1e-6) ? 0.0 : x.a;
        double rb = (std::fabs(x.b) < 1e-6) ? 0.0 : x.b;
        os << std::fixed << std::setprecision(6)
           << ra
           << (rb < -1e-6 ? "-" : "+")
           << std::fixed << std::setprecision(6)
           << std::fabs(rb) << "i";
        return os;
    }
};

} // namespace sjtu

#endif // SRC_HPP_SJTU_COMPLEX
