#include "reader.hpp"
#include "exiv2/exiv2.hpp"
#include <map>

void get_exiv_info(const std::string& path, std::map<std::string, int>) {
    try {
        auto image = Exiv2::ImageFactory::open(path);
        image->readMetadata();

        Exiv2::ExifData& data = image->exifData();


    } catch (Exiv2::Error& e) {

    }
}