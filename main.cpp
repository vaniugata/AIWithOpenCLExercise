#include <utility>

#include "KernelParser.h"
#include "OpenCLMgr.h"

int main(){

    OpenCLMgr ocl_mgr;
    ocl_mgr.init();
    ocl_mgr.build_program_from_source("./backprop.ocl", "backpropagate");

    float data1[] = {-12,2,3,4,5,6};
    // size_t size = sizeof(data) / sizeof(*data);
    float data2[] = {1,2,3,4,5,6};


    cl::Buffer* buffer1 = ocl_mgr.send_data_to_kernel( 0, data1, sizeof(data1), CL_MEM_READ_WRITE, true );
    cl::Buffer* buffer2 = ocl_mgr.send_data_to_kernel( 1, data2, sizeof(data2), CL_MEM_READ_WRITE, true );

    ocl_mgr.set_idx_range( cl::NDRange(10), cl::NDRange(1) );

    float* result = ocl_mgr.read_data_from_kernel<float>( buffer1, sizeof(data1), false, 0 );
    
    for(size_t i = 0; i < sizeof(data1)/sizeof(data1[0]); i++){
        printf("%f ", result[i] );
    }
    printf("\n");

    delete[] result;
    delete buffer1;
    delete buffer2;

    return 0;
}