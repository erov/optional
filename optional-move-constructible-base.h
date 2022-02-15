#pragma once

#include "optional-copy-constructible-base.h"

namespace optional_traits {

template <typename T, bool is_trivially>
struct optional_move_constructible_base
    : optional_copy_constructible_base<T, std::is_trivially_copy_constructible_v<T>> {
  using base = optional_copy_constructible_base<T, std::is_trivially_copy_constructible_v<T>>;
  using base::base;

  constexpr optional_move_constructible_base(optional_move_constructible_base const&) = default;
  constexpr optional_move_constructible_base(optional_move_constructible_base&& other) {
    if (other.is_calculated) {
      new (&this->value) T(std::move(other.value));
      this->is_calculated = true;
    }
  }
  optional_move_constructible_base& operator=(optional_move_constructible_base const&) = default;
  optional_move_constructible_base& operator=(optional_move_constructible_base&&) = default;
};

template <typename T>
struct optional_move_constructible_base<T, true>
    : optional_copy_constructible_base<T, std::is_trivially_copy_constructible_v<T>> {
  using base = optional_copy_constructible_base<T, std::is_trivially_copy_constructible_v<T>>;
  using base::base;

  constexpr optional_move_constructible_base(optional_move_constructible_base const&) = default;
  constexpr optional_move_constructible_base(optional_move_constructible_base&&) = default;
  optional_move_constructible_base& operator=(optional_move_constructible_base const&) = default;
  optional_move_constructible_base& operator=(optional_move_constructible_base&&) = default;
};

}
