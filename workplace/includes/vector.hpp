/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:48:41 by cmariot           #+#    #+#             */
/*   Updated: 2023/12/20 10:25:56 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <list>
#include <initializer_list>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace ft
{

    // template <typename T>
    // class Matrix;

    template <typename T>
    class Vector
    {

        /*
        Vectors are ordered lists of objects that can be accessed by their index.
        */

        typedef T               value_type;
        typedef T &             reference;
        typedef const T &       const_reference;
        typedef size_t          size_type;


        public:

            Vector();
            Vector(size_type size);
            Vector(size_type size, const_reference val);
            // Vector(std::initializer_list<T> initList);
            Vector(const Vector &copy);
            // Vector(const Matrix<T> &copy);

            ~Vector();

            size_type size() const;

            // Addition : Add two vectors
            Vector operator+(const Vector &rhs) const
            {
                Vector result(*this);

                if (result.size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");
                for (size_type i = 0; i < result.size(); i++)
                    result[i] += rhs[i];
                return result;
            }

            // Operator += : Add two vectors
            Vector &operator+=(const Vector &rhs)
            {
                if (this->size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");
                for (size_type i = 0; i < this->size(); i++)
                    (*this)[i] += rhs[i];
                return *this;
            }

            // add : Add two vectors
            Vector &add(const Vector &rhs)
            {
                if (this->size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");
                for (size_type i = 0; i < this->size(); i++)
                    (*this)[i] += rhs[i];
                return *this;
            }

            // Substraction : Substract two vectors
            Vector operator-(const Vector &rhs) const
            {
                Vector result(*this);

                if (result.size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");
                for (size_type i = 0; i < result.size(); i++)
                    result[i] -= rhs[i];
                return result;
            }

            // Operator -= : Substract two vectors
            Vector &operator-=(const Vector &rhs)
            {
                if (this->size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");
                for (size_type i = 0; i < this->size(); i++)
                    (*this)[i] -= rhs[i];
                return *this;
            }

            // Substract : Substract two vectors
            Vector &sub(const Vector &rhs)
            {
                if (this->size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");
                for (size_type i = 0; i < this->size(); i++)
                    (*this)[i] -= rhs[i];
                return *this;
            }

            // Operator * : Scale a vector by a scalar
            Vector operator*(const_reference rhs) const
            {
                Vector result(*this);

                for (size_type i = 0; i < result.size(); i++)
                    result[i] *= rhs;
                return result;
            }

            // Operator *= : Scale a vector
            Vector operator*=(const_reference rhs)
            {
                for (size_type i = 0; i < this->size(); i++)
                    (*this)[i] *= rhs;
                return *this;
            }

            // Scale : Scale a vector
            Vector &scl(const_reference rhs)
            {
                for (size_type i = 0; i < this->size(); i++)
                    (*this)[i] *= rhs;
                return *this;
            }

            // Linear combination : Linear combination of two vectors
            static Vector linear_combination(const std::list<Vector<double> > &u, const std::list<double> &v)
            {
                /*
                Linear combination of two lists u and v is a vector w defined as:
                w = v1 * u1 + v2 * u2 + ... + vn * un

                Example:

                    u = list({1, 0, 0}, {0, 1, 0}, {0, 0, 1})
                    v = {10, -2, 0.5}

                    w = 10 * u1 + (-2) * u2 + 0.5 * u3
                    w = {10, -2, 0.5}

                It's used to get the span of a set of vectors.
                The span of a set of vectors is the set of all possible linear combinations of the vectors.

                */

                if (u.size() != v.size())
                    throw std::length_error("Lists are not the same size.");
                else if (u.size() == 0)
                    throw std::length_error("Lists are empty.");

                std::list<Vector<double> >::const_iterator it_u = u.begin();
                std::list<double>::const_iterator         it_v = v.begin();
                ft::Vector<double>                        lin_comb((*it_u).size());

                // For each element in u and v
                for (; it_u != u.end(); ++it_u, ++it_v)
                {

                    // Check if all vectors in u have the same size
                    if ((*it_u).size() != lin_comb.size())
                        throw std::length_error("Vectors are not the same dimension.");
                    else if ((*it_u).size() == 0)
                        throw std::length_error("Vectors are empty.");

                    // Compute the linear combination
                    for (size_type i = 0; i < lin_comb.size(); i++)
                        lin_comb[i] = std::fma((*it_u)[i], *it_v, lin_comb[i]);

                }
                return lin_comb;
            }


            // Dot product : Dot product of two vectors
            double dot(const Vector<T> & rhs) const
            {
                if (this->size() != rhs.size())
                    throw std::length_error("Vectors are not the same size.");

                typename std::vector<T>::const_iterator it1 = this->_vector.begin();
                typename std::vector<T>::const_iterator it2 = rhs._vector.begin();
                double result = 0.0;

                while (it1 != this->_vector.end())
                {
                    result = std::fma(*it1, *it2, result);
                    ++it1;
                    ++it2;
                }
                return result;
            }

            double norm_1() const
            {
                /*
                The 1-norm is simply the sum of the absolute values of the columns.
                */

                typename std::vector<T>::const_iterator it = this->_vector.begin();
                double result = 0.0;

                while (it != this->_vector.end())
                {
                    result += std::max(-*it, *it);
                    ++it;
                }
                return result;
            }

            double norm() const
            {
                /*
                Euclidean norm is the square root of the sum of the squares of the elements.

                pythagore : a^2 + b^2 = c^2
                -> c = sqrt(a^2 + b^2)
                */

                typename std::vector<T>::const_iterator it = this->_vector.begin();
                double result = 0.0;

                while (it != this->_vector.end())
                {
                    result = std::fma(*it, *it, result);
                    ++it;
                }
                return std::pow(result, 0.5);
            }

            double norm_inf() const
            {
                /*
                Infinity norm is the maximum absolute value of the elements.
                */

                typename std::vector<T>::const_iterator it = this->_vector.begin();
                double result = 0.0;

                while (it != this->_vector.end())
                {
                    result = std::max(result, std::max(-*it, *it));
                    ++it;
                }
                return result;

            }

            // Operator << : Display the vector
            friend std::ostream &operator<<(std::ostream &os, const Vector &vector)
            {
                os << "[";
                for (size_type i = 0; i < vector._vector.size(); i++)
                {
                    os << vector._vector[i];
                    if (i < vector._vector.size() - 1)
                        os << ", ";
                }
                os << "]";
                return os;
            }

            // Operator [] : Access element
            reference operator[](size_type pos)
            {
                return _vector[pos];
            }

            const_reference operator[](size_type pos) const
            {
                return _vector[pos];
            }

            // Operator = : Assign content
            Vector &operator=(const Vector &rhs)
            {
                _vector = rhs._vector;
                return *this;
            }

            Vector &operator=(Vector &rhs)
            {
                _vector = rhs._vector;
                return *this;
            }

            // Operator == : Compare content
            bool operator==(const Vector &rhs) const
            {
                if (_vector.size() != rhs._vector.size())
                {
                    std::cout << "Size is different" << std::endl;
                    return false;
                }
                for (size_type i = 0; i < _vector.size(); i++)
                {
                    if (_vector[i] != rhs._vector[i])
                    {
                        std::cout << "Element " << i << " is different" << std::endl;
                        std::cout << "lhs = " << _vector[i] << std::endl;
                        std::cout << "rhs = " << rhs._vector[i] << std::endl;
                        return false;
                    }
                }
                return true;
            }

            // Operator != : Compare content
            bool operator!=(const Vector &rhs) const
            {
                return !(*this == rhs);
            }

        private:

            std::vector<T> _vector;

    };


}

// Constructor : Default
template <typename T>
ft::Vector<T>::Vector()
{
    _vector = std::vector<T>();
}

// Constructor : Size
template <typename T>
ft::Vector<T>::Vector(size_type size)
{
    _vector = std::vector<T>(size);
}

// Constructor : Size and value
template <typename T>
ft::Vector<T>::Vector(size_type size, const_reference val)
{
    _vector = std::vector<T>(size, val);
}

// Constructor : Copy
template <typename T>
ft::Vector<T>::Vector(const Vector &copy)
{
    _vector = copy._vector;
}

// // Constructor : Copy from Matrix
// template <typename T>
// ft::Vector<T>::Vector(const Matrix<T> &copy)
// {
//     for (size_type i = 0; i < copy.size()[0]; i++)
//         for (size_type j = 0; j < copy.size()[1]; j++)
//             _vector.push_back(copy[i][j]);
// }

// Constructor : Initializer list
// template <typename T>
// ft::Vector<T>::Vector(std::initializer_list<T> initList)
// {
//     _vector = std::vector<T>(initList);
// }

// Destructor
template <typename T>
ft::Vector<T>::~Vector()
{
    _vector.clear();
}


// Size
template <typename T>
typename ft::Vector<T>::size_type ft::Vector<T>::size() const
{
    return _vector.size();
}



#endif
