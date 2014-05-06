#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include "filestat.hpp"

namespace po = boost::program_options;

bool ask_if_continue(std::string topic)
{
    int invalids = 0;
    std::string response;
    std::cout << "would you like to " << topic << "? (y/n): ";
    do {
        response = std::cin.get();
        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
        if ( response.at(0) == 'y' ) {
            return true;
        } else if ( response.at(0) == 'n' ) {
            return false;
        } else {
            std::cout << "please enter [y]es or [n]o:";
            ++invalids;
        }
    } while (invalids < 5);
    std::cout << "\n!!! 消える !!!\n";
    return false;
}

int main( int argc, char** argv )
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,H", "produce help message")
        ("infile,i", po::value<std::string>(), "specify input file")
        ("height,h", po::value<int>(), "specify max height of info printed to screen")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line( argc, argv, desc), vm );
    po::notify( vm );

    if ( vm.count("help") ) {
        std::cout << desc << "\n\n";
        std::cout
            << "anumcount is a program designed to read all characters in a given text file,\n"
            << "record which characters appear, how many times each recorded character appears,\n"
            << "and produce a bar graph\n\n";
        return 1;
    }

    std::string input_file;
    if ( vm.count("infile") ) {
        try {
            input_file = vm["infile"].as<std::string>();
        } catch (std::exception &e) {
            std::cerr << "コンソールの入力が読みません：" << e.what() << std::endl;
            input_file = "exception.txt";
        }
    } else {
        std::cout << "no input file specified\n";
        if ( !ask_if_continue("specify a file") )
        {
            return 1;
        }
        std::cout << "please enter file name: ";
        std::cin >> input_file;
    }
    std::cout << "input file: " << input_file << std::endl;

    int maxheight;
    if ( vm.count("height") ) {
        maxheight = vm["height"].as<int>();
    } else {
        maxheight = 36;
    }
    std::cout << "max height: " << maxheight << std::endl;

    filestat fs(input_file, maxheight);
    fs.analyze_file();
    std::string info = fs.write_info();

    std::cout << info;

    return 0;
}

