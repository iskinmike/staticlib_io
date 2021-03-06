/*
 * Copyright 2017, alex at staticlibs.net
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
 * File:   negative_read_source.hpp
 * Author: alex
 *
 * Created on January 29, 2017, 2:29 PM
 */

#ifndef STATICLIB_IO_TEST_NEGATIVE_READ_SOURCE_HPP
#define STATICLIB_IO_TEST_NEGATIVE_READ_SOURCE_HPP

class negative_read_source {
public:
    negative_read_source() { }

    std::streamsize read(sl::io::span<char>) {
        return -2;
    }
};

#endif /* STATICLIB_IO_TEST_NEGATIVE_READ_SOURCE_HPP */

