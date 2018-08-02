#include "MNISTData.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>

MNISTData::MNISTData() :
	_images_num(0)
	,_labels_num(0)
{}

MNISTData::~MNISTData() 
{}

uc*** MNISTData::ReadImages(std::string file_path) {
	std::ifstream file(file_path, std::ios::binary);
	if( !file.is_open() ){
		std::cerr << "Error: Failed to load file: " << file_path << "\n";
		return nullptr;
	}
	int magic_number = 0;
	int rows = 0, cols = 0;
	_images_num = 0;

	std::cout << "Reading data...\n";

	file.read( (char*)& magic_number, sizeof(magic_number) );
	magic_number = ReverseInt(magic_number);

	file.read( (char*)& _images_num, sizeof(_images_num) );
	_images_num = ReverseInt(_images_num);

	file.read( (char*)& rows, sizeof(rows) );
	rows = ReverseInt(rows);

	file.read( (char*)& cols, sizeof(cols) );
	cols = ReverseInt(cols);
	
	uc pixel_val = 0;
	uc*** images = new uc**[_images_num];
	for(int n = 0; n < _images_num; n++){
		images[n] = new uc*[rows];
		for(int i = 0; i < rows; i++){
			images[n][i] = new uc[cols];
			for(int j = 0; j < cols; j++){
				file.read( (char*)& pixel_val, sizeof(pixel_val) );
				images[n][i][j] = pixel_val;
			}
		}	
	}
	std::cout << "Done.\n";
	return images;
}

uc* MNISTData::ReadLabels( std::string file_path ) {
	std::ifstream file( file_path, std::ios::binary );
	if( !file.is_open() ){
		std::cerr << "Failed to open: " << file_path << "\n";
		return nullptr;
	}

	int magic_number = 0;
	
	file.read( (char*)& magic_number, sizeof(magic_number) );
	magic_number = ReverseInt( magic_number );

	if( magic_number != 2049){
		std::cerr << "Invalid MNIST label file.\n";
		return nullptr;
	}
	std::cout << "Reading labels...\n"; 
	_labels_num = 0;
	file.read( (char*)& _labels_num, sizeof(_labels_num) );
	
	uc* labels = new uc[_labels_num];
	for(int i = 0; i < _labels_num; i++){
		file.read( (char*)& labels[i], 1 );
	}
	std::cout << "Done.\n";
	return labels;
}

void MNISTData::Free( uc*** &images, uc* labels ) {
	for(int i = 0; i < _images_num; i++){
		for(int j = 0; j < 28; j++){
				delete[] images[i][j];
		}
		delete[] images[i];
	}
	delete[] images;
	delete[] labels;
}

double* MNISTData::FlattenImage( uint8_t** image ){

double* flatten_image = new double[784];

	for( uint8_t i = 0; i < 28; i++ )
		for( uint8_t j = 0; j < 28; j++ )
			flatten_image[ i * 28 + j ] = image[i][j];
		
	return flatten_image;
}


int MNISTData::ReverseInt(int n) {
	uc c1 = n & UCHAR_MAX;
	uc c2 = ( n>>8 ) & UCHAR_MAX;
	uc c3 = ( n>>16 ) & UCHAR_MAX;
	uc c4 = ( n>>24 ) & UCHAR_MAX;

	return ( (int)c1<<24 ) + ( (int)c2<<16 ) + ( (int)c3<<8 ) + c4;
}

