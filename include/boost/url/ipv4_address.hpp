//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAllinace/url
//

#ifndef BOOST_URL_IPV4_ADDRESS_HPP
#define BOOST_URL_IPV4_ADDRESS_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/error.hpp>
#include <boost/url/string.hpp>
#include <array>
#include <cstdint>
#include <iosfwd>

namespace boost {
namespace urls {

/** Represents an IP version 4 style address

    Objects of this type are used to construct
    and manipulate IP version 4 addresses.

    @par Specification
    @li <a href="https://en.wikipedia.org/wiki/IPv4">
        IPv4 (Wikipedia)</a>

    @see
        @ref make_ipv4_address,
        @ref ipv6_address.
*/
class ipv4_address
{
public:
    /** The number of characters in the longest possible ipv4 string

        The longest ipv4 address string is "255.255.255.255".
    */
    static
    constexpr
    std::size_t max_str_len = 15;

    /** The type used to represent an address as an unsigned integer
    */
    using uint_type =
        std::uint_least32_t;

    /** The type used to represent an address as an array of bytes
    */
    using bytes_type =
        std::array<unsigned char, 4>;

    /** Constructor
    */
    ipv4_address() noexcept
        : addr_(0)
    {
    }

    /** Construct from raw bytes
    */
    BOOST_URL_DECL
    explicit
    ipv4_address(
        bytes_type const& bytes);

    /** Construct from an unsigned integer
    */
    BOOST_URL_DECL
    explicit
    ipv4_address(uint_type addr);

    /** Constructor
    */
    ipv4_address(
        ipv4_address const& other) noexcept
        : addr_(other.addr_)
    {
    }

    /** Assign from another address
    */
    ipv4_address&
    operator=(
        ipv4_address const& other) noexcept
    {
        addr_ = other.addr_;
        return *this;
    }

    /** Return the address as bytes, in network byte order
    */
    BOOST_URL_DECL
    bytes_type
    to_bytes() const noexcept;

    /** Return the address as an unsigned integer
    */
    BOOST_URL_DECL
    uint_type
    to_uint() const noexcept;

    /** Return the address as a string in dotted decimal format

        @par Exception Safety

        Strong guarantee.
        Calls to allocate may throw.

        @param a An optional allocator the returned
        string will use. If this parameter is omitted,
        the default allocator is used.

        @return A @ref string_value using the
        specified allocator.
    */
    template<class Allocator =
        std::allocator<char>>
    string_value
    to_string(Allocator const& a = {}) const;

    /** Write a dotted decimal string representing the address to a buffer

        The resulting buffer is not null-terminated.

        @throw std::length_error `dest_size < ipv4_address::max_str_len`

        @return The formatted string

        @param dest The buffer in which to write,
        which must have at least `dest_size` space.

        @param dest_size The size of the output buffer.
    */
    BOOST_URL_DECL
    string_view
    to_buffer(
        char* dest,
        std::size_t dest_size) const;

    /** Return true if the address is a loopback address
    */
    BOOST_URL_DECL
    bool
    is_loopback() const noexcept;

    /** Return true if the address is unspecified
    */
    BOOST_URL_DECL
    bool
    is_unspecified() const noexcept;

    /** Return true if the address is a multicast address
    */
    BOOST_URL_DECL
    bool
    is_multicast() const noexcept;

    /** Return true if two addresses are equal
    */
    friend
    bool
    operator==(
        ipv4_address const& a1,
        ipv4_address const& a2) noexcept
    {
        return a1.addr_ == a2.addr_;
    }

    /** Return true if two addresses are not equal
    */
    friend
    bool
    operator!=(
        ipv4_address const& a1,
        ipv4_address const& a2) noexcept
    {
        return a1.addr_ != a2.addr_;
    }

    /** Return an address object that represents any address
    */
    static
    ipv4_address
    any() noexcept
    {
        return ipv4_address();
    }

    /** Return an address object that represents the loopback address
    */
    static
    ipv4_address
    loopback() noexcept
    {
        return ipv4_address(0x7F000001);
    }

    /** Return an address object that represents the broadcast address
    */
    static
    ipv4_address
    broadcast() noexcept
    {
        return ipv4_address(0xFFFFFFFF);
    }

private:
    friend class ipv6_address;

    BOOST_URL_DECL
    std::size_t
    print_impl(
        char* dest) const noexcept;

    uint_type addr_;
};

/** Format the address to an output stream
*/
BOOST_URL_DECL
std::ostream&
operator<<(
    std::ostream& os,
    ipv4_address const& addr);

/** Return an IPv4 address from an IP address string in dotted decimal form
*/
BOOST_URL_DECL
ipv4_address
make_ipv4_address(
    string_view s,
    error_code& ec) noexcept;

/** Return an IPv4 address from an IP address string in dotted decimal form
*/
BOOST_URL_DECL
ipv4_address
make_ipv4_address(
    string_view s);

} // urls
} // boost

#include <boost/url/impl/ipv4_address.hpp>

#endif
