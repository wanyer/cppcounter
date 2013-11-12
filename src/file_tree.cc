#include "file_tree.h"

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

#include "file_utils.h"
#include "common.h"

namespace cpp_counter {

FileTree::FileTree(std::string src_dir)
    : m_max_depth(0),
      m_cur_depth(0),
      m_total_lines(0) {
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
//        std::cout << "dir: " << src_dir << std::endl;
        DIR* cur_dir = opendir(src_dir.c_str());
        if (cur_dir == NULL) {
            std::string error_msg = "cannot opendir " + src_dir;
            perror(error_msg.c_str());
            return false;
        }
        m_cur_depth++;
        if (m_cur_depth > m_max_depth) {
            m_max_depth = m_cur_depth;
        }

        // traverse child directories
        struct dirent* ent;
        while ((ent = readdir(cur_dir)) != NULL) {
            std::string child_path = src_dir + "/" + ent->d_name;
            AddSourceFile(child_path.c_str());
        }
        m_cur_depth--;
    } else if (S_ISREG(st.st_mode)) {
        if (FileFilter(src_dir)) {
//            std::cout << "file: " << src_dir << std::endl;
            ParseSingleFile(src_dir);
        } else {
//            std::cout << "wrong file: " << src_dir << std::endl;
        }
    } else {
        std::cout << "wrong file mode" << std::endl;
    }

    return true;
}

void FileTree::ParseSingleFile(std::string& file_path) {
    FileNode file_node(file_path);
    if (file_node.Parse()) {
        std::map<std::string, FileNode>::iterator it;
        if ((it = m_file_tree.find(file_path)) != m_file_tree.end()) {
            m_total_lines -= it->second.GetLines();
        }
        m_total_lines += file_node.GetLines();
        m_file_tree.insert(std::pair<std::string, FileNode>(
                           file_path, file_node));
    } else {
        std::string error_msg = "fail to parse file: " + file_path;
        perror(error_msg.c_str());
    }
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
    if (m_filter.find(GetFileSuffix(filename)) != m_filter.end()) {
        return true;
    }
    return false;
}

void FileTree::PrintAll() {
    Println("Total lines: " << m_total_lines);
    Println("Total files: " << m_file_tree.size());
    Println("Max depth: " << m_max_depth);
    std::map<std::string, FileNode>::iterator it;
    for (it = m_file_tree.begin(); it != m_file_tree.end(); ++it) {
        Println(it->first);
        it->second.Print();
    }
}

}
