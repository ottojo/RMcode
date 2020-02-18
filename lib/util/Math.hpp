#ifndef RMCODE_MATH_HPP
#define RMCODE_MATH_HPP

namespace util {
    class Math {
    public:

        /**
         * constexpr binomial coefficient,
         * stolen from user "Walter" on stackoverflow: https://stackoverflow.com/a/44719165/4162386
         */
        static constexpr unsigned int binom(unsigned int n, unsigned int k) noexcept {
            return
                    (k > n) ? 0 :                       // out of range
                    (k == 0 || k == n) ? 1 :            // edge
                    (k == 1 || k == n - 1) ? n :        // first
                    (k + k < n) ?                       // recursive:
                    (binom(n - 1, k - 1) * n) / k :     //  path to k=1   is faster
                    (binom(n - 1, k) * n) / (n - k);    //  path to k=n-1 is faster
        }

        /**
         * Modulo 2 addition of arrays
         * @tparam T array type
         * @param t1
         * @param t2
         * @return t1 ⊕ t2
         */
        template<typename T>
        static T addArrayBin(T t1, T t2) {
            T result;
            for (std::size_t i = 0; i < t1.size(); i++) {
                result[i] = (t1[i] + t2[i]) % 2;
            }
            return result;
        }
    };
}

#endif //RMCODE_MATH_HPP
