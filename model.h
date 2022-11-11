// C++ std libraries

#include <eigen/Eigen/Dense>
#include <iostream>
#include <string>

#include "entity.h"

using namespace std;


class Model
{
public:
	virtual void init(double dt_seconds) = 0;
	virtual void update(double dt_seconds) = 0;
};


class PropulsionModel : Model
{
public:

};