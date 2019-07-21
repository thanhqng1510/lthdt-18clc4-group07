cmake_minimum_required(VERSION 3.0)

project(ProjectSellingApp)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_GXX_FLAGS "${CMAKE_GXX_FLAGS} -Wall -std=c++17")
set(source_dir "${PROJECT_SOURCE_DIR}/ProjectSellingApp/")

add_executable(Output ${source_dir}/Main.cpp ${source_dir}/Utility/Util.cpp ${source_dir}/Person/Person.cpp ${source_dir}/Person/Customer.cpp ${source_dir}/Menu/MainMenu.cpp ${source_dir}/BookStore/BookStore.cpp ${source_dir}/Account/Account.cpp)
