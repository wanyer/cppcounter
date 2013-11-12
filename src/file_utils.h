#ifndef  FILE_UTILS_H
#define  FILE_UTILS_H

#include <string>

bool SplitPath(std::string& full_path, std::string* last_part, std::string* rest_part = NULL);

std::string GetFileSuffix(std::string filename);

#endif  // FILE_UTILS_H
