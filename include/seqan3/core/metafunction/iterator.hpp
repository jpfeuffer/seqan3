// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2019, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2019, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

/*!\file
 * \brief Provides various metafunctions for use on iterators.
 * \author Hannes Hauswedell <hannes.hauswedell AT fu-berlin.de>
 */

#pragma once

#include <iterator>
#include <type_traits>

#include <seqan3/core/platform.hpp>
#include <seqan3/core/metafunction/pre.hpp>
#include <seqan3/std/iterator>

namespace seqan3
{

/*!\addtogroup metafunction
 * \{
 */

// ----------------------------------------------------------------------------
// value_type
// ----------------------------------------------------------------------------

/*!\brief Type metafunction that returns the `value_type` of another type [specialisation for input iterators].
 * \tparam it_t The type you wish to query; must satisfy std::input_Iterator.
 */
template <std::InputIterator it_t>
struct value_type<it_t>
{
    //!\brief Return the member type as return type.
    using type = typename std::iterator_traits<std::remove_reference_t<it_t>>::value_type;
};

// see specialisation for ranges in core/metafunction/range.hpp

// ----------------------------------------------------------------------------
// reference
// ----------------------------------------------------------------------------

/*!\brief Type metafunction that returns the `reference` of another type [specialisation for input iterators].
 * \tparam it_t The type you wish to query; must satisfy std::input_Iterator.
 */
template <std::InputIterator it_t>
struct reference<it_t>
{
    //!\brief Return the member type as return type.
    using type = typename std::iterator_traits<std::remove_reference_t<it_t>>::reference;
};

// see specialisation for ranges in core/metafunction/range.hpp

// ----------------------------------------------------------------------------
// rvalue_reference
// ----------------------------------------------------------------------------

/*!\brief Type metafunction that returns the `rvalue_reference` of another type [specialisation for input iterators].
 * \tparam it_t The type you wish to query; must satisfy std::input_Iterator.
 */
template <std::InputIterator it_t>
struct rvalue_reference<it_t>
{
    //!\brief Return the member type as return type.
    using type = decltype(std::ranges::iter_move(std::declval<it_t &>()));
};

// see specialisation for ranges in core/metafunction/range.hpp

// ----------------------------------------------------------------------------
// const_reference
// ----------------------------------------------------------------------------

// only defined for ranges

// ----------------------------------------------------------------------------
// difference_type
// ----------------------------------------------------------------------------

/*!\brief Type metafunction that returns the `difference_type` of another type [specialisation for iterators].
 * \tparam it_t The type you wish to query; must satisfy std::WeaklyIncrementable.
 */
template <std::WeaklyIncrementable it_t>
struct difference_type<it_t>
{
    //!\brief Return the member type as return type.
    using type = typename std::iterator_traits<std::remove_reference_t<it_t>>::difference_type;
};

// see specialisation for ranges in core/metafunction/range.hpp

// ----------------------------------------------------------------------------
// size_type
// ----------------------------------------------------------------------------

/*!\brief Type metafunction that returns the `size_type` of another type [specialisation for iterators].
 * \tparam it_t The type you wish to query; must satisfy std::WeaklyIncrementable.
 */
template <std::WeaklyIncrementable it_t>
struct size_type<it_t>
{
    //!\brief Return the member type as return type.
    using type = std::make_unsigned_t<difference_type_t<it_t>>;
};

// see specialisation for ranges in core/metafunction/range.hpp

// ----------------------------------------------------------------------------
// iterator_tag
// ----------------------------------------------------------------------------

/*!\brief Type metafunction that deduces the
 * [iterator_category](https://en.cppreference.com/w/cpp/iterator/iterator_tags) from the modelled
 * concept [Type metafunction].
 * \tparam it_t The type to operate on.
 *
 * <table>
 *   <tr>
 *     <th>Modelled concept</th>
 *     <th>iterator_tag<it_t>::type</th>
 *   </tr>
 *   <tr>
 *     <td>\ref std::InputIterator "std::InputIterator<it_t>"</td>
 *     <td>std::input_iterator_tag</td>
 *   </tr>
 *   <tr>
 *     <td>\ref std::InputIterator "!std::InputIterator<it_t>" &amp;&amp;
 *         \ref std::OutputIterator "std::OutputIterator<it_t, value_type<it_t>>"</td>
 *     <td>std::output_iterator_tag</td>
 *   </tr>
 *   <tr>
 *     <td>\ref std::ForwardIterator "std::ForwardIterator<it_t>"</td>
 *     <td>std::forward_iterator_tag</td>
 *   </tr>
 *   <tr>
 *     <td>\ref std::BidirectionalIterator "std::BidirectionalIterator<it_t>"</td>
 *     <td>std::bidirectional_iterator_tag</td>
 *   </tr>
 *   <tr>
 *     <td>\ref std::RandomAccessIterator "std::RandomAccessIterator<it_t>"</td>
 *     <td>std::random_access_iterator_tag</td>
 *   </tr>
 * </table>
 *
 * \attention
 * If [std::iterator_traits<it_t>::iterator_category](https://en.cppreference.com/w/cpp/iterator/iterator_traits)
 * is defined for a type `it_t`, this metafunction acts as an alias for it.
 * If it is not defined and no concepts are modelled, iterator_tag<it_t>::type is not defined.
 */
template <typename it_t>
struct iterator_tag
{
SEQAN3_DOXYGEN_ONLY(
    //!\brief The [iterator_category](https://en.cppreference.com/w/cpp/iterator/iterator_tags).
    using type = iterator_category;
)
};

//!\cond
template <typename it_t>
    requires requires { typename std::iterator_traits<it_t>::iterator_category; }
struct iterator_tag<it_t>
{
    using type = typename std::iterator_traits<it_t>::iterator_category;
};

template <std::InputIterator it_t>
    requires !requires { typename std::iterator_traits<it_t>::iterator_category; }
struct iterator_tag<it_t>
{
    using type = std::input_iterator_tag;
};

template <typename it_t>
    requires !std::InputIterator<it_t> && std::OutputIterator<it_t, value_type_t<it_t>> &&
             !requires { typename std::iterator_traits<it_t>::iterator_category; }
struct iterator_tag<it_t>
{
    using type = std::output_iterator_tag;
};

template <std::ForwardIterator it_t>
    requires !requires { typename std::iterator_traits<it_t>::iterator_category; }
struct iterator_tag<it_t>
{
    using type = std::forward_iterator_tag;
};

template <std::BidirectionalIterator it_t>
    requires !requires { typename std::iterator_traits<it_t>::iterator_category; }
struct iterator_tag<it_t>
{
    using type = std::bidirectional_iterator_tag;
};

template <std::RandomAccessIterator it_t>
    requires !requires { typename std::iterator_traits<it_t>::iterator_category; }
struct iterator_tag<it_t>
{
    using type = std::random_access_iterator_tag;
};
//!\endcond

/*!\brief Return the `iterator_category` type of the input type [Type metafunction, shortcut].
 * \tparam it_t The type to operate on.
 */
template <typename it_t>
//!\cond
    requires requires { typename iterator_tag<it_t>::type; }
//!\endcond
using iterator_tag_t = typename iterator_tag<it_t>::type;
//!\}

} // namespace seqan3
