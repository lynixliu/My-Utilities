//
//  NestVector.h
//
//  Created by Yang Liu on 13/07/18.
//  Copyright © 2018 Yang Liu.
//  See the LICENSE file for license information.
//

#ifndef NestVector_h
#define NestVector_h

#include <vector>

template <class T, template<typename,typename> class Cont,template <typename,typename> class InnerCont = std::vector>
class NestVector_iterator
{
    typedef InnerCont<T,std::allocator<T>> innerContainer;
    typedef Cont<innerContainer*, std::allocator<innerContainer*>> container;
    typedef typename container::iterator dataIterator;
    typedef typename innerContainer::iterator innerIterator;
    typedef T elem_type;
    container& mData;
    dataIterator mOuterItr;
    innerIterator mInnerItr;
public:
    NestVector_iterator(container& c, dataIterator outer, innerIterator inner) : mData(c), mOuterItr(outer), mInnerItr(inner){}
    
    NestVector_iterator(const NestVector_iterator& other) : mData(other.mData), mOuterItr(other.mOuterItr), mInnerItr(other.mInnerItr) {}
    
    NestVector_iterator& operator=(const NestVector_iterator& other) {
        mData = other.mData;
        mOuterItr = other.mOuterItr;
        mInnerItr = other.mInnerItr;
        return *this;
    }
    
    bool operator==(const NestVector_iterator& other) const {return (mOuterItr == other.mOuterItr && mInnerItr == other.mInnerItr);}
    
    bool operator!=(const NestVector_iterator& other) const {return !(*this==other);}
    
    elem_type& operator*() {return *mInnerItr;}
    
    NestVector_iterator operator++(int) {
        NestVector_iterator tmp(*this); operator++(); return tmp;
    }
    
    NestVector_iterator& operator++() {
        if (mOuterItr == mData.end()) {
            mOuterItr = mData.end();
            mInnerItr = mData.back()->end();
            return *this;
        }
        if (mInnerItr == (*mOuterItr)->end() || mInnerItr + 1 == (*mOuterItr)->end()) {
            mOuterItr++;
            mInnerItr = (mOuterItr == mData.end()) ? mData.back()->end() : (*mOuterItr)->begin();
            return *this;
        }
        mInnerItr++;
        return *this;
    }
    
    NestVector_iterator operator+(size_t temp) const {
        NestVector_iterator result(*this);
        size_t count = temp;
        while (result.mOuterItr != mData.end() && (*result.mOuterItr)->size() <= count) {
            count-=(*(result.mOuterItr))->size();
            result.mOuterItr++;
        }
        if (result.mOuterItr == mData.end()) {
            result.mOuterItr = mData.end();
            result.mInnerItr = mData.back()->end();
            return result;
        }
        result.mInnerItr = (*(result.mOuterItr))->begin() + count;
        return result;
        
        return result;
    }
};

template <class T, template <typename,typename> class OuterCont = std::vector, template <typename, typename> class InnerCount = std::vector>
class NestedVector {
public:
    typedef T elem_type;
    typedef InnerCount<elem_type,std::allocator<elem_type>> innerContainer;
    typedef NestVector_iterator<elem_type, OuterCont, InnerCount> iterator;
    
    /// the caller should allocate and destroy the inseted data
    NestedVector() : mData(0, NULL), mSize(0){}
    virtual ~NestedVector() {}
    
    iterator begin() {
        return iterator(mData, mData.begin(), mData.front()->begin());
    }
    iterator end() {
        return iterator(mData, mData.end(), mData.back()->end());
    }
    void insert(innerContainer& dataPack) {
        mData.push_back(&dataPack);
        mSize += dataPack.size();
    }
    
    size_t getIndex(size_t& groupId, size_t index) const {
        groupId = 0;
        for (auto data : mData) {
            if (not data) {
                return 0;
            }
            if (index < data->size())
                return index;
            index -= data->size();
            groupId++;
        }
        return index;
    }
    size_t size() {return mSize;}
    
    void clear() {
        mData.clear();
        mSize = 0;
    }
    void getIndeces(std::vector<size_t>& indexes) {
        size_t i = 0;
        if (not indexes.empty()) indexes.clear();
        indexes.reserve(mSize);
        for (iterator it = begin(),end_it = end();
             it!= end_it; it++) {
            indexes.push_back(i++);
        }
    }
    elem_type at(size_t index) {
        return *(begin() + index);
    }
private:
    typedef InnerCount<innerContainer*, std::allocator<innerContainer*>> outerContainer;
    
    outerContainer mData;
    size_t mSize;
};
#endif /* NestVector_h */
