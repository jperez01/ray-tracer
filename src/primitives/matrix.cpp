#include "primitives/matrix.h"
#include "primitives/math.h"

#include <cassert>
#include <vector>
#include <sstream>
#include <math.h>

Matrix::Matrix(int h, int w) {
    height_ = h;
    width_ = w;
    data = (float *) calloc(h * w, sizeof(float));
}

Matrix::~Matrix() {
    
}

Matrix::Matrix(int h, int w, std::vector<float> values) {
    height_ = h;
    width_ = w;
    data = (float *) calloc(h * w, sizeof(float));

    std::vector<float>::size_type size = w * h;
    assert(size == values.size());

    for (std::vector<float>::size_type i = 0; i < values.size(); i++) {
        data[i] = values[i];
    }
}

Matrix &Matrix::operator=(const Matrix& matrix) {
    if (*this != matrix) {
        if (width_ == matrix.width() && height_ == matrix.height()) {
            memcpy(data, matrix.data, width_ * height_ * sizeof(float));
        } else {
            width_ = matrix.width();
            height_ = matrix.height();
            free(data);
            data = (float *) malloc(height_ * width_ * sizeof(float));
            memcpy(data, matrix.data, height_ * width_ * sizeof(float));
        }
    }
    return *this;
}

inline int Matrix::matrixIndex(int row, int col) const {
    return col + row * height_;
}

float Matrix::operator()(int row, int col) const {
    int index = matrixIndex(row, col);
    return data[index];
}

void Matrix::set(float value, int row, int col) {
    int index = matrixIndex(row, col);
    data[index] = value;
}

bool Matrix::operator==(const Matrix other) {
    if (width_ != other.width() || height_ != other.height()) return false;

    for (int row = 0; row < height_; row++) {
        for (int col = 0; col < width_; col++) {
            float otherValue = other(row, col);
            float value = this->operator()(row, col);

            if (!epsilon_eq(value, otherValue)) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix other) {
    return !(*this == other);
}

Matrix Matrix::operator*(const Matrix other) {
    Matrix current = *this;
    Matrix result = Matrix(other.height(), other.width());

    for (int row = 0; row < other.height(); row++) {
        for (int col = 0; col < other.width(); col++) {
            float total = 0;
            for (int i = 0; i < other.height(); i++) {
                total += current(row, i) * other(i, col);
            }
            result.set(total, row, col);
        }
    }
    return result;
}

Tuple Matrix::operator*(const Tuple other) {
    Matrix m = *this;
    Tuple t = other;
    return Tuple(
    m(0, 0) * t.x + m(0, 1) * t.y + m(0, 2) * t.z + m(0, 3) * t.w,
    m(1, 0) * t.x + m(1, 1) * t.y + m(1, 2) * t.z + m(1, 3) * t.w,
    m(2, 0) * t.x + m(2, 1) * t.y + m(2, 2) * t.z + m(2, 3) * t.w,
    m(3, 0) * t.x + m(3, 1) * t.y + m(3, 2) * t.z + m(3, 3) * t.w
  );
}

Tuple operator*(const Matrix &m, const Tuple &t) {
    return Tuple(
        m(0, 0) * t.x + m(0, 1) * t.y + m(0, 2) * t.z + m(0, 3) * t.w,
        m(1, 0) * t.x + m(1, 1) * t.y + m(1, 2) * t.z + m(1, 3) * t.w,
        m(2, 0) * t.x + m(2, 1) * t.y + m(2, 2) * t.z + m(2, 3) * t.w,
        m(3, 0) * t.x + m(3, 1) * t.y + m(3, 2) * t.z + m(3, 3) * t.w
  );
}

Matrix Matrix::transpose() {
    Matrix transpose = Matrix(this->height(), this->width());
    for (int row = 0; row < this->height(); row++) {
        for (int col = 0; col < this->width(); col++) {
            transpose.set(this->operator()(row, col), col, row);
        }
    }

    return transpose;
}

Matrix Matrix::subMatrix(int row, int col) {
    Matrix sub = Matrix(this->height() - 1, this->width() - 1);

    int y = 0;
    for (int r = 0; r < this->height(); r++) {
        if (r == row) continue;

        int x = 0;
        for (int c = 0; c < this->width(); c++) {
            if (c != col) {
                float value = this->operator()(r, c);
                sub.set(value, y, x);
                x++;
            }
        }
        y++;
    }

    return sub;
 }

float Matrix::determinant() {
    if (this->width() == 2) {
        return this->operator()(0, 0) * this->operator()(1, 1)
            - this->operator()(1, 0) * this->operator()(0, 1);
    } else {
        float determinant = 0;
        for (int col = 0; col < this->width(); col++) {
            determinant += this->operator()(0, col) * this->cofactor(0, col);
        }
        return determinant;
    }
}

float Matrix::cofactor(int row, int col) {
    float minor = this->subMatrix(row, col).determinant();

    if ((row + col) % 2 == 1) return -1 * minor;
    else return minor;
}

bool Matrix::isInvertible() {
    return this->determinant() != 0;
}

Matrix Matrix::inverse() {
    float determinant = this->determinant();
    Matrix inverse = Matrix(this->height(), this->width());

    for (int row = 0; row < this->height(); row++) {
        for (int col = 0; col < this->width(); col++) {
            float cofactor = this->cofactor(row, col);
            inverse.set(cofactor / determinant, col, row);
        }
    }

    return inverse;
}

std::string Matrix::debugString() {
    std::stringstream stream;
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            stream << operator()(y, x);
            if (x == width_ - 1) stream << "\n";
            else stream << " ";
        }
    }

    return stream.str();
}

Matrix identityMatrix(int dimensions) {
    Matrix result = Matrix(dimensions, dimensions);
    for (int i = 0; i < dimensions; i++) result.set(1, i, i);
    return result;
}

Matrix translationMatrix(float x, float y, float z) {
    Matrix translation = identityMatrix(4);
    translation.set(x, 0, 3);
    translation.set(y, 1, 3);
    translation.set(z, 2, 3);

    return translation;
}

Matrix scaleMatrix(float x, float y, float z) {
    Matrix scale = Matrix(4, 4);
    scale.set(x, 0, 0);
    scale.set(y, 1, 1);
    scale.set(z, 2, 2);
    scale.set(1, 3, 3);

    return scale;
}

Matrix rotationX(float radians) {
    Matrix rotation = Matrix(4, 4);
    float cosR = cos(radians);
    float sinR = sin(radians);

    rotation.set(1, 0, 0);
    rotation.set(cosR, 1, 1);
    rotation.set(-sinR, 1, 2);
    rotation.set(sinR, 2, 1);
    rotation.set(cosR, 2, 2);
    rotation.set(1, 3, 3);

    return rotation;
}

Matrix rotationY(float radians) {
    Matrix rotation = Matrix(4, 4);
    float cosR = cos(radians);
    float sinR = sin(radians);

    rotation.set(1, 1, 1);
    rotation.set(cosR, 0, 0);
    rotation.set(-sinR, 2, 0);
    rotation.set(sinR, 0, 2);
    rotation.set(cosR, 2, 2);
    rotation.set(1, 3, 3);

    return rotation;
}

Matrix rotationZ(float radians) {
    Matrix rotation = Matrix(4, 4);
    float cosR = cos(radians);
    float sinR = sin(radians);

    rotation.set(1, 2, 2);
    rotation.set(cosR, 0, 0);
    rotation.set(-sinR, 0, 1);
    rotation.set(sinR, 1, 0);
    rotation.set(cosR, 1, 1);
    rotation.set(1, 3, 3);

    return rotation;
}

Matrix shear(int xy, int xz, int yx, int yz, int zx, int zy) {
    Matrix shear = identityMatrix(4);

    shear.set(xy, 0, 1);
    shear.set(xz, 0, 2);
    shear.set(yx, 1, 0);
    shear.set(yz, 1, 2);
    shear.set(zx, 2, 0);
    shear.set(zy, 2, 1);

    return shear;
}

Matrix viewTransform(Tuple &from, Tuple &to, Tuple &up) {
    Tuple forward = (to - from).normalized();
    Tuple upn = up.normalized();
    Tuple left = cross(forward, upn);
    Tuple true_up = cross(left, forward);

    Matrix orientation = identityMatrix(4);
    orientation.set(left.x, 0, 0);
    orientation.set(left.y, 0, 1);
    orientation.set(left.z, 0, 2);

    orientation.set(true_up.x, 1, 0);
    orientation.set(true_up.y, 1, 1);
    orientation.set(true_up.z, 1, 2);

    orientation.set(-forward.x, 2, 0);
    orientation.set(-forward.y, 2, 1);
    orientation.set(-forward.z, 2, 2);

    return orientation * translationMatrix(-from.x, -from.y, -from.z);
}