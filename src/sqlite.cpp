#include <fmt/format.h>

#include <sqlite3_cpp/sqlite3_cpp.hpp>

namespace sqlite {

SQLite::SQLite(const std::string& filename, int flags) noexcept
{
    sqlite3_open_v2(filename.c_str(), &m_handle, flags, nullptr);
}

SQLite::~SQLite()
{
    if (auto ec = sqlite3_close_v2(m_handle); ec != SQLITE_OK) {
        fmt::println(stderr, "error closing SQLite connection with code {}", ec);
    }
}

Statement SQLite::prepare(const std::string& sql, int nByte, unsigned flags)
{
    return Statement(*this, sql, nByte, flags);
}

void SQLite::exec(const std::string& sql)
{
    auto ec = sqlite3_exec(m_handle, sql.c_str(), nullptr, nullptr, nullptr);
    if (ec != SQLITE_OK) {
        auto msg = fmt::format("error executing statement: {}", ec);
        throw std::runtime_error(msg);
    }
}

} // namespace sqlite
