#include "file_tree.h"

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

namespace cpp_counter {
FileTree::FileTree() {

}

FileTree::FileTree(std::string src_dir) {
    AddFilter("cc");
    AddFilter("h");
    AddSourceFile(src_dir);
}

FileTree::~FileTree() {

}

bool FileTree::AddSourceFile(std::string src_dir) {
    if (!PathFilter(src_dir)) {
        return false;
    }

    struct stat st;
    if (stat(src_dir.c_str(), &st) != 0) {
        std::string error_msg = "cannot stat " + src_dir;
        perror(error_msg.c_str());
        return false;
    }
    if (S_ISDIR(st.st_mode)) {
        std::cout << "dir: " << src_dir << std::endl;
        DIR* cur_dir = opendir(src_dir.c_str());
        struct dirent* ent;
        while ((ent = readdir(cur_dir)) != NULL) {
            std::string child_path = src_dir + "/" + ent->d_name;
            AddSourceFile(child_path.c_str());
        }
    } else if (S_ISREG(st.st_mode)) {
        if (FileFilter(src_dir)) {
            std::cout << "file: " << src_dir << std::endl;
        } else {
            std::cout << "wrong file: " << src_dir << std::endl;
        }
    } else {
        std::cout << "wrong file mode" << std::endl;
    }

    return true;
}

bool FileTree::PathFilter(std::string path) {
    if (access(path.c_str(), R_OK) != 0) {
        perror("unaccessable path ");
        return false;
    }

    // skip hidden files
    if (path[0] == '.') {
        return false;
    }

    // skip current directory and parent directory
    std::string last_part;
    SplitPath(path, &last_part);
    if (last_part == "." || last_part == "..") {
        return false;
    }
    return true;
}

bool FileTree::FileFilter(std::string filename) {
    if (m_filter.find(GetSuffix(filename)) != m_filter.end()) {
        return true;
    }
    return false;
}

bool FileTree::SplitPath(std::string& full_path,
                         std::string* last_part,
                         std::string* rest_part) {
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

std::string FileTree::GetSuffix(std::string filename) {
    std::string::size_type pos = filename.rfind(".");

    if (pos != std::string::npos) {
        return filename.substr(pos + 1);
    }
    return "";
}

}
