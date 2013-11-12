#ifndef  FILE_TREE_H
#define  FILE_TREE_H

#include <map>
#include <set>
#include <string>

#include "file_node.h"

namespace cpp_counter {
class FileTree {
public:
    FileTree(std::string src_dir);
    ~FileTree();

    bool AddSourceFile(std::string src_dir);
    bool AddFilter(std::string suffix) {
        m_filter.insert(suffix);
    }
    bool RemoveFilter(std::string suffix) {
        m_filter.erase(suffix);
    }
    void PrintAll();

private:
    FileTree() {};
    bool FileFilter(std::string filename);
    bool PathFilter(std::string path);
    void ParseSingleFile(std::string& file_path);

private:
    int32_t m_max_depth;
    int32_t m_cur_depth;
    std::set<std::string> m_filter;
    std::map<std::string, FileNode> m_file_tree;
};
}

#endif  // FILE_TREE_H
