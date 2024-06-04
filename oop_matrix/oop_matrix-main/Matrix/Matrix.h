#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <ostream>

class Iterator;

class Matrix {
private:
    double** arr_;                          // массив с данными
    std::pair<size_t, size_t> dimensions_;  // размер матрицы

    double** create_arr(size_t n, size_t m);
    void clear_arr();

    void swap_rows(size_t i, size_t j);
    void add_row(size_t i, size_t j, double scalar);
public:
    Matrix();
    Matrix(size_t n, size_t m);

    Matrix(const Matrix& other);
    Matrix(Matrix&& other);

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);

    [[nodiscard]] uint32_t rank() const;
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    [[nodiscard]] bool operator==(const Matrix& other) const;
    [[nodiscard]] bool operator!=(const Matrix& other) const;

    [[nodiscard]] bool operator<(const Matrix& other) const;
    [[nodiscard]] bool operator>(const Matrix& other) const;
    [[nodiscard]] bool operator<=(const Matrix& other) const;
    [[nodiscard]] bool operator>=(const Matrix& other) const;

    std::ostream& operator<<(std::ostream& out) const;

    [[nodiscard]] std::pair<size_t, size_t> get_dimensions() const;
    [[nodiscard]] double& at(size_t i, size_t j) const;
    
    ~Matrix();

    Iterator begin();
    Iterator end();
};

class Iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = double;
    using difference_type = std::ptrdiff_t;
    using pointer = double*;
    using reference = double&;

private:
    Matrix* matrix_;
    size_t i_, j_;

public:
    Iterator(Matrix* matrix, size_t i, size_t j);

    reference operator*() const;
    pointer operator->() const;
    
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    Iterator& operator+=(difference_type n);
    Iterator operator+(difference_type n) const;
    Iterator& operator-=(difference_type n);
    Iterator operator-(difference_type n) const;

    difference_type operator-(const Iterator& other) const;
    
    reference operator[](difference_type n) const;

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    bool operator<(const Iterator& other) const;
    bool operator>(const Iterator& other) const;
    bool operator<=(const Iterator& other) const;
    bool operator>=(const Iterator& other) const;
    
};

#endif