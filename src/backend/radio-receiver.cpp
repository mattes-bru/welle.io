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

#include <string>
#include <memory>
#include "radio-receiver.h"

using namespace std;

static constexpr size_t AUDIOBUFFERSIZE = 32768;

RadioReceiver::RadioReceiver(
                RadioControllerInterface& rci,
                InputInterface& input,
                const std::string& mscFileName,
                const std::string& mp2FileName) :
    rci(rci),
    input(input),
    mscFilename(mscFileName),
    mp2Filename(mp2FileName),
    mscHandler(rci, params, false, mscFilename, mp2Filename),
    ficHandler(rci),
    ofdmProcessor(input,
        params,
        rci,
        mscHandler,
        ficHandler,
        3, 3)
{
}

void RadioReceiver::restart(bool doScan)
{
    ofdmProcessor.set_scanMode(doScan);
    mscHandler.stopProcessing();
    ficHandler.clearEnsemble();
    ofdmProcessor.coarseCorrectorOn();
    ofdmProcessor.reset();
}

audiodata_t RadioReceiver::getAudioServiceData(const std::string& label)
{
    return ficHandler.getAudioServiceData(label);
}

void RadioReceiver::selectAudioService(const audiodata_t& ad)
{
    mscHandler.setAudioChannel(ad);
}

void RadioReceiver::selectAudioService(const Service& s)
{
    audiodata_t ad = ficHandler.getAudioServiceData(s.serviceLabel.label);
    mscHandler.setAudioChannel(ad);
}

std::string RadioReceiver::getEnsembleName(void) const
{
    return ficHandler.getEnsembleName();
}

std::vector<Service> RadioReceiver::getServiceList(void) const
{
    return ficHandler.getServiceList();
}
