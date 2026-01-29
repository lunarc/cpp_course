//
// Copyright (c) 2026 Jonas Lindemann
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Simple printing utilities for Eigen matrices and arrays.

#pragma once

#include <iostream>
#include <string>
#include <print>

#include <Eigen/Dense>

// Predefined format styles
namespace PrintFormat {
// Default Eigen format
inline const Eigen::IOFormat Default(Eigen::StreamPrecision, 0, " ", "\n", "", "");

// Compact format: [1, 2, 3; 4, 5, 6]
inline const Eigen::IOFormat Compact(Eigen::StreamPrecision, 0, ", ", ", ", "", "", "[", "]");

// Python-style: [[1, 2, 3], [4, 5, 6]]
inline const Eigen::IOFormat Python(Eigen::StreamPrecision, 0, ", ", ",\n ", "[", "]", "[", "]");

// Clean format with custom precision
inline const Eigen::IOFormat Clean(4, 0, ", ", "\n", "[", "]");

// Octave/MATLAB style
inline const Eigen::IOFormat Octave(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "];");

// CSV format
inline const Eigen::IOFormat CSV(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
inline const Eigen::IOFormat ShortCompact(4, 0, ", ", ", ", "", "", "[", "]");
inline const Eigen::IOFormat ShortClean(4, 0, ", ", "\n", "[", "]");
inline const Eigen::IOFormat ShortOctave(4, 0, ", ", ";\n", "", "", "[", "];");
inline const Eigen::IOFormat ShortPython(4, 0, ", ", ",\n", "[", "]", "[", "]");
}

namespace utils {

// Print with custom format
template<typename Derived>
void print(const std::string& name, 
           const Eigen::MatrixBase<Derived>& matrix,
           const Eigen::IOFormat& fmt)
{
    std::cout << name << "\n\n" << matrix.format(fmt) << "\n\n";
}

// Print with default format
template<typename Derived>
void print(const std::string& name, const Eigen::MatrixBase<Derived>& matrix)
{
    std::cout << name << "\n\n" << matrix.format(PrintFormat::ShortPython) << "\n\n";
}

// Print without name, with custom format
template<typename Derived>
void print(const Eigen::MatrixBase<Derived>& matrix, const Eigen::IOFormat& fmt)
{
    std::cout << matrix.format(fmt) << "\n\n";
}

// Print without name, default format
template<typename Derived>
void print(const Eigen::MatrixBase<Derived>& matrix)
{
    std::cout << matrix.format(PrintFormat::ShortPython) << "\n\n";
}

// Array overloads
// Print array with custom format
template<typename Derived>
void print(const std::string& name, 
           const Eigen::ArrayBase<Derived>& array,
           const Eigen::IOFormat& fmt)
{
    std::cout << name << "\n\n" << array.format(fmt) << "\n\n";
}

// Print array with default format
template<typename Derived>
void print(const std::string& name, const Eigen::ArrayBase<Derived>& array)
{
    std::cout << name << "\n\n" << array.format(PrintFormat::ShortPython) << "\n\n";
}

// Print array without name, with custom format
template<typename Derived>
void print(const Eigen::ArrayBase<Derived>& array, const Eigen::IOFormat& fmt)
{
    std::cout << array.format(fmt) << "\n\n";
}

// Print array without name, default format
template<typename Derived>
void print(const Eigen::ArrayBase<Derived>& array)
{
    std::cout << array.format(PrintFormat::ShortPython) << "\n\n";
}

// Print address of matrix
template < typename Derived > void print_addr(const Eigen::MatrixBase< Derived > &matrix)
{
    std::print("Address of matrix data: {}\n", static_cast< const void * >(matrix.derived().data()));
}



} // namespace utils
