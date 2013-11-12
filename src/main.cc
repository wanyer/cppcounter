#include <stdio.h>

#include "file_tree.h"

int main(int argc, char* argv[]) {
    std::string src_dir;
    if (argc < 2) {
        src_dir = "src";
    } else {
        src_dir = argv[1];
    }
    cpp_counter::FileTree file_tree(src_dir);
    file_tree.AddSourceFile(src_dir);
    file_tree.PrintAll();
    return 0;
}
