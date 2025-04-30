#ifndef _NOTE_H_
#define _NOTE_H_

#include "Frequency.h"
#include <ostream>
#include <string>
#include <vector>

constexpr double SIXTEENTH_NOTE = 0.125/2.0;
constexpr double EIGHTH_NOTE = 0.125;
constexpr double QUARTER_NOTE = 0.25;
constexpr double HALF_NOTE = 0.50;
constexpr double WHOLE_NOTE = 1.00;

class Note {
    protected:
        std::string name;
        double duration;
        static const std::vector<std::string> g_names_flat;

    public:
        Note();
        Note(const std::string& full_note);
        Note(const std::string& name, const double& duration);
        Note(const std::string& name, const std::string& duration_str);

        const std::string& getName() const;
        const double& getDuration() const;
        double getFrequency() const;

        void setName(const std::string& name);
        void setDuration(const double duration);
        void setDuration(const std::string& duration_str);
        void set(const std::string& full_note);

        // Note Run Task
        std::string keyName() const;
        int octaveNumber() const;
        unsigned int findKeyPositionFlat() const;
        std::string relativeNoteNameFlat(unsigned int semitones) const;

    protected:
        void splitString(const std::string& full_note, std::string& name, std::string& duration);
};

std::ostream& operator<<(std::ostream& output_stream, const Note& note);

#endif /* _NOTE_H_ */
