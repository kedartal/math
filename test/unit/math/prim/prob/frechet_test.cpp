#include <stan/math/prim.hpp>
#include <test/unit/math/prim/prob/vector_rng_test_helper.hpp>
#include <test/unit/math/prim/prob/util.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <vector>

class FrechetTestRig : public VectorRealRNGTestRig {
 public:
  FrechetTestRig()
      : VectorRealRNGTestRig(10000, 10, {0.5, 1.0, 1.3, 2.0}, {1, 2, 3},
                             {-2.5, -1.7, -0.1, 0.0}, {-3, -2, -1, 0},
                             {0.1, 1.0, 1.7, 2.1}, {1, 2, 3, 4},
                             {-2.7, -1.5, -0.5, 0.0}, {-3, -2, -1, 0}) {}

  /*
   * Since boost does not have a Frechet distribution, generate values from
   * a Weibull distribution using the Frechet rng, and compare against the
   * quantiles from a Weibull distribution.
   */
  template <typename T1, typename T2, typename T3, typename T_rng>
  auto generate_samples(const T1& alpha, const T2& sigma, const T3&,
                        T_rng& rng) const {
    return stan::math::inv(stan::math::frechet_rng(alpha, sigma, rng));
  }

  std::vector<double> generate_quantiles(double alpha, double sigma,
                                         double) const {
    std::vector<double> quantiles;
    double K = stan::math::round(2 * std::pow(N_, 0.4));
    boost::math::weibull_distribution<> dist(alpha, 1.0 / sigma);

    for (int i = 1; i < K; ++i) {
      double frac = i / K;
      quantiles.push_back(quantile(dist, frac));
    }
    quantiles.push_back(std::numeric_limits<double>::max());

    return quantiles;
  }
};

TEST(ProbDistributionsFrechet, errorCheck) {
  check_dist_throws_all_types(FrechetTestRig());
}

TEST(ProbDistributionsFrechet, distributionTest) {
  check_quantiles_real_real(FrechetTestRig());
}

TEST(ProbDistributionsFrechet, error_check) {
  boost::random::mt19937 rng;
  EXPECT_NO_THROW(stan::math::frechet_rng(2.0, 3.0, rng));

  EXPECT_THROW(stan::math::frechet_rng(-2.0, 3.0, rng), std::domain_error);
  EXPECT_THROW(stan::math::frechet_rng(2.0, -3.0, rng), std::domain_error);
  EXPECT_THROW(
      stan::math::frechet_rng(stan::math::positive_infinity(), 3.0, rng),
      std::domain_error);
}

TEST(ProbDistributionsFrechet, chiSquareGoodnessFitTest) {
  boost::random::mt19937 rng;
  int N = 10000;
  int K = stan::math::round(2 * std::pow(N, 0.4));

  // and invert them to compare to Weibull
  std::vector<double> samples;
  for (int i = 0; i < N; ++i) {
    samples.push_back(1.0 / stan::math::frechet_rng(2.0, 1.0 / 5.0, rng));
  }

  // Generate quantiles from boost's Frechet distribution
  // Actually, boost doesn't have a Frechet distribution
  // So we use the Weibull.
  boost::math::weibull_distribution<> dist(2.0, 5.0);
  std::vector<double> quantiles;
  for (int i = 1; i < K; ++i) {
    double frac = static_cast<double>(i) / K;
    quantiles.push_back(quantile(dist, frac));
  }
  quantiles.push_back(std::numeric_limits<double>::max());

  // Assert that they match
  assert_matches_quantiles(samples, quantiles, 1e-6);
}
