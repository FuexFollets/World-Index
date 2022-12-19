#pragma once

#include <cstdint>
#include <ratio>
#include <concepts>
#include <type_traits>

#include "unit_options.hpp"

namespace unit { namespace constraints {
        // Integral constant that checks if two unit templates (template structs that have derived from basic_unit) are the same

        // Integral constant which evaluates to true if type 'T' is a unit
        template <typename T>
            struct is_unit : std::integral_constant<bool,
                requires { requires T::is_unit::value; }> {};

        // Type constrant for unit
        template <typename T>
            concept unit = is_unit<T>::value;

        // Integral constant that checks if two units have the same metric prefix ratio
        template <unit T, unit U>
        using is_same_metric_prefix_ratio = std::is_same<
            typename T::unit_option::metric_prefix,
            typename U::unit_option::metric_prefix
        >;

        // Integral constant that checks if two units have the same power
        template <unit T, unit U>
        using is_same_power = std::integral_constant<bool,
              T::unit_option::power == U::unit_option::power
        >;

        template <unit T, unit U>
        struct is_same_unit_template : std::is_same<T, U> {};

        template <
            template <typename...> typename unit_template,
            typename T1arg1, typename T1arg2,
            typename T2arg1, typename T2arg2
        > struct is_same_unit_template<unit_template<T1arg1, T1arg2>, unit_template<T2arg1, T2arg2>>
            : std::true_type {};


        template <typename T, typename U>
        concept same_unit_as = 
            is_unit<T>::value && is_unit<U>::value &&
            std::is_same_v<T, U>;
    } // end of namespace constraints


    struct no_include_base_10_compensator {};

    /* Inheritable template struct for implementing unit templates */
    template <
        unit_option_type option,
        template <typename> typename specalized_template
    >
    struct basic_unit {
        protected:

        typename option::quantative_type value; // only member variable

        public:

        using unit_option = option;
        using this_type = basic_unit<option, specalized_template>;
        using is_unit = std::integral_constant<bool, true>;

        this_type operator+(const this_type& measure) { return this_type {value + measure.value}; }
    };
} // end of namespace unit

