#pragma once

#include <sqlite3.h>
#include <string>

#include <sqlite3_cpp/def.h>

namespace sqlite {

class SQLITE_PUB SQLite;
class SQLITE_PUB Statement;

//! TODO: to be implemented:
//!     - *_bind
//!     - *_step
//!     - *_column
//!     - *_exec

//! TODO: add move and copy constructors and assignments for classes

class SQLite {
    using pSqlite3 = sqlite3*;

public:
    SQLite(const std::string& filename, int flags = SQLITE_OPEN_READWRITE) noexcept;

    ~SQLite();

    operator pSqlite3() const noexcept
    {
        return m_handle;
    }

    Statement prepare(const std::string& sql, int nByte, unsigned flags = 0);

private:
    sqlite3* m_handle = nullptr;
};

class Statement {
    using pStmt = sqlite3_stmt*;

public:
    Statement(SQLite& db, const std::string& sql, int nByte, unsigned flags = 0);

    ~Statement();

    operator pStmt() const noexcept
    {
        return m_handle;
    }

private:
    sqlite3_stmt* m_handle;
};

} // namespace sqlite3
