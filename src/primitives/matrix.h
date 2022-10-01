#ifndef RTC_MATRIX
#define RTC_MATRIX

#include <vector>
#include <string>

#include "primitives/tuple.h"

class Matrix {
    public:
        Matrix(int h, int w);
        Matrix(int h, int w, std::vector<float> values);
        ~Matrix();

        Matrix &operator=(const Matrix &matrix);

        float operator()(int row, int col) const;
        void set(float value, int row, int col);

        inline int height() const { return height_; };
        inline int width() const { return width_; };

        bool operator==(const Matrix other);
        bool operator!=(const Matrix other);
        Matrix operator*(const Matrix other);
        Tuple operator*(const Tuple other);

        Matrix transpose();
        bool isInvertible();
        Matrix inverse();
        Matrix subMatrix(int row, int col);
        float determinant();
        float cofactor(int row, int col);
        std::string debugString();


    private:
        int height_, width_;
        float* data;
        inline int matrixIndex(int row, int col) const;
};

Tuple operator*(const Matrix &m, const Tuple &t);

Matrix identityMatrix(int dimensions);
Matrix translationMatrix(float x, float y, float z);
Matrix scaleMatrix(float x, float y, float z);

Matrix rotationX(float radians);
Matrix rotationY(float radians);
Matrix rotationZ(float radians);
Matrix shear(int xy, int xz, int yx, int yz, int zx, int zy);
Matrix viewTransform(Tuple &from, Tuple &to, Tuple &up);
#endif