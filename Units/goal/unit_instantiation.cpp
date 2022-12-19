#include "../unit.hpp"
#include <ratio>

namespace unit { namespace distance {
    template <typename option> 
        // requires option::power and option::prefix to exist
        requires requires { option::power; typeid(typename option::prefix); }

    struct basic_meter : basic_unit<
        unit_option<typename option::power, typename option::prefix, unit_name_literal<'m'>>,
        basic_meter
    > {};

    //      name        unit name                                                   power   prefix
    using	meter	=	basic_meter<derived_unit_option<std::integral_constant<int,	1>,     no_prefix>>;
    using	kilo_meter	=	basic_meter<derived_unit_option<std::integral_constant<int,	1>,	std::kilo>>;
}} // End of namespaces unit and distance
