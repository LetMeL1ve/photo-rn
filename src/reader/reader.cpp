#include "reader.hpp"
#include "exiv2/exiv2.hpp"

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

void get_exif_info(const std::string& path, FileInfo& file_info) {
    try {
        auto image = Exiv2::ImageFactory::open(path);
        image->readMetadata();

        Exiv2::ExifData& data = image->exifData();

        auto value = get_value_safe(data, "Exif.Image.Copyright");
        
    } catch (Exiv2::Error& e) {
        throw "Unable to read EXIF data.";
    }
}