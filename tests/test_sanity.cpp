#include "gtest/gtest.h"

TEST(SanityTest, BasicAssertions) {
  // Expect two values to be equal.
  EXPECT_EQ(1 + 1, 2);

  // Expect a condition to be true.
  EXPECT_TRUE(true);

  // Expect a condition to be false.
  EXPECT_FALSE(false);
}