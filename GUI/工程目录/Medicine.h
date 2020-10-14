#ifndef MEDICINE_H
#define MEDICINE_H


#include "Object.h"

using namespace std;

class Medicine : public Object
{
public:
    Medicine(int t, const string &imageFile);
    ~Medicine();

friend class Scene;
friend class ProcessGame;
};
#endif // MEDICINE_H

extern vector<Medicine*> lifesupply;
