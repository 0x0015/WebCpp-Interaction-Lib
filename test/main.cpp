#include <iostream>
#include "../Elements/Element.hpp"

int main(){
	std::cout<<"Hello World"<<std::endl;
	std::shared_ptr<Element> input = Element::getById("in");
	std::cout<<"Input value: "<<input->getValue()<<std::endl;
	input->setValue("New value");
}
