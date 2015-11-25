///////////////////////////////////////////////////////////////////////////////////
// SoftFM - Software decoder for FM broadcast radio with stereo support          //
//                                                                               //
// Copyright (C) 2015 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_HACKRFSOURCE_H_
#define INCLUDE_HACKRFSOURCE_H_

#include <cstdint>
#include <string>
#include <vector>
#include "libhackrf/hackrf.h"

#include "Source.h"

class HackRFSource : public Source
{
public:

    //static const int default_block_length = 65536;

    /** Open HackRF device. */
    HackRFSource(int dev_index);

    /** Close HackRF device. */
    virtual ~HackRFSource();

    virtual bool configure(std::string configuration);

    /** Return current sample frequency in Hz. */
    virtual std::uint32_t get_sample_rate();

    /** Return device current center frequency in Hz. */
    virtual std::uint32_t get_frequency();

    /** Print current parameters specific to device type */
    virtual void print_specific_parms();

    /**
     * Fetch a bunch of samples from the device.
     *
     * This function must be called regularly to maintain streaming.
     * Return true for success, false if an error occurred.
     */
    virtual bool get_samples(IQSampleVector& samples);

    /** Return true if the device is OK, return false if there is an error. */
    virtual operator bool() const
    {
        return m_dev && m_error.empty();
    }

    /** Return a list of supported devices. */
    static void get_device_names(std::vector<std::string>& devices);

private:
    /**
     * Configure HackRF tuner and prepare for streaming.
     *
     * sample_rate  :: desired sample rate in Hz.
     * frequency    :: desired center frequency in Hz.
     * ext_amp      :: extra amplifier engaged
     * lna_gain     :: desired LNA gain: 0, 3 or 6 dB.
     * vga1_gain    :: desired VGA1 gain:
     * vga2_gain    :: desired VGA1 gain:
     *
     * Return true for success, false if an error occurred.
     */
    bool configure(std::uint32_t sample_rate,
                   std::uint32_t frequency,
				   bool ext_amp,
                   int lna_gain,
                   int vga1_gain,
                   int vga2_gain,
    );

    struct hackrf_device* m_dev;;
};

#endif /* INCLUDE_HACKRFSOURCE_H_ */