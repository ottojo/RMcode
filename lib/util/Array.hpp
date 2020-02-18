#ifndef RMCODE_ARRAY_HPP
#define RMCODE_ARRAY_HPP

namespace util {
    class Array {
    public:

        /**
         * Returns a new array containing the first k elements of the vector.
         * @tparam k length of resulting array
         * @tparam n length of input array
         * @tparam T element type of input array
         */
        template<std::size_t k, std::size_t n, typename T>
        static std::array<T, k> firstK(const std::array<T, n> &input) {
            static_assert(k <= n, "Input array smaller than output array");
            std::array<T, k> result;
            std::copy(input.begin(), input.begin() + k, result.begin());
            return result;
        }

        /**
         * Returns a new array containing the last k elements of the vector.
         * @tparam k length of resulting array
         * @tparam n length of input array
         * @tparam T element type of input array
         */
        template<std::size_t k, std::size_t n, typename T>
        static std::array<T, k> lastK(const std::array<T, n> &input) {
            static_assert(k <= n, "Input array smaller than output array");
            std::array<T, k> result;
            std::copy(input.end() - k, input.end(), result.begin());
            return result;
        }

        /**
         * Returns a new array containing the elements of both input arrays
         * @tparam T element type of input array
         * @tparam n length of first array
         * @tparam k length of second array
         */
        template<typename T, std::size_t n, std::size_t k>
        static std::array<T, n + k> concat(const std::array<T, n> &a1, const std::array<T, k> &a2) {
            std::array<T, n + k> result;
            std::copy(a1.begin(), a1.end(), result.begin());
            std::copy(a2.begin(), a2.end(), result.begin() + a1.size());
            return result;
        }

        /**
         * Converts an array to a string by calling std::to_string on each element
         * @tparam T element type of input array
         * @tparam n length of array
         */
        template<typename T, std::size_t n>
        static std::string print(const std::array<T, n> &in) {
            std::string r;
            for (const auto &b:in) {
                r += std::to_string(b);
            }
            return r;
        }
    };
}

#endif //RMCODE_ARRAY_HPP
