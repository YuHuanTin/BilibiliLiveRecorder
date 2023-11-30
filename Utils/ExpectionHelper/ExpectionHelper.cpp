//
// Created by YuHuanTin on 2023/11/19.
//

#include "ExpectionHelper.h"

#include <print>
#include <stacktrace>


void ExpectionHelper::dumpExpection(std::exception &Exception, bool With_Stack) {
    if (With_Stack)
        std::println("exception: {}\nstack info: \n{}", Exception.what(), std::stacktrace::current());
    else
        std::println("exception: {}", Exception.what());
}

void ExpectionHelper::dumpExpection(const char *Additional, std::exception &Exception, bool With_Stack) {
    std::println("{}", Additional);
    ExpectionHelper::dumpExpection(Exception, With_Stack);
}
