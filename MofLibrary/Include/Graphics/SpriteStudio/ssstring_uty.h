#ifndef __SSSTRING_UTY__
#define __SSSTRING_UTY__


#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

void	split_string( const std::string &in_str , 
						const char key, 
						std::vector<std::string>& out_array );
bool	is_digit_string( std::string &in_str , bool* is_priod = 0 );

std::string path2dir(const std::string &path);
std::string path2file(const std::string &path);
std::string getFullPath( const std::string& basePath , const std::string &relPath);
std::string nomarizeFilename( std::string str );

#endif
