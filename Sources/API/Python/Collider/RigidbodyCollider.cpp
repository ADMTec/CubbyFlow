/*************************************************************************
> File Name: RigidbodyCollider.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: RigidbodyCollider functions for CubbyFlow Python API.
> Created Time: 2018/02/10
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Collider/RigidbodyCollider.h>
#include <API/Python/Utils/pybind11Utils.h>
#include <Core/Collider/Collider2.h>
#include <Core/Collider/Collider3.h>
#include <Core/Collider/RigidBodyCollider2.h>
#include <Core/Collider/RigidBodyCollider3.h>
#include <Core/Surface/Surface2.h>
#include <Core/Surface/Surface3.h>
#include <Core/Vector/Vector2.h>
#include <Core/Vector/Vector3.h>
#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddRigidBodyCollider2(pybind11::module& m)
{
    pybind11::class_<RigidBodyCollider2, RigidBodyCollider2Ptr, Collider2>(
        m, "RigidBodyCollider2")
        .def("__init__",
             [](RigidBodyCollider2& instance, const Surface2Ptr& surface,
                pybind11::object linearVelocity, double angularVelocity) {
                 new (&instance) RigidBodyCollider2(
                     surface, ObjectToVector2D(linearVelocity),
                     angularVelocity);
             },
             R"pbdoc(
            Constructs RigidBodyCollider2

            This method constructs RigidBodyCollider2 with surface, linear
            velocity, and angular velocity.
        )pbdoc",
             pybind11::arg("surface"),
             pybind11::arg("linear_velocity") = Vector2D{},
             pybind11::arg("angular_velocity") = 0.0)
        .def_property("linear_velocity",
                      [](const RigidBodyCollider2& instance) {
                          return instance.linearVelocity;
                      },
                      [](RigidBodyCollider2& instance, pybind11::object obj) {
                          instance.linearVelocity = ObjectToVector2D(obj);
                      },
                      R"pbdoc(
            Linear velocity of the collider.
        )pbdoc")
        .def_readwrite("angular_velocity", &RigidBodyCollider2::angularVelocity,
                       R"pbdoc(
            Angular velocity of the collider.
        )pbdoc")
        .def("velocity_at",
             [](const RigidBodyCollider2& instance, pybind11::object obj) {
                 return instance.VelocityAt(ObjectToVector2D(obj));
             },
             R"pbdoc(
            Returns the velocity of the collider at given point.
        )pbdoc",
             pybind11::arg("point"));
}

void AddRigidBodyCollider3(pybind11::module& m)
{
    pybind11::class_<RigidBodyCollider3, RigidBodyCollider3Ptr, Collider3>(
        m, "RigidBodyCollider3")
        .def("__init__",
             [](RigidBodyCollider3& instance, const Surface3Ptr& surface,
                pybind11::object linearVelocity,
                pybind11::object angularVelocity) {
                 new (&instance) RigidBodyCollider3(
                     surface, ObjectToVector3D(linearVelocity),
                     ObjectToVector3D(angularVelocity));
             },
             R"pbdoc(
            Constructs RigidBodyCollider3

            This method constructs RigidBodyCollider3 with surface, linear
            velocity, and angular velocity.
        )pbdoc",
             pybind11::arg("surface"),
             pybind11::arg("linear_velocity") = Vector3D{},
             pybind11::arg("angular_velocity") = Vector3D{})
        .def_property("linear_velocity",
                      [](const RigidBodyCollider3& instance) {
                          return instance.linearVelocity;
                      },
                      [](RigidBodyCollider3& instance, pybind11::object obj) {
                          instance.linearVelocity = ObjectToVector3D(obj);
                      },
                      R"pbdoc(
            Linear velocity of the collider.
        )pbdoc")
        .def_property("angular_velocity",
                      [](const RigidBodyCollider3& instance) {
                          return instance.angularVelocity;
                      },
                      [](RigidBodyCollider3& instance, pybind11::object obj) {
                          instance.angularVelocity = ObjectToVector3D(obj);
                      },
                      R"pbdoc(
            Angular velocity of the collider.
        )pbdoc")
        .def("velocity_at",
             [](const RigidBodyCollider3& instance, pybind11::object obj) {
                 return instance.VelocityAt(ObjectToVector3D(obj));
             },
             R"pbdoc(
            Returns the velocity of the collider at given point.
        )pbdoc",
             pybind11::arg("point"));
}