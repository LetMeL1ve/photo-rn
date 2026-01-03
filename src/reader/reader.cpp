#include "reader.hpp"
#include <numeric>  // For std::gcd in get_exposure
#include "exiv2/exiv2.hpp"

namespace reader {

std::string get_value_safe(Exiv2::ExifData& data, const std::string& key) {
    try {
        auto it = data.findKey(Exiv2::ExifKey(key));
        if (it == data.end() || it->toString().empty())
            return "N/A";  
        else
            return it->toString();
    } catch (Exiv2::Error& e) {
        return "N/A";
    }
}

void get_datetime(std::string& date, std::string& time, Exiv2::ExifData& data) {
    std::string raw_datetime = get_value_safe(data, "Exif.Photo.DateTimeOriginal");  // Reading values

    int space_idx = raw_datetime.find(' '); // Getting separator position.

    if (space_idx = std::string::npos)  // Throwing an exception if data are invalid.
        throw "Unable to read DateTimeOriginal.";


    // Setting values.
    date = raw_datetime.substr(0, space_idx);
    time = raw_datetime.substr(space_idx + 1, raw_datetime.size() - space_idx);
}

void get_exposure(Exposure& exposure, Exiv2::ExifData& data) {
    Exiv2::Exifdatum raw_exposure = data["Exif.Photo.ExposureTime"]; // Reading values.

    // Converting into rational.
    Exiv2::Rational rational = raw_exposure.toRational();

    // Getting GCD
    int gcd = std::gcd(rational.first, rational.second);

    // 
    unsigned int numerator = rational.first / gcd;
    unsigned int denominator = rational.first / gcd;

    // Setting values
    exposure = Exposure(numerator, denominator);
}

void get_camera(std::string& camera, Exiv2::ExifData& data) {
    std::string make = get_value_safe(data, "Exif.Image.Make"), model = get_value_safe(data, "Exif.Image.Model");
    camera = (make != "N/A" ? make : "") + ( model != "N/A" ? model : ""); 
}

bool get_iso(unsigned int& iso, Exiv2::ExifData& data) {
    try {
        auto raw_iso = data["Exif.Photo.ISOSpeedRatings"];
        iso = raw_iso.toInt64();  
    } catch (Exiv2::Error& e) {
        return false;
    }
    return true;
}

bool get_focous_length(unsigned int& focus_length, Exiv2::ExifData& data) {
    try {
        auto raw_focus_length = data["Exif.Photo.ISOSpeedRatings"];
        focus_length = raw_focus_length.toInt64();  
    } catch (Exiv2::Error& e) {
        return false;
    }
    return true;
}

bool get_aperture(float& aperture, Exiv2::ExifData& data) {
    try {
        auto raw_aperture = data["Exif.Photo.FNumber"];
        aperture = raw_aperture.toFloat();
    } catch (Exiv2::Error& e) {
        return false;
    }
    return true;
}

FileInfo& get_exif_info(const std::string& path) {
    try {
        auto image = Exiv2::ImageFactory::open(path);
        image->readMetadata();

        Exiv2::ExifData& data = image->exifData();

        // Creating all variables for FileInfo constructor.
        std::string date, time, camera;
        Exposure exposure;
        unsigned int iso, focus_length;
        float aperture;
        bool iso_given, focus_length_given, aperture_given;

        
        // Getting values for variables.
        get_datetime(date, time, data);
        get_camera(camera, data);
        get_exposure(exposure, data);
        iso_given = get_iso(iso, data);
        focus_length_given = get_focous_length(focus_length, data);
        aperture_given = get_aperture(aperture, data);


        FileInfo file_info(
            date,
            time,
            camera,
            exposure,
            iso, iso_given,
            focus_length, focus_length_given,
            aperture, aperture_given
        );

        return file_info;

    } catch (Exiv2::Error& e) {
        throw "Unable to read EXIF data.";
    }
}
}