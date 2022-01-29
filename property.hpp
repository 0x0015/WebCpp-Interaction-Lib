#pragma once
#include <iostream>
#include <functional>

template<typename T> class property{
public:
	std::function<T()> get;
	std::function<void(T&)> set;
	property<T>& operator = (T& val){
		if(set){
			set(val);
		}
		return *this;
	};
	property<T>& operator = (T val){
		if(set){
			set(val);
		}
		return *this;
	};
	operator const T() const{
		if(get){
			return(get());
		}else{
			T def = T();
			return(def);
		}
	}
	property(std::function<T()> g, std::function<void(T&)> s){
		get = g;
		set = s;
	}
	property(std::function<T()> g){
		get = g;
	}
	property(std::function<void(T&)> s){
		set = s;
	}
	property(){

	}
};
