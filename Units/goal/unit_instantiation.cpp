#include "../unit.hpp"

namespace unit { namespace distance {

    template <metric_prefix_ratio ratio>
    using basic_meter = basic_unit<
        unit_option<1, ratio, "m">
    >;

    using meter = basic_meter<no_prefix>;

}} // End of namespaces unit and distance
