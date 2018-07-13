/*
 * ArrayMap.h
 *  Created on: Mar 20, 2015
 *      Author: liuyang
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
 */

#ifndef ARRAYMAP_H_
#define ARRAYMAP_H_

template <class _Tp, size_t _Nm>
struct arrayMap
{
    // types:
    typedef arrayMap 				  			  __self;
    typedef _Tp                                   value_type;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef value_type*                           iterator;
    typedef const value_type*                     const_iterator;
    typedef value_type*                           pointer;
    typedef const value_type*                     const_pointer;
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    size_type __map_[_Nm > 0 ? _Nm : 1];
    value_type __elems_[_Nm > 0 ? _Nm : 1];
    size_type __start_;
    size_type __end_;
    size_type __count_;
    arrayMap()
    {
		std::fill_n(__elems_, _Nm-1, value_type());
		for(int i = 0; i < _Nm; i++)
			__map_[i]=i;
		__start_ = __end_ = __count_ = 0;
    }
    arrayMap(value_type __u[],size_type __s)
	{

    	__start_ = 0;
   		if(__s > 0)
    		__end_ = __s-1;
    	else
    		__end_ = 0;
    	std::copy(__u, __u + __end_ + 1,__elems_ );
    	for(int i = 0; i < _Nm; i++)
			__map_[i]=i;
		__count_ = __s;
	}
    // No explicit construct/copy/destroy for aggregate type
    /*
     * set all element to @__u
     */
    void assign(const value_type& __u)
	{
    	__start_ = 0;
    	if(_Nm > 0){
    		__end_ = _Nm-1;
    		__count_ = _Nm;
    		std::fill_n(__elems_, _Nm-1, __u);
    	}
    	else
    		__end_ = 0;
    		__count_ = 0;
		for(int i = 0; i <= __end_; i++)
			__map_[i] = i;
	}
    void insert(const value_type& __u)
	{
		__end_++;
    	__end_%=_Nm;
    	__count_++;
    	if(__end_ == __start_)
    	{
    		__start_++;
    		__start_%=_Nm;
    		__count_ = _Nm;
    	}
		std::fill_n(__elems_+__map_[__end_], 1, __u);
	}
    void insert(const value_type& __u,const size_type& __i)
	{

		__end_++;
    	__end_%=_Nm;
    	__count_++;
    	if(__end_ == __start_)
    	{
    		__start_++;
    		__start_%=_Nm;
    		__count_ = _Nm;
    	}
		size_type temp = __map_[__end_];
		int i = __end_;
		for(; i > (__start_+__i)%_Nm; i--)
			__map_[i] =  __map_[i-1];
		__map_[i] = temp;
		std::fill_n(__elems_+temp, 1, __u);
	}
    //if the size full,replace the first element
    void push_front(const value_type& __u)
   	{
       	__count_++;
       	if(__count_ < _Nm)
       	{
			__start_--;
       		__start_%=_Nm;
       	}
       	std::fill_n(__elems_+__map_[__start_], 1, __u);
   	}
    void swap(arrayMap& __a)
    {
    	std::swap_ranges(__elems_, __elems_ + _Nm, __a.__elems_);
    	std::swap_ranges(__map_, __map_ + _Nm, __a.__map_);
    	__start_ = __a.__start_%_Nm;
    	__end_ = __a.__end_%_Nm;
    	__count_ = _Nm;
    }

    // iterators:
    iterator begin() {return iterator(&__elems_[__map_[__start_]]);}
    const_iterator begin() const {return const_iterator(&__elems_[__map_[__start_]]);}
    iterator end() {return iterator(&__elems_[__map_[__end_]]);}
    const_iterator end() const {return const_iterator(&__elems_[__map_[__end_]]);}

    reverse_iterator rbegin() {return reverse_iterator(end());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    reverse_iterator rend() {return reverse_iterator(begin());}
    const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

    const_iterator cbegin() const {return begin();}
    const_iterator cend() const {return end();}
    const_reverse_iterator crbegin() const {return rbegin();}
    const_reverse_iterator crend() const {return rend();}

    // capacity:
    size_type size() const {return __count_;}
    size_type max_size() const {return _Nm;}
    bool empty() const {return (__end_==__start_);}
    void clear()
    {		
    	std::fill_n(__elems_, _Nm-1, value_type());
		for(int i = 0; i < _Nm; i++)
			__map_[i] = i;
		__start_ = __end_ = __count_ = 0;
    }

    // element access:
    /*
     * if @__i >size(), insert one element after the current last one
     */
    reference operator[](size_type __i)
    {
    	if (__i >= size())
    	{
              insert(value_type());
    	}
    	return __elems_[__map_[(__start_+__i)%_Nm]];
    }
    value_type* data() {return __elems_;}
    const value_type* data() const {return __elems_;}
    bool erase(size_type __i)
    {
		if(__count_ == 0)
			return true;
		size_type cur_map = __map_[(__start_ + __i) % _Nm];
		__elems_[cur_map] = value_type();

		if((__i<<1) < size())
		{
			for(size_type i = __i; i > 0; i--){
				__map_[(__start_ + i) % _Nm] = __map_[(__start_ + i - 1) % _Nm];
			}
			__map_[(__start_ ) % _Nm] = cur_map;
			__start_++;
			__start_%=_Nm;
		}
    	else
    	{
			for(size_type i = __i; i < _Nm-1; i++)
			{
				__map_[(__start_ + i) % _Nm] = __map_[(__start_ + i + 1) % _Nm];
			}
			__map_[(__start_ + _Nm-1) % _Nm] = cur_map;
			__end_--;
			__end_%=_Nm;
    	}
    	__count_--;
    	return true;
    }
};

#endif /* ARRAYMAP_H_ */
