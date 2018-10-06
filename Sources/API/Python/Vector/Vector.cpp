/*************************************************************************
> File Name: Vector.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Vector functions for CubbyFlow Python API.
> Created Time: 2018/01/28
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Utils/pybind11Utils.h>
#include <API/Python/Vector/Vector.h>
#include <Core/Vector/Vector3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddVector2F(pybind11::module& m)
{
    pybind11::class_<Vector2F>(m, "Vector2F")
        .def("__init__",
             [](Vector2F& instance, float x, float y) {
                 new (&instance) Vector2F(x, y);
             },
             R"pbdoc(
             Constructs Vector2F.
             This method constructs float-type 2-D vector with x and y.
             )pbdoc",
             pybind11::arg("x") = 0.0f, pybind11::arg("y") = 0.0f)
        .def_readwrite("x", &Vector2F::x)
        .def_readwrite("y", &Vector2F::y)
        .def("setZero", &Vector2F::SetZero)
        .def("normalize", &Vector2F::Normalize)
        .def("dot",
             [](const Vector2F& instance, pybind11::object other) {
                 return instance.Dot(ObjectToVector2F(other));
             })
        .def("cross",
             [](const Vector2F& instance, pybind11::object other) {
                 return instance.Cross(ObjectToVector2F(other));
             })
        .def("sum", &Vector2F::Sum)
        .def("avg", &Vector2F::Avg)
        .def("min", &Vector2F::Min)
        .def("max", &Vector2F::Max)
        .def("absmin", &Vector2F::AbsMin)
        .def("absmax", &Vector2F::AbsMax)
        .def("dominantAxis", &Vector2F::DominantAxis)
        .def("subdominantAxis", &Vector2F::SubdominantAxis)
        .def("normalized", &Vector2F::Normalized)
        .def("length", &Vector2F::Length)
        .def("lengthSquared", &Vector2F::LengthSquared)
        .def("distanceTo",
             [](const Vector2F& instance, pybind11::object other) {
                 return instance.DistanceTo(ObjectToVector2F(other));
             })
        .def("distanceSquaredTo",
             [](const Vector2F& instance, pybind11::object other) {
                 return instance.DistanceSquaredTo(ObjectToVector2F(other));
             })
        .def("reflected",
             [](const Vector2F& instance, pybind11::object other) {
                 return instance.Reflected(ObjectToVector2F(other));
             })
        .def("projected",
             [](const Vector2F& instance, pybind11::object other) {
                 return instance.Projected(ObjectToVector2F(other));
             })
        .def("tangential", &Vector2F::Tangential)
        .def("__getitem__",
             [](const Vector2F& instance, size_t i) -> float {
                 return instance[i];
             })
        .def("__setitem__",
             [](Vector2F& instance, size_t i, float val) { instance[i] = val; })
        .def("__add__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Add(object.cast<float>());
                 }
                 else
                 {
                     return instance.Add(ObjectToVector2F(object));
                 }
             })
        .def("__sub__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Sub(object.cast<float>());
                 }
                 else
                 {
                     return instance.Sub(ObjectToVector2F(object));
                 }
             })
        .def("__rsub__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.RSub(object.cast<float>());
                 }
                 else
                 {
                     return instance.RSub(ObjectToVector2F(object));
                 }
             })
        .def("__mul__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Mul(object.cast<float>());
                 }
                 else
                 {
                     return instance.Mul(ObjectToVector2F(object));
                 }
             })
        .def("__div__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Div(object.cast<float>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector2F(object));
                 }
             })
        .def("__rdiv__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.RDiv(object.cast<float>());
                 }
                 else
                 {
                     return instance.RDiv(ObjectToVector2F(object));
                 }
             })
        .def("__truediv__",
             [](const Vector2F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Div(object.cast<float>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector2F(object));
                 }
             })
        .def("__len__", [](const Vector2F&) { return 2; })
        .def("__iter__",
             [](const Vector2F& instance) {
                 return pybind11::make_iterator(&instance.x, &instance.y + 1);
             })
        .def("__str__",
             [](const Vector2F& instance) {
                 return std::string(std::to_string(instance.x) + ", " +
                                    std::to_string(instance.y));
             })
        .def("__eq__", [](const Vector2F& instance, pybind11::object obj) {
            Vector2F other = ObjectToVector2F(obj);
            return instance == other;
        });
    ;
}

void AddVector2D(pybind11::module& m)
{
    pybind11::class_<Vector2D>(m, "Vector2D")
        .def("__init__",
             [](Vector2D& instance, double x, double y) {
                 new (&instance) Vector2D(x, y);
             },
             R"pbdoc(
             Constructs Vector2D.
             This method constructs double-type 2-D vector with x and y.
             )pbdoc",
             pybind11::arg("x") = 0.0, pybind11::arg("y") = 0.0)
        .def_readwrite("x", &Vector2D::x)
        .def_readwrite("y", &Vector2D::y)
        .def("setZero", &Vector2D::SetZero)
        .def("normalize", &Vector2D::Normalize)
        .def("dot",
             [](const Vector2D& instance, pybind11::object other) {
                 return instance.Dot(ObjectToVector2D(other));
             })
        .def("cross",
             [](const Vector2D& instance, pybind11::object other) {
                 return instance.Cross(ObjectToVector2D(other));
             })
        .def("sum", &Vector2D::Sum)
        .def("avg", &Vector2D::Avg)
        .def("min", &Vector2D::Min)
        .def("max", &Vector2D::Max)
        .def("absmin", &Vector2D::AbsMin)
        .def("absmax", &Vector2D::AbsMax)
        .def("dominantAxis", &Vector2D::DominantAxis)
        .def("subdominantAxis", &Vector2D::SubdominantAxis)
        .def("normalized", &Vector2D::Normalized)
        .def("length", &Vector2D::Length)
        .def("lengthSquared", &Vector2D::LengthSquared)
        .def("distanceTo",
             [](const Vector2D& instance, pybind11::object other) {
                 return instance.DistanceTo(ObjectToVector2D(other));
             })
        .def("distanceSquaredTo",
             [](const Vector2D& instance, pybind11::object other) {
                 return instance.DistanceSquaredTo(ObjectToVector2D(other));
             })
        .def("reflected",
             [](const Vector2D& instance, pybind11::object other) {
                 return instance.Reflected(ObjectToVector2D(other));
             })
        .def("projected",
             [](const Vector2D& instance, pybind11::object other) {
                 return instance.Projected(ObjectToVector2D(other));
             })
        .def("tangential", &Vector2D::Tangential)
        .def("__getitem__",
             [](const Vector2D& instance, size_t i) -> double {
                 return instance[i];
             })
        .def("__setitem__", [](Vector2D& instance, size_t i,
                               double val) { instance[i] = val; })
        .def("__add__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Add(object.cast<double>());
                 }
                 else
                 {
                     return instance.Add(ObjectToVector2D(object));
                 }
             })
        .def("__sub__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Sub(object.cast<double>());
                 }
                 else
                 {
                     return instance.Sub(ObjectToVector2D(object));
                 }
             })
        .def("__rsub__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.RSub(object.cast<double>());
                 }
                 else
                 {
                     return instance.RSub(ObjectToVector2D(object));
                 }
             })
        .def("__mul__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Mul(object.cast<double>());
                 }
                 else
                 {
                     return instance.Mul(ObjectToVector2D(object));
                 }
             })
        .def("__div__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Div(object.cast<double>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector2D(object));
                 }
             })
        .def("__rdiv__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.RDiv(object.cast<double>());
                 }
                 else
                 {
                     return instance.RDiv(ObjectToVector2D(object));
                 }
             })
        .def("__truediv__",
             [](const Vector2D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Div(object.cast<double>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector2D(object));
                 }
             })
        .def("__len__", [](const Vector2D&) { return 2; })
        .def("__iter__",
             [](const Vector2D& instance) {
                 return pybind11::make_iterator(&instance.x, &instance.y + 1);
             })
        .def("__str__",
             [](const Vector2D& instance) {
                 return std::string(std::to_string(instance.x) + ", " +
                                    std::to_string(instance.y));
             })
        .def("__eq__", [](const Vector2D& instance, pybind11::object obj) {
            Vector2D other = ObjectToVector2D(obj);
            return instance == other;
        });
}

void AddVector3F(pybind11::module& m)
{
    pybind11::class_<Vector3F>(m, "Vector3F")
        .def("__init__",
             [](Vector3F& instance, float x, float y, float z) {
                 new (&instance) Vector3F(x, y, z);
             },
             R"pbdoc(
             Constructs Vector3F.
             This method constructs float-type 3-D vector with x, y, and z.
             )pbdoc",
             pybind11::arg("x") = 0.0f, pybind11::arg("y") = 0.0f,
             pybind11::arg("z") = 0.0f)
        .def_readwrite("x", &Vector3F::x)
        .def_readwrite("y", &Vector3F::y)
        .def_readwrite("z", &Vector3F::z)
        .def("setZero", &Vector3F::SetZero)
        .def("normalize", &Vector3F::Normalize)
        .def("dot",
             [](const Vector3F& instance, pybind11::object other) {
                 return instance.Dot(ObjectToVector3F(other));
             })
        .def("cross",
             [](const Vector3F& instance, pybind11::object other) {
                 return instance.Cross(ObjectToVector3F(other));
             })
        .def("sum", &Vector3F::Sum)
        .def("avg", &Vector3F::Avg)
        .def("min", &Vector3F::Min)
        .def("max", &Vector3F::Max)
        .def("absmin", &Vector3F::AbsMin)
        .def("absmax", &Vector3F::AbsMax)
        .def("dominantAxis", &Vector3F::DominantAxis)
        .def("subdominantAxis", &Vector3F::SubdominantAxis)
        .def("normalized", &Vector3F::Normalized)
        .def("length", &Vector3F::Length)
        .def("lengthSquared", &Vector3F::LengthSquared)
        .def("distanceTo",
             [](const Vector3F& instance, pybind11::object other) {
                 return instance.DistanceTo(ObjectToVector3F(other));
             })
        .def("distanceSquaredTo",
             [](const Vector3F& instance, pybind11::object other) {
                 return instance.DistanceSquaredTo(ObjectToVector3F(other));
             })
        .def("reflected",
             [](const Vector3F& instance, pybind11::object other) {
                 return instance.Reflected(ObjectToVector3F(other));
             })
        .def("projected",
             [](const Vector3F& instance, pybind11::object other) {
                 return instance.Projected(ObjectToVector3F(other));
             })
        .def("tangential", &Vector3F::Tangential)
        .def("__getitem__",
             [](const Vector3F& instance, size_t i) -> float {
                 return instance[i];
             })
        .def("__setitem__",
             [](Vector3F& instance, size_t i, float val) { instance[i] = val; })
        .def("__add__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Add(object.cast<float>());
                 }
                 else
                 {
                     return instance.Add(ObjectToVector3F(object));
                 }
             })
        .def("__sub__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Sub(object.cast<float>());
                 }
                 else
                 {
                     return instance.Sub(ObjectToVector3F(object));
                 }
             })
        .def("__rsub__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.RSub(object.cast<float>());
                 }
                 else
                 {
                     return instance.RSub(ObjectToVector3F(object));
                 }
             })
        .def("__mul__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Mul(object.cast<float>());
                 }
                 else
                 {
                     return instance.Mul(ObjectToVector3F(object));
                 }
             })
        .def("__div__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Div(object.cast<float>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector3F(object));
                 }
             })
        .def("__rdiv__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.RDiv(object.cast<float>());
                 }
                 else
                 {
                     return instance.RDiv(ObjectToVector3F(object));
                 }
             })
        .def("__truediv__",
             [](const Vector3F& instance, pybind11::object object) {
                 if (pybind11::isinstance<float>(object))
                 {
                     return instance.Div(object.cast<float>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector3F(object));
                 }
             })
        .def("__len__", [](const Vector3F&) { return 3; })
        .def("__iter__",
             [](const Vector3F& instance) {
                 return pybind11::make_iterator(&instance.x, &instance.z + 1);
             })
        .def("__str__",
             [](const Vector3F& instance) {
                 return std::string(std::to_string(instance.x) + ", " +
                                    std::to_string(instance.y) + ", " +
                                    std::to_string(instance.z));
             })
        .def("__eq__", [](const Vector3F& instance, pybind11::object obj) {
            Vector3F other = ObjectToVector3F(obj);
            return instance == other;
        });
    ;
}

void AddVector3D(pybind11::module& m)
{
    pybind11::class_<Vector3D>(m, "Vector3D")
        .def("__init__",
             [](Vector3D& instance, double x, double y, double z) {
                 new (&instance) Vector3D(x, y, z);
             },
             R"pbdoc(
             Constructs Vector3D.
             This method constructs double-type 3-D vector with x, y, and z.
             )pbdoc",
             pybind11::arg("x") = 0.0, pybind11::arg("y") = 0.0,
             pybind11::arg("z") = 0.0)
        .def_readwrite("x", &Vector3D::x)
        .def_readwrite("y", &Vector3D::y)
        .def_readwrite("z", &Vector3D::z)
        .def("setZero", &Vector3D::SetZero)
        .def("normalize", &Vector3D::Normalize)
        .def("dot",
             [](const Vector3D& instance, pybind11::object other) {
                 return instance.Dot(ObjectToVector3D(other));
             })
        .def("cross",
             [](const Vector3D& instance, pybind11::object other) {
                 return instance.Cross(ObjectToVector3D(other));
             })
        .def("sum", &Vector3D::Sum)
        .def("avg", &Vector3D::Avg)
        .def("min", &Vector3D::Min)
        .def("max", &Vector3D::Max)
        .def("absmin", &Vector3D::AbsMin)
        .def("absmax", &Vector3D::AbsMax)
        .def("dominantAxis", &Vector3D::DominantAxis)
        .def("subdominantAxis", &Vector3D::SubdominantAxis)
        .def("normalized", &Vector3D::Normalized)
        .def("length", &Vector3D::Length)
        .def("lengthSquared", &Vector3D::LengthSquared)
        .def("distanceTo",
             [](const Vector3D& instance, pybind11::object other) {
                 return instance.DistanceTo(ObjectToVector3D(other));
             })
        .def("distanceSquaredTo",
             [](const Vector3D& instance, pybind11::object other) {
                 return instance.DistanceSquaredTo(ObjectToVector3D(other));
             })
        .def("reflected",
             [](const Vector3D& instance, pybind11::object other) {
                 return instance.Reflected(ObjectToVector3D(other));
             })
        .def("projected",
             [](const Vector3D& instance, pybind11::object other) {
                 return instance.Projected(ObjectToVector3D(other));
             })
        .def("tangential", &Vector3D::Tangential)
        .def("__getitem__",
             [](const Vector3D& instance, size_t i) -> double {
                 return instance[i];
             })
        .def("__setitem__", [](Vector3D& instance, size_t i,
                               double val) { instance[i] = val; })
        .def("__add__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Add(object.cast<double>());
                 }
                 else
                 {
                     return instance.Add(ObjectToVector3D(object));
                 }
             })
        .def("__sub__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Sub(object.cast<double>());
                 }
                 else
                 {
                     return instance.Sub(ObjectToVector3D(object));
                 }
             })
        .def("__rsub__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.RSub(object.cast<double>());
                 }
                 else
                 {
                     return instance.RSub(ObjectToVector3D(object));
                 }
             })
        .def("__mul__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Mul(object.cast<double>());
                 }
                 else
                 {
                     return instance.Mul(ObjectToVector3D(object));
                 }
             })
        .def("__div__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Div(object.cast<double>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector3D(object));
                 }
             })
        .def("__rdiv__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.RDiv(object.cast<double>());
                 }
                 else
                 {
                     return instance.RDiv(ObjectToVector3D(object));
                 }
             })
        .def("__truediv__",
             [](const Vector3D& instance, pybind11::object object) {
                 if (pybind11::isinstance<double>(object))
                 {
                     return instance.Div(object.cast<double>());
                 }
                 else
                 {
                     return instance.Div(ObjectToVector3D(object));
                 }
             })
        .def("__len__", [](const Vector3D&) { return 3; })
        .def("__iter__",
             [](const Vector3D& instance) {
                 return pybind11::make_iterator(&instance.x, &instance.z + 1);
             })
        .def("__str__",
             [](const Vector3D& instance) {
                 return std::string(std::to_string(instance.x) + ", " +
                                    std::to_string(instance.y) + ", " +
                                    std::to_string(instance.z));
             })
        .def("__eq__", [](const Vector3D& instance, pybind11::object obj) {
            Vector3D other = ObjectToVector3D(obj);
            return instance == other;
        });
}