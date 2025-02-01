cmake_minimum_required(VERSION 3.5.0)
project(QM_algorithm VERSION 0.1.0 LANGUAGES C CXX)

add_executable(QM_algorithm main.cpp minimized_terms.cpp minterm_collection.cpp solution.cpp solution_log.cpp util.cpp)

