#pragma once

#include "mstl/internal/config.h"

namespace mstl {

    template<typename T>    struct remove_cv                    { using type = T; };
    template<typename T>    struct remove_cv<const T>           { using type = T; };
    template<typename T>    struct remove_cv<volatile T>        { using type = T; };
    template<typename T>    struct remove_cv<const volatile T>  { using type = T; };

    template<typename T>    struct remove_reference             { using type = T; };
    template<typename T>    struct remove_reference<T&>         { using type = T; };
    template<typename T>    struct remove_reference<T&&>        { using type = T; };

    template<typename T>
    using remove_cv_t = typename remove_cv<T>::type;

    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;

} // namespace mstl