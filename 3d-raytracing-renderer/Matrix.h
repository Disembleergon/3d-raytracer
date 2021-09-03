#ifndef MATRIX_H
#define MATRIX_H
#define _USE_MATH_DEFINES

#include "Equal.h"
#include "Tuple.h"
#include <array>
#include <math.h>
#include <stdexcept>
#include <vector>

#include <iostream>

using element_type = double;
using elementlist = std::vector<std::vector<element_type>>;

class Matrix
{
  public:
    using size_type = std::vector<std::vector<element_type>>::size_type;

    Matrix(const size_type &rows, const size_type &cols) : m_rows{rows}, m_cols{cols}
    {

        for (size_type row = 0; row < m_rows; row++)
        {
            std::vector<element_type> rowvect{};
            for (size_type col = 0; col < m_cols; col++)
            {
                rowvect.push_back(element_type{});
            }
            m_elements.push_back(rowvect);
        }
    }

    Matrix(const std::vector<std::vector<element_type>> &elements)
        : m_rows{elements.size()}, m_cols{elements.at(0).size()}
    {
        if (m_rows < 1)
        {
            throw std::logic_error{"Matrix hat keine Zeilen (keine Elemente)"};
        }

        for (auto &row : elements)
        {
            if (row.size() != m_cols)
            {
                throw std::logic_error{"Matrix hat Zeilen mit unterschiedlich langen Spalten"};
            }
            m_elements.push_back(row);
        }
    }

    size_type rows() const
    {
        return m_rows;
    }
    size_type cols() const
    {
        return m_cols;
    }
    elementlist elements() const
    {
        return m_elements;
    };
    void resize(const size_type &rows, const size_type &cols)
    {
        m_rows = rows;
        m_cols = cols;
        m_elements.clear();
    }

    void set(size_type row, size_type col, const element_type &value)
    {
        m_elements[row][col] = value;
    }

    const element_type get(const size_type &row, const size_type &col) const
    {
        return m_elements[row][col];
    }

    element_type get(size_type row, size_type col)
    {
        return m_elements[row][col];
    }

    Matrix transpose()
    {
        std::vector<std::vector<element_type>> temp_elements;

        for (size_type row = 0; row < rows(); row++)
        {
            std::vector<element_type> rowvect{};
            for (size_type col = 0; col < cols(); col++)
            {
                rowvect.push_back(m_elements[row][col]);
            }
            temp_elements.push_back(rowvect);
        }

        for (size_type row = 0; row < rows(); row++)
        {
            for (size_type col = 0; col < cols(); col++)
            {
                temp_elements[col][row] = m_elements[row][col];
            }
        }

        m_elements = temp_elements;

        return *this;
    }

    friend bool operator==(const Matrix &mat1, const Matrix &mat2)
    {
        if ((mat1.rows() != mat2.rows()) || (mat1.cols() != mat2.cols()))
            return false;

        for (size_type row = 0; row < mat1.rows(); row++)
        {
            for (size_type col = 0; col < mat1.cols(); col++)
            {
                if (!(floatEqual(mat1.get(row, col), mat2.get(row, col))))
                    return false;
            }
        }

        return true;
    }

    Matrix operator*(const Matrix &mat) const
    {
        Matrix m{mat.rows(), mat.cols()};

        for (size_type row = 0; row < 4; row++)
        {
            for (size_type col = 0; col < 4; col++)
            {
                element_type val = get(row, 0) * mat.get(0, col) + get(row, 1) * mat.get(1, col) +
                                   get(row, 2) * mat.get(2, col) + get(row, 3) * mat.get(3, col);
                m.set(row, col, val);
            }
        }

        return m;
    }

    // default copy constructor
    Matrix(const Matrix &orig) = default;

    Matrix &operator=(const Matrix &m)
    {
        resize(m.rows(), m.cols());
        m_elements = m.elements();

        return *this;
    }

    Tuple operator*(const Tuple &tup)
    {

        if (m_rows != 4 || m_cols != 4)
            throw std::logic_error("Matrix isn't a 4x4 Matrix");

        std::array<element_type, 4> result{};

        for (int i = 0; i < 4; i++)
        {
            result[i] = get(i, 0) * tup.x + get(i, 1) * tup.y + get(i, 2) * tup.z + get(i, 3) * tup.w;
        }

        return {result[0], result[1], result[2], static_cast<int>(result[3])};
    }

    Matrix submatrix(size_type rowToRemove, size_type colToRemove) const
    {
        Matrix result{rows() - 1, cols() - 1};
        unsigned int sourceRow = 0;

        for (size_type i = 0; i < rows() - 1; i++)
        {
            // Reihe �berspringen
            if (i == rowToRemove)
            {
                sourceRow++;
            }

            unsigned int sourceCol = 0;

            for (size_type j = 0; j < cols() - 1; j++)
            {

                // Spalte �berspringen
                if (j == colToRemove)
                {
                    sourceCol++;
                }

                result.set(i, j, get(sourceRow, sourceCol));
                sourceCol++;
            }
            sourceRow++;
        }

        return result;
    }

    element_type minor(const size_type pRow, const size_type pCol) const
    {
        return submatrix(pRow, pCol).determinant();
    }

    element_type cofactor(const size_type pRow, const size_type pCol) const
    {
        return minor(pRow, pCol) * ((pRow + pCol) % 2 == 0 ? 1 : -1);
    }

    element_type determinant() const
    {
        if ((rows() * cols()) <= 4)
            return (get(0, 0) * get(1, 1)) - (get(0, 1) * get(1, 0));

        element_type det{};
        for (size_type col = 0; col < cols(); col++)
        {
            det += get(0, col) * cofactor(0, col);
        }

        return det;
    }

    Matrix inverse()
    {
        if (determinant() == 0)
            throw std::logic_error("Matrix ist nicht invertierbar!");

        Matrix m2{rows(), cols()};

        for (int col = 0; col < cols(); col++)
        {
            for (int row = 0; row < rows(); row++)
            {
                element_type c = cofactor(row, col);
                m2.set(col, row, (c / determinant()));
            }
        }
        return m2;
    }

  private:
    elementlist m_elements;
    size_type m_rows;
    size_type m_cols;
};

inline Matrix IDENTITY_MATRIX()
{
    return Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
};

/*
    gew�nschte Reihenfolge immer r�ckw�rts angeben!
    A = translate(...), B = rotate(...), C = scale(...)
    gew�nschte Reihenfolge: rotate, scale, translate
    -> (B * C * A) * teapot
 */

inline Matrix translation(const element_type &x, const element_type &y, const element_type &z)
{
    return Matrix({{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}});
}

inline Matrix scaling(const element_type &x, const element_type &y, const element_type &z)
{
    return Matrix({{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}});
}

inline element_type toRadians(const element_type &deg)
{
    return (M_PI / 180) * deg;
}

inline Matrix rotate_x(const element_type &r)
{
    return Matrix({{1, 0, 0, 0}, {0, cos(r), -sin(r), 0}, {0, sin(r), cos(r), 0}, {0, 0, 0, 1}});
}

inline Matrix rotate_y(const element_type &r)
{
    return Matrix({{cos(r), 0, sin(r), 0}, {0, 1, 0, 0}, {-sin(r), 0, cos(r), 0}, {0, 0, 0, 1}});
}

inline Matrix rotate_z(const element_type &r)
{
    return Matrix({{cos(r), -sin(r), 0, 0}, {sin(r), cos(r), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}

inline Matrix shearing(const element_type &xy, const element_type &xz, const element_type &yx, const element_type &yz,
                       const element_type &zx, const element_type &zy)
{
    return Matrix({{1, xy, xz, 0}, {yx, 1, yz, 0}, {zx, zy, 1, 0}, {0, 0, 0, 1}});
}

inline Matrix view_transform(const Tuple &from, const Tuple &to, const Tuple &up)
{

    const Tuple forward = normalize(to - from);
    const Tuple upn = normalize(up);
    const Tuple left = cross(forward, upn);
    const Tuple true_up = cross(left, forward);

    const Matrix orientation = Matrix({{left.x, left.y, left.z, 0},
                                       {true_up.x, true_up.y, true_up.z, 0},
                                       {-forward.x, -forward.y, -forward.z, 0},
                                       {0, 0, 0, 1}});
    return orientation * translation(-from.x, -from.y, -from.z);
}

#endif
