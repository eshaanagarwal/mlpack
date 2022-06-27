/**
 * @file base.hpp
 *
 * The most basic core includes that mlpack expects; standard C++ includes and
 * Armadillo only
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_BASE_HPP
#define MLPACK_BASE_HPP

// First, check if Armadillo was included before, warning if so.
#ifdef ARMA_INCLUDES
#pragma message "Armadillo was included before mlpack; this can sometimes cause\
 problems.  It should only be necessary to include <mlpack/core.hpp> and not \
<armadillo>."
#endif

// Defining _USE_MATH_DEFINES should set M_PI.
#define _USE_MATH_DEFINES
#include <cmath>

// Next, standard includes.
#include <cctype>
#include <cfloat>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>

// But if it's not defined, we'll do it.
#ifndef M_PI
  #define M_PI 3.141592653589793238462643383279
#endif

// MLPACK_COUT_STREAM is used to change the default stream for printing
// purpose.
#if !defined(MLPACK_COUT_STREAM)
 #define MLPACK_COUT_STREAM std::cout
#endif

// MLPACK_CERR_STREAM is used to change the stream for printing warnings
// and errors.
#if !defined(MLPACK_CERR_STREAM)
 #define MLPACK_CERR_STREAM std::cerr
#endif

// Give ourselves a nice way to force functions to be inline if we need.
#define mlpack_force_inline
#if defined(__GNUG__) && !defined(DEBUG)
  #undef mlpack_force_inline
  #define mlpack_force_inline __attribute__((always_inline))
#elif defined(_MSC_VER) && !defined(DEBUG)
  #undef mlpack_force_inline
  #define mlpack_force_inline __forceinline
#endif

// Backport this functionality from C++14, if it doesn't exist.
#if __cplusplus <= 201103L
#if !defined(_MSC_VER) || _MSC_VER <= 1800
namespace std {

template<bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

}
#endif
#endif

// Backport std::any from C+17 to C++11 to replace boost::any.
// Use mnmlstc backport implementation only if compiler does not
// support C++17.
#if __cplusplus < 201703L
  #include <mlpack/core/std_backport/any.hpp>
  #include <mlpack/core/std_backport/string_view.hpp>
  #define ANY core::v2::any
  #define ANY_CAST core::v2::any_cast
  #define STRING_VIEW core::v2::string_view
#else
  #include <any>
  #include <string_view>
  #define ANY std::any
  #define ANY_CAST std::any_cast
  #define STRING_VIEW std::string_view
#endif 

// Now include Armadillo through the special mlpack extensions.
#include <mlpack/core/arma_extend/arma_extend.hpp>
#include <mlpack/core/util/arma_traits.hpp>

// On Visual Studio, disable C4519 (default arguments for function templates)
// since it's by default an error, which doesn't even make any sense because
// it's part of the C++11 standard.
#ifdef _MSC_VER
  #pragma warning(disable : 4519)
#endif

// Ensure that the user isn't doing something stupid with their Armadillo
// defines.
#include <mlpack/core/util/arma_config_check.hpp>

// This can be removed with Visual Studio supports an OpenMP version with
// unsigned loop variables.
#ifdef _WIN32
  #define omp_size_t intmax_t
#else
  #define omp_size_t size_t
#endif

// We need to be able to mark functions deprecated.
#include <mlpack/core/util/deprecated.hpp>

#endif
