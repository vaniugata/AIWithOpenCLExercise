#ifndef OPENCL_MGR_H
#define OPENCL_MGR_H

#include <CL/cl.hpp>
#include <vector>
#include <string>

#include "error.hpp"

class OpenCLMgr
{
private:

	cl::Platform _platform;
	std::vector<cl::Device> _devices;
	cl::Context _context;
	cl::Program _program;
	cl::CommandQueue _cmd_queue;
	cl::Kernel _kernel;
	cl::Event _event;

public:
	OpenCLMgr();
	~OpenCLMgr();

	/** Init platform, devices and context */
	void init();
	void build_program_from_source( const std::string& src_path, const std::string& kernel_name );
	void set_idx_range( cl::NDRange global, cl::NDRange local );

	template < typename T > inline 
	cl::Buffer* send_data_to_kernel( unsigned arg_idx, T* data, size_t data_size,
		cl_mem_flags flags, bool blocking, size_t offset = 0 )
	{
		cl::Buffer* buffer = new cl::Buffer( _context, flags, data_size );
		int err = _kernel.setArg( arg_idx, *buffer);
		check_error(err);
		_cmd_queue.enqueueWriteBuffer( *buffer, blocking, offset, data_size, data );
		
		return buffer;
	}

	template < typename T > inline
	T* read_data_from_kernel( cl::Buffer* buffer, size_t data_size, bool blocking, size_t offset ){
		
		T* result = new T[data_size];
		memset( result, 0, data_size );
		_cmd_queue.enqueueReadBuffer( *buffer, blocking, offset, data_size, result, NULL, &_event);

		return result;
	}
};

#endif // OPENCL_MGR_H