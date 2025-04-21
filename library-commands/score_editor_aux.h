#ifndef _SCORE_EDITOR_AUX_H_
#define _SCORE_EDITOR_AUX_H_

#include "ApplicationData.h"


void readScoreUI(ApplicationData& app);

void listScoreWaveformsUI(ApplicationData& app);
void addScoreWaveformUI(ApplicationData& app);
void editScoreWaveformUI(ApplicationData& app);

void listScoreEnvelopesUI(ApplicationData& app);
void addScoreEnvelopeUI(ApplicationData& app);
void editScoreEnvelopeUI(ApplicationData& app);

int register_score_editor_commands(ApplicationData& app_data);

int score_editor(ApplicationData& app_data);

#endif /* _SCORE_EDITOR_AUX_H_ */