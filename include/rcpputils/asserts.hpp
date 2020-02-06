// Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RCPPUTILS__ASSERTS_HPP_
#define RCPPUTILS__ASSERTS_HPP_

#include <exception>
#include <stdexcept>
#include <string>

#include "rcpputils/visibility_control.hpp"

// Needed to disable compiler warning for exporting a class that extends a
// non-DLL-interface class.
// This should be fine since its extending an STL class.
#ifdef _WIN32
# pragma warning(push)
# pragma warning(disable:4251)
# pragma warning(disable:4275)
#endif

namespace rcpputils
{

class RCPPUTILS_PUBLIC AssertionException : public std::exception
{
  std::string msg_;

public:
  explicit AssertionException(const char * msg);

  virtual const char * what() const throw();
};

class RCPPUTILS_PUBLIC IllegalStateException : public std::exception
{
  std::string msg_;

public:
  explicit IllegalStateException(const char * msg);

  virtual const char * what() const throw();
};

/**
 * Checks that an argument condition passes.
 *
 * \param condition
 * \throw std::invalid_argument if the condition is not met.
 */
inline void require_true(bool condition)
{
  if (!condition) {
    throw std::invalid_argument{"Invalid argument passed!"};
  }
}

/**
 * Checks that a state condition passes.
 *
 * \param condition
 * \throw rcpputils::IllegalStateException if the condition is not met.
 */
inline void check_true(bool condition)
{
  if (!condition) {
    throw rcpputils::IllegalStateException{"Check reported invalid state!"};
  }
}

/**
 * Asserts that a condition passes.
 *
 * This function behaves similar to assert, except that it throws instead of invoking abort().
 * \param condition
 * \throw rcpputils::AssertionException if the macro NDEBUG is not set and the condition is not met.
 */
inline void assert_true(bool condition)
{
// Same macro definition used by cassert
#ifndef NDEBUG
  if (!condition) {
    throw rcpputils::AssertionException{"Assertion failed!"};
  }
#else
  (void) condition;
#endif
}
}  // namespace rcpputils

#ifdef _WIN32
# pragma warning(pop)
#endif

#endif  // RCPPUTILS__ASSERTS_HPP_