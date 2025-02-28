#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H
#include "Globals.h"
#include <string>

using namespace std;

class Authenticate {
	
	public:
		Authenticate();
		~Authenticate();
		string generateUUID();
		string get_userID();


};

#endif //AUTHENTICATE_H

