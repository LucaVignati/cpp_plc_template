/* This is a template for the implementation of
*  PLC algorithms in C++ usable in Python.
*/

template<int n_audio_channels>
class BasePlcTemplate
{

public:

    BasePlcTemplate() = default;

    virtual ~BasePlcTemplate() = default;


    /**
     * @brief This method will be called before the first call to process().
     *        It is used to initialize the PLC algorithm.
     *
     * @param sampling_rate Sampling rate in Hertz
     * @param audio_buffer_size Audio buffer size in frames
     */
    virtual void prepare_to_play(float sampling_rate,
                                 int audio_buffer_size)
    {
        _buffer_size = audio_buffer_size;
    }


    /**
     * @brief Turn on/off Packet Loss Concealment
     *
     * @param active True if PLC should be performed
     */
    void set_plc_active(bool active) noexcept
    {
        _plc_active = active;
    }

    /**
     * @brief Get the status of PLC
     *
     * @return True if PLC is active
     */
    bool is_plc_active() noexcept
    {
        return _plc_active;
    }


    /**
     * @brief Main function for audio processing.
     *
     * @param inputs Input buffers
     * @param outputs Output buffers
     * @param is_packet_valid True if input buffers contain data received from the network.
     *                        False if data is missing due to drop packets and should be replaced by the PLC algorithm.
     */
    virtual void process(const float* const * inputs, float** outputs, bool is_packet_valid) noexcept
    {
        if (is_packet_valid)
        {
            for (int channel = 0; channel < n_audio_channels; channel++)
            {
                std::copy(inputs[channel], inputs[channel] + _buffer_size, outputs[channel]);
            }
        }
        else
        {
            for (int channel = 0; channel < n_audio_channels; channel++)
            {
                std::fill(outputs[channel], outputs[channel] + _buffer_size, 0.0f);
            }
        }
    }


private:
    bool _plc_active {true};
    int _buffer_size {0};
};
