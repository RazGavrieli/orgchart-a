#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("level order")
{
    /*
    This tests the correctness of level iterator
    */
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

TEST_CASE("pre order")
{
    /*
    This tests the correctness of pre order iterator
    */
    OrgChart organization;
    organization.add_root("6")
        .add_sub("6", "5")    
        .add_sub("6", "4")    
        .add_sub("6", "3")   
        .add_sub("5", "2")  
        .add_sub("3", "1");
/*              6
       |--------|--------|
       5        4        3
       |                 |
       2                 1
 */
    size_t i = 0;
    vector<std::string> expectedNames = {"6", "5", "2", "4", "3", "1"};
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
    CHECK_EQ(expectedNames.at(i++), (*it));
    } 
}

TEST_CASE("reverse level iterator")
{
    /*
    This tests the correctness of reverse level iterator
    */
    OrgChart organization;
    organization.add_root("6")
        .add_sub("6", "5")    
        .add_sub("6", "4")    
        .add_sub("6", "3")   
        .add_sub("4", "2")  
        .add_sub("3", "1");
/*              6
       |--------|--------|
       5        4        3
                |        |
                2        1
 */
    size_t i = 0;
    vector<std::string> expectedNames = {"2", "1", "5", "4", "3", "6"};
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
    CHECK_EQ(expectedNames.at(i++), (*it));
    } 
}

TEST_CASE("bad cases")
{
    SUBCASE("two iterators") {
        OrgChart organization;
        organization.add_root("first")
        .add_sub("first", "second-1")
        .add_sub("first", "second-2"); 
        auto it2 =  organization.begin_preorder();
        auto it = organization.begin_preorder();
        CHECK_NOTHROW(it++);
        it2++;
        CHECK_EQ(it, it2);
        it2++;
        CHECK_NE(it, it2);
    }
    SUBCASE("mid iteration edit") {
    /* This checks if the iterator throws an exception if the tree has been edited since iterator creation */
    OrgChart organization;
    organization.add_root("first")
        .add_sub("first", "second-1")
        .add_sub("first", "second-2");  
    auto it = organization.begin_preorder();
    CHECK_NOTHROW(it++);
    organization.add_sub("second-1", "third");
    CHECK_THROWS(it++);
    }

    SUBCASE("out of bounds") {
    /* This checks if the iterator throws an exception if the tree has been fully iterated */
    OrgChart organization;
    organization.add_root("first")
        .add_sub("first", "second-1")
        .add_sub("first", "second-2");   
    auto it = organization.begin_preorder();
    CHECK_NOTHROW(it++);
    CHECK_NOTHROW(it++);
    CHECK_NOTHROW(it++); // end of tree
    CHECK_THROWS(it++);
    }

    SUBCASE("Not found") {
    /* This checks if the chart throws an exception if the node does not exists */
    OrgChart organization;
    organization.add_root("first")
        .add_sub("first", "second-1")
        .add_sub("first", "second-2");   
    CHECK_THROWS(organization.add_sub("third", "fourth")); // third was not found
    }

    SUBCASE("Root already exists") {
    /* This checks if the program does not faults if the root is being changed */
    OrgChart organization;
    organization.add_root("first")
        .add_sub("first", "second-1")
        .add_sub("first", "second-2");   
    size_t i = 0;
    vector<std::string> expectedNames = {"first", "second-1", "second-2"};
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
    CHECK_EQ(expectedNames.at(i++), (*it));
    } 
    CHECK_NOTHROW(organization.add_root("new first")); 

    i = 0;
    expectedNames = {"new first", "second-1", "second-2"};
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
    CHECK_EQ(expectedNames.at(i++), (*it));
    } 

    }

}