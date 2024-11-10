#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace primeCompression {

template <typename T, std::size_t N>
class Array {
public:
    using elementType = T;
    T array[N];

    T& operator[](std::size_t pos) { 
        return array[pos];
    }

    const T& operator[](std::size_t pos) { 
        return array[pos];
    }

    void fill(const T& value) {
        std::fill_n(begin(), size(), value);
    }

    T* data() {
        return array;
    }

    const T* data() {
        return array;
    }

    T* begin() {
        return array;
    }

    const T* begin() {
        return array;
    }
  
    T* end() {
        return array + N;
    }

    const T* end() {
        return array + N;
    }

    T& back() {
        return array[N - 1];
    }

    const T& back() {
        return array[N - 1];
    }

    constexpr std::size_t size() {
        return N;
    }
};

} // end of namespace 

#endif
