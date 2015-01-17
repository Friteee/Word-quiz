#include "configuration.h"
#include <fstream>
#include <string>
#include <vector>

namespace utility
{


/**
 * Function to initialize configuration (REALLY??)
 * Returns true on success and false on failure(mainly if file is not found)
 */
Configuration::Configuration(std::string filename)
{
    std::string buffer;
    std::pair<std::string,std::string> string_pair;
    std::ifstream cfg;
    std::size_t first_word_letter = 0 , last_word_letter = 0;
    cfg.open(filename.c_str() , std::ifstream::in);
    if(!cfg.is_open())
    {
        printf("Warning, there is no file named %s\n",filename.c_str());
    }
    while(!cfg.eof())
    {
        std::getline(cfg,buffer);
        // use # as commentary
        std::size_t position = buffer.find('#');
        if(position != std::string::npos)
            buffer.erase(position,std::string::npos);
        // find = in the cfg
        position = buffer.find('=',0);
        // if = not found, read next line until we find normal cfg line
        if(position == std::string::npos)
            continue;
        // extract two strings separated by =
        string_pair.first = buffer.substr(0,position);
        string_pair.second = buffer.substr(position+1 , position - buffer.length());
        // remove spaces from first word
        first_word_letter = string_pair.first.find_first_not_of(' ');
        string_pair.first = string_pair.first.substr(first_word_letter , string_pair.first.length());
        last_word_letter = string_pair.first.find_last_not_of(' ' );
        string_pair.first = string_pair.first.substr(0 , last_word_letter+1);
        // remove spaces from second word
        first_word_letter = string_pair.second.find_first_not_of(' ');
        string_pair.second = string_pair.second.substr(first_word_letter , string_pair.second.length());
        last_word_letter = string_pair.second.find_last_not_of(' ' );
        string_pair.second = string_pair.second.substr(0 , last_word_letter+1);
        // push the pair into vector
        config.push_back(string_pair);

    }
}

/**
 * Function to find a string in a vector, containing configurations
 * Returns ONE string if the searched value is found
 * Else returns 'NOT FOUND'
 */
std::string Configuration::find_string(std::string searched)
{
    for(auto & found : config)
    {
        if(found.first == searched)
        {
            return found.second;
        }
    }
    return "NOT FOUND";
}

/**
 * Function to find strings in a vector, containing configurations
 * Returns ALL strings if the searched value is found
 * Else returns empty vector
 */
std::vector<std::string> Configuration::find_strings(std::string searched)
{
    std::vector<std::string> returned_values;
    for(auto & found : config)
    {
        if(found.first == searched)
        {
            returned_values.push_back(found.second);
        }
    }
    return returned_values;
}

}//end of utility namespace
