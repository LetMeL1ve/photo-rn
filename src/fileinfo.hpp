#pragma once
#include <string>

// This class is used for exposure inside FileInfo class.
class Exposure {
private:
    unsigned int numerator;
    unsigned int denominator;
    bool given;
public:
    Exposure() {}
    Exposure(bool _given, unsigned int _numerator, unsigned int _denominator) 
    : numerator(_numerator), denominator(_denominator), given(_given) {}

    bool has_value() const { return given; }

    std::string as_string() const { return numerator + "/" + denominator; }

    float as_float() const { return numerator * 1.0f / denominator; }
};

// This class stores EXIF data. It is used for sending data from ```reader.cpp``` to ```generator.cpp```.
class FileInfo {
private:
    std::string date;  // DD-MM-YYYY
    std::string time;  // HH-mm-SS
    std::string camera;  // Camera make and model
    Exposure exposure;
    unsigned int iso;
    unsigned int focus_length; 
    float aperture;

    bool iso_given, focus_length_given, aperture_given;  // Flags for checking were parameters given.

public:
    // Constructor
    FileInfo(std::string, std::string, std::string, Exposure, unsigned int, bool, unsigned int, bool, float, bool);

    std::string get_date() const { return date; }
    std::string get_time() const { return time; }
    std::string get_camera() const { return camera; }
    Exposure& get_exposure() { return exposure; }

    bool has_focal_length() const { return focus_length_given; }
    unsigned int get_focal_length() const { return focus_length;}

    bool has_iso() const { return iso_given; }
    unsigned int get_iso() const { return iso; }

    bool has_aperture() const { return aperture_given; }
    float get_aperture() const { return aperture; }
};