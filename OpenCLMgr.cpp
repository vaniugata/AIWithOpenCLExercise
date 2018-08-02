#include "OpenCLMgr.h"
#include "KernelParser.h"


OpenCLMgr::OpenCLMgr()
{
}

OpenCLMgr::~OpenCLMgr()
{
    printf("OpenCLMgr destroyed.\n");
}

void OpenCLMgr::init() {

	int err = CL_SUCCESS;

    err = cl::Platform::get( &_platform );
    check_error(err);

    err = _platform.getDevices( CL_DEVICE_TYPE_ALL, &_devices );
    check_error(err);

    _context = cl::Context( _devices[0] );

    _cmd_queue = cl::CommandQueue( _context, _devices[0] );
}

void OpenCLMgr::build_program_from_source( const std::string& src_path, const std::string& kernel_name ){

	int err = CL_SUCCESS;

	KernelParser kernel_data( src_path );
    std::pair<const char*, size_t > kernel_source( kernel_data.data(), kernel_data.length() );
   
    cl::Program::Sources sources;
    sources.push_back( kernel_source );

    _program = cl::Program( _context, sources );
    err = _program.build( _devices );
    check_error(err);

	_kernel = cl::Kernel( _program, kernel_name.c_str(), &err );
	check_error(err);
}

void OpenCLMgr::set_idx_range( cl::NDRange global, cl::NDRange local ){
     
    int err = _cmd_queue.enqueueNDRangeKernel( _kernel, cl::NullRange,
        global, local, NULL, &_event );

    check_error(err);

    _event.wait();
}