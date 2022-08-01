//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

// Test that header file is self-contained.
#include <boost/url/rfc/gen_delim_chars.hpp>

#include "test_rule.hpp"

namespace boost {
namespace urls {

struct gen_delim_chars_test
{
    void
    run()
    {
        test_char_set(
            gen_delim_chars,
                ":/?#[]@");
    }
};

TEST_SUITE(
    gen_delim_chars_test,
    "boost.url.gen_delim_chars");

} // urls
} // boost