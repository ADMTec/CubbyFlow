#include "gtest/gtest.h"

#include <Core/Geometry/Ray.hpp>

using namespace CubbyFlow;

TEST(Ray3, Constructors)
{
    Ray3D ray;
    EXPECT_EQ(Vector3D(), ray.origin);
    EXPECT_EQ(Vector3D(1, 0, 0), ray.direction);

    Ray3D ray2({ 1, 2, 3 }, { 4, 5, 6 });
    EXPECT_EQ(Vector3D(1, 2, 3), ray2.origin);
    EXPECT_EQ(Vector3D(4, 5, 6).Normalized(), ray2.direction);

    Ray3D ray3(ray2);
    EXPECT_EQ(Vector3D(1, 2, 3), ray3.origin);
    EXPECT_EQ(Vector3D(4, 5, 6).Normalized(), ray3.direction);
}

TEST(Ray3, PointAt)
{
    Ray3D ray;
    EXPECT_EQ(Vector3D(4.5, 0.0, 0.0), ray.PointAt(4.5));
}