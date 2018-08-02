#ifndef KERNEL_PARSER_H
#define KERNEL_PARSER_H

#include <string>

class KernelParser {

private:
std::string _source_str;

public:

KernelParser();
KernelParser( const std::string& path );
~KernelParser();

void read_file( const std::string& path );

inline const char* data() { return _source_str.c_str(); }

inline size_t length() { return _source_str.length(); }

};

#endif // !KERNEL_PARSER_H