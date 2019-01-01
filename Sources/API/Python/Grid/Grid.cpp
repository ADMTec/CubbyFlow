/*************************************************************************
> File Name: Grid.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Grid functions for CubbyFlow Python API.
> Created Time: 2018/02/04
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Grid/Grid.h>
#include <Core/Grid/Grid2.h>
#include <Core/Grid/Grid3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddGrid2(pybind11::module& m)
{
    pybind11::class_<Grid2, Grid2Ptr, Serializable>(m, "Grid2",
                                                    R"pbdoc(
        Abstract base class for 2-D cartesian grid structure.
        This class represents 2-D cartesian grid structure. This class is an
        abstract base class and does not store any data. The class only stores the
        shape of the grid. The grid structure is axis-aligned and can have different
        grid spacing per axis.
        )pbdoc")
        .def_property_readonly("resolution", &Grid2::GetResolution,
                               R"pbdoc(Resolution of the grid.)pbdoc")
        .def_property_readonly("origin", &Grid2::GetOrigin,
                               R"pbdoc(Origin of the grid.)pbdoc")
        .def_property_readonly("grid_spacing", &Grid2::GetGridSpacing,
                               R"pbdoc(Spacing between grid points.)pbdoc")
        .def_property_readonly("bounding_box", &Grid2::GetBoundingBox,
                               R"pbdoc(Bounding box of the entire grid.)pbdoc")
        .def_property_readonly(
            "cell_center_position", &Grid2::GetCellCenterPosition,
            R"pbdoc(Function that maps grid index to the cell-center position.)pbdoc")
        .def("for_each_cell_index",
             [](Grid2& instance, pybind11::function func) {
                 instance.ForEachCellIndex(func);
             },
             R"pbdoc(
             Invokes the given function `func` for each grid cell.
             This function invokes the given function object `func` for each grid
             cell in serial manner. The input parameters are `i` and `j` indices of a
             grid cell. The order of execution is i-first, j-last.
             )pbdoc",
             pybind11::arg("func"))
        .def("has_same_shape",
             [](const Grid2& instance, const Grid2Ptr& other) {
                 return instance.HasSameShape(*other);
             },
             R"pbdoc(
             Returns true if resolution, grid-spacing and origin are same.
             )pbdoc")
        .def("swap",
             [](Grid2& instance, Grid2Ptr& other) {
                 return instance.Swap(other.get());
             },
             R"pbdoc(
             Swaps the data with other grid.
             )pbdoc");
}

void AddGrid3(pybind11::module& m)
{
    pybind11::class_<Grid3, Grid3Ptr, Serializable>(m, "Grid3",
                                                    R"pbdoc(
        Abstract base class for 3-D cartesian grid structure.
        This class represents 3-D cartesian grid structure. This class is an
        abstract base class and does not store any data. The class only stores the
        shape of the grid. The grid structure is axis-aligned and can have different
        grid spacing per axis.
        )pbdoc")
        .def_property_readonly("resolution", &Grid3::GetResolution,
                               R"pbdoc(Resolution of the grid.)pbdoc")
        .def_property_readonly("origin", &Grid3::GetOrigin,
                               R"pbdoc(Origin of the grid.)pbdoc")
        .def_property_readonly("grid_spacing", &Grid3::GetGridSpacing,
                               R"pbdoc(Spacing between grid points.)pbdoc")
        .def_property_readonly("bounding_box", &Grid3::GetBoundingBox,
                               R"pbdoc(Bounding box of the entire grid.)pbdoc")
        .def_property_readonly(
            "cell_center_position", &Grid3::GetCellCenterPosition,
            R"pbdoc(Function that maps grid index to the cell-center position.)pbdoc")
        .def("for_each_cell_index",
             [](Grid3& instance, pybind11::function func) {
                 instance.ForEachCellIndex(func);
             },
             R"pbdoc(
             Invokes the given function `func` for each grid cell.
             This function invokes the given function object `func` for each grid
             cell in serial manner. The input parameters are `i`, `j`, and `k` indices of a
             grid cell. The order of execution is i-first, k-last.
             )pbdoc",
             pybind11::arg("func"))
        .def("has_same_shape",
             [](const Grid3& instance, const Grid3Ptr& other) {
                 return instance.HasSameShape(*other);
             },
             R"pbdoc(
             Returns true if resolution, grid-spacing and origin are same.
             )pbdoc")
        .def("swap",
             [](Grid3& instance, Grid3Ptr& other) {
                 return instance.Swap(other.get());
             },
             R"pbdoc(
             Swaps the data with other grid.
             )pbdoc");
}