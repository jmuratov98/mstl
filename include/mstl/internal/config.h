#pragma once

#if __cplusplus == 201103L
    #define MSTL_CPP11
#elif __cplusplus == 201402L
    #define MSTL_CPP14
#elif __cplusplus == 201703L
    #define MSTL_CPP17
#elif __cplusplus == 202002L
    #define MSTL_CPP20
#endif

#ifdef MSTL_CPP14
    #define MSTL_CPP14_CONSTEXPR constexpr
#else
    #define MSTL_CPP14_CONSTEXPR inline
#endif

#ifdef MSTL_CPP17
    #define MSTL_CPP17_CONSTEXPR constexpr
#else
    #define MSTL_CPP17_CONSTEXPR inline
#endif

#ifdef MSTL_CPP20
    #define MSTL_CPP20_CONSTEXPR constexpr
    #define MSTL_CPP20_NODISCARD [[nodiscard]]
#else
    #define MSTL_CPP20_CONSTEXPR inline
    #define MSTL_CPP20_NODISCARD
#endif

#define MSTL_DEPRECATED
