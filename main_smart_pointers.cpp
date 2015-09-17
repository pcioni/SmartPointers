#include <iostream>
#include <cassert>
#include <string>
#include <set>

// simple homemade smart pointers
#include "ds_smart_pointers.h"


// ====================================================
// BALLOON: a toy class with dynamically allocated memory
// ====================================================

#define MAX_NUM_ROPES 10

class Balloon {
public:
  // CONSTRUCTOR & DESTRUCTOR
  Balloon(const std::string& name_) : name(name_) {
    std::cout << "Balloon constructor " << name << std::endl;
    num_ropes = 0;
    ropes = new Balloon* [MAX_NUM_ROPES];
  }
  ~Balloon() {
    std::cout << "Balloon destructor " << name << std::endl;
    // don't try to destroy attached balloons, just delete array
    delete [] ropes;
  }

  // ACCESSORS
  void friend deleteAll(Balloon* b);
  void friend buildSet(std::set<Balloon*> &s, Balloon* b);
  const std::string& getName() const { return name; }
  int numRopes() const { return num_ropes; }
  const Balloon* getRope(int i) const { return ropes[i]; }

  // print the balloons we are attached to
  void print() { 
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes[i]->name << " ";
    }
    if (num_ropes == 0) std::cout << "nothing";
    std::cout << std::endl;
  }
  // add a rope connecting this balloon to another
  void addRope(Balloon* b) { 
    assert (num_ropes < MAX_NUM_ROPES);
    ropes[num_ropes] = b;
    num_ropes++;
  }
  // detach a rope connecting this balloon to another
  void removeRope(Balloon* b) { 
    for (int i = 0; i < MAX_NUM_ROPES; i++) {
      if (ropes[i] == b) { ropes[i] = ropes[num_ropes-1]; num_ropes--; break; }
    }
  }
 
private:
  std::string name;
  int num_ropes;
  // a dynamically allocated C-style array of ropes connecting to other Balloons
  Balloon** ropes; 
};

void buildSet(std::set<Balloon*> &s, Balloon* b) {
	std::pair<std::set<Balloon*>::iterator,bool> ret;
	for (int i = 0; i < b->num_ropes; ++i) {
		ret = s.insert(b->ropes[i]);
		if (ret.second == true )
			buildSet(s, b->ropes[i]);
		else
			return;
	}
}

void deleteAll(Balloon* b) {
	std::set<Balloon*> balloons;
	std::set<Balloon*>::iterator itr;
	buildSet(balloons, b);
	for (itr = balloons.begin(); itr != balloons.end(); ++itr)
		delete *itr;
}

// ====================================================
// ====================================================

int main() {

  std::cout << "start of main" << std::endl;
