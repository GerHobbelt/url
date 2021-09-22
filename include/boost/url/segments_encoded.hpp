//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_SEGMENTS_ENCODED_HPP
#define BOOST_URL_SEGMENTS_ENCODED_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/string.hpp>
#include <boost/url/detail/except.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost {
namespace urls {

#ifndef BOOST_URL_DOCS
class url;
#endif

/** A reference-like container to modifiable URL segments

    This class implements a <em>RandomAccessContainer</em>
    representing the path segments in a @ref url as
    percent-encoded strings. Ownership of the segments
    is not transferred; the container references the
    buffer in the url. Therefore, the lifetime of the
    url must remain valid until this container no
    longer exists.

    Objects of this type are not constructed directly;
    Instead, call the corresponding non-const member
    function of @ref url to obtain an instance of
    the container:

    @par Example
    @code
    url u = parse_relative_ref( "/path/to/file.txt" );

    segments_encoded se = u.encoded_segments();
    @endcode

    The @ref reference and @ref const_reference
    nested types are defined as publicly accessible
    nested classes. They proxy the behavior of a
    reference to a percent-encoded string in the
    underlying URL. The primary use of these
    references is to provide l-values that can be
    returned from element-accessing operations.
    Any reads or writes which happen through a
    @ref reference or @ref const_reference
    potentially read or write the underlying
    @ref url.

    @see
        @ref url.
*/
class segments_encoded
{
    url* u_ = nullptr;

    friend class url;

    explicit
    segments_encoded(
        url& u) noexcept
        : u_(&u)
    {
    }

public:
#ifdef BOOST_URL_DOCS
    /** A random-access iterator referencing segments in a url path

        When dereferenced, this iterator returns a
        proxy which allows conversion to stringlike
        types, assignments which change the underlying
        container, and comparisons.
    */
    using iterator = __see_below__;

    /** A random-access iterator referencing segments in a url path

        When dereferenced, this iterator returns a
        proxy which allows conversion to stringlike
        types, and comparisons.
    */
    using const_iterator = __see_below__;

    /** A proxy for a percent-encoded path segment

        This type is a proxy for a modifiable
        percent-encoded path segment. It supports
        assignment, conversion to stringlike types,
        and comparison.
    */
    using reference = __see_below__;

    /** A proxy for a percent-encoded path segment

        This type is a proxy for a read-only
        percent-encoded path segment. It supports
        conversion to stringlike types, and comparison.
    */
    using const_reference = __see_below__;
#else
    class iterator;
    class const_iterator;
    class reference;
    class const_reference;
#endif

    /** A type which can represent a segment as a value
    */
    using value_type = std::string;

    /** An unsigned integer type
    */
    using size_type = std::size_t;

    /** A signed integer type
    */
    using difference_type = std::ptrdiff_t;

    //--------------------------------------------

    // element access

    /** Return an element with bounds checking

        This function returns a proxy reference
        to the i-th element. If i is greater than
        @ref size, an exception is thrown.

        @par Exception Safety
        Strong guarantee.
        Exception thrown on invalid parameter.

        @throws std::out_of_range `i >= size()`

        @return A proxy reference to the element.

        @param i The zero-based index of the
        element.
    */
    inline
    reference
    at(std::size_t i);

    /** Return an element with bounds checking

        This function returns a proxy reference
        to the i-th element. If i is greater than
        @ref size, an exception is thrown.

        @par Exception Safety
        Strong guarantee.
        Exception thrown on invalid parameter.

        @throws std::out_of_range `i >= size()`

        @return A proxy reference to the element.

        @param i The zero-based index of the
        element.
    */
    inline
    const_reference
    at(std::size_t i) const;

    /** Return an element

        This function returns a proxy reference
        to the i-th element.

        @par Preconditions
        @code
        i < size()
        @endcode

        @par Exception Safety
        Strong guarantee.

        @return A proxy reference to the element.

        @param i The zero-based index of the
        element.
    */
    inline
    reference
    operator[](std::size_t i) noexcept;

    /** Return an element

        This function returns a proxy reference
        to the i-th element.

        @par Preconditions
        @code
        i < size()
        @endcode

        @par Exception Safety
        Strong guarantee.

        @return A proxy reference to the element.

        @param i The zero-based index of the
        element.
    */
    inline
    const_reference
    operator[](std::size_t i) const noexcept;

    /** Return the first element
    */
    inline
    const_reference
    front() const;

    /** Return the first element
    */
    inline
    reference
    front();

    /** Return the last element
    */
    inline
    const_reference
    back() const;

    /** Return the last element
    */
    inline
    reference
    back();

    // iterators

    /** Return an iterator to the beginning
    */
    inline
    iterator
    begin() noexcept;

    /** Return an iterator to the beginning
    */
    inline
    const_iterator
    begin() const noexcept;

    /** Return an iterator to the beginning
    */
    inline
    const_iterator
    cbegin() const noexcept;

    /** Return an iterator to the end
    */
    inline
    iterator
    end() noexcept;

    /** Return an iterator to the end
    */
    inline
    const_iterator
    end() const noexcept;

    /** Return an iterator to the end
    */
    inline
    const_iterator
    cend() const noexcept;

    // capacity

    /** Return true if the container is empty
    */
    bool
    empty() const noexcept
    {
        return size() == 0;
    }

    /** Return the number of elements in the container
    */
    BOOST_URL_DECL
    std::size_t
    size() const noexcept;

    // modifiers

    /** Remove the contents of the container

        @par Postconditions
        @code
        empty() == true
        @endcode

        @par Exception Safety
        Does not throw.
    */
    inline
    void
    clear() noexcept;

    /** Insert an element

        This function inserts a segment specified
        by the percent-encoded string `s`, at the
        position preceding `before`. The string
        must contain a valid percent-encoding, or
        else an exception is thrown.

        @par Exception Safety
        Exceptions thrown on invalid input.
        Calls to allocate may throw.

        @return An iterator pointing to the
        inserted value.

        @param before An iterator before which the
        new segment will be inserted.

        @param s A valid percent-encoded string
        to be inserted.
    */
    BOOST_URL_DECL
    iterator
    insert(
        const_iterator before,
        string_view s);

    /** Insert an element

        This function inserts a segment specified
        by the percent-encoded stringlike `t`,
        at the position preceding `before`. The
        stringlike must contain a valid percent-encoding,
        or else an exception is thrown.

        This function participates in overload
        resolution only if
        `is_stringlike<T>::value == true`.

        @par Exception Safety
        Exceptions thrown on invalid input.
        Calls to allocate may throw.

        @return An iterator pointing to the
        inserted value.

        @param before An iterator before which the
        new segment will be inserted.

        @param t The stringlike value to insert.
    */
    template<class T
#ifndef BOOST_URL_DOCS
        , class = typename std::enable_if<
            is_stringlike<T>::value,
                bool>::type
#endif
    >
    iterator
    insert(
        const_iterator before,
        T const& t);

    /** Erase an element

        This function erases the element pointed
        to by `pos`.
    */
    inline
    iterator
    erase(
        const_iterator pos);

    /** Erase elements

        This function erases the elements in
        the range `[first, last)`.
    */
    BOOST_URL_DECL
    iterator
    erase(
        const_iterator first,
        const_iterator last);

    /** Add an element to the end

        This function appends a segment
        containing the percent-encoded string
        `s` to the end of the container. The
        string must contain a valid
        percent-encoding or else an exception
        is thrown.

        @par Exception Safety
        Strong guarantee.
        Exceptions thrown on invalid input.

        @param s The string to add
    */
    inline
    void
    push_back(
        string_view s);

    /** Add an element to the end

        This function appends a segment
        containing the percent-encoded stringlike
        `t` to the end of the container. The
        stringlike must contain a valid
        percent-encoding or else an exception
        is thrown.

        This function participates in overload
        resolution only if
        `is_stringlike<T>::value == true`.

        @par Exception Safety
        Strong guarantee.
        Exceptions thrown on invalid input.

        @param t The stringlike to add
    */
    template<class T
#ifndef BOOST_URL_DOCS
        , class = typename std::enable_if<
            is_stringlike<T>::value,
                bool>::type
#endif
    >
    void
    push_back(
        T const& t)
    {
        return push_back(
            to_string_view(t));
    }

    /** Remove the last element

        This function removes the last element
        from the container.

        @par Preconditions
        @code
        size() > 0
        @endcode
    */
    inline
    void
    pop_back();
};

} // urls
} // boost

#include <boost/url/impl/segments_encoded.hpp>

#endif