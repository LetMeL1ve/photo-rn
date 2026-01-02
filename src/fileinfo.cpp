#include "fileinfo.hpp"
#include <limits>

// Main constructor, used in ```reader.cpp```
FileInfo::FileInfo(std::string _date, std::string _time, std::string _camera, Exposure _exposure,
                   unsigned int _iso, bool _iso_given,
                   unsigned int _focus_length, bool _focus_length_given,
                   float _aperture, bool _aperture_given)
                   : date(_date), time(_time), camera(_camera), exposure(_exposure) {
           
    // Setting flags.
    this->aperture_given = _aperture_given;
    this->iso_given = _iso_given;
    this->focus_length_given = _focus_length_given;

    // Setting variables
    if (iso_given) this->iso = _iso;
    if (aperture_given) this->aperture = _aperture;
    if (focus_length_given) this->focus_length = _focus_length;
}
                   