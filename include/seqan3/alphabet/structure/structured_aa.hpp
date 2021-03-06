// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2019, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2019, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

/*!\file
 * \author Joerg Winkler <j.winkler AT fu-berlin.de>
 * \brief Contains the composite of aminoacid with structure alphabets.
 */

#pragma once

#include <iostream>
#include <string>
#include <utility>

#include <seqan3/alphabet/aminoacid/all.hpp>
#include <seqan3/alphabet/composite/alphabet_tuple_base.hpp>
#include <seqan3/alphabet/concept.hpp>
#include <seqan3/alphabet/structure/dssp9.hpp>

namespace seqan3
{

/*!\brief A seqan3::alphabet_tuple_base that joins an aminoacid alphabet with a protein structure alphabet.
 * \ingroup structure
 * \implements seqan3::Alphabet
 * \implements seqan3::detail::ConstexprAlphabet
 * \implements seqan3::TriviallyCopyable
 * \implements seqan3::StandardLayout
 * \tparam sequence_alphabet_t Type of the first aminoacid letter; must satisfy seqan3::Alphabet.
 * \tparam structure_alphabet_t Types of further structure letters; must satisfy seqan3::Alphabet.
 *
 * This composite pairs an aminoacid alphabet with a structure alphabet. The rank values
 * correpsond to numeric values in the size of the composite, while the character values
 * are taken from the sequence alphabet and the structure annotation is taken from the structure
 * alphabet.
 *
 * As with all `seqan3::alphabet_tuple_base` s you may access the individual alphabet letters in
 * regular c++ tuple notation, i.e. `get<0>(t)` and objects can be brace-initialized
 * with the individual members.
 *
 * \snippet test/snippet/alphabet/structure/structured_aa.cpp general
 *
 * This seqan3::alphabet_tuple_base itself fulfills seqan3::Alphabet.
 */
template <typename sequence_alphabet_t = aa27, typename structure_alphabet_t = dssp9>
//!\cond
    requires Alphabet<sequence_alphabet_t> && Alphabet<structure_alphabet_t>
//!\endcond
class structured_aa :
    public alphabet_tuple_base<structured_aa<sequence_alphabet_t, structure_alphabet_t>,
                                 sequence_alphabet_t, structure_alphabet_t>
{
private:
    //!\brief The base type.
    using base_type = alphabet_tuple_base<structured_aa<sequence_alphabet_t, structure_alphabet_t>,
                                            sequence_alphabet_t, structure_alphabet_t>;
public:
    //!\brief First template parameter as member type.
    using sequence_alphabet_type = sequence_alphabet_t;
    //!\brief Second template parameter as member type.
    using structure_alphabet_type = structure_alphabet_t;

    //!\brief Equals the char_type of sequence_alphabet_type.
    using char_type = alphabet_char_t<sequence_alphabet_type>;

    /*!\name Constructors, destructor and assignment
     * \{
     */
    constexpr structured_aa()                                    noexcept = default; //!< Defaulted.
    constexpr structured_aa(structured_aa const &)               noexcept = default; //!< Defaulted.
    constexpr structured_aa(structured_aa &&)                    noexcept = default; //!< Defaulted.
    constexpr structured_aa & operator =(structured_aa const &)  noexcept = default; //!< Defaulted.
    constexpr structured_aa & operator =(structured_aa &&)       noexcept = default; //!< Defaulted.
    ~structured_aa()                                             noexcept = default; //!< Defaulted.

    using base_type::base_type; // Inherit non-default constructors


    //!\copydoc alphabet_tuple_base::alphabet_tuple_base(component_type const alph)
    SEQAN3_DOXYGEN_ONLY(( constexpr structured_aa(component_type const alph) {} ))
    //!\copydoc alphabet_tuple_base::alphabet_tuple_base(indirect_component_type const alph)
    SEQAN3_DOXYGEN_ONLY(( constexpr structured_aa(indirect_component_type const alph) {} ))
    //!\copydoc alphabet_tuple_base::operator=(component_type const alph)
    SEQAN3_DOXYGEN_ONLY(( constexpr structured_aa & operator=(component_type const alph) {} ))
    //!\copydoc alphabet_tuple_base::operator=(indirect_component_type const alph)
    SEQAN3_DOXYGEN_ONLY(( constexpr structured_aa & operator=(indirect_component_type const alph) {} ))
    //!\}

    // Inherit operators from base
    using base_type::operator=;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>=;
    using base_type::operator<=;
    using base_type::operator<;
    using base_type::operator>;

    /*!\name Write functions
     * \{
     */
    //!\brief Assign from a nucleotide character. This modifies the internal sequence letter.
    constexpr structured_aa & assign_char(char_type const c) noexcept
    {
        seqan3::assign_char_to(c, get<0>(*this));
        return *this;
    }

    //!\brief Strict assign from a nucleotide character. This modifies the internal sequence letter.
    structured_aa & assign_char_strictly(char_type const c)
    {
        seqan3::assign_char_strictly_to(c, get<0>(*this));
        return *this;
    }
    //!\}

    /*!\name Read functions
     * \{
     */
    //!\brief Return a character. This reads the internal sequence letter.
    constexpr char_type to_char() const noexcept
    {
        return seqan3::to_char(get<0>(*this));
    }
    //!\}

    //!\brief Validate whether a character is valid in the sequence alphabet.
    static constexpr bool char_is_valid(char_type const c) noexcept
    {
        return char_is_valid_for<sequence_alphabet_type>(c);
    }
};

//!\brief Type deduction guide enables usage of structured_aa without specifying template args.
//!\relates structured_aa
template <typename sequence_alphabet_type, typename structure_alphabet_type>
structured_aa(sequence_alphabet_type &&, structure_alphabet_type &&)
    -> structured_aa<std::decay_t<sequence_alphabet_type>, std::decay_t<structure_alphabet_type>>;

} // namespace seqan3
