#pragma once
#include <iostream>
#include <functional>

template<typename T, typename T2> class property_sb{
public:
	std::function<T(T2)> get;
	T operator[](T2 i){
		if(get){
			return(get(i));
		}else{
			T def = T();
			return(def);
		}
	}
	property_sb(std::function<T(T2)> g){
		get = g;
	}
	property_sb(){

	}
};
