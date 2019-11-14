/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include <gtest/gtest.h>
#include <dlfcn.h>
#include <thread>
#include <iostream>
#include <ctime>

extern "C" {
    #include "utils.h"
    #include "top_utils.h"
    #include "top_single.h"
    #include "object.h"
}

#define MAX_THREAD std::thread::hardware_concurrency()

class TopUtils: public ::testing::Test {};

TEST_F(TopUtils, TestHeap) {
    Top arr[5] = {
        {1, 0},
        {3.5, 2},
        {2.1, 4},
        {4.5, 3},
        {4.7, 1},
        };
    Top etalon[5] = {
        {4.7, 1},
        {4.5, 3},
        {3.5, 2},
        {2.1, 4},
        {1, 0},
        };


    make_heap(arr, 5);
    unsigned size = 5;
    for (size_t i = 0; i < 5; i++) {
        Top temp = extract_max(arr, &size);
        ASSERT_TRUE(temp.avr_rate == etalon[i].avr_rate);
        ASSERT_TRUE(temp.obj_id == etalon[i].obj_id);
    }
}

TEST_F(TopUtils, TestGetAverage) {
    Object *objs = create_object(0);
    ASSERT_TRUE(objs);
    ASSERT_TRUE(!add_rate(objs, static_cast<Mark>(5), 0));
    ASSERT_TRUE(!add_rate(objs, static_cast<Mark>(4), 0));
    ASSERT_TRUE(!add_rate(objs, static_cast<Mark>(3), 0));
    ASSERT_TRUE(!add_rate(objs, static_cast<Mark>(2), 0));
    ASSERT_TRUE(!add_rate(objs, static_cast<Mark>(1), 0));
    ASSERT_EQ(get_average(objs), 3.0);
}

TEST_F(TopUtils, TestFindTop) {
    Top arr[5] = {
            {1, 0},
            {3.5, 2},
            {2.1, 4},
            {4.5, 3},
            {4.7, 1},
    };
    Top etalon[2] = {
            {4.7, 1},
            {4.5, 3}
    };
    Top *temp = find_top(arr, 5, 2);
    for (size_t i = 0; i < 2; i++) {
        ASSERT_TRUE(temp[i].avr_rate == etalon[i].avr_rate);
        ASSERT_TRUE(temp[i].obj_id == etalon[i].obj_id);
    }
}

TEST_F(TopUtils, TestBinSearch) {
    unsigned arr[10] = {
            0,1,2,3,4,5,6,7,8,9
    };
    ASSERT_EQ(bin_search(arr, 0, 10, 5), 5);
    ASSERT_EQ(bin_search(arr, 0, 10, 10), -1);
}

class TopTest: public ::testing::Test{};

TEST_F(TopTest, testTops) {
    std::cout << "Max thread count: " << MAX_THREAD << std::endl;

    void *library;
    Top* (*get_top_multi)(const Objects *o, const User *u, unsigned c);
    library = dlopen("./libtop_multi.so", RTLD_LAZY);
    ASSERT_TRUE(library);
    get_top_multi = (Top *(*)(const Objects *, const User *, unsigned int)) (dlsym(library, "get_top"));
    Users *users = gen_users(5000000);
    ASSERT_TRUE(users);
    Objects *objects = gen_objects(16000);
    ASSERT_TRUE(objects);

    auto start = clock();
    auto flag = make_random_rate(users, objects, 500000000, MAX_THREAD - 1);
    auto fin = clock();
    ASSERT_TRUE(!flag);
    std::cout << "Generation time: "
              << (double) (fin - start)/CLOCKS_PER_SEC/(MAX_THREAD - 1)
              << std::endl;

    start = clock();
    auto top_single = get_top(objects, &users->array[0], 10);
    fin = clock();
    ASSERT_TRUE(top_single);
    std::cout << "Single get top time: "
              << (double) (fin - start)/CLOCKS_PER_SEC
              << std::endl;

    start = clock();
    auto top_multi = get_top_multi(objects, &users->array[0], 10);
    fin = clock();
    ASSERT_TRUE(top_multi);
    std::cout << "Multi get top time: "
              << (double) (fin - start)/CLOCKS_PER_SEC/MAX_THREAD
              << std::endl;

    print_top(top_multi, 10);
    print_top(top_single, 10);

    for (size_t i = 0; i < 10; i++) {
        ASSERT_TRUE(top_multi[i].avr_rate == top_single[i].avr_rate);
        ASSERT_TRUE(top_multi[i].obj_id == top_single[i].obj_id);
    }

    free_objects(objects);
    free_users(users);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
