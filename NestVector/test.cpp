//
//  test.cpp
//
//  Created by Yang Liu on 11/20/17.
//  Copyright © 2017 Yang Liu. All rights reserved.
//  See the LICENSE file for license information.
//

#include <iostream>
#include "NestVector.h"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    using namespace std;
    typedef NestedVector<float> DataContainer;
    std::vector<float> aa;
    std::vector<float> bb;
    std::vector<float> cc;
    aa.push_back(1.1);
    aa.push_back(1.3);
    aa.push_back(1.2);
    
    bb.push_back(2.1);
    bb.push_back(2.2);
    bb.push_back(2.3);
    cc.push_back(3.1);
    cc.push_back(3.2);
    cc.push_back(3.3);
    DataContainer dc;
    dc.insert(aa);
    dc.insert(bb);
    dc.insert(cc);
    DataContainer::iterator it = dc.begin();
    std::vector<size_t> indexes;
    dc.getIndeces(indexes);
    for (size_t j=0; j< indexes.size();j++){
        cout<<"value:"<<dc.at(j)<<std::endl;
    }
    it = dc.begin();
    auto comp = [&](size_t idx1, size_t idx2) {
        if (idx1 > 9 && idx2 < 9) return false;
        if (idx1 < 9 && idx2 > 9) return true;
        if (idx1 == idx2) return false;
        cout<<"cmp:"<<idx1<<":"<<*(it + idx1)<<">"<<idx2<<":"<<*(it + idx2)<<std::endl;
        return *(it + idx1) > *(it + idx2);
    };
    size_t worstNum = 100;
    if (indexes.size() > worstNum) {
        partial_sort(indexes.begin(), indexes.begin() + worstNum, indexes.end(), comp);
        indexes.resize(worstNum);
    } else {
        sort(indexes.begin(), indexes.end(), comp);
    }
    std::cout<<"retuslt:"<<std::endl;
    for (auto id : indexes) {
        if (id > indexes.size()) id = 1;
        std::cout<<id<<":"<<*(dc.begin()+id)<<std::endl;
    }
    return 0;
}

