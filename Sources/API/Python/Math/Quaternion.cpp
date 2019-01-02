/*************************************************************************
> File Name: Quaternion.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Quaternion functions for CubbyFlow Python API.
> Created Time: 2018/01/30
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Math/Quaternion.h>
#include <API/Python/Utils/pybind11Utils.h>
#include <Core/Math/Quaternion.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddQuaternionF(pybind11::module& m)
{
    pybind11::class_<QuaternionF>(static_cast<pybind11::handle>(m),
                                  "QuaternionF")
        .def("__init__",
             [](QuaternionF& instance, float w, float x, float y, float z) {
                 new (&instance) QuaternionF(w, x, y, z);
             },
             R"pbdoc(
			Constructs QuaternionF.

			This method constructs float-type quaternion with w, x, y, and z.
		)pbdoc",
             pybind11::arg("w") = 1.0f, pybind11::arg("x") = 0.0f,
             pybind11::arg("y") = 0.0f, pybind11::arg("z") = 0.0f)
        .def_readwrite("w", &QuaternionF::w)
        .def_readwrite("x", &QuaternionF::x)
        .def_readwrite("y", &QuaternionF::y)
        .def_readwrite("z", &QuaternionF::z)
        .def("angle", &QuaternionF::Angle)
        .def("axis", &QuaternionF::Axis)
        .def("normalized", &QuaternionF::Normalized)
        .def("inverse", &QuaternionF::Inverse)
        .def("l2norm", &QuaternionF::L2Norm)
        .def("set_axis_angle",
             [](QuaternionF& instance, pybind11::object axis, float angle) {
                 instance.Set(ObjectToVector3F(axis), angle);
             },
             R"pbdoc(
			Sets the quaternion with given rotation axis and angle.
		)pbdoc",
             pybind11::arg("axis"), pybind11::arg("angle"))
        .def("set_from_to",
             [](QuaternionF& instance, pybind11::object from,
                pybind11::object to) {
                 instance.Set(ObjectToVector3F(from), ObjectToVector3F(to));
             },
             R"pbdoc(
			Sets the quaternion with from and to vectors.
		)pbdoc",
             pybind11::arg("from"), pybind11::arg("to"))
        .def("set_rotation_basis",
             [](QuaternionF& instance, pybind11::object basis0,
                pybind11::object basis1, pybind11::object basis2) {
                 instance.Set(ObjectToVector3F(basis0),
                              ObjectToVector3F(basis1),
                              ObjectToVector3F(basis2));
             },
             R"pbdoc(
			Sets quaternion with three basis vectors.
		)pbdoc",
             pybind11::arg("basis0"), pybind11::arg("basis1"),
             pybind11::arg("basis2"))
        .def("set_identity", &QuaternionF::SetIdentity)
        .def("normalize", &QuaternionF::Normalize)
        .def("rotate",
             [](const QuaternionF& instance, pybind11::object other) {
                 return instance.Mul(ObjectToVector3F(other));
             },
             R"pbdoc(
			Returns this quaternion * other vector.
		)pbdoc",
             pybind11::arg("other"))
        .def("dot", &QuaternionF::Dot)
        .def("__mul__",
             [](const QuaternionF& instance, pybind11::object other) {
                 return instance.Mul(ObjectToQuaternionF(other));
             },
             R"pbdoc(
			Returns this quaternion * other quaternion.
		)pbdoc",
             pybind11::arg("other"))
        .def("__imul__",
             [](QuaternionF& instance, pybind11::object other) {
                 instance.IMul(ObjectToQuaternionF(other));
             },
             R"pbdoc(
			This quaternion *= other quaternion.
		)pbdoc",
             pybind11::arg("other"))
        .def("__setitem__", [](QuaternionF& instance, size_t i,
                               float val) { instance[i] = val; })
        .def("__getitem__",
             [](const QuaternionF& instance, size_t i) -> float {
                 return instance[i];
             })
        .def("__eq__", [](const QuaternionF& instance, pybind11::object obj) {
            QuaternionF other = ObjectToQuaternionF(obj);
            return instance == other;
        });
}

void AddQuaternionD(pybind11::module& m)
{
    pybind11::class_<QuaternionD>(static_cast<pybind11::handle>(m),
                                  "QuaternionD")
        .def("__init__",
             [](QuaternionD& instance, double w, double x, double y, double z) {
                 new (&instance) QuaternionD(w, x, y, z);
             },
             R"pbdoc(
			Constructs QuaternionD.

			This method constructs double-type quaternion with w, x, y, and z.
		)pbdoc",
             pybind11::arg("w") = 1.0, pybind11::arg("x") = 0.0,
             pybind11::arg("y") = 0.0, pybind11::arg("z") = 0.0)
        .def_readwrite("w", &QuaternionD::w)
        .def_readwrite("x", &QuaternionD::x)
        .def_readwrite("y", &QuaternionD::y)
        .def_readwrite("z", &QuaternionD::z)
        .def("angle", &QuaternionD::Angle)
        .def("axis", &QuaternionD::Axis)
        .def("normalized", &QuaternionD::Normalized)
        .def("inverse", &QuaternionD::Inverse)
        .def("l2norm", &QuaternionD::L2Norm)
        .def("set_axis_angle",
             [](QuaternionD& instance, pybind11::object axis, double angle) {
                 instance.Set(ObjectToVector3D(axis), angle);
             },
             R"pbdoc(
			Sets the quaternion with given rotation axis and angle.
		)pbdoc",
             pybind11::arg("axis"), pybind11::arg("angle"))
        .def("set_from_to",
             [](QuaternionD& instance, pybind11::object from,
                pybind11::object to) {
                 instance.Set(ObjectToVector3D(from), ObjectToVector3D(to));
             },
             R"pbdoc(
			Sets the quaternion with from and to vectors.
		)pbdoc",
             pybind11::arg("from"), pybind11::arg("to"))
        .def("set_rotation_basis",
             [](QuaternionD& instance, pybind11::object basis0,
                pybind11::object basis1, pybind11::object basis2) {
                 instance.Set(ObjectToVector3D(basis0),
                              ObjectToVector3D(basis1),
                              ObjectToVector3D(basis2));
             },
             R"pbdoc(
			Sets quaternion with three basis vectors.
		)pbdoc",
             pybind11::arg("basis0"), pybind11::arg("basis1"),
             pybind11::arg("basis2"))
        .def("set_identity", &QuaternionD::SetIdentity)
        .def("normalize", &QuaternionD::Normalize)
        .def("rotate",
             [](const QuaternionD& instance, pybind11::object other) {
                 return instance.Mul(ObjectToVector3D(other));
             },
             R"pbdoc(
			Returns this quaternion * other vector.
		)pbdoc",
             pybind11::arg("other"))
        .def("dot", &QuaternionD::Dot)
        .def("__mul__",
             [](const QuaternionD& instance, pybind11::object other) {
                 return instance.Mul(ObjectToQuaternionD(other));
             },
             R"pbdoc(
			Returns this quaternion * other quaternion.
		)pbdoc",
             pybind11::arg("other"))
        .def("__imul__",
             [](QuaternionD& instance, pybind11::object other) {
                 instance.IMul(ObjectToQuaternionD(other));
             },
             R"pbdoc(
			This quaternion *= other quaternion.
		)pbdoc",
             pybind11::arg("other"))
        .def("__setitem__", [](QuaternionD& instance, size_t i,
                               double val) { instance[i] = val; })
        .def("__getitem__",
             [](const QuaternionD& instance, size_t i) -> double {
                 return instance[i];
             })
        .def("__eq__", [](const QuaternionD& instance, pybind11::object obj) {
            QuaternionD other = ObjectToQuaternionD(obj);
            return instance == other;
        });
}