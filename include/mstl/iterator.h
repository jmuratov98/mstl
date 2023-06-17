#pragma once

#include "mstl/internal/config.h"

#include <cstddef>

namespace mstl {

    // TODO: move to type_traits
#ifdef MSTL_CPP11
    template<typename... Ts> struct make_void { using type = void; };
    template<typename... Ts> using void_t = typename make_void<Ts...>::type;
#else
    template<typename... Ts> using void_t = void;
#endif

    // TODO: std::advance;

    // Iterator tags -- https://en.cppreference.com/w/cpp/iterator/iterator_tags
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
#ifdef MSTL_CPP20
    struct contiguous_iterator_tag : public random_access_iterator_tag {};
#endif

    // Iterator concept
#ifdef MSTL_CPP20
    #define MSTL_CONCEPTS_NOT_YET_IMPL
#endif

    template<
        typename Categroy,
        typename T,
        typename Distance = ptrdiff_t,
        typename Pointer = T*,
        typename Reference = T&
    >
    class MSTL_DEPRECATED iterator
    {
    public:
        using iterator_category = Categroy;
        using value_type        = T;
        using difference_type   = Distance;
        using pointer           = Pointer;
    };

    namespace internal {
        template<typename Iter, class = void>
        struct default_iterator_traits {};

        template<typename Iter>
        struct default_iterator_traits<
            Iter,
            void_t<
#if defined(MSTL_CPP20) && !defined(MSTL_CONCEPTS_NOT_YET_IMPL)
                typename Iter::iterator_concept,
#endif
                typename Iter::iterator_category,
                typename Iter::value_type,
                typename Iter::difference_type,
                typename Iter::pointer,
                typename Iter::reference
            >
        >
        {
#if defined(MSTL_CPP20) && !defined(MSTL_CONCEPTS_NOT_YET_IMPL)
            using iterator_concept      = typename Iter::iterator_concept;
#endif
            using iterator_category     = typename Iter::iterator_category;
            using value_type            = typename Iter::value_type;
            using difference_type       = typename Iter::difference_type;
            using pointer               = typename Iter::pointer;
            using reference             = typename Iter::reference;
        };
    }

    template<typename Iter>
    struct iterator_traits : internal::default_iterator_traits<Iter> {};

    template<typename Iter>
    struct iterator_traits<Iter*>
    {
#if defined(MSTL_CPP20) && !defined(MSTL_CONCEPTS_NOT_YET_IMPL)
        using iterator_concept          = contiguous_iterator_tag; 
#endif
        using iterator_category         = random_access_iterator_tag;
        using value_type                = typename Iter::value_type;
        using difference_type           = typename Iter::difference_type;
        using pointer                   = typename Iter::pointer;
        using reference                 = typename Iter::reference;
    };

#ifndef MSTL_CPP20
    template<typename Iter>
    struct iterator_traits<const Iter*>
    {
        using iterator_category         = random_access_iterator_tag;
        using value_type                = typename Iter::value_type;
        using difference_type           = typename Iter::difference_type;
        using pointer                   = typename Iter::pointer;
        using reference                 = typename Iter::reference;
    };
#endif // !MSTL_CPP20

    template<typename BiDirIt>
    MSTL_CPP17_CONSTEXPR BiDirIt prev(BiDirIt it, typename mstl::iterator_traits<BiDirIt>::difference_type n = 1) {
        std::advance(it, -n);
        return it;
    }

    template<typename Iter>
    class reverse_iterator
    {
    public:
        using iterator_type         = Iter;
#ifndef MSTL_CPP20
        using iterator_category     = typename mstl::iterator_traits<Iter>::iterator_category;
        using value_type            = typename mstl::iterator_traits<Iter>::value_type;
        using difference_type       = typename mstl::iterator_traits<Iter>::difference_type;
        using pointer               = typename mstl::iterator_traits<Iter>::pointer;
        using reference             = typename mstl::iterator_traits<Iter>::reference;
#else
        // TODO: Change this to the new standard
        using iterator_category     = typename mstl::iterator_traits<Iter>::iterator_category;
        using value_type            = typename mstl::iterator_traits<Iter>::value_type;
        using difference_type       = typename mstl::iterator_traits<Iter>::difference_type;
        using pointer               = typename mstl::iterator_traits<Iter>::pointer;
        using reference             = typename mstl::iterator_traits<Iter>::reference;
#endif
    public:
        MSTL_CPP17_CONSTEXPR reverse_iterator() = default;
        MSTL_CPP17_CONSTEXPR explicit reverse_iterator(Iter it)
            : m_it(it)
        {}

        template<typename U>
        MSTL_CPP17_CONSTEXPR explicit reverse_iterator(const U& other)
            : m_it(other.base())
        {}

        template<typename U>
        MSTL_CPP17_CONSTEXPR reverse_iterator& operator=(const U* other)
        {
            m_it = other.base();
            return *this;
        }

        MSTL_CPP17_CONSTEXPR iterator_type base() const { return m_it; }

        MSTL_CPP17_CONSTEXPR reference operator*() const {
            Iter tmp = m_it;
            return *--tmp;
        }

        MSTL_CPP17_CONSTEXPR pointer operator->() const { return &(operator*()); }

        MSTL_CPP17_CONSTEXPR reference operator[](difference_type n) const { return m_it[-n - 1]; }

        MSTL_CPP17_CONSTEXPR reverse_iterator operator+(difference_type n) const { return reverse_iterator(m_it - n); }
        MSTL_CPP17_CONSTEXPR reverse_iterator &operator+=(difference_type n) { m_it -= n; return *this; }
        MSTL_CPP17_CONSTEXPR reverse_iterator &operator++() { --m_it; return *this; }
        MSTL_CPP17_CONSTEXPR reverse_iterator operator++(int) { reverse_iterator temp = m_it; --m_it; return temp; }
        MSTL_CPP17_CONSTEXPR reverse_iterator operator-(difference_type n) const { return reverse_iterator(m_it + n); }
        MSTL_CPP17_CONSTEXPR reverse_iterator &operator-=(difference_type n) { m_it += n; return *this; }
        MSTL_CPP17_CONSTEXPR reverse_iterator &operator--() { ++m_it; return *this; }
        MSTL_CPP17_CONSTEXPR reverse_iterator operator--(int) { reverse_iterator temp = m_it; ++m_it; return temp; }

        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR bool operator==(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it == rhs.m_it;
        }

        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR bool operator!=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it != rhs.m_it;
        }

        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR bool operator<(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it < rhs.m_it;
        }

        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR bool operator<=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it <= rhs.m_it;
        }

        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR bool operator>(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it > rhs.m_it;
        }

        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR bool operator>=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it >= rhs.m_it;
        }

#ifdef MSTL_CPP20
        template<typename Iter1, typename Iter2>
        friend MSTL_CPP17_CONSTEXPR std::strong_ordering operator<=>(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {
            return lhs.m_it <=> rhs.m_it;
        }
#endif

    protected:
        Iter m_it = Iter(); // The standard calls this current
    };

    template<typename Iter>
    MSTL_CPP17_CONSTEXPR reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it) {
        return reverse_iterator<Iter>(it.base() - n);
    }

    template<typename Iter>
    MSTL_CPP17_CONSTEXPR reverse_iterator<Iter> operator-(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it) {
        return reverse_iterator<Iter>(it.base() + n);
    }

#ifdef MSTL_CPP20
    // TODO: iter_move()
    // TODO: iter_swap()
#endif

#ifdef MSTL_CPP14
    template<typename Iter>
    MSTL_CPP17_CONSTEXPR reverse_iterator<Iter> make_reverse_iterator(Iter i) {
        return reverse_iterator<Iter>(i);
    }
#endif

} // namespace mstl
