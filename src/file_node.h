#ifndef  FILE_NODE_H
#define  FILE_NODE_H

#include <string>

namespace cpp_counter {
class FileNode {
public:
    FileNode(std::string file_name);
    ~FileNode();
    bool Parse();
    std::string GetName() {
        return m_filename;
    }

private:
    std::string m_filename;
    std::string m_filepath;
    int32_t m_lines;
};
}
#endif  // FILE_NODE_H
