#include "file_node.h"

#include <iostream>
#include <fstream>

#include "common.h"
#include "file_utils.h"

namespace cpp_counter {
FileNode::FileNode(std::string fullpath) {
    SplitPath(fullpath, &m_filename, &m_filepath);
}

FileNode::~FileNode() {

}

bool FileNode::Parse() {
    m_lines = 0;
    m_chars = 0;
    m_space_lines = 0;
    m_code_lines = 0;
    std::string fullpath = m_filepath + "/" + m_filename;
    std::ifstream ifs(fullpath.c_str(), std::ios::in);
    if (!ifs) {
        std::string err_msg = "open file failed: " + fullpath;
        perror(err_msg.c_str());
        return false;
    }
    char line_buffer[1024];
    while (ifs.getline(line_buffer, sizeof(line_buffer))) {
        ClassifyLine(line_buffer);
        m_lines++;
        m_chars += strlen(line_buffer);
    }
    return true;
}

void FileNode::ClassifyLine(char* line) {
    int32_t len = strlen(line);
    for (int32_t i = 0; i < len; ++i) {
        if (!IsSpaceChar(line[i])) {
            m_code_lines++;
            return;
        }
    }
    m_space_lines++;
}

void FileNode::Print() {
    Println(m_filename);
    Println("{");
    Println("\t" + m_filepath);
    Println("\tlines: " << m_lines);
    Println("\tcode_lines: " << m_code_lines);
    Println("\tspace_lines: " << m_space_lines);
    Println("\tchars: " << m_chars);
    Println("}");
}
}
