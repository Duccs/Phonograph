#ifndef _MULTI_TRACK_CREATOR_AUX_H_
#define _MULTI_TRACK_CREATOR_AUX_H_
#include "wav_file_creator_aux.h"
#include "audio_track_creator_aux.h"

void multi_track_configure_audio_track_and_wav_file(ApplicationData& app_data);
void multi_track_fill_channels(ApplicationData& app_data);
int multi_track_creator(ApplicationData& app_data);

#endif /* _MULTI_TRACK_CREATOR_AUX_H_ */