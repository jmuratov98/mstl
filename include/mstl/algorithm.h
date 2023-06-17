#pragma once

#include "mstl/internal/config.h"

namespace mstl {

    template<typename Iterator1, typename Iterator2>
    MSTL_CPP20_CONSTEXPR bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2) {
        for(; first1 != last1; ++first1, ++first2) {
            if(*first1 != *first2)
                return false;
        }
        return true;
    }

    template<typename Iterator1, typename Iterator2>
    MSTL_CPP20_CONSTEXPR bool lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
        for(; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
            if(*first1 < *first2)
                return true;
            if(*first2 < first1)
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

    template<typename OutputIt, typename Size, typename T>
    MSTL_CPP20_CONSTEXPR fill_n(OutputIt first, Size count, const T& value) {
        for(Size i = 0; i < count; i++)
            *first++ = value;
        return first;
    }

} // namespace mstl