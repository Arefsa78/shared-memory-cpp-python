#include <sw/redis++/redis++.h>

#include <iostream>
#include <string>

using namespace sw::redis;


int main()
{
    auto redis = Redis("tcp://127.0.0.1:6379");


    redis.set("key", "val213");
    auto val = redis.get("key");

    std::vector<double> vec = {1.1,2.2,3.3};
    redis.rpush("list", vec.begin(), vec.end());

    std::cout << "Done" << std::endl;
}