#include "Integer.h"

#include <utility>
#include <stdexcept>

Integer::Integer(std::int64_t number) : sign_(number < 0), number_(Natural(std::abs(number))) {}

Integer::Integer(const std::string &str_number) : sign_(false) {
    size_t sign_pos = str_number.find_first_of("-+");
    if (sign_pos != std::string::npos)
        sign_ = str_number[sign_pos] == '-';
    number_ = Natural{str_number.substr(sign_pos + 1)};
}

std::string Integer::str() const {
    return (sign_ ? "-" : "") + number_.str();
}


[[nodiscard]] digit Integer::isPositive() const {
    if (number_.isZero()) //если число равно 0, возвращаем 0
        return 0;
    return sign_ ? 1 : 2; //если число отрицательное, возвращаем 1, иначе 2
}


Integer Integer::abs() const {
    //создание объекта типа Integer с использованием текущего значения, без учета знака
    return Integer{number_};
}


Integer::Integer(Natural natural) : number_(std::move(natural)), sign_(false) {}
// присваиваем числу абсолютную часть, а знаку false (+)


[[nodiscard]] Integer Integer::operator*(const Integer &other) const {
    if (this->isPositive() == 0 || other.isPositive() == 0)
        return Integer{0};
    Natural n_this = this->toNatural(), n_other = other.toNatural(); //абсолютные части чисел
    Integer new_num(n_other * n_this); //абсолютная часть произведения чисел
    new_num.sign_ = this->sign_ ^ other.sign_; // меняем знак у результата в зависимости от знаков операндов
    return new_num;
}



Natural Integer::toNatural() const {
    return Natural{number_}; // возвращаем натуральное число
}


Integer Integer::operator/(const Integer &other) const {
    if (other.isPositive() == 0)  // если делитель = 0
        throw std::invalid_argument("Деление на 0 невозможно");

    if (this->isPositive() == 0) // если первое число 0 - результат 0
        return Integer{0};

    // вычисляем модуль результата используя деление нацело для натуральных чисел
    Integer result = Integer(this->number_ / other.number_);

    // если делитель - отрицательный и деление не нацело, то добавляем к ответу единицу
    if ((this->number_ % other.number_) != Natural{0} && this->isPositive() == 1)
        result = result + Integer{1};

    // меняем знак у результата в зависимости от знаков делимого и делителя (sign a XOR sign b)
    result.sign_ = this->sign_ ^ other.sign_;

    return result; // возвращаем полученный результат
}


Integer Integer::operator-(const Integer &other) const {
    // Проверяем, является ли одно из чисел нулем и возвращаем другое число
    if (this->isPositive() == 0)
        return other.negative();
    if (other.isPositive() == 0)
        return *this;

    Natural number_other = other.abs().number_; // Получаем абсолютную часть второго числа (ABS_Z_Z)
    Integer res{0};
    // Если числа имеют одинаковые знаки (POZ_Z_D)
    if (other.isPositive() == this->isPositive()) {
        // Вычитаем два натуральных числа
        switch (Natural::cmp(number_, number_other)) {
            case 1:   // если первое < второго
                res = Integer{number_other - number_}; // Вычитаем два натуральных числа
                res.sign_ = !sign_; // Меняем знак
                break;
            case 2: // если первое > второго
                res = Integer{number_ - number_other}; // Вычитаем
                res.sign_ = sign_; // Сохраняем исходный знак
                break;
        }
        return res; // Возвращаем результат
    }
    // Если одно число положительное, а другое отрицательное
    res = Integer{number_ + number_other}; // Складываем два натуральных числа
    res.sign_ = sign_; // Сохраняем исходный знак
    return res; // Возвращаем результат
}


Integer Integer::negative() const {
    if (this->isPositive() == 0)
        return *this;
    Integer answer(*this); // копируем число
    answer.sign_ = !answer.sign_; // меняем знак числа
    return answer; // возвращаем новое число
}

Integer Integer::operator+(const Integer &other) const {
    // если одно из чисел 0 - возвращаем другое
    if (this->isPositive() == 0)
        return other;
    if (other.isPositive() == 0)
        return *this;

    Natural number_other = other.abs().number_; // получаю абсолютную часть второго числа (ABS_Z_Z)
    Integer res{0};
    // Если одно число положительное, а другое отрицательное
    if (other.isPositive() != this->isPositive()) {
        switch (Natural::cmp(number_, number_other)) { // сравниваю два натуральных числа (COM_NN_D)
            case 1:// если первое < второго
                res = Integer{number_other - number_};
                res.sign_ = other.sign_;
                break;
            case 2: // если первое > второго
                res = Integer{number_ - number_other};
                res.sign_ = sign_;
                break;
                // если первое == второе оставляем все как есть
        }
        return res;
    }
    // если числа имеют одинаковые знаки (POZ_Z_D)
    res = Integer{number_ + number_other}; // Складываю два натуральных числа
    res.sign_ = sign_; // оставляю исходный знак
    return res;
}

Integer Integer::operator%(const Integer &other) const {
    //проверка на деление на 0
    if (other == Integer(0)) throw std::invalid_argument("Деление на 0 невозможно!");
    // Возвращаемое значение равно разности левого числа и произведения правого на разность деления 2 чисел
    return *this - (other * (*this / other));
}

bool Integer::operator==(const Integer &other) const {
    return number_ == other.number_ && sign_ == other.sign_;
}

bool Integer::operator!=(const Integer &other) const {
    return !(*this == other);
}
