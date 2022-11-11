// C++ std libraries

#include <eigen/Eigen/Dense>
#include <iostream>
#include <string>

#include "entity.h"

using namespace std;


class Model
{
public:
	virtual void init() = 0;
	virtual void update(double dt_seconds) = 0;
};


class PropulsionModel : Model
{
public:
	virtual void init() override;
	virtual void update(double dt_seconds) override;
};


class HeatTransferModel : Model
{
public:
	virtual void init() override;
	virtual void update(double dt_seconds) override;
};