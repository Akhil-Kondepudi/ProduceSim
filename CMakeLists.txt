cmake_minimum_required(VERSION 3.21)
project(P4)

set(CMAKE_CXX_STANDARD 14)

add_executable(P4 P4driver.cpp customer.h customer.cpp delivery.h delivery.cpp produce.cpp produce.h pickyCustomer.cpp pickyCustomer.h segmentCustomer.cpp segmentCustomer.h ProduceListTabDelimited-1.txt)

