#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <functional>
#include <map>

// A signal object may call multiple slots with the
// same signature. You can connect functions to the signal
// which will be called when the emit() method on the
// signal object is invoked. Any argument passed to emit()
// will be passed to the given functions.

template <typename... Args>
class Signal {

 public:

  Signal() : current_id_(0) {}

  // copy creates new signal
  Signal(Signal const& other) : current_id_(0) {}

  // connects a member function to this Signal
  template <typename T>
  int connect_member(T *inst, void (T::*func)(Args...)) {
    return connect([=](Args... args) { 
      (inst->*func)(args...); 
    });
  }

  // connects a const member function to this Signal
  template <typename T>
  int connect_member(T *inst, void (T::*func)(Args...) const) {
    return connect([=](Args... args) {
      (inst->*func)(args...); 
    });
  }

  // connects a std::function to the signal. The returned
  // value can be used to disconnect the function again
  int connect(std::function<void(Args...)> const& slot) const {
    slots_.insert(std::make_pair(++current_id_, slot));
    return current_id_;
  }

  // disconnects a previously connected function
  void disconnect(int id) const {
    slots_.erase(id);
  }

  // disconnects all previously connected functions
  void disconnect_all() const {
    slots_.clear();
  }

  // calls all connected functions
  void emit(Args... p) {
    for(auto it : slots_) {
      it.second(p...);
    }
  }

  // assignment creates new Signal
  Signal& operator=(Signal const& other) {
    disconnect_all();
  }

 private:
  mutable std::map<int, std::function<void(Args...)>> slots_;
  mutable int current_id_;
};

#endif /* SIGNAL_HPP */
/* Usage
#include "Signal.hpp"
#include <iostream>

int main() {

  // create new signal
  Signal<std::string, int> signal;

  // attach a slot
  signal.connect([](std::string arg1, int arg2) {
      std::cout << arg1 << " " << arg2 << std::endl;
  });

  signal.emit("The answer:", 42);

  return 0;
}

#include "Signal.hpp"
#include <iostream>

class Button {
 public:
  Signal<> on_click;
};

class Message {
 public:
  void display() const {
    std::cout << "Hello World!" << std::endl;
  }
};

int main() {
  Button  button;
  Message message;

  button.on_click.connect_member(&message, &Message::display);
  button.on_click.emit();

  return 0;
}


#include "Signal.hpp"
#include <iostream>

class Person {
public:
  Person(std::string const &name) : name_(name) {}

  Signal<std::string const &> say;

  void listen(std::string const &message) {
    std::cout << name_ << " received: " << message << std::endl;
  }

private:
  std::string name_;
};

int main() {
  Person alice("Alice"), bob("Bob");

  alice.say.connect_member(&bob, &Person::listen);
  bob.say.connect_member(&alice, &Person::listen);

  alice.say.emit("Have a nice day!");
  bob.say.emit("Thank you!");

  return 0;
}
*/

