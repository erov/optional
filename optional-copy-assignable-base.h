#pragma once

#include "optional-move-constructible-base.h"

namespace optional_traits {

template <typename T, bool is_trivially>
struct optional_copy_assignable_base
    : optional_move_constructible_base<T, std::is_trivially_move_constructible_v<T>> {
  using base = optional_move_constructible_base<T, std::is_trivially_move_constructible_v<T>>;
  using base::base;

  constexpr optional_copy_assignable_base(optional_copy_assignable_base const&) = default;
  constexpr optional_copy_assignable_base(optional_copy_assignable_base&&) = default;
  optional_copy_assignable_base& operator=(optional_copy_assignable_base const& other) {
    if (this != &other) {
      if (this->is_calculated) {
        if (!other.is_calculated) {
          this->destroy();
        } else {
          this->value = other.value;
        }
      } else {
        if (other.is_calculated) {
          this->construct(other.value);
        }
      }
    }
    return *this;
  }
  optional_copy_assignable_base& operator=(optional_copy_assignable_base&&) = default;
};

template <typename T>
struct optional_copy_assignable_base<T, true>
    : optional_move_constructible_base<T, std::is_trivially_move_constructible_v<T>> {
  using base = optional_move_constructible_base<T, std::is_trivially_move_constructible_v<T>>;
  using base::base;

  constexpr optional_copy_assignable_base(optional_copy_assignable_base const&) = default;
  constexpr optional_copy_assignable_base(optional_copy_assignable_base&&) =  default;
  optional_copy_assignable_base& operator=(optional_copy_assignable_base const&) = default;
  optional_copy_assignable_base& operator=(optional_copy_assignable_base&&) = default;
};

}
