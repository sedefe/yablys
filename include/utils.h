#pragma once

#include <type_traits>

template <typename E>  // Чтоб конвертировать стронг енумы в инты
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}
