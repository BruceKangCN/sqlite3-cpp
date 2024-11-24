#include <fmt/format.h>
#include <stdexcept>

#include <sqlite3_cpp/sqlite3_cpp.hpp>

namespace sqlite {

Statement::Statement(SQLite& db, const std::string& sql, int nByte, unsigned flags)
{
    const char* tail = nullptr;
    sqlite3_prepare_v3(db, sql.c_str(), nByte, flags, &m_handle, &tail);

    if (tail) {
        auto msg = fmt::format("error preparing statement at byte {}", tail - sql.c_str());
        throw std::runtime_error(msg);
    }
}

Statement::~Statement()
{
    if (auto ec = sqlite3_finalize(m_handle); ec != SQLITE_OK) {
        fmt::println(stderr, "error deleting SQLite prepare statement with code {}", ec);
    }
}

} // namespace sqlite
