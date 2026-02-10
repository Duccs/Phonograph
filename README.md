
# Phonograph

A C++ command-line application for composing, editing, and rendering musical scores to WAV audio files. Define waveforms, envelopes, and instruments, arrange notes on staves, and export compositions as playable `.wav` files, all from the terminal.

## Features

- **Score Composition**: Create and edit musical scores with configurable time signatures and tempo
- **Waveform Synthesis**: Generate audio using Sine, Square, and Triangle waveforms with adjustable amplitude
- **Envelope Shaping**: Shape sound dynamics with AD (Attack-Decay) and ADSR (Attack-Decay-Sustain-Release) envelopes
- **Instrument Design**: Build instruments by pairing any waveform with any envelope
- **Multi-Staff Arrangement**: Compose across multiple staves, each with its own instrument assignment
- **Note Entry**: Add individual notes or runs of notes to staves
- **Score File I/O**: Read and write scores using a human-readable `.score` file format
- **WAV Export**: Render completed scores to WAV audio files with configurable sample rate and bit depth

## Building

### Prerequisites

- C++ compiler with C++11 support
- `make`

### Compile

```bash
make
```

This builds all libraries and the main `score_editor` executable (located in `program-score-editor/`).

To clean all build artifacts:

```bash
make clean
```


## Usage

Run the score editor:

```bash
./program-score-editor/score_editor
```

The application provides an interactive menu-driven interface. Available commands are:

| Command | Description |
|---|---|
| `score-read` | Read a score from a `.score` file |
| `score-write` | Write the current score to a file |
| `score-render` | Render the score to a `.wav` file |
| `score-set-tempo` | Set beats per minute |
| `score-set-time-signature` | Set beats per bar and beat value |
| `score-add-waveform` | Add a waveform (sine, square, triangle) |
| `score-edit-waveform` | Edit an existing waveform's amplitude |
| `score-list-waveforms` | List all waveforms in the score |
| `score-add-envelope` | Add an envelope (AD or ADSR) |
| `score-edit-envelope` | Edit an existing envelope |
| `score-list-envelopes` | List all envelopes in the score |
| `score-add-instrument` | Create an instrument from a waveform + envelope |
| `score-edit-instrument` | Change an instrument's waveform or envelope |
| `score-list-instruments` | List all instruments |
| `score-build-all-instruments` | Auto-generate instruments for every waveform/envelope combination |
| `score-add-staff` | Add a new staff with an assigned instrument |
| `score-show-staff` | Display a staff's notes |
| `score-list-staves` | List all staves |
| `score-staff-set-instrument` | Reassign an instrument to a staff |
| `score-staff-add-note` | Add a note to a staff |
| `score-staff-add-note-run` | Add a run of three notes (root + intervals) |


## Score File Format

Created scores can be saved in a simple text-based format (`.score`):

```
SCORE

  WAVEFORM sin1 sine
    AMPLITUDE 0.8
  WAVEFORM-END

  ENVELOPE adsr4 ADSR
    ATTACK-SECONDS 0.016
    DECAY-SECONDS 0.017
    SUSTAIN-AMPLITUDE 0.57
    RELEASE-SECONDS 0.018
  ENVELOPE-END

  INSTRUMENT ins1

    WAVEFORM sin1 sine
    AMPLITUDE 0.8
    WAVEFORM-END

    ENVELOPE ad1 AD
    ATTACK-SECONDS 0.011
    DECAY-SECONDS 0
    SUSTAIN-AMPLITUDE 0
    RELEASE-SECONDS 0
    ENVELOPE-END

  INSTRUMENT-END

SCORE-END
```
