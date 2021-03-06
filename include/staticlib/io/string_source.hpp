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
 * File:   string_source.hpp
 * Author: alex
 *
 * Created on November 6, 2015, 3:59 PM
 */

#ifndef STATICLIB_IO_STRING_SOURCE_HPP
#define STATICLIB_IO_STRING_SOURCE_HPP

#include <ios>
#include <string>
#include <cstdint>
#include <cstring>

#include "staticlib/config.hpp"

#include "staticlib/io/io_exception.hpp"
#include "staticlib/io/span.hpp"

namespace staticlib {
namespace io {

/**
 * Source implementation that reads data from the specified string
 */
class string_source {
    /**
     * Source string
     */
    std::string str;
    /**
     * Current string position
     */
    size_t idx;
    /**
     * String length to read
     */
    size_t str_len;

public:
    /**
     * Constructor
     * 
     * @param str source string
     */
    string_source(std::string&& str) :
    str(std::move(str)),
    idx(0),
    str_len(this->str.length()) { }

    /**
     * Constructor
     * 
     * @param str source string
     */
    string_source(const std::string& str) :
    string_source(std::string(str.data(), str.length())) { }

    /**
     * Constructor
     * 
     * @param str source string
     * @param from start index (inclusive)
     * @param to end index (exclusive)
     */
    string_source(std::string&& str, size_t from, size_t to) :
    str(std::move(str)),
    idx(from),
    str_len(to) { }

    /**
     * Deleted copy constructor
     * 
     * @param other instance
     */
    string_source(const string_source&) = delete;

    /**
     * Deleted copy assignment operator
     * 
     * @param other instance
     * @return this instance 
     */
    string_source& operator=(const string_source&) = delete;

    /**
     * Move constructor
     * 
     * @param other other instance
     */
    string_source(string_source&& other) STATICLIB_NOEXCEPT :
    str(std::move(other.str)),
    idx(other.idx),
    str_len(other.str_len) {
        other.idx = 0;
        other.str_len = 0;
    }

    /**
     * Move assignment operator
     * 
     * @param other other instance
     * @return this instance
     */
    string_source& operator=(string_source&& other) STATICLIB_NOEXCEPT {
        str = std::move(other.str);
        idx = other.idx;
        other.idx = 0;
        str_len = other.str_len;
        other.str_len = 0;
        return *this;
    }

    /**
     * Buffered read implementation
     * 
     * @param span buffer span
     * @return number of bytes processed
     */
    std::streamsize read(span<char> span) {
        size_t ulen = span.size();
        size_t avail = str_len - idx;
        if (avail > 0) {            
            size_t len = ulen <= avail ? ulen : avail;
            std::memcpy(span.data(), std::addressof(str.front()) + idx, len);
            this->idx += len;
            return static_cast<std::streamsize> (len);
        } else return std::char_traits<char>::eof();        
    }

    /**
     * Underlying string accessor
     * 
     * @return underlying string
     */
    std::string& get_string() {
        return str;
    }

};

} // namespace
}

#endif /* STATICLIB_IO_STRING_SOURCE_HPP */

