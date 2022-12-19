#include "../unit.hpp"

namespace unit { namespace distance {
    template <
        typename prefix,
        typename power
    > struct meter : basic_unit<
        unit_option<power, prefix, unit_name_literal<'m'>>,
        meter
    > {};
}} // End of namespaces unit and distance
