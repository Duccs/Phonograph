#ifndef _INSTRUMENT_DESIGNER_AUX_H_
#define _INSTRUMENT_DESIGNER_AUX_H_

#include "ApplicationData.h"

void listWaveformsUI(ApplicationData& app_data);
void addWaveformUI(ApplicationData& app_data);
void editWaveformUI(ApplicationData& app_data);

void listEnvelopesUI(ApplicationData& app_data);
void addEnvelopeUI(ApplicationData& app_data);
void editEnvelopeUI(ApplicationData& app_data);

void listInstrumentsUI(ApplicationData& app_data);
void addInstrumentUI(ApplicationData& app_data);
void editInstrumentUI(ApplicationData& app_data);

void put_frequency_in_register(ApplicationData& app_data);

void configureAudioQualityUI(ApplicationData& app_data);

void configureTrackDurationUI(ApplicationData& app_data);

void recordInstrumentNoteUI(ApplicationData& app_data);

int register_instrument_designer_commands(ApplicationData& app_data);

int instrument_designer(ApplicationData& app_data);

#endif /* _INSTRUMENT_DESIGNER_AUX_H_ */