#include  "random.h"

int Random::randomNumber(int min, int max, int seed) {
    typedef std::mt19937 range_t;
    std::uniform_int_distribution<range_t::result_type> udist(min, max);
    range_t range;

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    range_t::result_type s = seed * ms;
    range.seed(s);

    range_t::result_type result = udist(range);

    return result;
}
