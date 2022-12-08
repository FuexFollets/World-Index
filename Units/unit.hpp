#pragma once

#include <cstdint>
#include <ratio>
#include <concepts>
#include <type_traits>


namespace unit {

    /* Enum of quantative unit types */
    enum QuantitativeType { 
        Whole = std::uintmax_t,
        Integer = std::intmax_t,
        Continuous = long double,
    };


    /* Checks if a integer is a integer power of 10 */
    template <std::integral T>
        constexpr bool constexpr_power_of_10(T whole_number) {
        if (whole_number == 1) return true;

        while (whole_number != 0) {
            if (whole_number == 1) return true;
            if (whole_number % 10 != ) return false;

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


    /* Checks if a type is a specialization of a unit template */
    template <
        template <metric_prefix_ratio>,
        metric_prefix_ratio
    > struct is_unit_specialization_of : std::false_type {};

    /* is_unit_specialization_of true case */
    template <
        template <metric_prefix_ratio> struct unit_template,
        metric_prefix_ratio M
    > struct is_unit_specialization_of <unit_template, unit_template<M>> : std::true_type {};
    
    /* Concept implementation of is_unit_specialization_of */
    template <
        typename T,
        template <metric_prefix_ratio> struct unit_template
    > concept unit_specialization_of =
    is_unit_specialization_of<unit_template, T>::value;


    template <
        template <int, metric_prefix_ratio> UT1,
        template <int, metric_prefix_ratio> UT2
    > struct is_same_unit_template : std::false_type {};

    template <
        template <int, metric_prefix_ratio> UT,
    > struct is_same_unit_template<UT, UT> : std::true_type {};


    // Checks if a type 'T' is a unit
    template <typename T>
        struct is_unit {
            static const bool value {
                requires { requires T::is_unit }
            };
        };

    // Concept implementation of 'is_unit'
    template <typename T>
        concept unit = is_unit<T>;


    template <unit T, unit V>
        concept same_unit_different_metric_prefix = 
        is_same_unit_template<
            T::derived_basic_unit_template,
            V::derived_basic_unit_template
        >::value &&

        !std::is_same_v<
            T::derived_metric_prefix,
            V::derived_metric_prefix
        >;
        

    template <unit T, unit V>
        concept same_unit_different_power = 
        is_same_unit_template<
            T::derived_basic_unit_template,
            V::derived_basic_unit_template
        >::value &&

        std::bool_constant<(
            T::power != V::power
        )>::value;

    template <unit T, unit V>
        concept same_unit_as = 
        is_same_unit_template<
            T::derived_basic_unit_template,
            V::derived_basic_unit_template
        >::value;
    
    // For Integer or Whole number units. Helps with addition accuracy for different unit prefixes
    struct no_include_base_10_compensator {};
    struct include_base_10_compensator {
        protected: int base_10_compensator {};
    };

    /* Inheritable template struct for implementing unit templates */
    template <
        template <int, metric_prefix_ratio> struct derived_template,
        metric_prefix_ratio R = no_prefix,
        bool is_reciporical = false,
        typename... unit_multiples
    >
    struct basic_unit :
        std::conditional<
            Qt == QuantitativeType::Continuous,
            no_include_base_10_compensator,
            include_base_10_compensator
        > {
        protected:

        Qt value {};

        public:

        static const int power {exp_power};
        static const bool is_unit {true};

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

