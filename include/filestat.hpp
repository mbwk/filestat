#ifndef FILESTAT_HPP
#define FILESTAT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

class filestat
{
public:
    filestat(std::string fpath, int height = 36);
    ~filestat();
    void analyze_file();
    std::string write_info();

private:
    std::ifstream ifs;
    int maxheight = 36;
    std::vector<char> keys;
    std::unordered_map<char, int> char_hash;
    int wordcount = 0;
    int alnumcount = 0;
};

#endif /* FILESTAT_HPP */

