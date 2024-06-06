#ifndef MATHY_MATRIX_H
#define MATHY_MATRIX_H

#include "Vec2.h"

namespace math {


template<typename T>
struct Matrix{

    size_t rows;
    size_t cols;
    std::vector<T> mat;

    Matrix() = default;
    Matrix(const Matrix&) = default;

    Matrix(size_t r, size_t c):rows(r), cols(c){
        mat.resize(r*c);
    };

    Matrix(size_t r, size_t c, T fill):rows(r), cols(c){
        mat.resize(r*c);
        std::fill(mat.begin(), mat.end(),fill);
    };

    inline Matrix<T> &operator= (const Matrix<T>& other){
        this->cols = other.cols;
        this->rows = other.rows;

        this->mat = other.mat;
        return *this;
    }

    inline T operator()(size_t row, size_t col) const{
        assert(((row * cols)+col) < mat.size() && "matrix out of bounds row col");
        return mat[(row * cols)+col];
    };

    inline T &operator()(size_t row, size_t col) {
        assert(((row * cols)+col) < mat.size() && "matrix out of bounds row col");
        return mat[(row * cols)+col];
    };

    inline T &operator[](size_t index) {
        assert((index) < mat.size() && "matrix out of bounds row col");
        return mat[index];
    };

    inline void insert(const Matrix&in, size_t row, size_t col){
        assert(((row * cols)+col) < mat.size() && "matrix out of bounds row col");

        for(int r = 0; r < in.rows; r++){
            for(int c = 0; c < in.cols; c++){
                operator()(row+r,col+c) = in(r,c);
            }
        }
    }

    inline bool checkBounds(size_t row, size_t col) const{
        if(((row * cols)+col) < mat.size()){
            return true;
        }

        return false;
    }


    inline void multiply(const math::Matrix<T>&other){
        assert(mat.size() == other.mat.size() && "matrix with different size (multiplication)");

        for (size_t i = 0; i < mat.size(); ++i) {
            mat[i] *= other.mat[i];
        }
    }

    inline void fill(const T value){
        std::fill(mat.begin(),mat.end(),value);
    }

    inline void printMat() const{
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                std::cout << "" << static_cast<int>(operator()(r,c)) << ",";
            }
            std::cout << "\n";
        }
        std::cout << "---------------------------\n";
    }

};

using matrix_u8     = math::Matrix<unsigned char>; // 0 - 255
using matrix_u32    = math::Matrix<uint32_t>;
using matrix_i32    = math::Matrix<int>;
using matrix_f32    = math::Matrix<float>;

static math::matrix_i32 segregate(const math::matrix_i32&mat){

    // get all neigbours
    // 0 1 0
    // 8 x 2
    // 0 4 0
    std::vector<math::Vec2i> walk4 = {
        math::Vec2i(-1,0),    // 1
        math::Vec2i(0,+1),    // 2
        math::Vec2i(+1,0),    // 4
        math::Vec2i(0,-1),    // 8
    };

    math::matrix_i32 resultMat(mat.rows,mat.cols,0);
    math::matrix_i32 visitedMat(mat.rows,mat.cols,0);
    math::matrix_i32 inverseMat(mat.rows,mat.cols);

    for (int index = 0; index < mat.mat.size(); ++index) {
        inverseMat[index] = (mat.mat[index] == 0)?1:0;
    }

    inverseMat.printMat();

    // iterate over the matrix and tag disconected grids
    for (int row = 0; row < inverseMat.rows; ++row) {
        for (int col = 0; col < inverseMat.cols; ++col) {


            if(inverseMat(row,col) == 1){ // it's a valid cell
                // check if has neighbours
                int hasNeighbour = -1;
                for(auto &walk:walk4){
                    // is inside the matrix boundaries?
                    if(inverseMat.checkBounds(row+walk.y,col+walk.y)){
                        auto value = mat(row+walk.y,col+walk.y);
                        if(value == 0){
                            // is value equals to maxCounter
                        }
                    }
                }
            }
        }
    }

    return inverseMat;
}


}

#endif // MATH_MATRIX_H
