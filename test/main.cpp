#include <iostream>
#include "../Elements/Element.hpp"

void printTest(){
	std::cout<<"printed Test!"<<std::endl;
}

int main(){
	std::cout<<"Hello World"<<std::endl;
	std::shared_ptr<Element> input = Element::getById("in");
	std::cout<<"Input value: "<<(std::string)input->dom_value<<std::endl;
	input->dom_value = "New value";
	std::shared_ptr<Element> button = Element::getById("button");
	button->dom_onclick = printTest;
	std::shared_ptr<Element> button2 = Element::getById("button2");
	std::function<void()> b2oncl = button2->dom_onclick;
	b2oncl();
}
