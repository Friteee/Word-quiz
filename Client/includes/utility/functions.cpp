
#include <sstream>
#include <vector>
namespace utility
{

/**
 * Gets a string and gets all numbers from it
 */
std::vector<int> get_numbers_from_string(std::string searched)
{
    int buffer;
    char comma;
    std::stringstream stream;
    std::vector<int> returned;
    stream<<searched;
    while(stream>>buffer)
    {
        returned.push_back(buffer);
        stream>>comma;
    }
    return returned;
}

/**
 * Gets a string and extracts all string from it
 */
std::vector<std::string> get_separated_strings(std::string searched)
{
    std::vector<std::string> returned;
    char delim = ',';
    std::stringstream ss(searched);
    std::string item;
    while (std::getline(ss, item, delim)) {
        returned.push_back(item);
    }
    return returned;
}

}// end of namespace utility
