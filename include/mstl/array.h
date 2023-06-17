#pragma once

#include "mstl/internal/config.h"
#include "mstl/iterator.h"
#include "mstl/algorithm.h"
#include "mstl/type_traits.h"
#include "mstl/utility.h"

#include <cstddef>

namespace mstl {

    template<typename T, size_t N>
    class _array_const_iterator
    {
    public:
#ifdef __cpp_lib_concepts
        // using iterator_concept = continuous_iterator_tag; // TODO: Implement
#endif
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

    public:
        _array_const_iterator() noexcept
            : m_ptr()
        {}

        explicit _array_const_iterator(pointer ptr) noexcept
            : m_ptr(ptr)
        {}

        reference operator*() const noexcept {
            return *m_ptr;
        }

        pointer operator->() const noexcept {
            return m_ptr;
        }

        _array_const_iterator operator+(const ptrdiff_t offset) const noexcept {
            _array_const_iterator temp = *this;
            temp += offset;
            return temp;
        }

        _array_const_iterator &operator++() noexcept {
            ++m_ptr;
            return *this;
        }

        _array_const_iterator operator++(int) noexcept {
            _array_const_iterator temp = *this;
            ++m_ptr;
            return temp;
        }
        
        _array_const_iterator &operator+=(const ptrdiff_t offset) noexcept {
            m_ptr += offset;
            return *this;
        }
        
        _array_const_iterator operator-(const ptrdiff_t offset) const noexcept {
            _array_const_iterator temp = *this;
            m_ptr -= offset;
            return temp;
        }

        _array_const_iterator &operator--() noexcept {
            --m_ptr;
            return *this;
        }

        _array_const_iterator operator--(int) noexcept {
            _array_const_iterator temp = *this;
            --m_ptr;
            return temp;
        }

        _array_const_iterator &operator-=(const ptrdiff_t offset) noexcept {
            m_ptr -= offset;
            return *this;
        }

        reference operator[](const ptrdiff_t offset) const noexcept {
            return *(*this + offset);
        }

        bool operator==(const _array_const_iterator& rhs) const noexcept {
            return m_ptr == rhs.m_ptr;
        }

#ifndef MSTL_CPP20
        bool operator!=(const _array_const_iterator& rhs) const noexcept {
            return m_ptr != rhs.m_ptr;
        }

        bool operator>(const _array_const_iterator& rhs) const noexcept {
            return m_ptr > rhs.m_ptr;
        }

        bool operator>=(const _array_const_iterator& rhs) const noexcept {
            return m_ptr >= rhs.m_ptr;
        }

        bool operator<(const _array_const_iterator& rhs) const noexcept {
            return m_ptr < rhs.m_ptr;
        }

        bool operator<=(const _array_const_iterator& rhs) const noexcept {
            return m_ptr <= rhs.m_ptr;
        }
#else // ifdef MSTL_CPP20
        constexpr std::strong_ordering operator<=>(const _array_const_iterator& rhs) const noexcept {
            return m_ptr <=> rhs.m_ptr;
        }
#endif

    private:
        const T *m_ptr;
    };

    template<typename T, size_t N>
    class _array_iterator : public _array_const_iterator<T, N>
    {
    private:
        using _base_iterator = _array_const_iterator<T, N>;

    public:
#if defined(__cpp_lib_concepts) && !defined(MSTL_CONCEPTS_NOT_YET_IMPL)
        // using iterator_concept = continuous_iterator_tag; // Implement
#endif
        using iterator_category = random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    
    public:
        _array_iterator() noexcept {}

        explicit _array_iterator(pointer ptr) noexcept
            : _base_iterator(ptr)
        {}

        reference operator*() const noexcept {
            return const_cast<reference>(_base_iterator::operator*());
        }

        pointer operator->() {
            return const_cast<pointer>(_base_iterator::operator->());
        }

        _array_iterator operator+(const ptrdiff_t offset) const noexcept {
            _array_iterator temp = *this;
            temp += offset;
            return temp;
        }

        _array_iterator &operator++() noexcept {
            _base_iterator::operator++();
            return *this;
        }

        _array_iterator operator++(int) noexcept {
            _array_iterator temp = *this;
            _base_iterator::operator++();
            return temp;
        }
        
        _array_iterator &operator+=(const ptrdiff_t offset) noexcept {
            _base_iterator::operator+=(offset);
            return *this;
        }
        
        _array_iterator operator-(const ptrdiff_t offset) const noexcept {
            _array_iterator temp = *this;
            temp -= offset;
            return temp;
        }

        _array_iterator &operator--() noexcept {
            _base_iterator::operator--();
            return *this;
        }

        _array_iterator operator--(int) noexcept {
            _array_iterator temp = *this;
            _base_iterator::operator--();
            return temp;
        }

        _array_iterator &operator-=(const ptrdiff_t offset) noexcept {
            _base_iterator::operator-=(offset);
            return *this;
        }

        reference operator[](const ptrdiff_t offset) const noexcept {
            return const_cast<reference>(_base_iterator::operator[](offset));
        }

    };

    template<typename T, size_t N>
    class array
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = T*;
        using iterator = _array_iterator<T, N>;
        using const_iterator = _array_const_iterator<T, N>;
        using reverse_iterator = mstl::reverse_iterator<iterator>;
        using const_reverse_iterator = mstl::reverse_iterator<const_iterator>;

    public:
        MSTL_CPP17_CONSTEXPR reference at(size_type i) {
            return __elements[i];
        }

        MSTL_CPP14_CONSTEXPR const_reference at(size_type i) const {
            return __elements[i];
        }

        MSTL_CPP17_CONSTEXPR reference operator[](size_type i) {
            return __elements[i];
        }

         MSTL_CPP14_CONSTEXPR const_reference operator[](size_type i) const {
            return __elements[i];
        }

        MSTL_CPP17_CONSTEXPR reference front() {
            return __elements[0];
        }

        MSTL_CPP14_CONSTEXPR const_reference front() const {
            return __elements[0];
        }

        MSTL_CPP17_CONSTEXPR reference back() {
            return __elements[N - 1];
        }

        MSTL_CPP14_CONSTEXPR const_reference back() const {
            return __elements[N - 1];
        }

        MSTL_CPP17_CONSTEXPR pointer data() {
            return __elements;
        }

        MSTL_CPP17_CONSTEXPR const_pointer data() const {
            return __elements;
        }

        MSTL_CPP17_CONSTEXPR iterator begin() noexcept {
            return iterator(__elements);
        }

        MSTL_CPP17_CONSTEXPR const_iterator begin() const noexcept {
            return const_iterator(__elements);
        }

        MSTL_CPP17_CONSTEXPR const_iterator cbegin() const noexcept {
            return iterator(__elements);
        }

        MSTL_CPP17_CONSTEXPR iterator end() noexcept {
            return iterator(__elements + N);
        }

        MSTL_CPP17_CONSTEXPR const_iterator end() const noexcept {
            return const_iterator(__elements + N);
        }

        MSTL_CPP17_CONSTEXPR const_iterator cend() const noexcept {
            return const_iterator(__elements + N);
        }
        
        MSTL_CPP17_CONSTEXPR reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        }
        
        MSTL_CPP17_CONSTEXPR const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        MSTL_CPP17_CONSTEXPR const_reverse_iterator crbegin() const noexcept {
            return rbegin();
        }

        MSTL_CPP17_CONSTEXPR reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        MSTL_CPP17_CONSTEXPR const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(begin());
        }

        MSTL_CPP17_CONSTEXPR const_reverse_iterator crend() const noexcept {
            return rend();
        }

        MSTL_CPP20_NODISCARD constexpr bool empty() const noexcept { return false; }
        constexpr size_t size() const noexcept { return N; }
        constexpr size_t max_size() const noexcept { return N; }

        // TODO: Replace this with my own function
        MSTL_CPP20_CONSTEXPR void fill(const_reference value) {
            mstl::fill_n(__elements, N, value);
        }

        MSTL_CPP20_CONSTEXPR void swap(array& other) noexcept {
            for (size_type i = 0; i < N; i++) {
                value_type temp = __elements[i];
                __elements[i] = other.__elements[i];
                other.__elements[i] = temp;
            }
        }

        value_type __elements[N];
    };

    template<typename T>
    class array<T, 0>
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = T*;
        using iterator = _array_iterator<T, 0>;
        using const_iterator = _array_const_iterator<T, 0>;
        using reverse_iterator = mstl::reverse_iterator<iterator>;
        using const_reverse_iterator = mstl::reverse_iterator<const_iterator>;

    public:
        MSTL_CPP17_CONSTEXPR reference at(size_type pos) { return *data(); }
        MSTL_CPP14_CONSTEXPR const_reference at(size_type pos) const { return *data(); }
        MSTL_CPP17_CONSTEXPR reference operator[](size_type pos) { return *data(); }
        MSTL_CPP14_CONSTEXPR const_reference operator[](size_type pos) const { return *data(); }
    
        MSTL_CPP17_CONSTEXPR reference front() { return *data(); }
        MSTL_CPP14_CONSTEXPR const_reference front() const { return *data(); }

        MSTL_CPP17_CONSTEXPR reference back() { return *data(); }
        MSTL_CPP14_CONSTEXPR const_reference back() const { return *data(); }

        MSTL_CPP17_CONSTEXPR pointer data() noexcept { return nullptr; }
        MSTL_CPP17_CONSTEXPR const_pointer data() const noexcept { return nullptr; }

        MSTL_CPP17_CONSTEXPR iterator begin() noexcept { return iterator(nullptr); }
        MSTL_CPP17_CONSTEXPR const_iterator begin() const noexcept { return const_iterator(nullptr); }
        MSTL_CPP17_CONSTEXPR const_iterator cbegin() const noexcept { return begin(); }

        MSTL_CPP17_CONSTEXPR iterator end() noexcept { return iterator(nullptr); }
        MSTL_CPP17_CONSTEXPR const_iterator end() const noexcept { return const_iterator(nullptr); }
        MSTL_CPP17_CONSTEXPR const_iterator cend() const noexcept { return end(); }

        MSTL_CPP17_CONSTEXPR reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        MSTL_CPP17_CONSTEXPR const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(cend()); }
        MSTL_CPP17_CONSTEXPR const_reverse_iterator crbegin() const noexcept { return rbegin(); }

        MSTL_CPP17_CONSTEXPR reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        MSTL_CPP17_CONSTEXPR const_reverse_iterator rend() const noexcept { return const_reverse_iterator(cbegin()); }
        MSTL_CPP17_CONSTEXPR const_reverse_iterator crend() const noexcept { return rend(); }

        MSTL_CPP20_NODISCARD constexpr bool empty() const noexcept { return true; }
        constexpr size_type size() const noexcept { return 0; }
        constexpr size_type max_size() const noexcept { return 0; }
    
        MSTL_CPP20_CONSTEXPR void fill(const_reference value) {}
        MSTL_CPP20_CONSTEXPR void swap(array<T, 0>& other) noexcept {}
    };

    template<typename T, size_t N>
    MSTL_CPP20_CONSTEXPR bool operator==(const array<T,N>& lhs, const array<T, N>& rhs) {
        return mstl::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    template<typename T, size_t N>
    MSTL_CPP20_CONSTEXPR bool operator!=(const array<T,N>& lhs, const array<T, N>& rhs) {
        return !mstl::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename T, size_t N>
    MSTL_CPP20_CONSTEXPR bool operator<(const array<T, N>& lhs, const array<T, N> rhs) {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    
    template<typename T, size_t N>
    MSTL_CPP20_CONSTEXPR bool operator<=(const array<T, N>& lhs, const array<T, N> rhs) {
        return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template<typename T, size_t N>
    MSTL_CPP20_CONSTEXPR bool operator>(const array<T, N>& lhs, const array<T, N> rhs) {
        return lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }
    
    template<typename T, size_t N>
    MSTL_CPP20_CONSTEXPR bool operator>=(const array<T, N>& lhs, const array<T, N> rhs) {
        return !lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    // TODO: <=>
#ifdef MSTL_CPP20
    template<typename T, size_t N>
    constexpr bool operator<=>(const array<T, N>& lhs, const array<T, N>& rhs) {
        // TODO: Implement this 
        return true;
    }
#endif

    template<size_t I, typename T, size_t N>
    MSTL_CPP20_CONSTEXPR T& get(const array<T, N>& array) noexcept {
        static_assert(I < N, "Array index out of bounds");
        return array.__elements[I];
    }
    
    template<size_t I, typename T, size_t N>
    MSTL_CPP20_CONSTEXPR const T& get(const array<T, N>& array) noexcept {
        static_assert(I < N, "Array index out of bounds");
        return array.__elements[I];
    }
    
    template<size_t I, typename T, size_t N>
    MSTL_CPP20_CONSTEXPR T&& get(const array<T, N>& array) {
        static_assert(I < N, "Array index out of bounds");
        return mstl::move(array.__elements[I]);
    }

    template<size_t I, typename T, size_t N>
    MSTL_CPP20_CONSTEXPR const T&& get(const array<T, N>& array) noexcept {
        static_assert(I < N, "Array index out of bounds");
        return mstl::move(array.__elements[I]);
    }

    template <typename T, size_t N>
    MSTL_CPP20_CONSTEXPR void swap(array<T, N>& a, array<T, N>& b) {
        for(size_t i = 0; i < N; i++) {
            T temp = a[i];
            a[i] = b[i];
            b[i] = temp;
        }
    }

#ifdef MSTL_CPP20
    namespace detail {
        template<typename T, size_t N, size_t... I>
        constexpr array<remove_cv_t<T>, N> to_array_impl(T (&a)[N], std::index_sequence<I...>) {
            return {{a[I]...}};
        }

        template<typename T, size_t N, size_t... I>
        constexpr array<remove_cv_t<T>, N> to_array_impl(T (&&a)[N], std::index_sequence<I...>) {
            return {{mstl::move(a[I])...}};
        }
    }

    template<typename T, size_t N>
    constexpr array<remove_cv_t<T>, N> to_array(T (&a)[N]) {
        return detail::to_array_impl(a, std::make_index_sequence<N>{});
    }
    
    template<typename T, size_t N>
    constexpr array<remove_cv_t<T>, N> to_array(T (&&a)[N]) {
        return detail::to_array_impl(a, std::make_index_sequence<N>{});
    }

#endif

    // TODO: std::tuple_size
    // TODO: std::tuple_element

} // namespace mstl
