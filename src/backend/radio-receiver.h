/*
 *    Copyright (C) 2018
 *    Matthias P. Braendli (matthias.braendli@mpb.li)
 *
 *    Copyright (C) 2017
 *    Albrecht Lohofener (albrechtloh@gmx.de)
 *
 *    This file is based on SDR-J
 *    Copyright (C) 2010, 2011, 2012
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *
 *    This file is part of the welle.io.
 *    Many of the ideas as implemented in welle.io are derived from
 *    other work, made available through the GNU general Public License.
 *    All copyrights of the original authors are recognized.
 *
 *    welle.io is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    welle.io is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with welle.io; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef RADIO_RECEIVER_H
#define RADIO_RECEIVER_H

#include <memory>
#include <string>
#include "radio-controller.h"
#include "fic-handler.h"
#include "msc-handler.h"
#include "ofdm/ofdm-processor.h"

class RadioReceiver {
    public:
        RadioReceiver(
                RadioControllerInterface& rci,
                InputInterface& input,
                const std::string& mscFileName,
                const std::string& mp2FileName);

        /* Restart the receiver, and specify if we want
         * to scan or receive. */
        void restart(bool doScan);

        audiodata_t getAudioServiceData(const std::string& label);

        void selectAudioService(const audiodata_t& ad);

    private:
        RadioControllerInterface& rci;
        InputInterface& input;

        DABParams params;

        MscHandler mscHandler;
        FicHandler ficHandler;
        OFDMProcessor ofdmProcessor;
};

#endif