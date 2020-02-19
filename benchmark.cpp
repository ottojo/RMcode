#include <benchmark/benchmark.h>
#include <RMCode/RMCode.hpp>
#include <iostream>

static void BM_Decode(benchmark::State &state) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    for (auto _:state) {
        state.PauseTiming();
        auto randomReceiveVector = util::Array::randomBool<RMCode<2, 5>::getN()>(generator);
        state.ResumeTiming();
        auto decoded = RMCode<2, 5>::getValidCodeword(randomReceiveVector);
        benchmark::DoNotOptimize(decoded);
    }
}

BENCHMARK(BM_Decode);

template<int m>
static void BM_Decode_Template(benchmark::State &state) {
    constexpr auto r = m / 2;
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    for (auto _:state) {
        state.PauseTiming();
        auto randomReceiveVector = util::Array::randomBool<RMCode<r, m>::getN()>(generator);
        state.ResumeTiming();
        auto decoded = RMCode<r, m>::getValidCodeword(randomReceiveVector);
        benchmark::DoNotOptimize(decoded);
    }
    state.SetLabel(
            "R(" + std::to_string(r) + "," + std::to_string(m) + ") (" + std::to_string(RMCode<r, m>::getN()) + "," +
            std::to_string(RMCode<r, m>::getK()) + "," + std::to_string(RMCode<r, m>::getD()) + ")");
    state.SetComplexityN(RMCode<r, m>::getN());
}

BENCHMARK_TEMPLATE1(BM_Decode_Template, 1);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 2);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 3);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 4);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 5);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 6);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 7);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 8);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 9);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 10);
BENCHMARK_TEMPLATE1(BM_Decode_Template, 15);

BENCHMARK_MAIN();