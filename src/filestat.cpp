#include "filestat.hpp"

#include <cctype>
#include <algorithm>
#include <sstream>

filestat::filestat(std::string fpath, int height)
{
    this->ifs.open(fpath, std::ios_base::in);
    this->maxheight = height;
}

filestat::~filestat()
{
    this->ifs.~basic_ifstream();
}

void filestat::analyze_file()
{
    bool inword = false;

    while (ifs.good()) {
        if (ifs.eof()) {
            std::cout << "END OF FILE REACHED\n";
        }

        char c;
        ifs.get(c);

        if ( std::isalnum(c) ) {

            ++alnumcount;

            if ( std::find( keys.begin(), keys.end(), c ) != keys.end() ) {
                ++char_hash.at(c);
            } else {
                keys.push_back(c);
                char_hash.emplace(c, 1);
            }

            if ( !inword ) {
                inword = true;
            }

        } else if ( (c == ' ') || (c == '\n') || (c == '\t') ) {

            if ( inword ) {
                inword = false;
                ++wordcount;
            }

        }
    }
    std::cout << "finished analyzing file\n";
}

std::string filestat::write_info()
{
    std::stringstream ss;
    int highest_count = 0;
    int interval = 1;
    for ( const auto &p : char_hash ) {
        if ( p.second > highest_count ) {
            highest_count = p.second;
        }
    }

    interval += highest_count / maxheight;

    int count = highest_count;

    ss << "WORD COUNT: " << wordcount
        << "\tALNUM COUNT: " << alnumcount
        << "\tAVG WORD LENGTH: " << alnumcount / wordcount
        << "\n\n";

    while ( count > 0 ) {
        ss << count;
        if ( count < 100) {
            ss << " ";
        }
        if ( count < 10 ) {
            ss << " ";
        }
        ss << "  |  ";
        for ( const auto &p : char_hash ) {
            if (p.second >= count ) {
                ss << "#";
            } else {
                ss << " ";
            }
            ss << "  ";
        }
        ss << "\n";
        count -= interval;
    }

    ss << "-----+--";
    for ( int i = char_hash.size(); i > 0; --i ) {
        ss << "---";
    }
    ss << "\n";

    ss << "chars:  ";
    for ( const auto &p : char_hash ) {
        ss << p.first << "  ";
    }
    ss << "\n\n";

    return ss.str();
}

