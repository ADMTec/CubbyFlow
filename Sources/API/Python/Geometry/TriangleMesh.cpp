/*************************************************************************
> File Name: TriangleMesh.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: TriangleMesh functions for CubbyFlow Python API.
> Created Time: 2018/01/28
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Geometry/TriangleMesh.h>
#include <API/Python/Utils/pybind11Utils.h>
#include <Core/Geometry/TriangleMesh3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddTriangleMesh3(pybind11::module& m)
{
    pybind11::class_<TriangleMesh3, TriangleMesh3Ptr, Surface3>(
        static_cast<pybind11::handle>(m), "TriangleMesh3",
        R"pbdoc(
			3-D triangle mesh geometry.

			This class represents 3-D triangle mesh geometry which extends Surface3 by
			overriding surface-related queries. The mesh structure stores point,
			normals, and UV coordinates.
		)pbdoc")
        .def("__init__",
             [](TriangleMesh3& instance, pybind11::list points,
                pybind11::list normals, pybind11::list uvs,
                pybind11::list pointIndices, pybind11::list normalIndices,
                pybind11::list uvIndices, const Transform3& transform,
                bool isNormalFlipped) {
                 TriangleMesh3::PointArray _points;
                 TriangleMesh3::NormalArray _normals;
                 TriangleMesh3::UVArray _uvs;
                 TriangleMesh3::IndexArray _pointIndices;
                 TriangleMesh3::IndexArray _normalIndices;
                 TriangleMesh3::IndexArray _uvIndices;

                 _points.Resize(points.size());
                 for (size_t i = 0; i < points.size(); ++i)
                 {
                     _points[i] = ObjectToVector3D(points[i]);
                 }

                 _normals.Resize(normals.size());
                 for (size_t i = 0; i < normals.size(); ++i)
                 {
                     _normals[i] = ObjectToVector3D(normals[i]);
                 }

                 _uvs.Resize(uvs.size());
                 for (size_t i = 0; i < uvs.size(); ++i)
                 {
                     _uvs[i] = ObjectToVector2D(uvs[i]);
                 }

                 _pointIndices.Resize(pointIndices.size());
                 for (size_t i = 0; i < pointIndices.size(); ++i)
                 {
                     _pointIndices[i] = ObjectToPoint3UI(pointIndices[i]);
                 }

                 _normalIndices.Resize(normalIndices.size());
                 for (size_t i = 0; i < normalIndices.size(); ++i)
                 {
                     _normalIndices[i] = ObjectToPoint3UI(normalIndices[i]);
                 }

                 _uvIndices.Resize(uvIndices.size());
                 for (size_t i = 0; i < uvIndices.size(); ++i)
                 {
                     _uvIndices[i] = ObjectToPoint3UI(uvIndices[i]);
                 }

                 new (&instance) TriangleMesh3(
                     _points, _normals, _uvs, _pointIndices, _normalIndices,
                     _uvIndices, transform, isNormalFlipped);
             },
             R"pbdoc(
			Constructs mesh with points, normals, uvs, and their indices.
		)pbdoc",
             pybind11::arg("points") = pybind11::list(),
             pybind11::arg("normals") = pybind11::list(),
             pybind11::arg("uvs") = pybind11::list(),
             pybind11::arg("point_indices") = pybind11::list(),
             pybind11::arg("normal_indices") = pybind11::list(),
             pybind11::arg("uv_indices") = pybind11::list(),
             pybind11::arg("transform") = Transform3(),
             pybind11::arg("is_normal_flipped") = false)
        .def("clear", &TriangleMesh3::Clear,
             R"pbdoc(
			Clears all content.
		)pbdoc")
        .def("set", &TriangleMesh3::Set,
             R"pbdoc(
			Copies the contents from `other` mesh.
		)pbdoc",
             pybind11::arg("other"))
        .def("swap",
             [](TriangleMesh3& instance, const TriangleMesh3Ptr& other) {
                 instance.Swap(*other);
             },
             R"pbdoc(
			Swaps the contents with `other` mesh.
		)pbdoc",
             pybind11::arg("other"))
        .def("area", &TriangleMesh3::Area,
             R"pbdoc(
			Returns area of this mesh.
		)pbdoc")
        .def("volume", &TriangleMesh3::Volume,
             R"pbdoc(
			Returns volume of this mesh.
		)pbdoc")
        .def("get_point",
             [](const TriangleMesh3& instance, size_t i) -> Vector3D {
                 return instance.Point(i);
             },
             R"pbdoc(
			Returns i-th point.
		)pbdoc",
             pybind11::arg("i"))
        .def("set_point",
             [](TriangleMesh3& instance, size_t i, const Vector3D& pt) {
                 instance.Point(i) = pt;
             },
             R"pbdoc(
			Sets `i`-th point with `pt`.
		)pbdoc",
             pybind11::arg("i"), pybind11::arg("pt"))
        .def("get_normal",
             [](const TriangleMesh3& instance, size_t i) -> Vector3D {
                 return instance.Normal(i);
             },
             R"pbdoc(
			Returns i-th normal.
		)pbdoc",
             pybind11::arg("i"))
        .def("set_normal",
             [](TriangleMesh3& instance, size_t i, const Vector3D& n) {
                 instance.Normal(i) = n;
             },
             R"pbdoc(
			Sets `i`-th normal with `pt`.
		)pbdoc",
             pybind11::arg("i"), pybind11::arg("n"))
        .def("get_point_index",
             [](const TriangleMesh3& instance, size_t i) -> Point3UI {
                 return instance.PointIndex(i);
             },
             R"pbdoc(
			Returns i-th pointIndex.
		)pbdoc",
             pybind11::arg("i"))
        .def("set_point_index",
             [](TriangleMesh3& instance, size_t i, const Point3UI& idx) {
                 instance.PointIndex(i) = idx;
             },
             R"pbdoc(
			Sets `i`-th pointIndex with `idx`.
		)pbdoc",
             pybind11::arg("i"), pybind11::arg("idx"))
        .def("get_normal_index",
             [](const TriangleMesh3& instance, size_t i) -> Point3UI {
                 return instance.NormalIndex(i);
             },
             R"pbdoc(
			Returns i-th normalIndexIndex.
		)pbdoc",
             pybind11::arg("i"))
        .def("set_normal_index",
             [](TriangleMesh3& instance, size_t i, const Point3UI& idx) {
                 instance.NormalIndex(i) = idx;
             },
             R"pbdoc(
			Sets `i`-th normalIndexIndex with `idx`.
		)pbdoc",
             pybind11::arg("i"), pybind11::arg("idx"))
        .def("get_uv_index",
             [](const TriangleMesh3& instance, size_t i) -> Point3UI {
                 return instance.UVIndex(i);
             },
             R"pbdoc(
			Returns i-th uvIndexIndex.
		)pbdoc",
             pybind11::arg("i"))
        .def("set_uv_index",
             [](TriangleMesh3& instance, size_t i, const Point3UI& idx) {
                 instance.UVIndex(i) = idx;
             },
             R"pbdoc(
			Sets `i`-th uvIndexIndex with `idx`.
		)pbdoc",
             pybind11::arg("i"), pybind11::arg("idx"))
        .def("triangle",
             [](const TriangleMesh3& instance, size_t i) {
                 return std::make_shared<Triangle3>(instance.Triangle(i));
             },
             R"pbdoc(
			Returns `i`-th triangle.
		)pbdoc",
             pybind11::arg("i"))
        .def("number_of_points", &TriangleMesh3::NumberOfPoints,
             R"pbdoc(
			Returns number of points.
		)pbdoc")
        .def("number_of_normals", &TriangleMesh3::NumberOfNormals,
             R"pbdoc(
			Returns number of normals.
		)pbdoc")
        .def("number_of_uvs", &TriangleMesh3::NumberOfUVs,
             R"pbdoc(
			Returns number of UV coordinates.
		)pbdoc")
        .def("number_of_triangles", &TriangleMesh3::NumberOfTriangles,
             R"pbdoc(
			Returns number of triangles.
		)pbdoc")
        .def("has_normals", &TriangleMesh3::HasNormals,
             R"pbdoc(
			Returns true if the mesh has normals.
		)pbdoc")
        .def("has_uvs", &TriangleMesh3::HasUVs,
             R"pbdoc(
			Returns true if the mesh has UV coordinates.
		)pbdoc")
        .def("add_point",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.AddPoint(ObjectToVector3D(obj));
             },
             R"pbdoc(
			Adds a point.
		)pbdoc",
             pybind11::arg("pt"))
        .def("add_normal",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.AddNormal(ObjectToVector3D(obj));
             },
             R"pbdoc(
			Adds a normal.
		)pbdoc",
             pybind11::arg("n"))
        .def("add_uv",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.AddUV(ObjectToVector2D(obj));
             },
             R"pbdoc(
			Adds a UV.
		)pbdoc",
             pybind11::arg("uv"))
        .def("add_point_triangle",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.AddPointTriangle(ObjectToPoint3UI(obj));
             },
             R"pbdoc(
			Adds a triangle with point.
		)pbdoc",
             pybind11::arg("new_point_indices"))
        .def("add_normal_triangle",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.AddNormalTriangle(ObjectToPoint3UI(obj));
             },
             R"pbdoc(
			Adds a triangle with normal.
		)pbdoc",
             pybind11::arg("new_normal_indices"))
        .def("add_uv_triangle",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.AddUVTriangle(ObjectToPoint3UI(obj));
             },
             R"pbdoc(
			Adds a triangle with UV.
		)pbdoc",
             pybind11::arg("new_uv_indices"))
        .def("add_triangle", &TriangleMesh3::AddTriangle,
             R"pbdoc(
			Add a triangle.
		)pbdoc",
             pybind11::arg("tri"))
        .def("set_face_normal", &TriangleMesh3::SetFaceNormal,
             R"pbdoc(
			Sets entire normals to the face normals.
		)pbdoc")
        .def("set_angle_weighted_vertex_normal",
             &TriangleMesh3::SetAngleWeightedVertexNormal,
             R"pbdoc(
			Sets angle weighted vertex normal.
		)pbdoc")
        .def("scale", &TriangleMesh3::Scale,
             R"pbdoc(
			Scales the mesh by given factor.
		)pbdoc",
             pybind11::arg("factor"))
        .def("translate",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.Translate(ObjectToVector3D(obj));
             },
             R"pbdoc(
			Translates the mesh.
		)pbdoc",
             pybind11::arg("t"))
        .def("rotate",
             [](TriangleMesh3& instance, pybind11::object obj) {
                 instance.Rotate(ObjectToQuaternionD(obj));
             },
             R"pbdoc(
			Rotates the mesh.
		)pbdoc",
             pybind11::arg("rot"))
        .def("write_obj",
             [](const TriangleMesh3& instance, const std::string& fileName) {
                 instance.WriteObj(fileName);
             },
             R"pbdoc(
			Writes the mesh in obj format to the file.
		)pbdoc",
             pybind11::arg("file_name"))
        .def("read_obj",
             [](TriangleMesh3& instance, const std::string& fileName) {
                 instance.ReadObj(fileName);
             },
             R"pbdoc(
			Reads the mesh in obj format from the file.
		)pbdoc",
             pybind11::arg("file_name"));
}