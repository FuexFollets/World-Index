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
        

        using derived_metric_prefix = R;
        using derived_basic_unit_template = derived_template;
        using derived_specialization = derived_template<exp_power, metric_prefix>;
        using quantative_type = Qt;



        derived_specialization operator+(const auto&);
        derived_specialization operator+(const same_unit_different_metric_prefix<derived_specialization> auto&);
        derived_specialization operator+(const derived_specialization&);

        derived_specialization operator-(const auto&);
        derived_specialization operator-(const same_unit_different_metric_prefix<derived_specialization> auto&);
        derived_specialization operator-(const derived_specialization&);

        derived_specialization operator*(const auto&);
        auto operator*(const same_unit_as<derived_specialization> auto& multiplied) -> 
            derived_template<decltype(multiplied)::power + power, derived_metric_prefix>;
        derived_specialization operator/(const auto&);
        auto operator/(const same_unit_as<derived_specialization> auto& multiplied) -> 
            derived_template<decltype(multiplied)::power - power, derived_metric_prefix>;

        derived_specialization operator+=(const auto&);
        derived_specialization operator-=(const auto&);
        derived_specialization operator*=(const auto&);
        derived_specialization operator/=(const auto&);
    };
}

