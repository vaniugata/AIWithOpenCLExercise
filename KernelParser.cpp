#include "KernelParser.h"

#include <iostream>
#include <fstream>

KernelParser::KernelParser() :
	_source_str()
{}

KernelParser::KernelParser( const std::string& path ){
	
	read_file( path );
}

KernelParser::~KernelParser(){
	std::cout << "KernelParser destroyed.\n";
}

void KernelParser::read_file( const std::string& path ){

	std::ifstream file( path.c_str() );
	
	if( !file.is_open() ){
		std::cerr << "Failed to open file: " << path << "\n";
		return;
	}

	std::string line;
	while( getline( file, line ) ){
		_source_str.append( line + "\n"  );
	}
}