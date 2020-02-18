/**
 * @file RMCode.hpp
 * @author jonas
 * @date 2/14/20
 * Description here TODO
 */

#ifndef RMCODE_RMCODE_HPP
#define RMCODE_RMCODE_HPP

#include <util/Math.hpp>
#include <array>
#include <optional>
#include <util/Array.hpp>

template<unsigned int r, unsigned int m>
class RMCode {
public:
    static constexpr unsigned int getN() {
        // Hacky constexpr 2^m
        return 1u << m;
    }

    static constexpr unsigned int getK() {
        unsigned int k = 0;
        for (unsigned int i = 0; i <= r; i++) {
            k += util::Math::binom(m, i);
        }
        return k;
    }

    static constexpr unsigned int getD() {
        // 2^(m-r)
        return 1u << (m - r);
    }

    /**
     * Decodes the input to a valid codeword
     * @param input y=c+e
     * @return c
     */
    static auto getValidCodeword(std::array<bool, getN()> input) -> std::optional<std::array<bool, getN()>> {
        auto y_u = util::Array::firstK<getN() / 2>(input);
        auto y_v = util::Array::lastK<getN() / 2>(input);

        // y_u + y_v
        auto y_u_y_v = util::Math::addArrayBin(y_u, y_v);

        // Decode with Cv
        auto v = RMCode<r - 1, m - 1>::getValidCodeword(y_u_y_v);
        if (not v.has_value()) {
            return std::nullopt;
        }

        // y_v + v
        auto y_v_v = util::Math::addArrayBin(y_v, v.value());

        auto u_1 = RMCode<r, m - 1>::getValidCodeword(y_u);
        auto u_2 = RMCode<r, m - 1>::getValidCodeword(y_v_v);

        if (not u_1.has_value() and not u_2.has_value()) {
            // Decoding u has failed
            return std::nullopt;
        }

        // Return (u|u+v)
        if (!u_1.has_value()) {
            return util::Array::concat(u_2.value(), util::Math::addArrayBin(u_2.value(), v.value()));
        }
        return util::Array::concat(u_1.value(), util::Math::addArrayBin(u_1.value(), v.value()));
    }
};

template<unsigned int m>
class RMCode<0, m> {
public:
    static constexpr int getN() {
        // Hacky constexpr 2^m
        return 1u << m;
    }

    static constexpr int getK() {
        return 1;
    }

    static constexpr int getD() {
        // 2^(m-r)
        return 1u << (m - 0);
    }

    /**
     * Decodes the input to a valid codeword
     *
     * Special case for repetition code
     *
     * @param input y=c+e
     * @return c
     */
    static auto getValidCodeword(std::array<bool, getN()> input) -> std::optional<std::array<bool, getN()>> {
        auto zeros = 0;
        auto ones = 0;
        for (auto bit : input) {
            if (bit == 1) {
                ones++;
            } else {
                zeros++;
            }
        }
        if (ones == zeros) {
            return std::nullopt;
        } else {
            std::array<bool, getN()> result;
            if (ones > zeros) {
                result.fill(1);
            } else {
                result.fill(0);
            }
            return result;
        }
    };
};

template<unsigned int m>
class RMCode<m, m> {
public:
    static constexpr int getN() {
        return 1u << m;
    }

    static constexpr int getK() {
        return getN();
    }

    static constexpr int getD() {
        return 1;
    }

    /**
        * Decodes the input to a valid codeword
        *
        * Special case: R(m, m) = C(n, k=n, 1) (no encoding)
        *
        * @param input y=c+e
        * @return c
        */
    static auto getValidCodeword(std::array<bool, getN()> input) -> std::optional<std::array<bool, getN()>> {
        return input;
    }
};

#endif //RMCODE_RMCODE_HPP
