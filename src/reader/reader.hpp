#pragma once
#include "../fileinfo.hpp"
#include <string>

namespace reader {
// Main method of reading EXIF values.
// ```path``` => path to the image.
FileInfo& get_exif_info(const std::string&);
}