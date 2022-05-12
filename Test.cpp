#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("RUN GAME")
{
    OrgChart organization;
    organization.add_root("1")
        .add_sub("1", "2")    
        .add_sub("1", "3")    
        .add_sub("1", "4")   
        .add_sub("2", "5")  
        .add_sub("4", "6")
        .add_sub("4", "7")
        .add_sub("4", "8")
        .add_sub("4", "9")
        .add_sub("4", "10")
        .add_sub("4", "11")
        .add_sub("4", "12")
        .add_sub("4", "13")
        .add_sub("4", "14")
        .add_sub("4", "15")
        .add_sub("4", "16")
        .add_sub("4", "17")
        .add_sub("4", "18")
        .add_sub("4", "19")
        .add_sub("4", "20");
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) {
    i++;   
    CHECK_EQ(to_string(i), (*it));

    }
    
}