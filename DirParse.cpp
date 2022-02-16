

#include <iostream>
#include "dirparser.h"
int main()
{
    Dirparser parser;
    std::string _pathname;
    std::string recursiveflag;


    std::cout << "enter directory path : ";
    std::cin >> _pathname;
    std::cout << std::endl;
    if (parser.check_if_path_exists(_pathname)) {

        parser.set_path(_pathname);
        std::cout << "do you want to make recursive search ? : y/n ";
        std::cin >> recursiveflag;
        std::cout << std::endl;

        if (recursiveflag == "yes" || recursiveflag == "y" || recursiveflag == "YES" || recursiveflag == "Y")
            parser.parse_all_recursive();
        else
            parser.parse_all_single_dir();
    }
    else {
        std::cout << "path is not valid" << std::endl;
    }
    return 1;
}

