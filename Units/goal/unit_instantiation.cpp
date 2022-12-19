#include "../unit.hpp"

namespace unit { namespace distance {
    template <
        typename prefix,
        typename power
    > struct meter : basic_unit<
        unit_option<power, prefix, "m">,
        meter
    > {};
}} // End of namespaces unit and distance
