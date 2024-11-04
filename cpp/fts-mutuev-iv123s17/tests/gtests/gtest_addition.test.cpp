#include <gtest/gtest.h>
#include <libmath/addition.hxx>

TEST(math, add) {
  const double first = 5.6;
  const double second = 23.4;
  const double exp_res = 29.0;
  const double real_res = mathfunctions::add(first, second);

  ASSERT_EQ(real_res, exp_res);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}