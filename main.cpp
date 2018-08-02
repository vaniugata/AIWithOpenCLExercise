#include <utility>

#include "KernelParser.h"
#include "OpenCLMgr.h"
#include "MNISTData.h"

int main(){

    OpenCLMgr ocl_mgr;
    ocl_mgr.init();
    ocl_mgr.build_program_from_source("./backprop.ocl", "backpropagate");

    float data1[] = {-12,2,3,4,5,6};

    MNISTData data_set;
    uc*** training_data = data_set.ReadImages("./DataSet/train-images-idx3-ubyte");
    uc* training_labels = data_set.ReadLabels("./DataSet/train-labels-idx1-ubyte");

    cl::Buffer* buffer1 = ocl_mgr.send_data_to_kernel( 0, data1, sizeof(data1), CL_MEM_READ_WRITE, true );
    ocl_mgr.set_idx_range( cl::NDRange(10), cl::NDRange(1) );

    float* result = ocl_mgr.read_data_from_kernel<float>( buffer1, sizeof(data1), false, 0 );
    
    for(size_t i = 0; i < sizeof(data1)/sizeof(data1[0]); i++){
        printf("%f ", result[i] );
    }
    printf("\n");

    delete[] result;
    delete buffer1;

    return 0;
}