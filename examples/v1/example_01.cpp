// Copyright 2018-20 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt of copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <skyr/url.hpp>



#if defined(BUILD_MONOLITHIC)
#define main(void)      url_example_v1_01_main(void)
#endif

int main(void)
{
  auto url = skyr::url("http://example.org/\xf0\x9f\x92\xa9");
  std::cout << url << std::endl;
  std::cout << url.pathname() << std::endl;
}
