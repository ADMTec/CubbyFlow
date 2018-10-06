/*************************************************************************
> File Name: CubicSemiLagrangian3.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Implementation of 3-D cubic semi-Lagrangian advection solver.
> Created Time: 2017/08/08
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Core/SemiLagrangian/CubicSemiLagrangian3.h>

namespace CubbyFlow
{
	CubicSemiLagrangian3::CubicSemiLagrangian3()
	{
		// Do nothing
	}

	std::function<double(const Vector3D&)> CubicSemiLagrangian3::GetScalarSamplerFunc(const ScalarGrid3& source) const
	{
		auto sourceSampler = CubicArraySampler3<double, double>(
			source.GetConstDataAccessor(),
			source.GetGridSpacing(),
			source.GetDataOrigin());
		return sourceSampler.Functor();
	}

	std::function<Vector3D(const Vector3D&)> CubicSemiLagrangian3::GetVectorSamplerFunc(const CollocatedVectorGrid3& source) const
	{
		auto sourceSampler = CubicArraySampler3<Vector3D, double>(
			source.GetConstDataAccessor(),
			source.GetGridSpacing(),
			source.GetDataOrigin());
		return sourceSampler.Functor();
	}

	std::function<Vector3D(const Vector3D&)> CubicSemiLagrangian3::GetVectorSamplerFunc(const FaceCenteredGrid3& source) const
	{
		auto uSourceSampler = CubicArraySampler3<double, double>(
			source.GetUConstAccessor(),
			source.GetGridSpacing(),
			source.GetUOrigin());
		auto vSourceSampler = CubicArraySampler3<double, double>(
			source.GetVConstAccessor(),
			source.GetGridSpacing(),
			source.GetVOrigin());
		auto wSourceSampler = CubicArraySampler3<double, double>(
			source.GetWConstAccessor(),
			source.GetGridSpacing(),
			source.GetWOrigin());
		return [uSourceSampler, vSourceSampler, wSourceSampler](const Vector3D& x)
		{
			return Vector3D(uSourceSampler(x), vSourceSampler(x), wSourceSampler(x));
		};
	}
}