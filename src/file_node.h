#ifndef  FILE_NODE_H
#define  FILE_NODE_H

#include <string>

namespace cpp_counter {
class FileNode {
public:
    FileNode(std::string full_path);
    ~FileNode();
    bool Parse();
    void Print();
    void ClassifyLine(char* line);
    std::string GetName() {
        return m_filename;
    }
    uint32_t GetLines() {
        return m_lines;
    }
    uint32_t GetChars() {
        return m_chars;
    }

private:
    std::string m_filename;
    std::string m_filepath;
    uint32_t m_chars;
    uint32_t m_lines;
    uint32_t m_code_lines;
    uint32_t m_space_lines;
};
}
#endif  // FILE_NODE_H
