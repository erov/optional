#pragma once

#include "optional-destructible-base.h"

namespace optional_traits {

template <typename T, bool is_trivially>
struct optional_copy_constructible_base
    : optional_destructible_base<T, std::is_trivially_destructible_v<T>> {
  using base = optional_destructible_base<T, std::is_trivially_destructible_v<T>>;
  using base::base;

  constexpr optional_copy_constructible_base(optional_copy_constructible_base const& other) {
    if (other.is_calculated) {
      new (&this->value) T(other.value);
      this->is_calculated = true;
    }
  }
  constexpr optional_copy_constructible_base(optional_copy_constructible_base&&) = default;
  optional_copy_constructible_base& operator=(optional_copy_constructible_base const&) = default;
  optional_copy_constructible_base& operator=(optional_copy_constructible_base&&) = default;
};

template <typename T>
struct optional_copy_constructible_base<T, true>
    : optional_destructible_base<T, std::is_trivially_destructible_v<T>> {
  using base = optional_destructible_base<T, std::is_trivially_destructible_v<T>>;
  using base::base;

  constexpr optional_copy_constructible_base(optional_copy_constructible_base const& other) = default;
  constexpr optional_copy_constructible_base(optional_copy_constructible_base&&) = default;
  optional_copy_constructible_base& operator=(optional_copy_constructible_base const&) = default;
  optional_copy_constructible_base& operator=(optional_copy_constructible_base&&) = default;
};

}
