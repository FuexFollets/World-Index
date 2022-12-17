#pragma once

#include <cstdint>
#include <ratio>
#include <concepts>
#include <type_traits>

#include "unit_options.hpp"

namespace unit {
    struct include_base_10_compensator {
        int compensated_power {};
    };

    struct no_include_base_10_compensator {};

    /* Inheritable template struct for implementing unit templates */
    template <
        unit_option_type option,
        template <typename...> typename specalized_template
    >
    struct basic_unit :
        std::conditional<
            std::is_integral_v<typename option::quantative_type>,
            no_include_base_10_compensator,
            include_base_10_compensator
        > {
        protected:

        typename option::quantative_type value;

        public:

        using unit_option = option;
        using this_type = basic_unit<option, specalized_template>;
    };
}

