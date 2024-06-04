#include "libraries/Interval.h"
#include <iostream>

// Пример использования класса

int main() {
    Interval interval1(5, 12);
    Interval interval2(2.5, 2.5);
    Interval interval3(9, -2);
    std::vector<Interval> intervals = {interval1, interval2, interval3};

    // Length
    for(auto inter : intervals) std::cout << inter.len() << " ";
    std::cout << '\n' << '\n';

    // In test
    std::cout << std::boolalpha;
    for(auto inter : intervals) std::cout << inter.in(2.5) << " ";
    std::cout << std::noboolalpha << '\n';

    // Split test
    for(auto inter : intervals) {
        std::cout << '\n';
        for(int value : {4, 1, -3}) {
            std::cout << "split = " << value << '\n';
            try {
                auto spl = inter.split(value);
                for(auto elem : spl) std::cout << elem << " ";
            } catch(const std::exception& ex) {
                std::cout << ex.what();
            }
            std::cout << '\n';
        }
    }
    std::cout << '\n';


    // Operators
    auto print_split = [] (const std::vector<double>& arr) {
        std::cout << arr[0] << " " << arr[1] << '\n';
    };
    print_split((interval1 * 2.7).split(1));
    print_split((interval3 / 4.20).split(1));
    print_split((interval1 + (-6.9)).split(1));
    print_split((interval2 - (52)).split(1));

    return 0;
}