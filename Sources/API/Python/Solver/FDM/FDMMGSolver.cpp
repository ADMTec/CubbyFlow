/*************************************************************************
> File Name: FDMMGSolver.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: FDMMGSolver functions for CubbyFlow Python API.
> Created Time: 2018/02/14
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Solver/FDM/FDMMGSolver.h>
#include <Core/Solver/FDM/FDMMGSolver2.h>
#include <Core/Solver/FDM/FDMMGSolver3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddFDMMGSolver2(pybind11::module& m)
{
    pybind11::class_<FDMMGSolver2, FDMMGSolver2Ptr, FDMLinearSystemSolver2>(
        m, "FDMMGSolver2",
        R"pbdoc(
			2-D finite difference-type linear system solver using multigrid.
		)pbdoc")
        .def(pybind11::init<size_t, uint32_t, uint32_t, uint32_t, uint32_t,
                            double, double, bool>(),
             pybind11::arg("max_number_of_levels"),
             pybind11::arg("number_of_restriction_iter") = 5,
             pybind11::arg("number_of_correction_iter") = 5,
             pybind11::arg("number_of_coarsest_iter") = 20,
             pybind11::arg("number_of_final_iter") = 20,
             pybind11::arg("max_tolerance") = 1e-9,
             pybind11::arg("sor_factor") = 1.5,
             pybind11::arg("use_red_black_ordering") = false)
        .def_property_readonly(
            "max_number_of_levels",
            [](const FDMMGSolver2& instance) {
                return instance.GetParams().maxNumberOfLevels;
            },
            R"pbdoc(
			Max number of multigrid levels.
		)pbdoc")
        .def_property_readonly(
            "number_of_restriction_iter",
            [](const FDMMGSolver2& instance) {
                return instance.GetParams().numberOfRestrictionIter;
            },
            R"pbdoc(
			Number of iteration at restriction step.
		)pbdoc")
        .def_property_readonly(
            "number_of_correction_iter",
            [](const FDMMGSolver2& instance) {
                return instance.GetParams().numberOfCorrectionIter;
            },
            R"pbdoc(
			Number of iteration at correction step.
		)pbdoc")
        .def_property_readonly(
            "number_of_coarsest_iter",
            [](const FDMMGSolver2& instance) {
                return instance.GetParams().numberOfCoarsestIter;
            },
            R"pbdoc(
			Number of iteration at coarsest step.
		)pbdoc")
        .def_property_readonly(
            "number_of_final_iter",
            [](const FDMMGSolver2& instance) {
                return instance.GetParams().numberOfFinalIter;
            },
            R"pbdoc(
			Number of iteration at final step.
		)pbdoc")
        .def_property_readonly("sor_factor", &FDMMGSolver2::GetSORFactor,
                               R"pbdoc(
			Returns the SOR (Successive Over Relaxation) factor.
		)pbdoc")
        .def_property_readonly("use_red_black_ordering",
                               &FDMMGSolver2::GetUseRedBlackOrdering,
                               R"pbdoc(
			Returns true if red-black ordering is enabled.
		)pbdoc");
}

void AddFDMMGSolver3(pybind11::module& m)
{
    pybind11::class_<FDMMGSolver3, FDMMGSolver3Ptr, FDMLinearSystemSolver3>(
        m, "FDMMGSolver3",
        R"pbdoc(
			3-D finite difference-type linear system solver using multigrid.
		)pbdoc")
        .def(pybind11::init<size_t, uint32_t, uint32_t, uint32_t, uint32_t,
                            double, double, bool>(),
             pybind11::arg("max_number_of_levels"),
             pybind11::arg("number_of_restriction_iter") = 5,
             pybind11::arg("number_of_correction_iter") = 5,
             pybind11::arg("number_of_coarsest_iter") = 20,
             pybind11::arg("number_of_final_iter") = 20,
             pybind11::arg("max_tolerance") = 1e-9,
             pybind11::arg("sor_factor") = 1.5,
             pybind11::arg("use_red_black_ordering") = false)
        .def_property_readonly(
            "max_number_of_levels",
            [](const FDMMGSolver3& instance) {
                return instance.GetParams().maxNumberOfLevels;
            },
            R"pbdoc(
			Max number of multigrid levels.
		)pbdoc")
        .def_property_readonly(
            "number_of_restriction_iter",
            [](const FDMMGSolver3& instance) {
                return instance.GetParams().numberOfRestrictionIter;
            },
            R"pbdoc(
			Number of iteration at restriction step.
		)pbdoc")
        .def_property_readonly(
            "number_of_correction_iter",
            [](const FDMMGSolver3& instance) {
                return instance.GetParams().numberOfCorrectionIter;
            },
            R"pbdoc(
			Number of iteration at correction step.
		)pbdoc")
        .def_property_readonly(
            "number_of_coarsest_iter",
            [](const FDMMGSolver3& instance) {
                return instance.GetParams().numberOfCoarsestIter;
            },
            R"pbdoc(
			Number of iteration at coarsest step.
		)pbdoc")
        .def_property_readonly(
            "number_of_final_iter",
            [](const FDMMGSolver3& instance) {
                return instance.GetParams().numberOfFinalIter;
            },
            R"pbdoc(
			Number of iteration at final step.
		)pbdoc")
        .def_property_readonly("sor_factor", &FDMMGSolver3::GetSORFactor,
                               R"pbdoc(
			Returns the SOR (Successive Over Relaxation) factor.
		)pbdoc")
        .def_property_readonly("use_red_black_ordering",
                               &FDMMGSolver3::GetUseRedBlackOrdering,
                               R"pbdoc(
			Returns true if red-black ordering is enabled.
		)pbdoc");
}