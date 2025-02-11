#pragma once
#include <string>
#include <fstream>
#include "skStr.h"
#include "json.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <android/log.h>

#define LOG_TAG "Kauth"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))

using json = nlohmann::json;

bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::string ReadFromJson(std::string path, std::string section) {
    if (!fileExists(path))
        return skCrypt("File Not Found").decrypt();
    std::ifstream file(path);
    json data = json::parse(file);
    return data[section];
}

bool CheckIfJsonKeyExists(std::string path, std::string section) {
    if (!fileExists(path))
        return skCrypt("File Not Found").decrypt();
    std::ifstream file(path);
    json data = json::parse(file);
    return data.contains(section);
}

bool WriteToJson(std::string path, std::string name, std::string value, bool userpass, std::string name2, std::string value2) {
    json file;
    if (!userpass) {
        file[name] = value;
    } else {
        file[name] = value;
        file[name2] = value2;
    }

    std::ofstream jsonfile(path, std::ios::out);
    jsonfile << file;
    jsonfile.close();
    if (!fileExists(path))
        return false;

    return true;
}

void checkAuthenticated(std::string ownerid) {
    while (true) {
        // Android does not have a direct equivalent to GlobalFindAtomA, so this part needs reimplementation.
        LOGI("Checking authentication for ownerid: %s", ownerid.c_str());
        sleep(1); // thread interval in seconds
    }
}
