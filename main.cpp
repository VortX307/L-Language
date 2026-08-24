#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: interpreter.exe <script_name>\n";
        return 1;
    }

    std::string file_name = argv[1];

    std::ifstream file(file_name);
    std::stringstream buffer;

    buffer << file.rdbuf();

    std::string source_code = buffer.str();
    std::cout << source_code;

    return 0;
}
