#include  "random.h"

int Random::randomNumber(int min, int max, int seed) {
    typedef std::mt19937 range_t;
    std::uniform_int_distribution<range_t::result_type> udist(min, max);
    range_t range;

    range_t::result_type s = seed;
    range.seed(s);

    range_t::result_type result = udist(range);

    return result;
}
