
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

}// end of namespace utility
