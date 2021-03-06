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
 * File:   buffered_sink_test.cpp
 * Author: alex
 *
 * Created on October 10, 2015, 8:39 AM
 */

#include "staticlib/io/buffered_sink.hpp"

#include <iostream>
#include <string>

#include "staticlib/config/assert.hpp"

#include "negative_write_sink.hpp"
#include "two_bytes_at_once_sink.hpp"
#include "test_utils.hpp"

void test_buffer_size() {
    sl::io::buffered_sink<two_bytes_at_once_sink, 4> sink{two_bytes_at_once_sink{}};
    auto written1 = sink.write({"foo", 3});
    slassert(3 == written1);
    slassert(0 == sink.get_sink().get_data().size());
    auto written2 = sink.write({"42", 2});
    slassert(2 == written2);
    slassert(3 == sink.get_sink().get_data().size());
    slassert("foo" == sink.get_sink().get_data());
}

void test_flush() {
    sl::io::buffered_sink<two_bytes_at_once_sink, 4> sink{two_bytes_at_once_sink{}};
    auto written = sink.write({"foo", 3});
    slassert(3 == written);
    slassert(0 == sink.get_sink().get_data().size());
    auto flushed = sink.flush();
    slassert(3 == flushed);
    slassert(3 == sink.get_sink().get_data().size());
    slassert("foo" == sink.get_sink().get_data());
}

void test_overwrite() {
    sl::io::buffered_sink<two_bytes_at_once_sink, 4> sink{two_bytes_at_once_sink{}};
    auto written = sink.write({"foo42", 5});
    slassert(5 == written);
    slassert(5 == sink.get_sink().get_data().size());
    slassert("foo42" == sink.get_sink().get_data());
}

void test_make_rvalue() {
    auto sink = sl::io::make_buffered_sink(two_bytes_at_once_sink{});
    (void) sink;
}

void test_make_lvalue() {
    two_bytes_at_once_sink dest{};
    auto sink = sl::io::make_buffered_sink(dest);
    (void) sink;
}

void test_throw() {
    sl::io::buffered_sink<two_bytes_at_once_sink, 4> sink{two_bytes_at_once_sink()};
    slassert(throws_exc([&sink] { sink.write({nullptr, -1}); }));
    slassert(throws_exc([] {
        auto ns = sl::io::make_buffered_sink(negative_write_sink());
        std::array<char, 16> buf;
        std::memset(buf.data(), '\0', buf.size());
        ns.write(buf);
        ns.flush();
    }));
}

int main() {
    try {
        test_buffer_size();
        test_flush();
        test_overwrite();
        test_make_rvalue();
        test_make_lvalue();
        test_throw();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

