#ifndef _INSTRUMENT_TEST_AUX_H_
#define _INSTRUMENT_TEST_AUX_H_

#include "Instrument.h"
#include "ApplicationData.h"

std::shared_ptr<Waveform> choose_waveform(ApplicationData& app_data);

std::shared_ptr<Envelope> choose_envelope(ApplicationData& app_data);

std::shared_ptr<Instrument> create_instrument(ApplicationData& app_data);

void fill_audio_track_from_instrument(ApplicationData& app_data, std::shared_ptr<Instrument> instrument_ptr); 

int instrument_test(ApplicationData& app_data);

#endif /* _INSTRUMENT_TEST_AUX_H_ */