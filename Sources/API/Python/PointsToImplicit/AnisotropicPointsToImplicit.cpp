/*************************************************************************
> File Name: AnisotropicPointsToImplicit.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: AnisotropicPointsToImplicit functions for CubbyFlow Python API.
> Created Time: 2018/02/11
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/PointsToImplicit/AnisotropicPointsToImplicit.h>
#include <Core/PointsToImplicit/AnisotropicPointsToImplicit2.h>
#include <Core/PointsToImplicit/AnisotropicPointsToImplicit3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddAnisotropicPointsToImplicit2(pybind11::module& m)
{
    pybind11::class_<AnisotropicPointsToImplicit2, PointsToImplicit2,
                     AnisotropicPointsToImplicit2Ptr>(
        m, "AnisotropicPointsToImplicit2",
        R"pbdoc(
			2-D points-to-implicit converter using Anisotropic kernels.

			\see Yu, Jihun, and Greg Turk. "Reconstructing surfaces of particle-based
			fluids using anisotropic kernels." ACM Transactions on Graphics (TOG)
			32.1 (2013): 5.
		)pbdoc")
        .def(pybind11::init<double, double, double, size_t, bool>(),
             R"pbdoc(
			Constructs the converter with given kernel radius and cut-off density.

			Parameters
			----------
			- kernel_radius : Smoothing kernel radius.
			- cut_off_density : Iso-contour value.
			- position_smoothing_factor : Position smoothing factor.
			- min_num_neighbors : Minimum number of neighbors to enable anisotropic kernel.
			- is_output_sdf : True if the output should be signed-distance field.
		)pbdoc",
             pybind11::arg("kernel_radius") = 1.0,
             pybind11::arg("cut_off_density") = 0.5,
             pybind11::arg("position_smoothing_factor") = 0.5,
             pybind11::arg("min_num_neighbors") = 8,
             pybind11::arg("is_output_sdf") = true);
}

void AddAnisotropicPointsToImplicit3(pybind11::module& m)
{
    pybind11::class_<AnisotropicPointsToImplicit3, PointsToImplicit3,
                     AnisotropicPointsToImplicit3Ptr>(
        m, "AnisotropicPointsToImplicit3",
        R"pbdoc(
			3-D points-to-implicit converter using Anisotropic kernels.

			\see Yu, Jihun, and Greg Turk. "Reconstructing surfaces of particle-based
			fluids using anisotropic kernels." ACM Transactions on Graphics (TOG)
			32.1 (2013): 5.
		)pbdoc")
        .def(pybind11::init<double, double, double, size_t, bool>(),
             R"pbdoc(
			Constructs the converter with given kernel radius and cut-off density.

			Parameters
			----------
			- kernel_radius : Smoothing kernel radius.
			- cut_off_density : Iso-contour value.
			- position_smoothing_factor : Position smoothing factor.
			- min_num_neighbors : Minimum number of neighbors to enable anisotropic kernel.
			- is_output_sdf : True if the output should be signed-distance field.
		)pbdoc",
             pybind11::arg("kernel_radius") = 1.0,
             pybind11::arg("cut_off_density") = 0.5,
             pybind11::arg("position_smoothing_factor") = 0.5,
             pybind11::arg("min_num_neighbors") = 25,
             pybind11::arg("is_output_sdf") = true);
}