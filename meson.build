project('paperplane', 'c',
        version: '3.33.90',
        license: 'GPLv2+',
        meson_version: '>= 0.49.0',
        default_options: [
          'buildtype=debugoptimized',
          'warning_level=1',
          'c_std=c99',
        ])

add_project_arguments([ 'pkg-config --cflags --libs gtk+-3.0', '-D_POSIX_C_SOURCE=200809L', '-D_XOPEN_SOURCE=700', '-D_DEFAULT_SOURCE' ], language: 'c')

gtk_req_version = '>= 3.12.0'

executable('build_test', 'main.c')
gtk_dep = dependency('gtk+-3.0', version: gtk_req_version)
