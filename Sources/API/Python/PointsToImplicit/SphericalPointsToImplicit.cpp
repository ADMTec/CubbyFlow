/*************************************************************************
> File Name: SphericalPointsToImplicit.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: SphericalPointsToImplicit functions for CubbyFlow Python API.
> Created Time: 2018/02/10
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/PointsToImplicit/SphericalPointsToImplicit.h>
#include <Core/PointsToImplicit/SphericalPointsToImplicit2.h>
#include <Core/PointsToImplicit/SphericalPointsToImplicit3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddSphericalPointsToImplicit2(pybind11::module& m)
{
    pybind11::class_<SphericalPointsToImplicit2, PointsToImplicit2,
                     SphericalPointsToImplicit2Ptr>(
        m, "SphericalPointsToImplicit2",
        R"pbdoc(
			2-D points-to-implicit converter based on simple sphere model.
		)pbdoc")
        .def(pybind11::init<double, bool>(),
             R"pbdoc(
			Constructs the converter with given sphere radius.

			Parameters
			----------
			- radius : Sphere radius.
			- is_output_sdf : True if the output should be signed-distance field.
		)pbdoc",
             pybind11::arg("radius") = 1.0,
             pybind11::arg("is_output_sdf") = true);
}

void AddSphericalPointsToImplicit3(pybind11::module& m)
{
    pybind11::class_<SphericalPointsToImplicit3, PointsToImplicit3,
                     SphericalPointsToImplicit3Ptr>(
        m, "SphericalPointsToImplicit3",
        R"pbdoc(
			3-D points-to-implicit converter based on simple sphere model.
		)pbdoc")
        .def(pybind11::init<double, bool>(),
             R"pbdoc(
			Constructs the converter with given sphere radius.

			Parameters
			----------
			- radius : Sphere radius.
			- is_output_sdf : True if the output should be signed-distance field.
		)pbdoc",
             pybind11::arg("radius") = 1.0,
             pybind11::arg("is_output_sdf") = true);
}