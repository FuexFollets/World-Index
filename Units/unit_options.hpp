#pragma once

#include <concepts>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <algorithm>

/* Synopsis:
 * Contains the default qunatative_type for all units
 * Contains unit_option, a type used for instantiating new units
 */

namespace unit {
    template <std::size_t name_size>
    struct unit_name_literal {
        constexpr unit_name_literal(const char (&str)[name_size]) {
            std::copy_n(str, name_size, value);
        }

        const char value[name_size];
    };

    using default_quantative_type = long double; // the quantative type for all units

    /* Checks if a integer is a integer power of 10 */
    template <std::integral T>
        constexpr bool constexpr_power_of_10(T whole_number) {
        if (whole_number == 1) return true;

        while (whole_number != 0) {
            if (whole_number == 1) return true;
            if (whole_number % 10 != 0) return false;

            whole_number /= 10;
        }
        return false;
    }


    /* Indicator for no metric prefix */
    struct no_prefix {};


    /* Metric prefix ratio concept (ex: std::milli, std::tera) */
    template <typename T>
        concept metric_prefix_ratio = requires {
            T::num;
            T::den;
        } &&
        constexpr_power_of_10(T::num) && constexpr_power_of_10(T::den) ||
        std::same_as<T, no_prefix>;

    template <
        typename exponent_power,
        metric_prefix_ratio ratio,
        unit_name_literal single_letter_name,
        typename QuantitativeType = default_quantative_type
    > struct unit_option {
        static constexpr const char* const unit_name = single_letter_name.value;
        static constexpr const int power {exponent_power::value};
        using quantative_type = QuantitativeType;
        using metric_prefix = ratio;
    };

    template <typename T>
        concept unit_option_type = requires {
            T::unit_name;
            T::power;
            typeid(T::quantative_type);
            typeid(T::metric_prefix);
    };
}
