#!/bin/bash

# Copyright 2020 Rene Rivera, Sam Darwin
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

set -e
export TRAVIS_BUILD_DIR=$(pwd)
export DRONE_BUILD_DIR=$(pwd)
export TRAVIS_BRANCH=$DRONE_BRANCH
export VCS_COMMIT_ID=$DRONE_COMMIT
export GIT_COMMIT=$DRONE_COMMIT
export REPO_NAME=$DRONE_REPO
export PATH=~/.local/bin:/usr/local/bin:$PATH

if [ "$DRONE_JOB_BUILDTYPE" == "boost" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop
if [ "$TRAVIS_BRANCH" = "master" ]; then BOOST_BRANCH=master; fi
cd ..
git clone -b $BOOST_BRANCH https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule init libs/headers
git submodule init libs/assert
git submodule init libs/config
git submodule init libs/predef
git submodule init libs/static_assert
git submodule init libs/throw_exception
git submodule init libs/type_traits
git submodule init tools/build
git submodule init tools/boost_install
git submodule init tools/cmake
git submodule update --jobs 4
cp -r $TRAVIS_BUILD_DIR/* libs/core
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

echo "using $TOOLSET : : $COMPILER ;" > ~/user-config.jam
BUILD_JOBS=`(nproc || sysctl -n hw.ncpu) 2> /dev/null`
./b2 -j $BUILD_JOBS libs/core/test toolset=$TOOLSET cxxstd=$CXXSTD variant=debug,release ${UBSAN:+cxxflags=-fsanitize=undefined cxxflags=-fno-sanitize-recover=undefined linkflags=-fsanitize=undefined define=UBSAN=1 debug-symbols=on} ${LINKFLAGS:+linkflags=$LINKFLAGS}

elif [ "$DRONE_JOB_BUILDTYPE" == "4c67227808-e034891c01" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop
if [ "$TRAVIS_BRANCH" = "master" ]; then BOOST_BRANCH=master; fi
cd ..
git clone -b $BOOST_BRANCH https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule init libs/headers
git submodule init libs/assert
git submodule init libs/config
git submodule init libs/predef
git submodule init libs/static_assert
git submodule init libs/throw_exception
git submodule init libs/type_traits
git submodule init tools/build
git submodule init tools/boost_install
git submodule init tools/cmake
git submodule update --jobs 4
cp -r $TRAVIS_BUILD_DIR/* libs/core
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

mkdir __build__ && cd __build__
cmake -DBOOST_ENABLE_CMAKE=1 -DBoost_VERBOSE=1 -DBOOST_INCLUDE_LIBRARIES=core ..
ctest --output-on-failure -R boost_core

elif [ "$DRONE_JOB_BUILDTYPE" == "840114c2a5-fda7c76df5" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop
if [ "$TRAVIS_BRANCH" = "master" ]; then BOOST_BRANCH=master; fi
git clone -b $BOOST_BRANCH https://github.com/boostorg/config.git ../config
git clone -b $BOOST_BRANCH https://github.com/boostorg/assert.git ../assert

echo '==================================> SCRIPT'

cd test/cmake_subdir_test && mkdir __build__ && cd __build__
cmake ..
cmake --build .
cmake --build . --target check

elif [ "$DRONE_JOB_BUILDTYPE" == "4c67227808-9137ea6891" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop
if [ "$TRAVIS_BRANCH" = "master" ]; then BOOST_BRANCH=master; fi
cd ..
git clone -b $BOOST_BRANCH https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule init libs/headers
git submodule init libs/assert
git submodule init libs/config
git submodule init libs/predef
git submodule init libs/static_assert
git submodule init libs/throw_exception
git submodule init libs/type_traits
git submodule init tools/build
git submodule init tools/boost_install
git submodule init tools/cmake
git submodule update --jobs 4
cp -r $TRAVIS_BUILD_DIR/* libs/core
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

mkdir __build__ && cd __build__
cmake -DBOOST_ENABLE_CMAKE=1 -DBoost_VERBOSE=1 -DBOOST_INCLUDE_LIBRARIES="assert;config;core" -DCMAKE_INSTALL_PREFIX=~/.local ..
cmake --build . --target install
cd ../libs/core/test/cmake_install_test && mkdir __build__ && cd __build__
cmake -DCMAKE_INSTALL_PREFIX=~/.local ..
cmake --build .
cmake --build . --target check

fi
