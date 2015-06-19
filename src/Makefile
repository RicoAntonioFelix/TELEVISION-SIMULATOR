# Copyright (C) 2014-2015 Rico Antonio Felix
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# author: Rico Antonio Felix <ricoantoniofelix@yahoo.com>

# Set compiler
CXX = g++

# Set langauge level
LANG = -std=c++1y

# Link libraries and create executable
simulator: simulator.o
    ${CXX} ${LANG} -o tvsim simulator.o

# Compile object file
simulator.o: simulator.cpp tv.hpp
    ${CXX} ${LANG} -c simulator.cpp
