#include "file_node.h"

#include <iostream>

#include "file_utils.h"

namespace cpp_counter {
FileNode::FileNode(std::string filepath) {
    SplitPath(filepath, &m_filename, &m_filepath);
    std::cout << "name: " << m_filename
        << " path: " << m_filepath << std::endl;
}

FileNode::~FileNode() {

}

bool FileNode::Parse() {
    return true;
}

}
