#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include<vector>
#include<string>

namespace utility{

// function to extract variables from a string
// variables here should be separated with a character
extern std::vector<int> get_numbers_from_string(std::string searched);

}
#endif // FUNCTIONS_H_INCLUDED
