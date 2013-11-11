#include "file_node.h"

namespace cpp_counter {
FileNode::FileNode(std::string filename)
    :m_filename(filename) {
}

FileNode::~FileNode() {

}

bool FileNode::Parse() {
    return true;
}
}
