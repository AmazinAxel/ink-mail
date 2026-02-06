project(
  'ink-mail',
  'cpp',
  version: 'v1.0.0',
  default_options: ['cpp_std=c++17'],
  meson_version: '>=1.1'
)

imap = get_option('imap')
email = get_option('email')
password = get_option('password')

gtk_dep = dependency('gtk+-2.0')
curl_dep = dependency('libcurl')
gmime_dep = dependency('gmime-3.0')

sources = files(
  './src/service/getMail.cpp',
  './src/widgets/mailItem.cpp',
  './src/mailList.cpp',
  './src/mailPage.cpp',
  './src/main.cpp',
  './src/utils.cpp',
)

# `xxd -i` converts a binary file to a C header file
xxd_exe = find_program('xxd')
xxd_gen = generator(
  xxd_exe,
  output: '@PLAINNAME@.h',
  arguments: ['-i', '-C', '-n', '@PLAINNAME@', '@INPUT@', '@OUTPUT@']
)

executable(
  'ink-mail',
  sources,
  dependencies: [ gtk_dep, curl_dep, gmime_dep ],
  cpp_args: ['-O2', '-static-libstdc++', '-Wno-deprecated-declarations',
    '-DIMAP="' + imap + '"',
    '-DEMAIL="' + email + '"',
    '-DPASSWORD="' + password + '"',
  ],
  link_args: ['-static-libstdc++']
)
