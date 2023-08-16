#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
#include "../cpp_plc/plc_template.h"

namespace py = pybind11;

constexpr int MAX_AUDIO_CHANS = 8;

template<int n_audio_channels>
class BasePlcTemplateWrapper
{
    public:
    BasePlcTemplateWrapper()
    {
        wrapped_object = new BasePlcTemplate<n_audio_channels>();
    }

    ~BasePlcTemplateWrapper()
    {
        wrapped_object->~BasePlcTemplate();
    }

    void set_plc_active(bool active)
    {
        wrapped_object->set_plc_active(active);
    }

    bool is_plc_active()
    {
        return wrapped_object->is_plc_active();
    }

    void prepare_to_play(float sampling_rate, int audio_buffer_size)
    {
        buffer_size = audio_buffer_size;
        wrapped_object->prepare_to_play(sampling_rate, audio_buffer_size);
    }

    void process(py::array_t<float, py::array::c_style | py::array::forcecast> inputs, py::array_t<float, py::array::c_style | py::array::forcecast> outputs, bool is_packet_valid)
    {
        if (inputs.ndim() > 2)
            throw std::runtime_error("Input cannot have more than 2 dimensions");
        if (outputs.ndim() > 2)
            throw std::runtime_error("Output cannot have more than 2 dimensions");

        const float * in_ptr = inputs.data(0);
        float * out_ptr = outputs.mutable_data(0);

        for (int i=0; i < n_audio_channels; i++)
        {
            vector_of_pointers_in[i] = in_ptr + i*buffer_size;
            vector_of_pointers_out[i] = out_ptr + i*buffer_size;
        }
        wrapped_object->process(vector_of_pointers_in, vector_of_pointers_out, is_packet_valid);
    }
    private:
    BasePlcTemplate<n_audio_channels>* wrapped_object;
    const float* vector_of_pointers_in[MAX_AUDIO_CHANS];
    float* vector_of_pointers_out[MAX_AUDIO_CHANS];
    int buffer_size;
};

PYBIND11_MODULE(cpp_plc_template, m) {
    constexpr int n_audio_channels = 2;
    py::class_<BasePlcTemplateWrapper<n_audio_channels>, std::shared_ptr<BasePlcTemplateWrapper<n_audio_channels>>> bec(m, "BasePlcTemplate");

    bec.def(py::init<>())
       .def("set_plc_active", &BasePlcTemplateWrapper<n_audio_channels>::set_plc_active)
       .def("is_plc_active", &BasePlcTemplateWrapper<n_audio_channels>::is_plc_active)
       .def("prepare_to_play", &BasePlcTemplateWrapper<n_audio_channels>::prepare_to_play)
       .def("process", &BasePlcTemplateWrapper<n_audio_channels>::process);
    
    m.doc() = "Template for C++ PLC algorithms wrapped for python use ";
}