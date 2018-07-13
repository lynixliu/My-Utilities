/*
*  ArrayMapTest.cpp
*  ArrayMap test
*
*  Created by Yang Liu on 13/07/18.
*
MIT License

Copyright (c) 2018 Yang LIU

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*
*/

#include <iostream>
#include <string>
#include "ArrayMap.h"


struct Payload {
    std::string name;
} ;
typedef arrayMap<Payload, 10> myDB;

class testDB
{
public:
    testDB(){}
    virtual ~testDB(){}
    void test()
    {
        myDB db;
        Payload a={"aa"};
        
        printf("testDB: max_size=%lu,size=%lu\n",db.max_size(),db.size());
        db[0] = a;
        printf("    size=%lu\n",db.size());
        for(int i = 0;i<db.max_size();i++)
            printf("db[0]=%s%s",db[i].name.empty()?"O":db[i].name.c_str(),i==9?".\n":",");
        db.clear();
    }
    void test2()
    {
        Payload payload[5] = {"payload0","payload1","payload2","payload3","payload4"};
        myDB db((Payload*)payload,sizeof(payload)/sizeof(Payload));
        printf("new %lu size %lu\n",sizeof(payload)/sizeof(Payload),db.size());
        
        Payload newpayload[5] = {"newpayload0","newpayload1","newpayload2","newpayload3","newpayload4"};
        for(size_t j =0;j<db.size();j++)
            printf("payload[%lu] = %s\n",j,db[j].name.c_str());
        
        db.erase(2);
        printf("erase elem[2] size %lu\n",db.size());
        for(size_t j =0;j<db.size();j++)
            printf("payload[%lu] = %s\n",j,db[j].name.c_str());
        db[4]=newpayload[4];
        printf("new elem[4] size %lu\n",db.size());
        for(size_t j =0;j<db.size();j++)
            printf("payload[%lu] = %s\n",j,db[j].name.c_str());
        
        db.erase(1);
        printf("erase elem[1] size %lu\n",db.size());
        for(size_t j =0;j<db.size();j++)
            printf("payload[%lu] = %s\n",j,db[j].name.c_str());
        db.clear();
    }
};

int main(int argc, const char * argv[]) {
    testDB aa;
    aa.test();
    aa.test2();
    return 0;
}
