#ifndef ERROR_H
#define ERROR_H

#include <cstdlib>
#include <cstdio>

inline void check_error( int err ){

    if( err < 0 ){
        printf( "ERROR: %d\n", err );
        exit(1);
    }
}

#endif