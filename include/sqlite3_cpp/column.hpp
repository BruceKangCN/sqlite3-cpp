#pragma once

#include <algorithm>
#include <fmt/format.h>
#include <vector>

#include <sqlite3_cpp/sqlite3_cpp.hpp>

namespace sqlite {

template <typename T>
std::optional<T> Row::column(int i) noexcept
{
    if (type(i) == SQLITE_NULL) {
        return std::nullopt;
    }

    return columnImpl<T>(i);
}

template <>
inline int Row::columnImpl(int i) noexcept
{
    return sqlite3_column_int(m_stmt, i);
}

template <>
inline sqlite_int64 Row::columnImpl(int i) noexcept
{
    return sqlite3_column_int64(m_stmt, i);
}

template <>
inline double Row::columnImpl(int i) noexcept
{
    return sqlite3_column_double(m_stmt, i);
}

template <>
inline std::string Row::columnImpl(int i) noexcept
{
    const auto* str = sqlite3_column_text(m_stmt, i);
    return std::string(reinterpret_cast<const char*>(str));
}

template <>
inline std::vector<std::byte> Row::columnImpl(int i) noexcept
{
    auto size = bytes(i);
    auto vec = std::vector<std::byte>(size);
    std::memcpy(vec.data(), sqlite3_column_blob(m_stmt, i), size);
    return vec;
}

} // namespace sqlite
