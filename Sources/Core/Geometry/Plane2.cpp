// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Geometry/Plane2.hpp>

namespace CubbyFlow
{
Plane2::Plane2(const Transform2& _transform, bool _isNormalFlipped)
    : Surface2{ _transform, _isNormalFlipped }
{
    // Do nothing
}

Plane2::Plane2(const Vector2D& _normal, const Vector2D& _point,
               const Transform2& _transform, bool _isNormalFlipped)
    : Surface2{ _transform, _isNormalFlipped }, normal(_normal), point(_point)
{
    // Do nothing
}

bool Plane2::IsBounded() const
{
    return false;
}

Vector2D Plane2::ClosestPointLocal(const Vector2D& otherPoint) const
{
    const Vector2D r = otherPoint - point;
    return r - normal.Dot(r) * normal + point;
}

Vector2D Plane2::ClosestNormalLocal(const Vector2D& otherPoint) const
{
    UNUSED_VARIABLE(otherPoint);

    return normal;
}

bool Plane2::IntersectsLocal(const Ray2D& ray) const
{
    return std::fabs(ray.direction.Dot(normal)) > 0;
}

SurfaceRayIntersection2 Plane2::ClosestIntersectionLocal(const Ray2D& ray) const
{
    SurfaceRayIntersection2 intersection;
    const double dDotN = ray.direction.Dot(normal);

    // Check if not parallel
    if (std::fabs(dDotN) > 0)
    {
        const double t = normal.Dot(point - ray.origin) / dDotN;
        if (t >= 0.0)
        {
            intersection.isIntersecting = true;
            intersection.distance = t;
            intersection.point = ray.PointAt(t);
            intersection.normal = normal;
        }
    }

    return intersection;
}

BoundingBox2D Plane2::BoundingBoxLocal() const
{
    static const double eps = std::numeric_limits<double>::epsilon();
    static const double dMax = std::numeric_limits<double>::max();

    if (std::fabs(normal.Dot(Vector2D{ 1, 0 }) - 1.0) < eps)
    {
        return BoundingBox2D{ point - Vector2D{ 0, dMax },
                              point + Vector2D{ 0, dMax } };
    }

    if (std::fabs(normal.Dot(Vector2D{ 0, 1 }) - 1.0) < eps)
    {
        return BoundingBox2D{ point - Vector2D{ dMax, 0 },
                              point + Vector2D{ dMax, 0 } };
    }

    return BoundingBox2D{ Vector2D{ dMax, dMax }, Vector2D{ dMax, dMax } };
}

Plane2::Builder Plane2::GetBuilder()
{
    return Builder{};
}

Plane2::Builder& Plane2::Builder::WithNormal(const Vector2D& _normal)
{
    m_normal = _normal;
    return *this;
}

Plane2::Builder& Plane2::Builder::WithPoint(const Vector2D& _point)
{
    m_point = _point;
    return *this;
}

Plane2 Plane2::Builder::Build() const
{
    return Plane2{ m_normal, m_point, m_transform, m_isNormalFlipped };
}

Plane2Ptr Plane2::Builder::MakeShared() const
{
    return std::shared_ptr<Plane2>(
        new Plane2{ m_normal, m_point, m_transform, m_isNormalFlipped },
        [](Plane2* obj) { delete obj; });
}
}  // namespace CubbyFlow