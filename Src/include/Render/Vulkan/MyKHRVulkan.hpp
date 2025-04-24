#pragma once
#include <vulkan.h>

#include <iostream>
#include <cstdint>

#include <vector>
#include <set>

class MyKHRVulkan{
    public:

    public:
    //Base Const Dist
    MyKHRVulkan();
    ~MyKHRVulkan();
    
    //Moveble
    MyKHRVulkan(MyKHRVulkan &other);
    MyKHRVulkan(MyKHRVulkan &&other);

    //Oerator
    MyKHRVulkan operator=(MyKHRVulkan &other);
    MyKHRVulkan operator=(MyKHRVulkan &&other);

};