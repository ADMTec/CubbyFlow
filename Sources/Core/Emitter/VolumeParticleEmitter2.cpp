// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Emitter/VolumeParticleEmitter2.hpp>
#include <Core/Geometry/SurfaceToImplicit2.hpp>
#include <Core/Matrix/Matrix.hpp>
#include <Core/PointGenerator/TrianglePointGenerator.hpp>
#include <Core/Searcher/PointHashGridSearcher2.hpp>
#include <Core/Utils/Logging.hpp>

namespace CubbyFlow
{
static const size_t DEFAULT_HASH_GRID_RESOLUTION = 64;

VolumeParticleEmitter2::VolumeParticleEmitter2(
    ImplicitSurface2Ptr implicitSurface, const BoundingBox2D& bounds,
    double spacing, const Vector2D& initialVel, size_t maxNumberOfParticles,
    double jitter, bool isOneShot, bool allowOverlapping, uint32_t seed)
    : m_rng(seed),
      m_implicitSurface(std::move(implicitSurface)),
      m_bounds(bounds),
      m_spacing(spacing),
      m_initialVel(initialVel),
      m_maxNumberOfParticles(maxNumberOfParticles),
      m_jitter(jitter),
      m_isOneShot(isOneShot),
      m_allowOverlapping(allowOverlapping)
{
    m_pointsGen = std::make_shared<TrianglePointGenerator>();
}

void VolumeParticleEmitter2::OnUpdate(double currentTimeInSeconds,
                                      double timeIntervalInSeconds)
{
    UNUSED_VARIABLE(currentTimeInSeconds);
    UNUSED_VARIABLE(timeIntervalInSeconds);

    auto particles = GetTarget();

    if (particles == nullptr)
    {
        return;
    }

    if (m_numberOfEmittedParticles > 0 && m_isOneShot)
    {
        return;
    }

    Array1<Vector2D> newPositions;
    Array1<Vector2D> newVelocities;

    Emit(particles, &newPositions, &newVelocities);

    particles->AddParticles(newPositions, newVelocities);
}

void VolumeParticleEmitter2::Emit(const ParticleSystemData2Ptr& particles,
                                  Array1<Vector2D>* newPositions,
                                  Array1<Vector2D>* newVelocities)
{
    if (!m_implicitSurface)
    {
        return;
    }

    m_implicitSurface->UpdateQueryEngine();

    // Reserving more space for jittering
    const double j = GetJitter();
    const double maxJitterDist = 0.5 * j * m_spacing;

    if (m_allowOverlapping || m_isOneShot)
    {
        m_pointsGen->ForEachPoint(
            m_bounds, m_spacing, [&](const Vector2D& point) {
                const double newAngleInRadian =
                    (Random() - 0.5) * (2 * PI_DOUBLE);
                const Matrix2x2D rotationMatrix =
                    Matrix2x2D::MakeRotationMatrix(newAngleInRadian);
                const Vector2D randomDir = rotationMatrix * Vector2D();
                const Vector2D offset = maxJitterDist * randomDir;
                const Vector2D candidate = point + offset;

                if (m_implicitSurface->SignedDistance(candidate) <= 0.0)
                {
                    if (m_numberOfEmittedParticles < m_maxNumberOfParticles)
                    {
                        newPositions->Append(candidate);
                        ++m_numberOfEmittedParticles;
                    }
                    else
                    {
                        return false;
                    }
                }

                return true;
            });
    }
    else
    {
        // Use serial hash grid searcher for continuous update.
        PointHashGridSearcher2 neighborSearcher(
            Vector2UZ(DEFAULT_HASH_GRID_RESOLUTION,
                      DEFAULT_HASH_GRID_RESOLUTION),
            2.0 * m_spacing);

        if (!m_allowOverlapping)
        {
            neighborSearcher.Build(particles->Positions());
        }

        m_pointsGen->ForEachPoint(
            m_bounds, m_spacing, [&](const Vector2D& point) {
                const double newAngleInRadian =
                    (Random() - 0.5) * (2 * PI_DOUBLE);
                const Matrix2x2D rotationMatrix =
                    Matrix2x2D::MakeRotationMatrix(newAngleInRadian);
                const Vector2D randomDir = rotationMatrix * Vector2D();
                const Vector2D offset = maxJitterDist * randomDir;
                const Vector2D candidate = point + offset;

                if (m_implicitSurface->IsInside(candidate) &&
                    (!m_allowOverlapping &&
                     !neighborSearcher.HasNearbyPoint(candidate, m_spacing)))
                {
                    if (m_numberOfEmittedParticles < m_maxNumberOfParticles)
                    {
                        newPositions->Append(candidate);
                        neighborSearcher.Add(candidate);
                        ++m_numberOfEmittedParticles;
                    }
                    else
                    {
                        return false;
                    }
                }

                return true;
            });
    }

    newVelocities->Resize(newPositions->Size());
    newVelocities->Fill(m_initialVel);
}

void VolumeParticleEmitter2::SetPointGenerator(
    const PointGenerator2Ptr& newPointsGen)
{
    m_pointsGen = newPointsGen;
}

const ImplicitSurface2Ptr& VolumeParticleEmitter2::GetSurface() const
{
    return m_implicitSurface;
}

void VolumeParticleEmitter2::SetSurface(const ImplicitSurface2Ptr& newSurface)
{
    m_implicitSurface = newSurface;
}

const BoundingBox2D& VolumeParticleEmitter2::GetMaxRegion() const
{
    return m_bounds;
}

void VolumeParticleEmitter2::SetMaxRegion(const BoundingBox2D& bounds)
{
    m_bounds = bounds;
}

double VolumeParticleEmitter2::GetJitter() const
{
    return m_jitter;
}

void VolumeParticleEmitter2::SetJitter(double newJitter)
{
    m_jitter = std::clamp(newJitter, 0.0, 1.0);
}

bool VolumeParticleEmitter2::GetIsOneShot() const
{
    return m_isOneShot;
}

void VolumeParticleEmitter2::SetIsOneShot(bool newValue)
{
    m_isOneShot = newValue;
}

bool VolumeParticleEmitter2::GetAllowOverlapping() const
{
    return m_allowOverlapping;
}

void VolumeParticleEmitter2::SetAllowOverlapping(bool newValue)
{
    m_allowOverlapping = newValue;
}

size_t VolumeParticleEmitter2::GetMaxNumberOfParticles() const
{
    return m_maxNumberOfParticles;
}

void VolumeParticleEmitter2::SetMaxNumberOfParticles(
    size_t newMaxNumberOfParticles)
{
    m_maxNumberOfParticles = newMaxNumberOfParticles;
}

double VolumeParticleEmitter2::GetSpacing() const
{
    return m_spacing;
}

void VolumeParticleEmitter2::SetSpacing(double newSpacing)
{
    m_spacing = newSpacing;
}

Vector2D VolumeParticleEmitter2::GetInitialVelocity() const
{
    return m_initialVel;
}

void VolumeParticleEmitter2::SetInitialVelocity(const Vector2D& newInitialVel)
{
    m_initialVel = newInitialVel;
}

double VolumeParticleEmitter2::Random()
{
    std::uniform_real_distribution<> d{ 0.0, 1.0 };
    return d(m_rng);
}

VolumeParticleEmitter2::Builder VolumeParticleEmitter2::GetBuilder()
{
    return Builder();
}

VolumeParticleEmitter2::Builder&
VolumeParticleEmitter2::Builder::WithImplicitSurface(
    const ImplicitSurface2Ptr& implicitSurface)
{
    m_implicitSurface = implicitSurface;

    if (!m_isBoundSet)
    {
        m_maxRegion = m_implicitSurface->BoundingBox();
    }

    return *this;
}

VolumeParticleEmitter2::Builder& VolumeParticleEmitter2::Builder::WithSurface(
    const Surface2Ptr& surface)
{
    m_implicitSurface = std::make_shared<SurfaceToImplicit2>(surface);

    if (!m_isBoundSet)
    {
        m_maxRegion = surface->BoundingBox();
    }

    return *this;
}

VolumeParticleEmitter2::Builder& VolumeParticleEmitter2::Builder::WithMaxRegion(
    const BoundingBox2D& maxRegion)
{
    m_maxRegion = maxRegion;
    m_isBoundSet = true;
    return *this;
}

VolumeParticleEmitter2::Builder& VolumeParticleEmitter2::Builder::WithSpacing(
    double spacing)
{
    m_spacing = spacing;
    return *this;
}

VolumeParticleEmitter2::Builder&
VolumeParticleEmitter2::Builder::WithInitialVelocity(const Vector2D& initialVel)
{
    m_initialVel = initialVel;
    return *this;
}

VolumeParticleEmitter2::Builder&
VolumeParticleEmitter2::Builder::WithMaxNumberOfParticles(
    size_t maxNumberOfParticles)
{
    m_maxNumberOfParticles = maxNumberOfParticles;
    return *this;
}

VolumeParticleEmitter2::Builder& VolumeParticleEmitter2::Builder::WithJitter(
    double jitter)
{
    m_jitter = jitter;
    return *this;
}

VolumeParticleEmitter2::Builder& VolumeParticleEmitter2::Builder::WithIsOneShot(
    bool isOneShot)
{
    m_isOneShot = isOneShot;
    return *this;
}

VolumeParticleEmitter2::Builder&
VolumeParticleEmitter2::Builder::WithAllowOverlapping(bool allowOverlapping)
{
    m_allowOverlapping = allowOverlapping;
    return *this;
}

VolumeParticleEmitter2::Builder&
VolumeParticleEmitter2::Builder::WithRandomSeed(uint32_t seed)
{
    m_seed = seed;
    return *this;
}

VolumeParticleEmitter2 VolumeParticleEmitter2::Builder::Build() const
{
    return VolumeParticleEmitter2(m_implicitSurface, m_maxRegion, m_spacing,
                                  m_initialVel, m_maxNumberOfParticles,
                                  m_jitter, m_isOneShot, m_allowOverlapping,
                                  m_seed);
}

VolumeParticleEmitter2Ptr VolumeParticleEmitter2::Builder::MakeShared() const
{
    return std::shared_ptr<VolumeParticleEmitter2>(
        new VolumeParticleEmitter2(m_implicitSurface, m_maxRegion, m_spacing,
                                   m_initialVel, m_maxNumberOfParticles,
                                   m_jitter, m_isOneShot, m_allowOverlapping),
        [](VolumeParticleEmitter2* obj) { delete obj; });
}
}  // namespace CubbyFlow