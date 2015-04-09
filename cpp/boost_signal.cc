#include <iostream>

#include <boost/signal.hpp>

struct HelloWorld {
  void operator()() const { std::cout << "Hello, World!" << std::endl; } 
};

// ...
//
// // Signal with no arguments and a void return value

int main() {
	boost::signal<void ()> sig;

	// Connect a HelloWorld slot
	HelloWorld hello;
	sig.connect(hello);

	// Call all of the slots
	sig();
	return 0;
}
