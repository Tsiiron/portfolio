#include "Matrix.h"

double** Matrix :: create_arr(size_t n, size_t m) {
    double** arr = new double* [n];
    for(size_t i = 0; i < n; i++) {
        arr[i] = new double [m];
    }
    return arr;
}

void Matrix :: clear_arr() {
    if(arr_ == nullptr) return;

    for(size_t i = 0; i < dimensions_.first; i++) {
        delete[] arr_[i];
    }
    delete[] arr_;
    arr_ = nullptr;
}

Matrix :: Matrix(size_t n, size_t m) :  arr_(nullptr),
                                        dimensions_{n, m}
{
    arr_ = create_arr(n, m);
}

Matrix :: Matrix() : Matrix(5, 5) {}

Matrix :: Matrix(const Matrix& other) : Matrix() {
    *this = other;
}

Matrix :: Matrix(Matrix&& other) : Matrix() {
    *this = std::move(other);
}

Matrix& Matrix :: operator=(const Matrix& other) {
    if(&other != this) {
        clear_arr();
        arr_ = create_arr(other.dimensions_.first, other.dimensions_.second);
        dimensions_ = other.dimensions_;

        for(size_t i = 0; i < dimensions_.first; i++) {
            for(size_t j = 0; j < dimensions_.second; j++) {
                arr_[i][j] = other.arr_[i][j];
            }
        }
    }
    return *this;
}

Matrix& Matrix :: operator=(Matrix&& other) {
    if(&other != this) {
        clear_arr();
        dimensions_ = std::move(other.dimensions_);
        arr_ = std::move(other.arr_);
        other.arr_ = nullptr;
    }
    return *this;
}

Matrix :: ~Matrix() {
    clear_arr();
}

void Matrix :: swap_rows(size_t i, size_t j) {
    std::swap(arr_[i], arr_[j]);
}

void Matrix :: add_row(size_t i, size_t j, double scalar) {
    for(size_t k = 0; k < dimensions_.second; k++) {
        arr_[i][k] += scalar * arr_[j][k];
    }
}

/*
вычисление ранга матрицы происходит
путем приведения матрицы к ступенчатому виду
и подсчета количества ненулевых строк
*/

[[nodiscard]] uint32_t Matrix :: rank() const {
    int32_t lead = 0;
    Matrix tmp(*this); 

    for(size_t i = 0; i < tmp.dimensions_.first; i++) {
        if(lead >= tmp.dimensions_.second) {
            break;
        }

        size_t row = i;
        while(tmp.arr_[row][lead] == 0) {
            row++;
            if(row == tmp.dimensions_.first) {
                row = i;
                lead++;
                if(lead >= tmp.dimensions_.second) {
                    break;
                }
            }
        }

        tmp.swap_rows(row, i);

        double scalar = tmp.arr_[i][lead];
        if(scalar == 0) {
            continue;
        }

        for(size_t j = 0; j < tmp.dimensions_.second; j++) {
            tmp.arr_[i][j] /= scalar;
        }

        for(size_t r = 0; r < tmp.dimensions_.first; r++) {
            if(r != i) {
                scalar = tmp.arr_[r][lead];
                tmp.add_row(r, i, -scalar);
            }
        }

        lead++;
    }

    uint32_t rank = 0;
    bool flag;
    for(size_t i = 0; i < tmp.dimensions_.first; i++) {
        flag = true;
        for(size_t j = 0; j < tmp.dimensions_.second; j++) {
            if(tmp.arr_[i][j] != 0) flag = false;
        }
        if(!flag) rank++;
    }

    return rank;
}

Matrix Matrix :: operator+(const Matrix& other) const {
    if(dimensions_.first != other.dimensions_.first 
    || dimensions_.second != other.dimensions_.second) {
        throw std::invalid_argument("Размеры матрицы не совпадают");    
    }

    Matrix tmp(*this);

    for(size_t i = 0; i < dimensions_.first; i++) {
        for(size_t j = 0; j < dimensions_.second; j++) {
            tmp.arr_[i][j] += other.arr_[i][j];
        }
    }

    return tmp;
}

Matrix Matrix :: operator-(const Matrix& other) const {
    if(dimensions_.first != other.dimensions_.first 
    || dimensions_.second != other.dimensions_.second) {
        throw std::invalid_argument("Размеры матрицы не совпадают");    
    }

    Matrix tmp(*this);

    for(size_t i = 0; i < dimensions_.first; i++) {
        for(size_t j = 0; j < dimensions_.second; j++) {
            tmp.arr_[i][j] -= other.arr_[i][j];
        }
    }

    return tmp;
}

Matrix Matrix :: operator*(const Matrix& other) const {
    if(dimensions_.second != other.dimensions_.first) {
        throw std::invalid_argument("Размеры матриц не позволяют умножить их");
    }

    Matrix tmp(dimensions_.first, other.dimensions_.second);

    for(size_t i = 0; i < dimensions_.first; i++) {
        for(size_t j = 0; j < other.dimensions_.second; j++) {
            for(size_t k = 0; k < dimensions_.second; k++) {
                tmp.arr_[i][j] += arr_[i][k] * other.arr_[k][j];
            }
        }
    }

    return tmp;
}

[[nodiscard]] bool Matrix :: operator==(const Matrix& other) const {
    if(rank() == other.rank()) {
        if(dimensions_.first == other.dimensions_.first
        && dimensions_.second == other.dimensions_.second) {
            for(size_t i = 0; i < dimensions_.first; i++) {
                for(size_t j = 0; j < dimensions_.second; j++) {
                    if(arr_[i][j] != other.arr_[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
    return false;
}

[[nodiscard]] bool Matrix :: operator!=(const Matrix& other) const {
    return !(*this == other);
}

[[nodiscard]] bool Matrix :: operator<(const Matrix& other) const {
    return rank() < other.rank();
}

[[nodiscard]] bool Matrix :: operator>(const Matrix& other) const {
    return rank() > other.rank();
}

[[nodiscard]] bool Matrix :: operator<=(const Matrix& other) const {
    return rank() <= other.rank();
}

[[nodiscard]] bool Matrix :: operator>=(const Matrix& other) const {
    return rank() >= other.rank();
}

std::ostream& Matrix :: operator<<(std::ostream& out) const {
    for(size_t i = 0; i < dimensions_.first; i++) {
        for(size_t j = 0; j < dimensions_.second; j++) {
            out << arr_[i][j] << " ";
        }
        out << '\n';
    }
    return out << '\n';
}

[[nodiscard]] double& Matrix :: at(size_t i, size_t j) const {
    if(i < dimensions_.first && j < dimensions_.second) {
        return arr_[i][j];
    }
    throw std::invalid_argument("Элемента с данными индексами не существуует");
}

[[nodiscard]] std::pair<size_t, size_t> Matrix :: get_dimensions() const {
    return dimensions_;
}

Iterator Matrix :: begin() {
    return Iterator(this, 0, 0);
}

Iterator Matrix :: end() {
    return Iterator(this, dimensions_.first, 0);
}

Iterator :: Iterator(Matrix* matrix, size_t i, size_t j) :  matrix_(matrix),
                                                            i_(i),
                                                            j_(j)
                                                            {}

Iterator :: reference Iterator :: operator*() const {
    return matrix_->at(i_, j_);
}

Iterator :: pointer Iterator :: operator->() const {
    return &(operator*());
}

Iterator& Iterator :: operator++() {
    if(++j_ == matrix_->get_dimensions().second) {
        j_ = 0;
        i_++;
    }
    return *this;
}

Iterator Iterator :: operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

Iterator& Iterator :: operator--() {
    if(j_ == 0) {
        j_ = matrix_->get_dimensions().second - 1;
        if(i_ == 0) {
            throw std::length_error("Выход за границы итератора");
        }
        i_--;
    } else {
        j_--;
    }
    return *this;
}

Iterator Iterator :: operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

Iterator& Iterator :: operator+=(difference_type n) {
    difference_type offset = n + j_;
    i_ += offset / matrix_->get_dimensions().second;
    j_ = offset % matrix_->get_dimensions().second;
    return *this;
}

Iterator Iterator :: operator+(difference_type n) const {
    Iterator tmp = *this;
    return tmp += n;
}

Iterator& Iterator :: operator-=(difference_type n) {
    return *this += -n;
}

Iterator Iterator :: operator-(difference_type n) const {
    Iterator tmp = *this;
    return tmp -= n;
}

Iterator :: difference_type Iterator :: operator-(const Iterator& other) const {
    return matrix_->get_dimensions().second * (i_ - other.i_) + (j_ - other.j_);
}

Iterator :: reference Iterator :: operator[](difference_type n) const {
    return *(*this + n);
}

bool Iterator :: operator==(const Iterator& other) const {
    return i_ == other.i_ && j_ == other.j_;
}

bool Iterator :: operator!=(const Iterator& other) const {
    return !(*this == other);
}

bool Iterator :: operator<(const Iterator& other) const {
    return i_ < other.i_ || (i_ == other.i_ && j_ < other.j_);
}

bool Iterator :: operator>(const Iterator& other) const {
    return other < *this;
}

bool Iterator :: operator<=(const Iterator& other) const {
    return !(other < *this);
}

bool Iterator :: operator>=(const Iterator& other) const {
    return !(*this < other);
}