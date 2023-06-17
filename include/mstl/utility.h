#pragma once

#include "mstl/internal/config.h"
#include "mstl/type_traits.h"

namespace mstl {

#ifdef MSTL_CPP14
    template<typename T, T... Ints>
    class integer_sequence
    {
    public:
        using type = T;

    public:
        static constexpr size_t size() noexcept {
            return sizeof...(Ints);
        }
    };

    template<size_t... Ints> 
    using index_sequence = integer_sequence<size_t, Ints...>;

    // TODO: std::make_integer_sequence
    // TODO: std::make_index_sequence

#endif

    template<typename T>
    MSTL_CPP14_CONSTEXPR remove_reference_t<T>&& move(T&& arg) noexcept {
        return static_cast<remove_reference_t<T>&&>(arg);
    }



} // namespace mstl