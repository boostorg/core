#!/usr/bin/python

# This is a temporary workaround to make CIs use the
# "Boost with C++20 modules" proposal, instead of the regular develop branch
# Call it instead of depinst

from subprocess import check_call
import os

def main():

    submodules = [
        ('tools/cmake',         'https://github.com/anarthal/boost-cmake'),
        ('libs/assert',         'https://github.com/anarthal/assert'),
        ('libs/throw_exception','https://github.com/anarthal/throw_exception'),
        ('libs/config',         'https://github.com/anarthal/config'),
    ]

    for submodule, url in submodules:
        os.chdir(submodule)
        check_call(['git', 'remote', 'add', 'modules', url])
        check_call(['git', 'fetch', '--depth', '1', 'modules', 'feature/cxx20-modules'])
        check_call(['git', 'checkout', 'modules/feature/cxx20-modules'])
        os.chdir('../..')


if __name__ == '__main__':
    main()
