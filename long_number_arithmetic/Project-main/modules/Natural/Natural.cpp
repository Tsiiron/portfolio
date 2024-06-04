#include "Natural.h"

#include <stdexcept>
#include <algorithm>

#include "../utils/utils.h"

Natural::Natural(std::size_t number) {
    if (number == 0)
        digits_.push_back(0);
    while (number > 0) {
        digits_.push_back(number % 10);
        number /= 10;
    }
    n_ = digits_.size() - 1;
}

Natural::Natural(const std::string &str_number) {
    std::string trimmed_number = utils::trim(str_number);
    if (trimmed_number.empty())
        throw std::invalid_argument("Operand expected not empty");
    utils::checkForRedundantSymbols(trimmed_number, " 0123456789");
    bool non_zero_encountered = false;
    for (digit digit: trimmed_number) {
        if (digit == '0' && !non_zero_encountered)
            continue;
        non_zero_encountered = true;
        digits_.push_back(digit - '0');
    }
    if (!non_zero_encountered)
        digits_.push_back(0);
    std::reverse(digits_.begin(), digits_.end());
    n_ = digits_.size() - 1;
}

std::string Natural::str() const {
    std::vector<digit> digits_copy = digits_;
    std::reverse(digits_copy.begin(), digits_copy.end());
    std::transform(digits_copy.begin(), digits_copy.end(), digits_copy.begin(),
                   [](digit digit) { return digit + '0'; });
    std::string res(digits_copy.begin(), digits_copy.end());
    return res;
}

bool Natural::isZero() const {
    return digits_[digits_.size() - 1] == 0;
    // Это проверка того, что последний элемент массива - это 0 (проверяем последний элемент, т.к.
    // числам хранятся в массиве в обратном порядке)
}

Natural Natural::mulByDigit(const digit multiplier) const {
    if (multiplier == 0) //если множитель равен нулю, то натуральное число равно нулю
        return Natural{0};
    Natural number(*this); //создаем копию от данного объекта
    int discharge = 0; //разряды. Используется, если результат умножения затрагивает и следующий разряд
    int add; //число, которое получается в результате умножения цифры разряда числа на цифру
    for (size_t i = 0; i <= number.n_; i++) {
        //добавляется discharge - часть результата прошлого умножения, относящаяся к новому разряду
        add = number.digits_[i] * multiplier + discharge;
        number.digits_[i] = (add) % 10;
        discharge = add / 10;
    }
    if (discharge != 0) {//если в результате умножения число стало на разряд больше
        number.digits_.push_back(discharge);
        number.n_++;
    }
    return number;
}

Natural Natural::subScaled(const Natural &other, digit k) const {
    Natural number(*this); //создаём копии объектов
    Natural other_num(other);
    other_num = other_num.mulByDigit(k); //умножаем вычитаемое на цифру
    number = number - other_num; //производим вычитание
    return number;
}

Natural Natural::operator%(const Natural &other) const {
    Natural number(*this);
    if (cmp(number, other) == 1) //если делимое меньше делителя возвращаем делимое
        return number;
    // целочисленное деление первого числа на второе, остаток деления на которое мы ищем
    Natural quotient = number / other;
    return number - quotient * other; // возвращаем остаток от деления
}


[[nodiscard]] Natural Natural::divFirstDigit(const Natural &other) const { // DIV_NN_Dk
    // Проверка, что числа не нули, большее не может быть нулем в натуральных числах
    if (this->isZero() || other.isZero())
        throw std::invalid_argument("Деление на 0 невыполнимо");
    // записываем большее в larger, меньшее в smaller
    Natural larger(other), smaller(*this);
    if (Natural::cmp(*this, other) == 2) {
        larger = Natural(*this);
        smaller = Natural(other);
    }
    // Создаем счетчик номера позиции первой цифры
    int k = 1;
    // Пока меньшее число, домноженное на 10^k, меньше большего, увеличиваем k
    while (Natural::cmp(larger, smaller.mulBy10K(k)) == 2 || Natural::cmp(larger, smaller.mulBy10K(k)) == 0) {
        k++;
    }
    k--; // Посчитали k, при котором меньшее, домноженное на 10^k, стало больше большего и вычли единицу
    smaller = smaller.mulBy10K(k); // Домножили меньшее на 10^k
    Natural firstDigit = Natural(0); // Создали переменную для подсчета старшего разряда частного и положили туда 0
    // запускаем цикл и вычитаем из большего меньшее до тех пор, пока большее не станет меньше меньшего
    while (Natural::cmp(larger, smaller) == 2 || Natural::cmp(larger, smaller) == 0) {
        larger = larger - smaller;
        firstDigit = firstDigit.addOne(); // Увеличиваем исходное значение на 1
    }
    // Возвращаем в качестве результата первую цифру (старший разряд частного), домноженную на 10^k, где k - номер позиции этой цифры (разряд)
    return firstDigit.mulBy10K(k);
}

digit Natural::cmp(const Natural &a, const Natural &b) {
    // если размер массива, в котором хранится число A < размера массива, в котором хранится число B,
    // то А < B гарантированно => выводим 1
    if (a.digits_.size() < b.digits_.size()) {
        return 1;
    }
        // если длина массива A > длины массива B => аналогично А > B => выводим 2
    else if (a.digits_.size() > b.digits_.size()) {
        return 2;
    }
    // если длина массива A = длине массива B, то нужно уже проверять по разрядам чисел
    // делаем это в цикле for начиная со старшего разряда, т.е с конца массива,
    // и идем до начала массива, сравнивая цифры в каждом разряде
    for (auto i = static_cast<int64_t>(a.digits_.size() - 1); i >= 0; --i) {
        // если какая-то цифра из разряда A оказалась < цифры из того же разряда B, то А < B => возвращаем 1
        if (a.digits_[i] < b.digits_[i])
            return 1;
            // если цифры в разряде равны, то продолжаем проверку на следующем разряде
        else if (a.digits_[i] == b.digits_[i])
            continue; // переходим на новую итерацию
        // иначе, остался лишь случай: цифра из разряда A оказалась > цифры из того же разряда =>
        // A > B => возвращаем 2
        return 2;
    }
    // сюда попадем только если A = B => возвращаем 0
    return 0;
}


[[nodiscard]] Natural Natural::mulBy10K(const std::size_t k) const {
    //копируем изменяемый объект
    Natural new_num(*this);

    // умножаем на 10^k
    for (size_t i = 0; i < k; i++)
        new_num.digits_.insert(new_num.digits_.begin(), 0);

    //обновляем поле старшего разряда числа
    new_num.n_ = new_num.digits_.size() - 1;

    //возвращаем результат
    return new_num;
}

[[nodiscard]] Natural Natural::lcm(const Natural &a, const Natural &b) {
    // формула НОК(а, b): a * b / НОД(a, b). Вычисляем и сразу возвращаем
    return a * b / gcd(a, b);
}

[[nodiscard]] Natural Natural::operator+(const Natural &other) const {//
    Natural tmp(*this), cur(other); //создаем копии
    if (cmp(tmp, cur) == 1)
        std::swap(tmp, cur);// если второе больше - меняем местами
    for (int i = 0; i < cur.digits_.size(); i++)
        // прибавляем к каждому числу первого каждое число второго по их порядку
        tmp.digits_[i] += cur.digits_[i];
    int fl = 0;
    for (digit &digit: tmp.digits_) {
        //далее оставляем только остаток от деления на 10
        digit += fl;  // добавляем перенесенный разряд
        fl = digit >= 10; // перенос разряда
        digit %= 10;  // оставляем остаток от деления на 10
    }
    if (fl == 1) {
        //если в конце чисел не осталось, но флаг не равен 0, заносим его в начало числа(конец массива)
        tmp.digits_.push_back(1);
        tmp.n_++;
    }
    return tmp; //результат
}

[[nodiscard]] Natural Natural::operator*(const Natural &other) const {
    std::vector<Natural> array;//массив чисел полученных путем умножения на конкретную цифру
    Natural tmp(*this), cur(other);
    if (cmp(tmp, cur) == 1)
        std::swap(tmp, cur); //если второе больше меняем их местами
    // if (cmp(tmp, other) == 2 || cmp(tmp, other) == 0) {
    for (unsigned char digit: cur.digits_) {
        // в массив чисел добавляем по одному первое число умноженное с помощью функции
        array.push_back(tmp.mulByDigit(digit));
        //MUL_ND_N на цифры из второго числа
    }
    Natural res(0);
    digit k = 0;
    for (const auto &i: array)
        // в цикле заносим в числа из array умноженные на 10^k степени где k - номер порядка
        res = res + i.mulBy10K(k++);
    //для пояснения:array[111,112,113] , тогда res = 113*100+112*10+111
    res.n_ = res.digits_.size() - 1;
    return res;
}

[[nodiscard]] Natural Natural::operator/(const Natural &other) const {
    Natural tmp(*this);//создаем копии чисел
    if (cmp(other, Natural(0)) == 0) //не допускаем деление на 0
        throw std::invalid_argument("Деление на 0 невыполнимо");
    Natural res(0), part;//создаем переменную в которую будем записывать результат поэтапного деления
    while (cmp(tmp, other) != 1) { // пока первое число >= второго
        // первое число = первое число минус второе умноженное на первую цифру деления(в 10^k степени)
        part = tmp.divFirstDigit(other);
        tmp = tmp - part * other; // вычитаем из первого числа полученный part умноженный на делитель
        res = res + part; //добавляем результат в res
    }
    res.n_ = res.digits_.size() - 1;
    return res;
}


Natural Natural::gcd(const Natural &a, const Natural &b) { // стандартный алгоритм Евклида для нахождения НОД
    Natural first(a), second(b);
    while (!first.isZero() && !second.isZero()) { // while a != 0 && b != 0
        if (first.cmp(first, second) == 2) // if first > second
            first = first % second;
        else
            second = second % first;
    }
    return first + second;
}


Natural Natural::addOne() const {
    Natural answer(*this); // создание копии числа
    answer.digits_[0]++; // добавляем 1 к последней цифре
    for (size_t i = 0; answer.digits_[i] == 10; i++) { // проходимся по цифрам пока текущая цифра == 10
        answer.digits_[i] = 0; // заменяем текущую цифру на 0
        if (i == answer.n_) { // если нет следующей цифры то добавляем 1
            answer.digits_.push_back(1);
            answer.n_++;
        } else {  // иначе увеличиваем следующую цифру на 1
            answer.digits_[i + 1]++;
        }
    }
    return answer; // возвращаем новое число
}

Natural Natural::operator-(const Natural &other) const {
    if (cmp(*this, other) == 1) { // если первое число меньше второго
        throw std::invalid_argument("Первое число меньше второго");
    } else if (cmp(*this, other) == 0) { // если числа равны
        return Natural(0); // возвращаем 0
    }

    Natural answer(*this); // создание копии числа
    int borrow = 0; // переменная нужная для того, чтобы занимать из следующего разряда
    int ai, bi, result;
    for (size_t i = 0; i <= this->n_; ++i) { // проходимся по всем цифрам первого числа
        // поскольку цикл идет по первому числу, нужны перемменные, отвечающие за цифры, которвые вычисляем, так как 1 число > 2 числа, значит в какой-то момент начнем вычитать нули
        ai = i <= this->n_ ? this->digits_[i] : 0; // берем цифру из 1 числа
        bi = i <= other.n_ ? other.digits_[i] : 0; // берем цифру из 2 числа

        result = ai - bi - borrow; // текущий результат = (цифра первого - цифра второго) - 1/0
        if (result < 0) { // если цифра < 0 - надо забрать еденицу из следующего разряда
            result += 10; // занимаем из следующего разряда => +10 в текующий разряд
            borrow = 1; // заполняем borrow тк мы заняли из следующего => на следующей итерации нужно уменьшить число на 1
        } else
            borrow = 0; // это число положительно из других разрядов не занимали
        answer.digits_[i] = result; // присваиваем текущей цифре нового числа вычисленный результат
    }

    while (answer.digits_.size() > 1 && answer.digits_.back() == 0) { // удаляем ведущие нули
        answer.digits_.pop_back();
        answer.n_--;
    }
    return answer; // возвращаем новое число
}

bool Natural::operator==(const Natural &other) const {
    return n_ == other.n_ && digits_ == other.digits_;
}

bool Natural::operator!=(const Natural &other) const {
    return !(*this == other);
}