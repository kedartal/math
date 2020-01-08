#include <test/unit/math/test_ad.hpp>
#include <limits>

TEST(mathMixScalFun, std_normal_cdf_derivatives) {
  auto f = [](const auto& y) { return stan::math::std_normal_cdf(y); };

  stan::test::expect_ad(f, -50.0);
  // the following fails because AD returns -nan in the Hessian
  // stan::test::expect_ad(f, -20.0 * stan::math::SQRT_TWO);
  // the following fails because AD returns inf in the Hessian
  // stan::test::expect_ad(f, -20.0);
  stan::test::expect_ad(f, -19);
  stan::test::expect_ad(f, -5.5);
  stan::test::expect_ad(f, 0.0);
  stan::test::expect_ad(f, 0.15);
  stan::test::expect_ad(f, 1.14);
  stan::test::expect_ad(f, 3.00);
  stan::test::expect_ad(f, 10.00);
}
