/*************************************************************************
> File Name: Size.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Size functions for CubbyFlow Python API.
> Created Time: 2018/01/29
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Size/Size.h>
#include <API/Python/Utils/pybind11Utils.h>
#include <Core/Size/Size2.h>
#include <Core/Size/Size3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddSize2(pybind11::module& m)
{
    pybind11::class_<Size2>(m, "Size2")
        .def("__init__",
             [](Size2& instance, size_t x, size_t y) {
                 new (&instance) Size2(x, y);
             },
             R"pbdoc(
             Constructs Size2
             This method constructs 2D size with x and y.
             )pbdoc",
             pybind11::arg("x") = 0, pybind11::arg("y") = 0)
        .def_readwrite("x", &Size2::x)
        .def_readwrite("y", &Size2::y)
        .def("__len__", [](const Size2&) { return 2; })
        .def("__iter__",
             [](const Size2& instance) {
                 return pybind11::make_iterator(&instance.x, &instance.y + 1);
             })
        .def("__eq__", [](const Size2& instance, pybind11::object obj) {
            Size2 other = ObjectToSize2(obj);
            return instance == other;
        });
}

void AddSize3(pybind11::module& m)
{
    pybind11::class_<Size3>(m, "Size3")
        .def("__init__",
             [](Size3& instance, size_t x, size_t y, size_t z) {
                 new (&instance) Size3(x, y, z);
             },
             R"pbdoc(
             Constructs Size3
             This method constructs 3D size with x, y, and z.
             )pbdoc",
             pybind11::arg("x") = 0, pybind11::arg("y") = 0,
             pybind11::arg("z") = 0)
        .def_readwrite("x", &Size3::x)
        .def_readwrite("y", &Size3::y)
        .def_readwrite("z", &Size3::z)
        .def("__len__", [](const Size3&) { return 3; })
        .def("__iter__",
             [](const Size3& instance) {
                 return pybind11::make_iterator(&instance.x, &instance.z + 1);
             })
        .def("__eq__", [](const Size3& instance, pybind11::object obj) {
            Size3 other = ObjectToSize3(obj);
            return instance == other;
        });
}