//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_GRAMMAR_SEQUENCE_RULE_HPP
#define BOOST_URL_GRAMMAR_SEQUENCE_RULE_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/grammar/error.hpp>
#include <boost/url/grammar/detail/tuple.hpp>
#include <boost/mp11/algorithm.hpp>
#include <tuple>

namespace boost {
namespace urls {
namespace grammar {

/** Match a series of rules in order

    This matches a series of rules in the
    order specified. Upon success the input
    will be adjusted to point to the first
    unconsumed character. There is no
    implicit specification of linear white
    space between each rule.

    @par Example
    @code
    constexpr auto ipv4_address_rule = sequence_rule(
        dec_octet_rule, char_rule('.'),
        dec_octet_rule, char_rule('.'),
        dec_octet_rule, char_rule('.'),
        dec_octet_rule );
    @endcode

    @par Value Type
    @code
    using value_type = std::tuple( typename Rules::value_type );
    @endcode

    @par BNF
    @code
    sequence     = rule1 rule2 rule3...
    @endcode

    @par Specification
    @li <a href="https://datatracker.ietf.org/doc/html/rfc5234#section-3.1"
        >3.1.  Concatenation (rfc5234)</a>

    @param rn A list of one or more rules to match

    @see
        @ref char_rule,
        @ref dec_octet_rule,
        @ref parse.
*/
#ifdef BOOST_URL_DOCS
template<class... Rules>
constexpr
__implementation_defined__
sequence_rule( Rules... rn ) noexcept;
#else
template<
    class R0,
    class... Rn>
class sequence_rule_t
{
    using T = mp11::mp_remove<
        std::tuple<
            typename R0::value_type,
            typename Rn::value_type...>,
        void>;
    static constexpr bool IsList =
        mp11::mp_size<T>::value != 1;

public:
    using value_type =
        mp11::mp_eval_if_c<IsList,
            T, mp11::mp_first, T>;

    template<
        class R0_,
        class... Rn_>
    friend
    constexpr
    auto
    sequence_rule(
        R0_ const& r0,
        Rn_ const&... rn) noexcept ->
            sequence_rule_t<R0_, Rn_...>;

    result<value_type>
    parse(
        char const*& it,
        char const* end) const;

private:
    constexpr
    sequence_rule_t(
        R0 const& r0,
        Rn const&... rn) noexcept
        : rn_(r0, rn...)
    {
    }

    detail::tuple<R0, Rn...> const rn_;
};

template<
    class R0,
    class... Rn>
constexpr
auto
sequence_rule(
    R0 const& r0,
    Rn const&... rn) noexcept ->
        sequence_rule_t<
            R0, Rn...>
{
    return { r0, rn... };
}
#endif

} // grammar
} // urls
} // boost

#include <boost/url/grammar/impl/sequence_rule.hpp>

#endif