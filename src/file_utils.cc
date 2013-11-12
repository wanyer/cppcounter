#include "file_utils.h"

bool SplitPath(std::string& full_path, std::string* last_part, std::string* rest_part) {
    if (full_path.at(full_path.length() - 1) == '/') {
        full_path = full_path.substr(0, full_path.length() - 2);
    }
    std::string::size_type pos = full_path.rfind("/");
    if (pos != std::string::npos) {
        if (rest_part) {
            *rest_part = full_path.substr(0, pos);
        }
        if (last_part) {
            *last_part = full_path.substr(pos + 1);
        }
    } else {
        if (last_part) {
            *last_part = full_path;
        }
    }
    return true;
}

std::string GetFileSuffix(std::string filename) {
    std::string::size_type pos = filename.rfind(".");
    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return "";
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
