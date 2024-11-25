#pragma once

#include <fmt/format.h>
#include <vector>

#include <sqlite3_cpp/sqlite3_cpp.hpp>

namespace sqlite {

template <typename T>
void Statement::bind(int i, T v)
{
    if (auto ec = tryBind(i, v); ec != SQLITE_OK) {
        auto msg = fmt::format("error binding value to arg: {}", ec);
        throw std::runtime_error(msg);
    }
}

template <>
inline int Statement::tryBind(int i, int v) noexcept
{
    return sqlite3_bind_int(m_handle, i, v);
}

template <>
inline int Statement::tryBind(int i, sqlite_int64 v) noexcept
{
    return sqlite3_bind_int64(m_handle, i, v);
}

template <>
inline int Statement::tryBind(int i, double v) noexcept
{
    return sqlite3_bind_double(m_handle, i, v);
}

template <>
inline int Statement::tryBind(int i, const std::string& v) noexcept
{
    return sqlite3_bind_text(m_handle, i, v.c_str(), v.length(), nullptr);
}

template <>
inline int Statement::tryBind(int i, const std::vector<std::byte>& v) noexcept
{
    return sqlite3_bind_blob(m_handle, i, v.data(), v.size(), nullptr);
}

} // namespace sqlite
