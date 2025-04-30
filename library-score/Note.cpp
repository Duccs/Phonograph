#include "Note.h"
#include <vector>

const std::vector<std::string> Note::g_names_flat = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"};

Note::Note() : name(""), duration(0.0) {}

Note::Note(const std::string& full_note) : name(""), duration(0.0) {
    set(full_note);
}

Note::Note(const std::string& name, const double& duration) : name(name), duration(duration) {}

Note::Note(const std::string& name, const std::string& duration_str) : name(name), duration(0.0) {
    setDuration(duration_str);
}

const std::string& Note::getName() const{
    return name;
}

const double& Note::getDuration() const{
    return duration;
}

double Note::getFrequency() const{
    return Frequency::getFrequency(name);
}

void Note::setName(const std::string& name){
    if(Frequency::getFrequency(name) != 0){
        this->name = name;
    }
}

void Note::setDuration(const double duration){
    if(duration > 0.0){
        this->duration = duration;
    }
}

void Note::setDuration(const std::string& duration_str) {
    // Map duration letters to their values
    static const std::map<char, double> duration_map = {
        {'w', WHOLE_NOTE},
        {'h', HALF_NOTE},
        {'q', QUARTER_NOTE},
        {'e', EIGHTH_NOTE},
        {'s', SIXTEENTH_NOTE}
    };

    if (duration_str.length() == 1) {
        auto it = duration_map.find(duration_str[0]);
        if (it != duration_map.end()) {
            duration = it->second;
        }
    } else if (duration_str.length() == 2) {
        auto it = duration_map.find(duration_str[0]);
        if (it != duration_map.end()) {
            if (duration_str[1] == '.') {
                duration = 1.5 * it->second;
            } else if (duration_str[1] == 't') {
                duration = (1.0 / 3.0) * it->second;
            }
        }
    }
    // else do nothing
}

void Note::set(const std::string& full_note) {
    std::string name_part, duration_part;
    splitString(full_note, name_part, duration_part);
    setName(name_part);
    setDuration(duration_part);
}

std::string Note::keyName() const {
    std::string str = this->name;
    int index = 0;
    while (index < str.length() && !std::isdigit(str[index])) {
        index++;
    }

    return str.substr(0, index);
}

int Note::octaveNumber() const{
    std::string str = this->name;
    int index = 0;
    while (index < str.length() && !std::isdigit(str[index])) {
        index++;
    }

    return std::stoi(str.substr(index));
}

unsigned int Note::findKeyPositionFlat() const{
    for (int index = 0; index < g_names_flat.size(); index++) {
        if (g_names_flat[index] == keyName()) {
            return index;
        }
    }

    return g_names_flat.size() + 1;
}

std::string Note::relativeNoteNameFlat(unsigned int semitones) const{
    int octave = octaveNumber();
    unsigned int key_index = findKeyPositionFlat();
    unsigned int new_key_index = (key_index + semitones) % g_names_flat.size();

    // If semitones are 12 or above account for wrapping
    double wrapping = semitones / 12.0;
    if(wrapping >= 1) {
        octave += static_cast<int>(wrapping);
    }

    // Go up an octave
    if (new_key_index < key_index) {
        octave++;
    }

    std::string relative_note_name = g_names_flat[new_key_index] + std::to_string(octave);

    return relative_note_name;
}

void Note::splitString(const std::string& full_note, std::string& name, std::string& duration) {
    name.clear();
    duration.clear();
    if (full_note.empty()) {
        return;
    }
    if (full_note.length() >= 2 && (full_note[1] == 't' || full_note[1] == '.')) {
        duration = full_note.substr(0, 2);
        name = full_note.substr(2);
    } else {
        duration = full_note.substr(0, 1);
        name = full_note.substr(1);
    }
}

std::ostream& operator<<(std::ostream& output_stream, const Note& note) {
    output_stream << note.getDuration() << " " << note.getName() << "(" << note.getFrequency() << ")";
    return output_stream;
}
