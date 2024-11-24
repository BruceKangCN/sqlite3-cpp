project(
  'sqlite3-cpp',
  'cpp',
  meson_version: '>=1',
  version: '0.1.0',
  default_options: [
    'warning_level=3',
    'cpp_std=c++17',
  ],
)

lib_args = ['-DBUILDING_SQLITE3_CPP']

inc = include_directories('include')

sqlite3_dep = dependency('sqlite3', include_type: 'system')
fmt_dep = dependency('fmt', include_type: 'system')

subdir('src')

lib = library(
  meson.project_name(),
  src,
  install: true,
  cpp_args: lib_args,
  include_directories: inc,
  dependencies: [sqlite3_dep, fmt_dep],
  gnu_symbol_visibility: 'hidden',
)

sqlite3_cpp_dep = declare_dependency(
  include_directories: inc,
  link_with: lib,
)

install_headers('include/sqlite3_cpp/sqlite3_cpp.hpp', subdir: 'sqlite3_cpp')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name: 'sqlite3-cpp',
  filebase: 'sqlite3_cpp',
  description: 'light and simple SQLite3 C++ wrapper',
  subdirs: 'sqlite3_cpp',
  libraries: lib,
)
