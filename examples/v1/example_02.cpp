// Copyright 2018-20 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt of copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <skyr/url.hpp>



#if defined(BUILD_MONOLITHIC)
#define main(void)      url_example_v1_02_main(void)
#endif

int main(void)
{
  auto url = skyr::make_url("\xf0\x9f\x8d\xa3\xf0\x9f\x8d\xba");
  if (!url) {
    std::cerr << "Parsing failed: " << static_cast<int>(url.error()) << std::endl;
  }
}
