#pragma once

#include <algorithm>
//#include <initializer_list>
//#include <format>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace Math {

// TODO: add support for different ways to calculate determinant
/**
 * @brief Probing Uranus
 *
 * @tparam T
 */
template <typename T> class Matrix {
public:
  explicit Matrix(std::size_t x = 0, std::size_t y = 0);

  auto & operator()(std::size_t x, std::size_t y);
  const auto &operator()(std::size_t x, std::size_t y) const;
  auto &at(std::size_t x, std::size_t y);
  const auto &at(std::size_t x, std::size_t y) const;

  std::size_t getHeight() const;
  std::size_t getWidth() const;


  void printMatrix() const;

private:
  static const std::size_t MaxHeight{100};
  static const std::size_t MaxWidth{100};
  std::size_t m_width{0}, m_height{0};
  std::vector<T> m_matrix;
};
/*
template<typename T>
class Determinat{
    virtual determinant(const Matrix<T> & ob) = 0;
}

*/
// MISC. FUNCS

// throws: invalid_argument
template <typename T, typename E>
Matrix<decltype(T() + E())> operator+(const Matrix<T> &lhs,
                                      const Matrix<E> &rhs);

// throws: invalid_argument
template <typename T, typename E>
Matrix<decltype(T() * E())> operator*(const Matrix<T> &lhs,
                                      const Matrix<E> &rhs);


template <typename T, typename E>
Matrix<decltype(T() * E())> operator*(E scalar, const Matrix<T> & ob);


template <typename T, typename E>
Matrix<decltype(T() * E())> operator*=(Matrix<T> &lhs, const Matrix<E> &rhs);
// decomposition method? dec_col - column by which the decomposition is
// performed 
//throws: invalid_argument
template <typename T>
auto determinant(const Matrix<T> &ob, std::size_t dec_col = 0);

template <typename T>
auto additionalMinor(const Matrix<T> &ob, std::size_t out_row, std::size_t out_column);

template <typename T>
auto transposition(const Matrix<T> &ob);

template <typename T>
auto inverseMatrix(const Matrix<T> &ob) /*->decltype(ob)*/;
//--------->
template <typename T>
Matrix<T>::Matrix(std::size_t x, std::size_t y)
    : m_width{std::min(x, MaxWidth)}, m_height{std::min(y, MaxHeight)},
      m_matrix{std::vector<T>(m_height * m_width)} {
  // m_matrix.reserve(m_height*m_width);
}

// template<typename T>
// Matrix<T>::Matrix(std::initializer_list<T> init) : m_matrix{init}{}

template <typename T>
inline auto &Matrix<T>::operator()(std::size_t x, std::size_t y) {
  return m_matrix[x * m_width + y];
}

template <typename T>
inline const auto &Matrix<T>::operator()(std::size_t x, std::size_t y) const {
  return m_matrix[x * m_width + y];
}

template <typename T> inline auto &Matrix<T>::at(std::size_t x, std::size_t y) {
  return m_matrix.at(x * m_width + y);
}

template <typename T>
inline const auto &Matrix<T>::at(std::size_t x, std::size_t y) const {
  return m_matrix.at(x * m_width + y);
}

template <typename T> inline std::size_t Matrix<T>::getHeight() const {
  return m_height;
}
template <typename T> inline std::size_t Matrix<T>::getWidth() const {
  return m_width;
}

//template <typename T>
//auto Matrix<T>::operator<=>(const Matrix<T> ob) const = default;

template <typename T, typename E>
Matrix<decltype(T() + E())> operator+(const Matrix<T> &lhs, const Matrix<E> &rhs) {
  if (lhs.getHeight() != rhs.getHeight() || lhs.getWidth() != rhs.getWidth()) {
    throw std::invalid_argument{"invalid argument"};
  }

  Matrix<decltype(T() + E())> tmp{lhs.getWidth(), lhs.getHeight()};

  for (size_t row{0}; row < lhs.getWidth(); ++row) {
    for (size_t column{0}; column < lhs.getHeight(); ++column) {
      tmp(row, column) = lhs(row, column) + rhs(row, column);
    }
  }
  return tmp;
}

template <typename T, typename E>
Matrix<decltype(T() * E())> operator*(const Matrix<T> &lhs, const Matrix<E> &rhs)
{
  if (lhs.getHeight() != rhs.getWidth()) {
    throw std::invalid_argument{
        "invalid argument: sizes of matrices must be the same"};
  }

  Matrix<decltype(T() * E())> tmp{lhs.getWidth(), rhs.getHeight()};

  for (size_t row{0}; row < tmp.getWidth(); ++row) {
    for (size_t column{0}; column < tmp.getHeight(); ++column) {
      for (size_t k{0}; k < lhs.getHeight(); ++k) {
        tmp(row, column) += lhs(row, k) * rhs(k, column);
      }
    }
  }
  return tmp;
}
template <typename T> void Matrix<T>::printMatrix() const {
  for (size_t row{0}; row < getWidth(); ++row) {
    std::cout << "| ";
    for (size_t column{0}; column < getHeight(); ++column) {
      //std::cout << std::format("{:<9.3} ", (*this)(row, column));
      std::cout<<(*this)(row, column)<<' ';
    }
    std::cout << "|\n";
  }
  std::cout << std::endl;
}

template <typename T>
auto determinant(const Matrix<T> &ob, std::size_t dec_col) {
  if (ob.getHeight() != ob.getWidth()) {
    throw std::invalid_argument{"Required square matrix"};
  }

  if (ob.getHeight() == 2) {
    return ob(0, 0) * ob(1, 1) - ob(1, 0) * ob(0, 1);
  } else if (ob.getHeight() == 1)
    return ob(0, 0);

  T det{};
  // check_for_null() //may will be helpful later

  dec_col = std::min(dec_col, ob.getHeight() - 1);

  for (std::size_t row{0}; row < ob.getWidth(); ++row) {
    det += ob(row, dec_col) * determinant(additionalMinor(ob, row, dec_col)) *
           ((row + dec_col) % 2 == 0 ? 1 : -1);
  }
  return det;
}
template <typename T>
auto additionalMinor(const Matrix<T> &ob, std::size_t out_row, std::size_t out_column) 
{
  if(out_row >= ob.getWidth() || out_column >= ob.getHeight()) throw std::invalid_argument{"invalid arguments"};
  Matrix<T> minor{ob.getWidth() - 1, ob.getHeight() - 1};

  for (std::size_t row{0}; row < ob.getWidth(); ++row) {
    for (std::size_t column{0}; column < ob.getHeight(); ++column) {
      if (row < out_row) {
        if (column < out_column) {
          minor(row, column) = ob(row, column);
        } else if (column > out_column) {
          minor(row, column - 1) = ob(row, column);
        }
      } else if (row > out_row) {
        if (column < out_column) {
          minor(row - 1, column) = ob(row, column);
        } else if (column > out_column) {
          minor(row - 1, column - 1) = ob(row, column);
        }
      }
    }
  }
  return minor;
}
template <typename T> auto transposition(const Matrix<T> &ob) {
  Matrix<T> trans_matrix{ob.getHeight(), ob.getWidth()};

  for (size_t row{0}; row < ob.getWidth(); ++row) {
    for (size_t column{0}; column < ob.getHeight(); ++column) {
      trans_matrix(column, row) = ob(row, column);
    }
  }

  return trans_matrix;
}
template <typename T> auto inverseMatrix(const Matrix<T> &ob) {
  if (determinant(ob) == 0) {
    throw std::invalid_argument{"Determinant equal to zero"};
    // return ob;
  }

  Matrix<T> result{ob.getWidth(), ob.getHeight()};

  auto det{determinant(ob)};

  for (size_t row{0}; row < result.getWidth(); ++row) {
    for (size_t column{0}; column < result.getHeight(); ++column) {
      result(row, column) = (determinant(additionalMinor(ob, row, column)) *
                             ((row + column) % 2 == 0 ? 1 : -1)) /
                            det;
    }
  }

  //result = transposition(result);
  //return result;
   return transposition(result); // Will RVO or NRVO work??? Which way is better?
}

template <typename T, typename E>
Matrix<decltype(T() * E())> operator*(E scalar, const Matrix<T> & ob){
  Matrix<decltype(T() * E())> tmp{ob};
  for(std::size_t row{0}; row<ob.getWidth();++row){
    for(std::size_t column{0}; column < ob.getHeight(); ++column){
      tmp(row,column) = ob(row,column) * scalar;
    }
  }
  return tmp;
}

template<typename T>
auto initWithIdentityMatrix(std::size_t x = 0) {
  auto result{Matrix<T> {x ,x} };
  for(std::size_t row{0}; row < x ; ++row){
       //result (row, row) = static_cast<T>(1);
    result(row,row) = 1;
}
  return result;
}

template <typename T, typename E>
Matrix<decltype(T() * E())> operator*=(Matrix<T> &lhs, const Matrix<E> &rhs){
  
  return lhs;
}
} // namespace Math
