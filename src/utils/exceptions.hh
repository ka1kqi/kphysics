/*  EXCEPTIONS  */

#ifndef KPHYSICS_SRC_UTILS_EXCEPTIONS_H
#define KPHYSICS_SRC_UTILS_EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>

/************************************************
 * Exception types
 *  voxel_init_exception: thrown when initialization
 *  of voxel fails,
 * 
 * 
 * *********************************************/

class voxel_init_exception : public std::exception {
    char message[1024] = "ERROR: failed to initialize voxel ";
public:
    virtual const char* what() const throw() {
        return message;
    }
} voxel_init_except;


#endif