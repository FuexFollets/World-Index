#pragma once

#include "../unit.hpp"

namespace unit {
    template <metric_prefix_ratio ratio>
    struct basic_meter : basic_unit<
        unit_option<std::integral_constant<int, 1>, ratio, unit_name_literal<'m'>,
        basic_meter<
    > {};

}
