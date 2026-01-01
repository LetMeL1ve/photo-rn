#pragma once
#include <string>

class FileInfo {
private:
    std::string date;
    std::string time;
    std::string camera;
    int iso;
    float exposure;
    float aperture;

public:
    // Getters 
    std::string get_date() const { return date; }
    std::string get_time() const { return time; }
    std::string get_camera() const { return camera; }
    int get_iso() const { return iso; }
    float get_exposure() const { return exposure; }
    float get_aperture() const { return aperture; }

    // Setters
    void set_date(std::string val) { date = val; }
    void set_time(std::string val) { time = val; }
    void set_camera(std::string val) { camera = val; }
    void set_iso(int val) { iso = val; }
    void set_exposure(float val) { exposure = val; }
    void set_aperture(float val) { aperture = val; }
};