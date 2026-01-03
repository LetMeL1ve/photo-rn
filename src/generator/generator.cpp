#include "generator.hpp"
#include "../reader/reader.hpp"

using reader::get_exif_info;

void generate_name(const std::string& pattern, std::string& result) {
    // 1. Tokenize pattern.
    // 2. Get EXIF data.
    // 3. Complete name.

    // Just for debuging.
    FileInfo file_info = get_exif_info("D:\\fotos lumix dc-s5d\\prague-25-12-25\\P1000177.JPG");
    
}
