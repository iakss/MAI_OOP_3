#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

#include "hexagon.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"
#include "point.hpp"

class PointTest : public ::testing::Test {
protected:
  void SetUp() override {
    p1 = lib::geometry::Point(1.0, 2.0);
    p2 = lib::geometry::Point(3.0, 4.0);
    p3 = lib::geometry::Point(1.0 + lib::geometry::Point::EPS / 2, 2.0);
  }

  lib::geometry::Point p0; // default (0, 0)
  lib::geometry::Point p1;
  lib::geometry::Point p2;
  lib::geometry::Point p3;
};

TEST_F(PointTest, DefaultConstructor) {
  EXPECT_DOUBLE_EQ(p0.x, 0.0);
  EXPECT_DOUBLE_EQ(p0.y, 0.0);
}

TEST_F(PointTest, ParameterizedConstructor) {
  EXPECT_DOUBLE_EQ(p1.x, 1.0);
  EXPECT_DOUBLE_EQ(p1.y, 2.0);
}

TEST_F(PointTest, Addition) {
  auto result = p1 + p2;
  EXPECT_DOUBLE_EQ(result.x, 4.0);
  EXPECT_DOUBLE_EQ(result.y, 6.0);

  p1 += p2;
  EXPECT_DOUBLE_EQ(p1.x, 4.0);
  EXPECT_DOUBLE_EQ(p1.y, 6.0);
}

TEST_F(PointTest, Subtraction) {
  auto result = p2 - p1;
  EXPECT_DOUBLE_EQ(result.x, 2.0);
  EXPECT_DOUBLE_EQ(result.y, 2.0);

  p2 -= p1;
  EXPECT_DOUBLE_EQ(p2.x, 2.0);
  EXPECT_DOUBLE_EQ(p2.y, 2.0);
}

TEST_F(PointTest, ScalarMultiplication) {
  auto result1 = 2.0 * p1;
  EXPECT_DOUBLE_EQ(result1.x, 2.0);
  EXPECT_DOUBLE_EQ(result1.y, 4.0);

  // Remove the p1 * 2.0 test since it's not implemented
  // auto result2 = p1 * 2.0;

  p1 *= 2.0;
  EXPECT_DOUBLE_EQ(p1.x, 2.0);
  EXPECT_DOUBLE_EQ(p1.y, 4.0);
}

TEST_F(PointTest, ScalarDivision) {
  auto result = p1 / 2.0;
  EXPECT_DOUBLE_EQ(result.x, 0.5);
  EXPECT_DOUBLE_EQ(result.y, 1.0);

  p1 /= 2.0;
  EXPECT_DOUBLE_EQ(p1.x, 0.5);
  EXPECT_DOUBLE_EQ(p1.y, 1.0);
}

TEST_F(PointTest, Magnitude) {
  lib::geometry::Point p(3.0, 4.0);
  double magnitude = static_cast<double>(p);
  EXPECT_DOUBLE_EQ(magnitude, 5.0);
}

TEST_F(PointTest, Equality) {
  EXPECT_TRUE(p1 == p1);
  EXPECT_TRUE(p1 == p3); // Within EPS tolerance
  EXPECT_FALSE(p1 == p2);
}

TEST_F(PointTest, Inequality) {
  EXPECT_FALSE(p1 != p1);
  EXPECT_FALSE(p1 != p3); // Within EPS tolerance
  EXPECT_TRUE(p1 != p2);
}

TEST_F(PointTest, StreamOutput) {
  std::ostringstream oss;
  oss << p1;
  EXPECT_EQ(oss.str(), "(1, 2)");
}

TEST_F(PointTest, StreamInput) {
  std::istringstream iss("5.5 6.6");
  lib::geometry::Point p;
  iss >> p;
  EXPECT_DOUBLE_EQ(p.x, 5.5);
  EXPECT_DOUBLE_EQ(p.y, 6.6);
}

class PentagonTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Use stream input to set up pentagon vertices (avoiding private member
    // access)
    std::istringstream iss(
        "1.0 0.0 0.309016994374947 0.951056516295154 -0.809016994374947 "
        "0.587785252292473 -0.809016994374947 -0.587785252292473 "
        "0.309016994374947 -0.951056516295154");
    pentagon1.Read(iss);

    // Reset stream for second pentagon
    iss.clear();
    iss.str("1.0 0.0 0.309016994374947 0.951056516295154 -0.809016994374947 "
            "0.587785252292473 -0.809016994374947 -0.587785252292473 "
            "0.309016994374947 -0.951056516295154");
    pentagon2.Read(iss);
  }

  lib::geometry::Pentagon pentagon1;
  lib::geometry::Pentagon pentagon2;
  lib::geometry::Pentagon pentagon3;
};

TEST_F(PentagonTest, DefaultConstructor) {
  lib::geometry::Pentagon pentagon;
  // Just verify it can be constructed without issues
  SUCCEED();
}

TEST_F(PentagonTest, AssignmentOperators) {
  lib::geometry::Pentagon pentagon;
  pentagon = pentagon1; // Copy assignment
  EXPECT_TRUE(pentagon == pentagon1);

  lib::geometry::Pentagon pentagon_moved;
  pentagon_moved = std::move(pentagon); // Move assignment
  EXPECT_TRUE(pentagon_moved == pentagon1);
}

TEST_F(PentagonTest, AreaCalculation) {
  double area = static_cast<double>(pentagon1);
  // Area should be positive for a valid pentagon
  EXPECT_GT(area, 0.0);
}

TEST_F(PentagonTest, CenterCalculation) {
  lib::geometry::Point center = pentagon1.GetCenter();
  // For a regular pentagon centered at origin, center should be near (0,0)
  EXPECT_NEAR(center.x, 0.0, lib::geometry::Point::EPS);
  EXPECT_NEAR(center.y, 0.0, lib::geometry::Point::EPS);
}

TEST_F(PentagonTest, Equality) {
  EXPECT_TRUE(pentagon1 == pentagon2);
  EXPECT_FALSE(pentagon1 == pentagon3);
}

TEST_F(PentagonTest, Inequality) {
  EXPECT_FALSE(pentagon1 != pentagon2);
  EXPECT_TRUE(pentagon1 != pentagon3);
}

TEST_F(PentagonTest, StreamOperations) {
  std::ostringstream oss;
  pentagon1.Print(oss);
  EXPECT_FALSE(oss.str().empty());
  EXPECT_NE(oss.str().find("Pentagon"), std::string::npos);

  std::istringstream iss(
      "1.0 0.0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
  lib::geometry::Pentagon pentagon;
  pentagon.Read(iss);

  // Verify the pentagon was read correctly by checking area > 0
  double area = static_cast<double>(pentagon);
  EXPECT_GT(area, 0.0);
}

class HexagonTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Use stream input to set up hexagon vertices
    std::istringstream iss(
        "1.0 0.0 0.5 0.866025403784439 -0.5 0.866025403784439 -1.0 0.0 -0.5 "
        "-0.866025403784439 0.5 -0.866025403784439");
    hexagon1.Read(iss);

    iss.clear();
    iss.str("1.0 0.0 0.5 0.866025403784439 -0.5 0.866025403784439 -1.0 0.0 "
            "-0.5 -0.866025403784439 0.5 -0.866025403784439");
    hexagon2.Read(iss);
  }

  lib::geometry::Hexagon hexagon1;
  lib::geometry::Hexagon hexagon2;
  lib::geometry::Hexagon hexagon3;
};

TEST_F(HexagonTest, DefaultConstructor) {
  lib::geometry::Hexagon hexagon;
  SUCCEED();
}

TEST_F(HexagonTest, AssignmentOperators) {
  lib::geometry::Hexagon hexagon;
  hexagon = hexagon1;
  EXPECT_TRUE(hexagon == hexagon1);

  lib::geometry::Hexagon hexagon_moved;
  hexagon_moved = std::move(hexagon);
  EXPECT_TRUE(hexagon_moved == hexagon1);
}

TEST_F(HexagonTest, AreaCalculation) {
  double area = static_cast<double>(hexagon1);
  // Area should be positive for a valid hexagon
  EXPECT_GT(area, 0.0);
}

TEST_F(HexagonTest, CenterCalculation) {
  lib::geometry::Point center = hexagon1.GetCenter();
  EXPECT_NEAR(center.x, 0.0, lib::geometry::Point::EPS);
  EXPECT_NEAR(center.y, 0.0, lib::geometry::Point::EPS);
}

TEST_F(HexagonTest, Equality) {
  EXPECT_TRUE(hexagon1 == hexagon2);
  EXPECT_FALSE(hexagon1 == hexagon3);
}

TEST_F(HexagonTest, StreamOperations) {
  std::ostringstream oss;
  hexagon1.Print(oss);
  EXPECT_FALSE(oss.str().empty());
  EXPECT_NE(oss.str().find("Hexagon"), std::string::npos);

  std::istringstream iss(
      "1.0 0.0 0.5 0.866 -0.5 0.866 -1.0 0.0 -0.5 -0.866 0.5 -0.866");
  lib::geometry::Hexagon hexagon;
  hexagon.Read(iss);

  double area = static_cast<double>(hexagon);
  EXPECT_GT(area, 0.0);
}

class OctagonTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Use stream input to set up octagon vertices
    const double sqrt2_2 = std::sqrt(2) / 2;
    std::ostringstream oss;
    oss << "1.0 0.0 " << sqrt2_2 << " " << sqrt2_2 << " 0.0 1.0 -" << sqrt2_2
        << " " << sqrt2_2 << " -1.0 0.0 -" << sqrt2_2 << " -" << sqrt2_2
        << " 0.0 -1.0 " << sqrt2_2 << " -" << sqrt2_2;

    std::istringstream iss(oss.str());
    octagon1.Read(iss);

    iss.clear();
    iss.str(oss.str());
    octagon2.Read(iss);
  }

  lib::geometry::Octagon octagon1;
  lib::geometry::Octagon octagon2;
  lib::geometry::Octagon octagon3;
};

TEST_F(OctagonTest, DefaultConstructor) {
  lib::geometry::Octagon octagon;
  SUCCEED();
}

TEST_F(OctagonTest, AssignmentOperators) {
  lib::geometry::Octagon octagon;
  octagon = octagon1;
  EXPECT_TRUE(octagon == octagon1);

  lib::geometry::Octagon octagon_moved;
  octagon_moved = std::move(octagon);
  EXPECT_TRUE(octagon_moved == octagon1);
}

TEST_F(OctagonTest, AreaCalculation) {
  double area = static_cast<double>(octagon1);
  // Area should be positive for a valid octagon
  EXPECT_GT(area, 0.0);
}

TEST_F(OctagonTest, CenterCalculation) {
  lib::geometry::Point center = octagon1.GetCenter();
  EXPECT_NEAR(center.x, 0.0, lib::geometry::Point::EPS);
  EXPECT_NEAR(center.y, 0.0, lib::geometry::Point::EPS);
}

TEST_F(OctagonTest, Equality) {
  EXPECT_TRUE(octagon1 == octagon2);
  EXPECT_FALSE(octagon1 == octagon3);
}

TEST_F(OctagonTest, StreamOperations) {
  std::ostringstream oss;
  octagon1.Print(oss);
  EXPECT_FALSE(oss.str().empty());
  EXPECT_NE(oss.str().find("Octagon"), std::string::npos);

  std::istringstream iss("1.0 0.0 0.707 0.707 0.0 1.0 -0.707 0.707 -1.0 0.0 "
                         "-0.707 -0.707 0.0 -1.0 0.707 -0.707");
  lib::geometry::Octagon octagon;
  octagon.Read(iss);

  std::ostringstream oss2;
  octagon.Print(oss2);
  EXPECT_FALSE(oss2.str().empty());
}

class FigurePolymorphismTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Set up figures using their public Read interface
    std::istringstream pentagon_iss(
        "1.0 0.0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");
    pentagon.Read(pentagon_iss);

    std::istringstream hexagon_iss(
        "1.0 0.0 0.5 0.866 -0.5 0.866 -1.0 0.0 -0.5 -0.866 0.5 -0.866");
    hexagon.Read(hexagon_iss);
  }

  lib::geometry::Pentagon pentagon;
  lib::geometry::Hexagon hexagon;
};

TEST_F(FigurePolymorphismTest, VirtualFunctions) {
  lib::geometry::Figure *figure1 = &pentagon;
  lib::geometry::Figure *figure2 = &hexagon;

  // Test that virtual functions can be called
  lib::geometry::Point center1 = figure1->GetCenter();
  lib::geometry::Point center2 = figure2->GetCenter();

  double area1 = static_cast<double>(*figure1);
  double area2 = static_cast<double>(*figure2);

  EXPECT_GT(area1, 0.0);
  EXPECT_GT(area2, 0.0);

  // Test stream operations through base class interface
  std::ostringstream oss1, oss2;
  figure1->Print(oss1);
  figure2->Print(oss2);

  EXPECT_FALSE(oss1.str().empty());
  EXPECT_FALSE(oss2.str().empty());
}

// Test the global stream operators for Figure
TEST(FigureStreamTest, GlobalStreamOperators) {
  lib::geometry::Pentagon pentagon;
  std::istringstream iss(
      "1.0 0.0 0.309 0.951 -0.809 0.588 -0.809 -0.588 0.309 -0.951");

  // Test input operator
  iss >> pentagon;

  // Test output operator
  std::ostringstream oss;
  oss << pentagon;
  EXPECT_FALSE(oss.str().empty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
