#include <iostream>
#include <cassert>
#include <string>
#include "lib/algorithm/KMP.h"

int main()
{
    std::string tar;
    std::string mod;
    std::cin >> tar >> mod;
    std::cout << kmpStr(tar, mod) << std::endl;
}