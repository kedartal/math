#ifndef STAN_MATH_PRIM_MAT_FUN_ATAN_HPP
#define STAN_MATH_PRIM_MAT_FUN_ATAN_HPP

#include <stan/math/prim/vectorize/apply_scalar_unary.hpp>
#include <cmath>

namespace stan {
namespace math {

/**
 * Structure to wrap atan() so it can be vectorized.
 *
 * @tparam T type of variable
 * @param x variable
 * @return Arctan of x in radians.
 */
struct atan_fun {
  template <typename T>
  static inline T fun(const T& x) {
    using std::atan;
    return atan(x);
  }
};

/**
 * Vectorized version of atan().
 *
 * @tparam T type of container
 * @param x container
 * @return Arctan of each value in x, in radians.
 */
template <typename T>
inline typename apply_scalar_unary<atan_fun, T>::return_t atan(const T& x) {
  return apply_scalar_unary<atan_fun, T>::apply(x);
}

}  // namespace math
}  // namespace stan

#endif
