#ifndef  FILE_TREE_H
#define  FILE_TREE_H

#include <map>
#include <set>
#include <string>

#include "file_node.h"

namespace cpp_counter {
class FileTree {
public:
    FileTree();
    FileTree(std::string src_dir);
    ~FileTree();

    bool AddSourceFile(std::string src_dir);
    bool AddFilter(std::string suffix) {
        m_filter.insert(suffix);
    }
    bool RemoveFilter(std::string suffix) {
        m_filter.erase(suffix);
    }

private:
    bool FileFilter(std::string filename);
    bool PathFilter(std::string path);
    bool SplitPath(std::string& full_path,
                   std::string* last_part,
                   std::string* rest_part = NULL);
    std::string GetSuffix(std::string filename);

private:
    std::set<std::string> m_filter;
    std::map<std::string, FileNode> m_file_tree;
};
}

#endif  // FILE_TREE_H
