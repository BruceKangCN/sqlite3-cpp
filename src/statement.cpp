#include <fmt/format.h>

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

void Statement::bindNull(int i)
{
    if (auto ec = sqlite3_bind_null(m_handle, i); ec != SQLITE_OK) {
        auto msg = fmt::format("error binding null to arg: {}", ec);
        throw std::runtime_error(msg);
    }
}

std::optional<Row> Statement::step()
{
    switch (auto ec = sqlite3_step(m_handle)) {
    case SQLITE_ROW:
        return Row(static_cast<sqlite3_stmt*>(*this));
    case SQLITE_DONE:
        return std::nullopt;
    default:
        auto msg = fmt::format("error fetching data: {}", ec);
        throw std::runtime_error(msg);
    }
}

} // namespace sqlite
