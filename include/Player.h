#ifndef _PLAYER_H_ //ensuring that this object is only initialized once
#define _PLAYER_H_

#include <iostream>
#include <string>

using namespace std;

class Player {
    public:
        Player();
        Player(string id, string name, string symbol);

        string Id {};
        string Name {};
        string Symbol {};
};

#endif // end _PLAYER_H_