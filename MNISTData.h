#ifndef MNIST_DATA_H
#define MNIST_DATA_H

#include <string>

typedef unsigned char uc;

class MNISTData {

private:
	int _images_num;
	int _labels_num;

public:
	MNISTData();
	~MNISTData();

	uc*** ReadImages( std::string file_path );
	uc* ReadLabels( std::string file_path );
	void Free( uc*** &images, uc* labels );

	inline unsigned GetImagesNum() { return _images_num; }
	inline unsigned GetLabelsNum() { return _labels_num; }

	double* FlattenImage( uint8_t** image );

private:
	int ReverseInt(int n);

};
#endif
