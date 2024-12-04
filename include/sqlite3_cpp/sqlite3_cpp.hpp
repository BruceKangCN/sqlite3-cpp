#pragma once

#include <optional>
#include <sqlite3.h>
#include <string>

#include <sqlite3_cpp/def.h>

namespace sqlite {

class SQLITE_PUB SQLite;
class SQLITE_PUB Statement;

/// row result wrapper for `Statement`.
class SQLITE_PUB Row;

//! TODO: add move and copy constructors and assignments for classes

class SQLite {
    using Sqlite3Ptr = sqlite3*;

public:
    SQLite(const std::string& filename, int flags = SQLITE_OPEN_READWRITE) noexcept;

    ~SQLite();

    operator Sqlite3Ptr() const noexcept
    {
        return m_handle;
    }

    Statement prepare(const std::string& sql, int nByte, unsigned flags = 0);

    void exec(const std::string& sql);

private:
    sqlite3* m_handle = nullptr;
};

class Statement {
    using StmtPtr = sqlite3_stmt*;

public:
    Statement(SQLite& db, const std::string& sql, int nByte, unsigned flags = 0);

    ~Statement();

    operator StmtPtr() const noexcept
    {
        return m_handle;
    }

    void bindNull(int i);

    /// function template for `sqlite3_bind_*`.
    ///
    /// **Note**: include `<sqlite3_cpp/bind.hpp>` to use instantiated function
    /// templates.
    ///
    /// types for `*`:
    ///     - int: int
    ///     - int64: sqlite3_int64
    ///     - double: double
    ///     - text: std::string
    ///     - blob: std::vector<std::byte>
    /// PS: for `zeroblob`, just pass an zero-filled vector.
    ///
    /// \sa bindNull
    template <typename T>
    void bind(int i, T v);

    std::optional<Row> step();

protected:
    /// `sqlite3_bind_*` wrapper.
    ///
    /// to simplify implementation of `bind`.
    ///
    /// \sa bind
    template <typename T>
    inline int tryBind(int i, T v) noexcept;

private:
    sqlite3_stmt* m_handle;
};

class Row {
public:
    Row() = delete;
    Row(const Row&) = delete;
    Row(Row&&) noexcept = default;
    explicit Row(sqlite3_stmt* s) noexcept: m_stmt{s} {}
    ~Row() = default;

    int type(int i) noexcept
    {
        return sqlite3_column_type(m_stmt, i);
    }

    int bytes(int i) noexcept
    {
        return sqlite3_column_bytes(m_stmt, i);
    }

    /// function template for `sqlite3_column_*`.
    ///
    /// **Note**: include `<sqlite3_cpp/column.hpp>` to use instantiated function
    /// templates.
    ///
    /// types for `*`:
    ///     - int: int
    ///     - int64: sqlite3_int64
    ///     - double: double
    ///     - text: std::string
    ///     - blob: std::vector<std::byte>
    template <typename T>
    std::optional<T> column(int i) noexcept;

protected:
    /// `sqlite3_column_*` wrapper.
    ///
    /// to simplify implementation of `column`.
    ///
    /// \sa column
    template <typename T>
    inline T columnImpl(int i) noexcept;

private:
    sqlite3_stmt* m_stmt;
};

} // namespace sqlite3
