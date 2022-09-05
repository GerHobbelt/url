//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_PARAM_HPP
#define BOOST_URL_PARAM_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/pct_string_view.hpp>
#include <string>

namespace boost {
namespace urls {

#ifndef BOOST_URL_DOCS
struct param_pct_view;
struct param_view;
#endif

//------------------------------------------------

/** A query parameter

    Objects of this type represent a single key
    and value pair in a query string where a key
    is always present and may be empty, while the
    presence of a value is indicated by
    @ref has_value equal to true.
    An empty value is distinct from no value.

    Depending on where the object was obtained,
    the strings may or may not contain percent
    escapes.

    For most usages, key comparisons are
    case-sensitive and duplicate keys in
    a query are possible. However, it is
    the authority that has final control
    over how the query is interpreted.

    @par BNF
    @code
    query-params    = query-param *( "&" query-param )
    query-param     = key [ "=" value ]
    key             = *qpchar
    value           = *( qpchar / "=" )
    @endcode

    @par Specification
    @li <a href="https://en.wikipedia.org/wiki/Query_string"
        >Query string (Wikipedia)</a>

    @see
        @ref param_view,
        @ref param_pct_view.
*/
struct param
{
    /** The key

        For most usages, key comparisons are
        case-sensitive and duplicate keys in
        a query are possible. However, it is
        the authority that has final control
        over how the query is interpreted.
    */
    std::string key;

    /** The value

        The presence of a value is indicated by
        @ref has_value equal to true.
        An empty value is distinct from no value.
    */
    std::string value;

    /** True if a value is present

        The presence of a value is indicated by
        `has_value == true`.
        An empty value is distinct from no value.
    */
    bool has_value = false;

    /** Constructor

        Default constructed query parameters
        have an empty key and no value.

        @par Example
        @code
        param qp;
        @endcode

        @par Postconditions
        @code
        this->key == "" && this->value == "" && this->has_value == false
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.
    */
    param() = default;

    /** Constructor

        Upon construction, this acquires
        ownership of the members of other
        via move construction. The moved
        from object will be as if default
        constructed.

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @par other The object to construct from.
    */
    param(param&& other) noexcept
        : key(std::move(other.key))
        , value(std::move(other.value))
        , has_value(other.has_value)
    {
    #ifdef BOOST_URL_COW_STRINGS
        // for copy-on-write std::string
        other.key.clear();
        other.value.clear();
    #endif
        other.has_value = false;
    }

    /** Constructor

        Upon construction, this becomes a copy
        of `other`.

        @par Postconditions
        @code
        this->key == other.key && this->value == other.value && this->has_value == other.has_value
        @endcode

        @par Complexity
        Linear in `other.key.size() + other.value.size()`.

        @par Exception Safety
        Calls to allocate may throw.

        @par other The object to construct from.
    */
    param(param const& other) = default;

    /** Assignment

        Upon assignment, this acquires
        ownership of the members of other
        via move assignment. The moved
        from object will be as if default
        constructed.

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @par other The object to assign from.
    */
    param&
    operator=(param&& other) noexcept
    {
        key = std::move(other.key);
        value = std::move(other.value);
        has_value = other.has_value;
    #ifdef BOOST_URL_COW_STRINGS
        // for copy-on-write std::string
        other.key.clear();
        other.value.clear();
    #endif
        other.has_value = false;
        return *this;
    }

    /** Assignment

        Upon assignment, this becomes a copy
        of `other`.

        @par Postconditions
        @code
        this->key == other.key && this->value == other.value && this->has_value == other.has_value
        @endcode

        @par Complexity
        Linear in `other.key.size() + other.value.size()`.

        @par Exception Safety
        Calls to allocate may throw.

        @par other The object to assign from.
    */
    param& operator=(
        param const&) = default;

    //--------------------------------------------

    /** Constructor

        This constructs a parameter with a key
        and no value.
        No validation is performed on the strings.
        Ownership of the key is acquired by
        making a copy.

        @par Example
        @code
        param qp( "key" );
        @endcode

        @par Postconditions
        @code
        this->key == key && this->value == "" && this->has_value == false
        @endcode

        @par Complexity
        Linear in `key.size()`.

        @par Exception Safety
        Calls to allocate may throw.

        @param key The key to set.
    */
    param(
        string_view key)
        : key(key)
    {
    }

    /** Constructor

        This constructs a parameter with a key
        and value.
        No validation is performed on the strings.
        Ownership of the key and value is acquired
        by making copies.

        @par Example
        @code
        param qp( "key", "value" );
        @endcode

        @par Postconditions
        @code
        this->key == key && this->value == value && this->has_value == true
        @endcode

        @par Complexity
        Linear in `key.size() + value.size()`.

        @par Exception Safety
        Calls to allocate may throw.

        @param key, value The key and value to set.
    */
    param(
        string_view key,
        string_view value)
        : key(key)
        , value(value)
        , has_value(true)
    {
    }

    /** Assignment

        The members of `other` are copied,
        re-using already existing string capacity.

        @par Postconditions
        @code
        this->key == other.key && this->value == other.value && this->has_value == other.has_value
        @endcode

        @par Complexity
        Linear in `other.key.size() + other.value.size()`.

        @par Exception Safety
        Calls to allocate may throw.

        @param other The parameter to copy.
    */
    param&
    operator=(param_view const& other);

    /** Assignment

        The members of `other` are copied,
        re-using already existing string capacity.

        @par Postconditions
        @code
        this->key == other.key && this->value == other.value && this->has_value == other.has_value
        @endcode

        @par Complexity
        Linear in `other.key.size() + other.value.size()`.

        @par Exception Safety
        Calls to allocate may throw.

        @param other The parameter to copy.
    */
    param&
    operator=(param_pct_view const& other);

#ifndef BOOST_URL_DOCS
    // arrow support
    param const*
    operator->() const noexcept
    {
        return this;
    }

    // aggregate construction
    param(
        string_view key,
        string_view value,
        bool has_value) noexcept
        : key(key)
        , value(has_value
            ? value
            : string_view())
        , has_value(has_value)
    {
    }
#endif
};

//------------------------------------------------

/** A query parameter

    Objects of this type represent a single key
    and value pair in a query string where a key
    is always present and may be empty, while the
    presence of a value is indicated by
    @ref has_value equal to true.
    An empty value is distinct from no value.

    Depending on where the object was obtained,
    the strings may or may not contain percent
    escapes.

    For most usages, key comparisons are
    case-sensitive and duplicate keys in
    a query are possible. However, it is
    the authority that has final control
    over how the query is interpreted.

    <br>

    Keys and values in this object reference
    external character buffers.
    Ownership of the buffers is not transferred;
    the caller is responsible for ensuring that
    the assigned buffers remain valid until
    they are no longer referenced.

    @par BNF
    @code
    query-params    = query-param *( "&" query-param )
    query-param     = key [ "=" value ]
    key             = *qpchar
    value           = *( qpchar / "=" )
    @endcode

    @par Specification
    @li <a href="https://en.wikipedia.org/wiki/Query_string"
        >Query string (Wikipedia)</a>

    @see
        @ref param,
        @ref param_pct_view.
*/
struct param_view
{
    /** The key

        For most usages, key comparisons are
        case-sensitive and duplicate keys in
        a query are possible. However, it is
        the authority that has final control
        over how the query is interpreted.
    */
    string_view key;

    /** The value

        The presence of a value is indicated by
        @ref has_value equal to true.
        An empty value is distinct from no value.
    */
    string_view value;

    /** True if a value is present

        The presence of a value is indicated by
        `has_value == true`.
        An empty value is distinct from no value.
    */
    bool has_value = false;

    //--------------------------------------------

    /** Constructor

        Default constructed query parameters
        have an empty key and no value.

        @par Example
        @code
        param_view qp;
        @endcode

        @par Postconditions
        @code
        this->key == "" && this->value == "" && this->has_value == false
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.
    */
    param_view() = default;

    /** Constructor

        This constructs a parameter with a key
        and no value.
        No validation is performed on the strings.
        The new key will reference the same
        underlying character buffer.
        Ownership of the buffers is not transferred;
        the caller is responsible for ensuring that
        the assigned buffers remain valid until
        they are no longer referenced.

        @par Example
        @code
        param_view qp( "key" );
        @endcode

        @par Postconditions
        @code
        this->key.data() == key.data() && this->value == "" && this->has_value == false
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @param key The key to set.
    */
    param_view(
        string_view key) noexcept
        : key(key)
    {
    }

    /** Constructor

        This constructs a parameter with a key
        and value.
        No validation is performed on the strings.
        The new key and value will reference
        the same corresponding underlying
        character buffers.
        Ownership of the buffers is not transferred;
        the caller is responsible for ensuring that
        the assigned buffers remain valid until
        they are no longer referenced.

        @par Example
        @code
        param_view qp( "key", "value" );
        @endcode

        @par Postconditions
        @code
        this->key.data() == key.data() && this->value.data() == value.data() && this->has_value == true
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @param key, value The key and value to set.
    */
    param_view(
        string_view key,
        string_view value) noexcept
        : key(key)
        , value(value)
        , has_value(true)
    {
    }

    /** Constructor

        This function constructs a param
        which references the character buffers
        representing the key and value in another
        container.
        Ownership of the buffers is not transferred;
        the caller is responsible for ensuring that
        the assigned buffers remain valid until
        they are no longer referenced.

        @par Example
        @code
        param qp( "key", "value" );
        param_view qpv( qp );
        @endcode

        @par Postconditions
        @code
        this->key == key && this->value == value && this->has_value == other.has_value
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.

        @param other The param to reference
    */
    param_view(
        param const& other) noexcept
        : param_view(
            other.key,
            other.value,
            other.has_value)
    {
    }

    /** Conversion

        This function performs a conversion from
        a reference-like query parameter to one
        retaining ownership of the strings by
        making a copy.
        No validation is performed on the strings.

        @par Complexity
        Linear in `this->key.size() + this->value.size()`.

        @par Exception Safety
        Calls to allocate may throw.
    */
    explicit
    operator
    param()
    {
        return { key, value, has_value };
    }

#ifndef BOOST_URL_DOCS
    // arrow support
    param_view const*
    operator->() const noexcept
    {
        return this;
    }

    // aggregate construction
    param_view(
        string_view key,
        string_view value,
        bool has_value) noexcept
        : key(key)
        , value(has_value
            ? value
            : string_view())
        , has_value(has_value)
    {
    }
#endif
};

//------------------------------------------------

/** A query parameter

    Objects of this type represent a single key
    and value pair in a query string where a key
    is always present and may be empty, while the
    presence of a value is indicated by
    @ref has_value equal to true.
    An empty value is distinct from no value.

    The strings may have percent escapes, and
    offer an additional invariant: they never
    contain an invalid percent-encoding.

    For most usages, key comparisons are
    case-sensitive and duplicate keys in
    a query are possible. However, it is
    the authority that has final control
    over how the query is interpreted.

    <br>

    Keys and values in this object reference
    external character buffers.
    Ownership of the buffers is not transferred;
    the caller is responsible for ensuring that
    the assigned buffers remain valid until
    they are no longer referenced.

    @par BNF
    @code
    query-params    = query-param *( "&" query-param )
    query-param     = key [ "=" value ]
    key             = *qpchar
    value           = *( qpchar / "=" )
    @endcode

    @par Specification
    @li <a href="https://en.wikipedia.org/wiki/Query_string"
        >Query string (Wikipedia)</a>

    @see
        @ref param,
        @ref param_view.
*/
struct param_pct_view
{
    /** The key

        For most usages, key comparisons are
        case-sensitive and duplicate keys in
        a query are possible. However, it is
        the authority that has final control
        over how the query is interpreted.
    */
    pct_string_view key;

    /** The value

        The presence of a value is indicated by
        @ref has_value equal to true.
        An empty value is distinct from no value.
    */
    pct_string_view value;

    /** True if a value is present

        The presence of a value is indicated by
        `has_value == true`.
        An empty value is distinct from no value.
    */
    bool has_value = false;

    //--------------------------------------------

    /** Constructor

        Default constructed query parameters
        have an empty key and no value.

        @par Example
        @code
        param_pct_view qp;
        @endcode

        @par Postconditions
        @code
        this->key == "" && this->value == "" && this->has_value == false
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Throws nothing.
    */
    param_pct_view() = default;

    /** Constructor

        This constructs a parameter with a key,
        which may contain percent escapes,
        and no value.
        The new key will reference the same
        underlying character buffer.
        Ownership of the buffers is not transferred;
        the caller is responsible for ensuring that
        the assigned buffers remain valid until
        they are no longer referenced.

        @par Example
        @code
        param_pct_view qp( "key" );
        @endcode

        @par Postconditions
        @code
        this->key.data() == key.data() && this->value == "" && this->has_value == false
        @endcode

        @par Complexity
        Linear in `key.size()`.

        @par Exception Safety
        Exceptions thrown on invalid input.

        @throw system_error
        `key` contains an invalid percent-encoding.

        @param key The key to set.
    */
    param_pct_view(
        pct_string_view key) noexcept
        : key(key)
    {
    }

    /** Constructor

        This constructs a parameter with a key
        and value, which may both contain percent
        escapes.
        The new key and value will reference
        the same corresponding underlying
        character buffers.
        Ownership of the buffers is not transferred;
        the caller is responsible for ensuring that
        the assigned buffers remain valid until
        they are no longer referenced.

        @par Example
        @code
        param_pct_view qp( "key", "value" );
        @endcode

        @par Postconditions
        @code
        this->key.data() == key.data() && this->value.data() == value.data() && this->has_value == true
        @endcode

        @par Complexity
        Linear in `key.size() + value.size()`.

        @par Exception Safety
        Exceptions thrown on invalid input.

        @throw system_error
        `key` or `value` contains an invalid percent-encoding.

        @param key, value The key and value to set.
    */
    param_pct_view(
        pct_string_view key,
        pct_string_view value) noexcept
        : key(key)
        , value(value)
        , has_value(true)
    {
    }
 
    /** Conversion

        This function performs a conversion from
        a reference-like query parameter to one
        retaining ownership of the strings by
        making a copy.

        @par Complexity
        Linear in `this->key.size() + this->value.size()`.

        @par Exception Safety
        Calls to allocate may throw.
    */
    explicit
    operator
    param()
    {
        return param(
            static_cast<std::string>(key),
            static_cast<std::string>(value),
            has_value);
    }

#ifndef BOOST_URL_DOCS
    // arrow support
    param_pct_view const*
    operator->() const noexcept
    {
        return this;
    }

    // aggregate construction
    param_pct_view(
        pct_string_view key,
        pct_string_view value,
        bool has_value) noexcept
        : key(key)
        , value(has_value
            ? value
            : pct_string_view())
        , has_value(has_value)
    {
    }
#endif
};

//------------------------------------------------

inline
param&
param::
operator=(
    param_view const& other)
{
    // VFALCO operator= assignment
    // causes a loss of original capacity:
    // https://godbolt.org/z/nYef8445K
    //
    // key = other.key;
    // value = other.value;

    // preserve capacity
    key.assign(
        other.key.data(),
        other.key.size());
    value.assign(
        other.value.data(),
        other.value.size());
    has_value = other.has_value;
    return *this;
}

inline
param&
param::
operator=(
    param_pct_view const& other)
{
    // preserve capacity
    key.assign(
        other.key.data(),
        other.key.size());
    value.assign(
        other.value.data(),
        other.value.size());
    has_value = other.has_value;
    return *this;
}

} // urls
} // boost

#endif