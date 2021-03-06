/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   io_exception.hpp
 * Author: alex
 *
 * Created on January 20, 2017, 10:01 PM
 */

#ifndef STATICLIB_IO_IO_EXCEPTION_HPP
#define STATICLIB_IO_IO_EXCEPTION_HPP

#include "staticlib/support.hpp"

namespace staticlib {
namespace io {

/**
 * Module specific exception
 */
class io_exception : public sl::support::exception {
public:
    /**
     * Default constructor
     */
    io_exception() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    io_exception(const std::string& msg) :
    sl::support::exception(msg) { }

};

}
} //namespace

#endif /* STATICLIB_IO_IO_EXCEPTION_HPP */

