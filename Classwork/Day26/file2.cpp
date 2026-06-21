// file: directory_demo.cpp

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

// Recursive directory listing
void listDir(const std::string& path, int depth = 0) {
    DIR* dir = opendir(path.c_str());
    if (!dir) { perror(("opendir: " + path).c_str()); return; }

    struct dirent* entry;
    std::vector<std::string> names;

    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;
        names.push_back(name);
    }
    closedir(dir);

    std::sort(names.begin(), names.end());

    for (const auto& name : names) {
        std::string fullPath = path + "/" + name;
        struct stat st;
        lstat(fullPath.c_str(), &st);

        std::string indent(depth * 2, ' ');
        std::cout << indent;

        if (S_ISDIR(st.st_mode)) {
            std::cout << "[DIR]  " << name << "/\n";
            listDir(fullPath, depth + 1);
        } else if (S_ISLNK(st.st_mode)) {
            char target[256] = {0};
            readlink(fullPath.c_str(), target, sizeof(target));
            std::cout << "[LINK] " << name << " → " << target << "\n";
        } else {
            std::cout << "[FILE] " << name
                      << " (" << st.st_size << " bytes)\n";
        }
    }
}


void makeFile(const std::string& path, const std::string& content) {
        int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        write(fd, content.c_str(), content.size());
        close(fd);
    }

int main() {
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║   Directory Operations — Complete Demo   ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n\n";

    // ── 1. Create directory structure ─────────────────────────────────
    std::cout << "─── 1. mkdir ───\n";
    mkdir("testdir",            0755);
    mkdir("testdir/subdir1",    0755);
    mkdir("testdir/subdir2",    0755);
    mkdir("testdir/subdir1/deep", 0755);
    std::cout << "Created testdir/ with subdirs\n";

    // Create some files
    // auto makeFile = [](const std::string& path, const std::string& content) {
    //     int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //     write(fd, content.c_str(), content.size());
    //     close(fd);
    // };
    makeFile("testdir/readme.txt",          "Project readme\n");
    makeFile("testdir/main.cpp",            "int main(){}\n");
    makeFile("testdir/subdir1/util.cpp",    "// utilities\n");
    makeFile("testdir/subdir1/deep/data.bin", "\x00\x01\x02");
    makeFile("testdir/subdir2/config.txt",  "key=value\n");
    symlink("../readme.txt", "testdir/subdir2/readme_link");

    // ── 2. List directory recursively ─────────────────────────────────
    std::cout << "\n─── 2. Directory listing ───\n";
    listDir("testdir");

    // ── 3. opendir / readdir / closedir manually ──────────────────────
    // std::cout << "\n─── 3. Manual readdir ───\n";
    // DIR* dir = opendir("testdir");
    // struct dirent* entry;
    // std::cout << "Direct children of testdir/:\n";
    // while ((entry = readdir(dir)) != nullptr) {
    //     if (entry->d_name[0] == '.') continue;
    //     std::cout << "  d_name=" << entry->d_name;
    //     // d_type (not always available on all filesystems):
    //     switch (entry->d_type) {
    //         case DT_REG:  std::cout << " [regular]";   break;
    //         case DT_DIR:  std::cout << " [directory]"; break;
    //         case DT_LNK:  std::cout << " [symlink]";   break;
    //         default:      std::cout << " [other]";     break;
    //     }
    //     std::cout << "\n";
    // }
    // closedir(dir);

    // // ── 4. getcwd and chdir ───────────────────────────────────────────
    // std::cout << "\n─── 4. getcwd / chdir ───\n";
    // char cwd[1024];
    // getcwd(cwd, sizeof(cwd));
    // std::cout << "Current dir: " << cwd << "\n";

    // chdir("testdir");
    // getcwd(cwd, sizeof(cwd));
    // std::cout << "After chdir to testdir: " << cwd << "\n";

    // chdir("..");   // go back
    // getcwd(cwd, sizeof(cwd));
    // std::cout << "After chdir ..: " << cwd << "\n";

    // // ── 5. rename() ───────────────────────────────────────────────────
    // std::cout << "\n─── 5. rename ───\n";
    // rename("testdir/readme.txt", "testdir/README.md");
    // std::cout << "Renamed readme.txt → README.md\n";

    // // ── 6. Cleanup: remove directory tree ─────────────────────────────
    // std::cout << "\n─── 6. Cleanup ───\n";
    // unlink("testdir/subdir2/readme_link");
    // unlink("testdir/subdir2/config.txt");
    // rmdir("testdir/subdir2");
    // unlink("testdir/subdir1/deep/data.bin");
    // rmdir("testdir/subdir1/deep");
    // unlink("testdir/subdir1/util.cpp");
    // rmdir("testdir/subdir1");
    // unlink("testdir/main.cpp");
    // unlink("testdir/README.md");
    // rmdir("testdir");
    // std::cout << "Cleaned up testdir/\n";

    return 0;
}