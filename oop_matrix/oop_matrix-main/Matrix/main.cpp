#include "Matrix.h"

int main() {
    Matrix mtr1(3,4);
    double value = 0;
    for(size_t i = 0; i < 3; i++) {
        for(size_t j = 0; j < 4; j++) {
            mtr1.at(i, j) = value;
            value += 0.5;
        }
    }

    std::cout << "Матрица №1 :\n";
    mtr1 << std::cout;

    Matrix mtr2(4,5);
    value = 7;
    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 5; j++) {
            mtr2.at(i, j) = value;
            value *= 1.03;
            if((i + j) % 6 == 0) {
                value *= -1.44;
            }
        }
    }

    std::cout << "Матрица №2 :\n";
    mtr2 << std::cout;
    
    Matrix mtr3; // размеры mtr3 - {5, 5}

    Matrix mtr4 = mtr1 * mtr2;
    std::cout << "Матрица №4 :\n";
    mtr4 << std::cout;

    try {
        Matrix mtr5 = mtr1 * mtr3;
    } catch(std::invalid_argument const& err) {
        std::cerr << err.what() << '\n'; // "Размеры матриц не позволяют умножить их"
    }

    // пример работы итератора
    std::cout << "Работа итератора : \n";
    for(auto it = mtr1.begin(); it < mtr1.end(); it+=2) {
        std::cout << *it << " ";
        if(*it == 3) {
            it--;
        }
        *it *= 2;
    }
    std::cout << '\n';

    std::cout << "Изменённая итератором матрица №1 : \n";
    mtr1 << std::cout;

    return 0;
}