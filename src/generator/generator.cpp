#include "generator.hpp"
#include "../reader/reader.hpp"

using reader::get_exif_info;

void generate_name(const std::string& pattern, std::string& result, const std::string path) {

    // Getting file info.
    FileInfo file_info = get_exif_info(path);

    // Getting tokens from pattern;
    std::vector<Token> tokens;
    get_tokens(pattern, tokens);

    for (int i = 0; i != tokens.size(); ++i) {
        if (tokens[i].get_type() == TokenType::LITERAL) {
            result += tokens[i].get_text();
            continue;
        }
        std::string val = tokens[i].get_text();
        if (val == "date")
            result += file_info.get_date();
        else if (val == "time")
            result += file_info.get_time();
        else if (val == "camera")
            result += file_info.get_camera();
        else if (val == "focal")
            result += file_info.get_focal_length();
        else if (val == "iso")
            result += std::to_string(file_info.get_iso());
        else if (val == "exp")
            result += file_info.get_exposure().as_string();
        else if (val == "f")
            result += ("F/" + std::to_string(file_info.get_aperture()));

    }
}
