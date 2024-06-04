#ifndef DM_MODULES_POLYNOMIAL_H
#define DM_MODULES_POLYNOMIAL_H

#include "../Rational/Rational.h"


class Polynomial : public iModel {
    std::vector<Rational> coefficients_; // массив дробных коэффициентов в прямом порядке (x^2 + 1/2 == [1/1, 0/1, 1/2]) 
    std::size_t degree_{}; // степень многочлена

    void removeLeadingZeros();

public:
    explicit Polynomial(const std::vector<Rational> &coefficients);

    explicit Polynomial(const std::string &polynomial);

    [[nodiscard]] static Polynomial gcd(const Polynomial &a, const Polynomial &b); //GCF_PP_P

    [[nodiscard]] std::string str() const override;

    [[nodiscard]] Polynomial scale(const Rational &scalar) const; // MUL_PQ_P

    [[nodiscard]] Polynomial mulByXk(std::size_t k) const; // MUL_Pxk_P

    [[nodiscard]] Rational leading() const; // LED_P_Q

    [[nodiscard]] std::size_t getDegree() const; // DEG_P_N

    [[nodiscard]] Polynomial factorize() const; // FAC_P_Q

    [[nodiscard]] Polynomial derivative() const; // DER_P_P

    [[nodiscard]] Polynomial singlify() const; // NMR_P_P

    [[nodiscard]] Polynomial operator+(const Polynomial &other) const; // ADD_PP_P

    [[nodiscard]] Polynomial operator-(const Polynomial &other) const; // SUB_PP_P

    [[nodiscard]] Polynomial operator*(const Polynomial &other) const; // MUL_PP_P

    [[nodiscard]] Polynomial operator/(const Polynomial &other) const; // DIV_PP_P

    [[nodiscard]] Polynomial operator%(const Polynomial &other) const; // MOD_PP_P

    [[nodiscard]] bool operator==(const Polynomial &other) const;

    [[nodiscard]] bool operator!=(const Polynomial &other) const;

    [[nodiscard]] Polynomial reduceAllCoefficients() const;
};


#endif //DM_MODULES_POLYNOMIAL_H