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
 * File:   non_copyable_sink.hpp
 * Author: alex
 *
 * Created on October 10, 2015, 2:04 PM
 */

#ifndef STATICLIB_IO_TEST_NON_COPYABLE_SINK_HPP
#define STATICLIB_IO_TEST_NON_COPYABLE_SINK_HPP

class non_copyable_sink {
    size_t count = 0;
    
public:

    non_copyable_sink() { }

    non_copyable_sink(const non_copyable_sink&) = delete;

    non_copyable_sink& operator=(const non_copyable_sink&) = delete;

    non_copyable_sink(non_copyable_sink&&) = delete;

    non_copyable_sink& operator=(non_copyable_sink&&) = delete;

    std::streamsize write(sl::io::span<const char> span) {
        count += span.size();
        return span.size_signed();
    }

    std::streamsize flush() {
        return 0;
    }
    
    size_t get_count() {
        return count;
    }

};

#endif /* STATICLIB_IO_TEST_NON_COPYABLE_SINK_HPP */

