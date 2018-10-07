/*************************************************************************
> File Name: GridEmitter.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: GridEmitter functions for CubbyFlow Python API.
> Created Time: 2018/02/11
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <API/Python/Emitter/GridEmitter.h>
#include <Core/Emitter/GridEmitter2.h>
#include <Core/Emitter/GridEmitter3.h>

#include <pybind11/pybind11.h>

using namespace CubbyFlow;

void AddGridEmitter2(pybind11::module& m)
{
    pybind11::class_<GridEmitter2, GridEmitter2Ptr>(m, "GridEmitter2",
                                                    R"pbdoc(
            Abstract base class for 2-D grid-based emitters.
        )pbdoc")
        .def("Update", &GridEmitter2::Update,
             R"pbdoc(
            Updates the emitter state from `current_time_in_seconds` to by
            `time_interval_in_seconds`.

            Parameters
            ----------
            - current_time_in_seconds : Starting time stamp.
            - time_interval_in_seconds : Time-step to advance.
        )pbdoc",
             pybind11::arg("current_time_in_seconds"),
             pybind11::arg("time_interval_in_seconds"))
        .def("set_on_begin_update_callback",
             [](GridEmitter2& instance, pybind11::function callback) {
                 instance.SetOnBeginUpdateCallback(callback);
             },
             R"pbdoc(
            Sets the callback function to be called when `Update` is invoked.

            The callback function takes current simulation time in seconds unit. Use
            this callback to track any motion or state changes related to this
            emitter.

            Parameters
            ----------
            - callback : The callback function.
        )pbdoc",
             pybind11::arg("callback"));
}

void AddGridEmitter3(pybind11::module& m)
{
    pybind11::class_<GridEmitter3, GridEmitter3Ptr>(m, "GridEmitter3",
                                                    R"pbdoc(
            Abstract base class for 3-D grid-based emitters.
        )pbdoc")
        .def("Update", &GridEmitter3::Update,
             R"pbdoc(
            Updates the emitter state from `current_time_in_seconds` to by
            `time_interval_in_seconds`.

            Parameters
            ----------
            - current_time_in_seconds : Starting time stamp.
            - time_interval_in_seconds : Time-step to advance.
            )pbdoc",
             pybind11::arg("current_time_in_seconds"),
             pybind11::arg("time_interval_in_seconds"))
        .def("set_on_begin_update_callback",
             [](GridEmitter3& instance, pybind11::function callback) {
                 instance.SetOnBeginUpdateCallback(callback);
             },
             R"pbdoc(
            Sets the callback function to be called when `update` is invoked.

            The callback function takes current simulation time in seconds unit. Use
            this callback to track any motion or state changes related to this
            emitter.

            Parameters
            ----------
            - callback : The callback function.
        )pbdoc",
             pybind11::arg("callback"));
}