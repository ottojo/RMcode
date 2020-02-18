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

BENCHMARK_MAIN();