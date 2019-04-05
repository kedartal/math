
#include <stan/math/rev.hpp>
#include <gtest/gtest.h>
#include <test/unit/math/rev/fun/nan_util.hpp>
#include <test/unit/math/rev/util.hpp>

#include <test/unit/math/rev/fun/util.hpp>
#include <vector>











void test_log_mix_vvv(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var theta_v = theta;
  var lambda1_v = lambda1;
  var lambda2_v = lambda2;

  std::vector<var> x;
  x.push_back(theta_v);
  x.push_back(lambda1_v);
  x.push_back(lambda2_v);

  var lp = log_mix(theta_v, lambda1_v, lambda2_v);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var theta_v2 = theta;
  var lambda1_v2 = lambda1;
  var lambda2_v2 = lambda2;

  std::vector<var> x2;
  x2.push_back(theta_v2);
  x2.push_back(lambda1_v2);
  x2.push_back(lambda2_v2);

  var lp2 = log(theta_v2 * exp(lambda1_v2) + (1 - theta_v2) * exp(lambda2_v2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  var theta_v3 = 2.0;
  EXPECT_THROW(log_mix(theta_v3, lambda1_v, lambda2_v), std::domain_error);
  stan::math::recover_memory();
}

void test_log_mix_vv_ex_lam_2(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var theta_v = theta;
  var lambda1_v = lambda1;

  std::vector<var> x;
  x.push_back(theta_v);
  x.push_back(lambda1_v);

  var lp = log_mix(theta_v, lambda1_v, lambda2);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var theta_v2 = theta;
  var lambda1_v2 = lambda1;

  std::vector<var> x2;
  x2.push_back(theta_v2);
  x2.push_back(lambda1_v2);

  var lp2 = log(theta_v2 * exp(lambda1_v2) + (1 - theta_v2) * exp(lambda2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  var theta_v3 = 2.0;
  EXPECT_THROW(log_mix(theta_v3, lambda1_v, lambda2), std::domain_error);
  stan::math::recover_memory();
}

void test_log_mix_vv_ex_lam_1(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var theta_v = theta;
  var lambda2_v = lambda2;

  std::vector<var> x;
  x.push_back(theta_v);
  x.push_back(lambda2_v);

  var lp = log_mix(theta_v, lambda1, lambda2_v);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var theta_v2 = theta;
  var lambda2_v2 = lambda2;

  std::vector<var> x2;
  x2.push_back(theta_v2);
  x2.push_back(lambda2_v2);

  var lp2 = log(theta_v2 * exp(lambda1) + (1 - theta_v2) * exp(lambda2_v2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  var theta_v3 = 2.0;
  EXPECT_THROW(log_mix(theta_v3, lambda1, lambda2_v), std::domain_error);
  stan::math::recover_memory();
}

void test_log_mix_vv_ex_theta(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var lambda1_v = lambda1;
  var lambda2_v = lambda2;

  std::vector<var> x;
  x.push_back(lambda1_v);
  x.push_back(lambda2_v);

  var lp = log_mix(theta, lambda1_v, lambda2_v);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var lambda1_v2 = lambda1;
  var lambda2_v2 = lambda2;

  std::vector<var> x2;
  x2.push_back(lambda1_v2);
  x2.push_back(lambda2_v2);

  var lp2 = log(theta * exp(lambda1_v2) + (1 - theta) * exp(lambda2_v2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  EXPECT_THROW(log_mix(2.0, lambda1_v, lambda2_v), std::domain_error);
  stan::math::recover_memory();
}

void test_log_mix_v_theta(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var theta_v = theta;

  std::vector<var> x;
  x.push_back(theta_v);

  var lp = log_mix(theta_v, lambda1, lambda2);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var theta_v2 = theta;

  std::vector<var> x2;
  x2.push_back(theta_v2);

  var lp2 = log(theta_v2 * exp(lambda1) + (1 - theta_v2) * exp(lambda2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  var theta_v3 = 2.0;
  EXPECT_THROW(log_mix(theta_v3, lambda1, lambda2), std::domain_error);
  stan::math::recover_memory();
}

void test_log_mix_v_lam_1(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var lambda1_v = lambda1;

  std::vector<var> x;
  x.push_back(lambda1_v);

  var lp = log_mix(theta, lambda1_v, lambda2);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var lambda1_v2 = lambda1;

  std::vector<var> x2;
  x2.push_back(lambda1_v2);

  var lp2 = log(theta * exp(lambda1_v2) + (1 - theta) * exp(lambda2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  EXPECT_THROW(log_mix(2.0, lambda1_v, lambda2), std::domain_error);
  stan::math::recover_memory();
}

void test_log_mix_v_lam_2(double theta, double lambda1, double lambda2) {
  using stan::math::var;

  var lambda2_v = lambda2;

  std::vector<var> x;
  x.push_back(lambda2_v);

  var lp = log_mix(theta, lambda1, lambda2_v);
  double val1 = lp.val();

  std::vector<double> g;
  lp.grad(x, g);

  stan::math::recover_memory();

  var lambda2_v2 = lambda2;

  std::vector<var> x2;
  x2.push_back(lambda2_v2);

  var lp2 = log(theta * exp(lambda1) + (1 - theta) * exp(lambda2_v2));
  double val2 = lp2.val();

  std::vector<double> g2;
  lp2.grad(x2, g2);

  EXPECT_FLOAT_EQ(val2, val1);
  EXPECT_EQ(g2.size(), g.size());
  for (size_t i = 0; i < g2.size(); ++i)
    EXPECT_FLOAT_EQ(g2[i], g[i]) << "failed on " << i << std::endl;

  EXPECT_THROW(log_mix(2.0, lambda1, lambda2_v), std::domain_error);
  stan::math::recover_memory();
}

TEST(AgradRev, log_mix) {
  test_log_mix_vvv(0.3, 10.4, -10.9);
  test_log_mix_vvv(0.7, -4.7, 10.1);

  test_log_mix_vv_ex_lam_2(0.7, 1.4, -1.9);
  test_log_mix_vv_ex_lam_2(0.3, -10.4, 7.8);

  test_log_mix_vv_ex_lam_1(0.7, 1.4, -1.9);
  test_log_mix_vv_ex_lam_1(0.3, -10.4, 7.8);

  test_log_mix_vv_ex_theta(0.7, 1.4, -1.9);
  test_log_mix_vv_ex_theta(0.3, -10.4, 7.8);

  test_log_mix_v_theta(0.7, 1.4, -1.9);
  test_log_mix_v_theta(0.3, -1.4, 1.7);

  test_log_mix_v_lam_1(0.7, 1.4, -1.9);
  test_log_mix_v_lam_1(0.8, -1.9, 10.9);

  test_log_mix_v_lam_2(0.7, 1.4, 3.99);
  test_log_mix_v_lam_2(0.1, -1.4, 3.99);
}

struct log_mix_fun {
  template <typename T0, typename T1, typename T2>
  inline typename stan::return_type<T0, T1, T2>::type operator()(
      const T0& arg1, const T1& arg2, const T2& arg3) const {
    return log_mix(arg1, arg2, arg3);
  }
};

TEST(AgradRev, log_mix_NaN) {
  log_mix_fun log_mix_;
  test_nan(log_mix_, 0.6, 0.3, 0.5, true, false);
}

TEST(AgradRev, check_varis_on_stack) {
  stan::math::var theta = 0.5;
  stan::math::var x = 10.0;
  stan::math::var y = 4.0;
  test::check_varis_on_stack(stan::math::log_mix(theta, x, y));
  test::check_varis_on_stack(stan::math::log_mix(theta, x, 4.0));
  test::check_varis_on_stack(stan::math::log_mix(theta, 10.0, y));
  test::check_varis_on_stack(stan::math::log_mix(theta, 10.0, 4.0));
  test::check_varis_on_stack(stan::math::log_mix(0.5, x, y));
  test::check_varis_on_stack(stan::math::log_mix(0.5, x, 4.0));
  test::check_varis_on_stack(stan::math::log_mix(0.5, 10.0, y));
}






using stan::math::log_mix;
using stan::math::row_vector_v;
using stan::math::var;
using stan::math::vector_d;
using stan::math::vector_v;

template <typename T_a, typename T_b>
void val_rev_test(T_a a, T_b b) {
  a[0] = 0.112;
  a[1] = 0.214;
  a[2] = 0.305;
  a[3] = 0.369;

  b[0] = -5.983;
  b[1] = -11.215;
  b[2] = -6.836;
  b[3] = -4.538;

  AVAR out = log_mix(a, b);

  out.grad();

  EXPECT_FLOAT_EQ(out.val(), -5.390580825249);

  vector_d prob_deriv(4);
  prob_deriv << 0.55298789093, 0.00295451971, 0.23564727846, 2.3456928701;
  vector_d dens_deriv(4);
  dens_deriv << 0.06193464378, 0.00063226722, 0.07187241993, 0.86556066907;

  for (int i = 0; i < 4; ++i) {
    EXPECT_FLOAT_EQ(a[i].adj(), prob_deriv[i]);
    EXPECT_FLOAT_EQ(b[i].adj(), dens_deriv[i]);
  }

  T_a a2(4);
  a2[0] = 0.112;
  a2[1] = 0.214;
  a2[2] = 0.305;
  a2[3] = 0.369;

  T_b b1(4), b2(4), b3(4);

  b1[0] = -5.983;
  b1[1] = -11.215;
  b1[2] = -6.836;
  b1[3] = -4.538;

  b2[0] = -10.365;
  b2[1] = -12.443;
  b2[2] = -15.091;
  b2[3] = -19.115;

  b3[0] = -4.117;
  b3[1] = -8.132;
  b3[2] = -7.931;
  b3[3] = -12.115;

  std::vector<T_b> c{b1, b2, b3};

  AVAR std_out = log_mix(a2, c);

  std_out.grad();

  EXPECT_FLOAT_EQ(std_out.val(), -23.9255869110932);

  vector_d std_prob_deriv(4);
  std_prob_deriv << 15.7666988503552, 1.03434231079226, 0.478019548364374,
      2.34955152303399;

  vector_d std_dens1_deriv(4);
  std_dens1_deriv << 0.061934643784246, 0.000632267218743, 0.071872419930696,
      0.865560669066315;

  vector_d std_dens2_deriv(4);
  std_dens2_deriv << 0.791240264915128, 0.189251877628038, 0.019094771903811,
      0.000413085553023;

  vector_d std_dens3_deriv(4);
  std_dens3_deriv << 0.91269536254040, 0.031465109662762, 0.054828770416628,
      0.001010757380203;

  for (int i = 0; i < 4; ++i) {
    EXPECT_FLOAT_EQ(a2[i].adj(), std_prob_deriv[i]);
    EXPECT_FLOAT_EQ(c[0][i].adj(), std_dens1_deriv[i]);
    EXPECT_FLOAT_EQ(c[1][i].adj(), std_dens2_deriv[i]);
    EXPECT_FLOAT_EQ(c[2][i].adj(), std_dens3_deriv[i]);
  }
}

TEST(AgradRevMatrix_mat, log_mix_vals) {
  vector_v vecv_prob(4), vecv_dens(4);
  row_vector_v row_vecv_prob(4), row_vecv_dens(4);
  std::vector<var> stvec_prob(4), stvec_dens(4);

  val_rev_test(vecv_prob, vecv_dens);
  val_rev_test(vecv_prob, row_vecv_dens);
  val_rev_test(vecv_prob, stvec_dens);

  val_rev_test(row_vecv_prob, vecv_dens);
  val_rev_test(row_vecv_prob, row_vecv_dens);
  val_rev_test(row_vecv_prob, stvec_dens);

  val_rev_test(stvec_prob, vecv_dens);
  val_rev_test(stvec_prob, row_vecv_dens);
  val_rev_test(stvec_prob, stvec_dens);
}

TEST(AgradRevMatrix_mat, log_mix_avec) {
  AVEC prob{0.15, 0.20, 0.40, 0.25};
  AVEC dens{-2.15, -3.89, -2.18, -8.82};

  AVAR out = stan::math::log_mix(prob, dens);

  out.grad();

  EXPECT_FLOAT_EQ(out.val(), -2.70582405);

  EXPECT_FLOAT_EQ(prob[0].adj(), 1.7433770185);
  EXPECT_FLOAT_EQ(prob[1].adj(), 0.3059982327);
  EXPECT_FLOAT_EQ(prob[2].adj(), 1.6918524409);
  EXPECT_FLOAT_EQ(prob[3].adj(), 0.0022112972);

  EXPECT_FLOAT_EQ(dens[0].adj(), 0.2615065527);
  EXPECT_FLOAT_EQ(dens[1].adj(), 0.0611996465);
  EXPECT_FLOAT_EQ(dens[2].adj(), 0.6767409763);
  EXPECT_FLOAT_EQ(dens[3].adj(), 0.0005528243);
}

TEST(AgradRevMatrix_mat, log_mix_vector_v) {
  using stan::math::vector_v;

  vector_v prob(4), dens(4);
  prob << 0.13, 0.22, 0.38, 0.27;
  dens << -3.15, -0.21, -10.55, -7.24;

  AVAR out = stan::math::log_mix(prob, dens);

  out.grad();

  EXPECT_FLOAT_EQ(out.val(), -1.69226023);

  EXPECT_FLOAT_EQ(prob[0].adj(), 0.2327617758);
  EXPECT_FLOAT_EQ(prob[1].adj(), 4.4028859801);
  EXPECT_FLOAT_EQ(prob[2].adj(), 0.0001422763);
  EXPECT_FLOAT_EQ(prob[3].adj(), 0.0038962537);

  EXPECT_FLOAT_EQ(dens[0].adj(), 0.0302590308);
  EXPECT_FLOAT_EQ(dens[1].adj(), 0.9686349156);
  EXPECT_FLOAT_EQ(dens[2].adj(), 5.406498E-05);
  EXPECT_FLOAT_EQ(dens[3].adj(), 0.0010519885);
}

TEST(AgradRevMatrix_mat, log_mix_row_vector_v) {
  using stan::math::row_vector_v;

  row_vector_v prob(4), dens(4);
  prob << 0.03, 0.21, 0.63, 0.13;
  dens << -19.41, -8.14, -2.18, -9.13;

  AVAR out = stan::math::log_mix(prob, dens);

  out.grad();

  EXPECT_FLOAT_EQ(out.val(), -2.64097823);

  EXPECT_FLOAT_EQ(prob[0].adj(), 5.215625E-08);
  EXPECT_FLOAT_EQ(prob[1].adj(), 0.0040907712);
  EXPECT_FLOAT_EQ(prob[2].adj(), 1.5856243363);
  EXPECT_FLOAT_EQ(prob[3].adj(), 0.0015200352);

  EXPECT_FLOAT_EQ(dens[0].adj(), 1.564688E-09);
  EXPECT_FLOAT_EQ(dens[1].adj(), 0.0008590619);
  EXPECT_FLOAT_EQ(dens[2].adj(), 0.9989433319);
  EXPECT_FLOAT_EQ(dens[3].adj(), 0.0001976046);
}

TEST(AgradRevMatrix_mat, log_mix_std_vector_v) {
  using stan::math::var;

  std::vector<var> prob(4);
  prob[0] = 0.03;
  prob[1] = 0.21;
  prob[2] = 0.63;
  prob[3] = 0.13;
  std::vector<var> dens(4);
  dens[0] = -19.41;
  dens[1] = -8.14;
  dens[2] = -2.18;
  dens[3] = -9.13;

  AVAR out = stan::math::log_mix(prob, dens);

  out.grad();

  EXPECT_FLOAT_EQ(out.val(), -2.64097823);

  EXPECT_FLOAT_EQ(prob[0].adj(), 5.215625E-08);
  EXPECT_FLOAT_EQ(prob[1].adj(), 0.0040907712);
  EXPECT_FLOAT_EQ(prob[2].adj(), 1.5856243363);
  EXPECT_FLOAT_EQ(prob[3].adj(), 0.0015200352);

  EXPECT_FLOAT_EQ(dens[0].adj(), 1.564688E-09);
  EXPECT_FLOAT_EQ(dens[1].adj(), 0.0008590619);
  EXPECT_FLOAT_EQ(dens[2].adj(), 0.9989433319);
  EXPECT_FLOAT_EQ(dens[3].adj(), 0.0001976046);
}
