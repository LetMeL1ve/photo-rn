#include "generator.hpp"
#include "../reader/reader.hpp"

using reader::get_exif_info;

void append_by_placeholder(const std::string& ph, FileInfo& file_info, std::string& result, bool brute) {
    const std::string unknown = "unknown";
    
    if (ph == "date") {
        bool has_value = !file_info.get_date().empty();
        if (has_value)
            result += file_info.get_date();
        else if (brute)
            throw "Missing argument: date (-brute).";
        else    
            result += unknown;
    } else if (ph == "time") {
        bool has_value = !file_info.get_time().empty();
        if (has_value)
            result += file_info.get_time();
        else if (brute)
            throw "Missing argument: time. (-brute)";
        else    
            result += unknown;
    } else if (ph == "camera") {
        bool has_value = !file_info.get_camera().empty();
        if (has_value)
            result += file_info.get_camera();
        else if (brute)
            throw "Missing argument: camera. (-brute)";
        else    
            result += unknown;
    } else if (ph == "exp") {
        bool has_value = file_info.get_exposure().has_value();
        if (has_value)
            result += file_info.get_exposure().as_string();
        else if (brute)
            throw "Missing argument: exposure (-brute).";
        else    
            result += unknown;
    } else if (ph == "iso") {
        bool has_value = file_info.has_iso();
        if (has_value)
            result += std::to_string(file_info.get_iso());
        else if (brute)
            throw "Missing argument: iso. (-brute)";
        else    
            result += unknown;
    } else if (ph == "f") {
        bool has_value = file_info.has_aperture();
        if (has_value)
            result += ("F/" + std::to_string(file_info.get_aperture()));
        else if (brute)
            throw "Missing argument: aperture. (-brute)";
        else    
            result += unknown;
    } else if (ph == "focal") {
        bool has_value = file_info.has_focal_length();
        if (has_value)
            result += std::to_string(file_info.get_focal_length());
        else if (brute)
            throw "Missing argument: focal length. (-brute)";
        else    
            result += unknown;
    } else {
        if (brute)
            throw "Invalid placeholder: " + ph + ". (-brute)";
        else
            result += unknown;
    }
}

void generate_name(const std::string& pattern, std::string& result, const std::string path, bool brute) {

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
        append_by_placeholder(tokens[i].get_text(), file_info, result, brute);
    }
}
