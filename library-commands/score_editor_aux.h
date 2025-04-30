#ifndef _SCORE_EDITOR_AUX_H_
#define _SCORE_EDITOR_AUX_H_

#include "ApplicationData.h"


void readScoreUI(ApplicationData& app);
void writeScoreUI(ApplicationData& app);
void renderScoreUI(ApplicationData& app);

void setScoreTimeSignatureUI(ApplicationData& app);
void setScoreTempoUI(ApplicationData& app);

void listScoreWaveformsUI(ApplicationData& app);
void addScoreWaveformUI(ApplicationData& app);
void editScoreWaveformUI(ApplicationData& app);

void listScoreEnvelopesUI(ApplicationData& app);
void addScoreEnvelopeUI(ApplicationData& app);
void editScoreEnvelopeUI(ApplicationData& app);

void listScoreInstrumentsUI(ApplicationData& app);
void addScoreInstrumentUI(ApplicationData& app);
void editScoreInstrumentUI(ApplicationData& app);

void setStaffInstrumentUI(ApplicationData& app);
void listScoreStavesUI(ApplicationData& app);
void addStaffUI(ApplicationData& app);
void showStaffUI(ApplicationData& app);
void addStaffNoteUI(ApplicationData& app);

// BuildAllInstruments Task
void buildScoreInstrumentFromWaveformAndEnvelopePair(ApplicationData& app, std::shared_ptr<Waveform> w, std::shared_ptr<Envelope> e);
void buildScoreAllPossibleInstrumentsUI(ApplicationData& app);

// AddNoteRun Task
void addStaffNoteRunUI(ApplicationData& app);

int register_score_editor_commands(ApplicationData& app_data);

int score_editor(ApplicationData& app_data);

#endif /* _SCORE_EDITOR_AUX_H_ */