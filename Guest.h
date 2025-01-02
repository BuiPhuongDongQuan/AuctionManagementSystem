#ifndef GUEST_H
#define GUEST_H
#include "User.h"
#include "Item.h"
using namespace std;

class Guest: public User{
    public:
        Guest();        
        void viewItem() const;
};
#endif
