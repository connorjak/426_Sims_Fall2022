// C++ std libraries

#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <memory>

#include "entity.h"

using namespace std;

// Abstract base class; don't modify
class Model
{
private:
	shared_ptr<Entity> en;

public:
	Model(shared_ptr<Entity> _en)
	{
		en = _en;
	}
	virtual void init() = 0;
	virtual void update(double dt_seconds) = 0;
};


class PropulsionModel : public Model
{
public:
	PropulsionModel(shared_ptr<Entity> _en) : Model(_en) {};
	virtual void init() override
	{
		/*Single Engine specs*/
		double Isp = 363;
		double g0 = 9.80665;
		double maxthrust = 606994;
		double nmaxengines = 8;
		double minthrottling = 0.40;
		double maxmdot = 1 / (Isp * g0 / maxthrust);


		/*HLS specs*/
		double oxidizerfullmass = 92550.4;
		double fuelfullmass = 26104.0;
		double mixtureratio = oxidizerfullmass / fuelfullmass;
		double propellantfullmass = oxidizerfullmass + fuelfullmass;
		double HLSfullmass = 166429.00;
		double HLSemptymass = HLSfullmass - (propellantfullmass);

		/*remainingfuel = input('Input remaining fuel mass') This line is used to input remaining fuel mass prior to firing*/
		double remainingfuel = fuelfullmass;

		/*remainingoxidizer = input('Input remaining oxidizer mass')  This line is used to input remaining oxidizer mass prior to firing*/
		double remainingoxidizer = oxidizerfullmass;

		double remainingpropellant = remainingfuel + remainingoxidizer;

		double HLSremainingmass = HLSemptymass + remainingpropellant;

		/*nengines = input('Input number of engines firing for thrust) This line is used to input the number of engines fired for thrust*/
		double nengines = nmaxengines;


		/*throttlelevel = input('Input thrust level between ' + str(minthrottling * 100) + '% and 100%') This line is used to input the thrust level for the engines*/
		double throttlelevel = minthrottling;

		double Thrust = (nengines * maxthrust) * throttlelevel;
		double propellantmdot = maxmdot * nengines * throttlelevel;

		double oxmdot = (propellantmdot / (mixtureratio + 1)) * mixtureratio;
		double fuelmdot = (propellantmdot / (mixtureratio + 1));

		/*firingtime = input('Input length of firing time')*/
		double firingtime = 10;

		//Connor: Looks like the rocket equation
		double deltav = (-1 * Thrust * log((HLSremainingmass - (propellantmdot * firingtime))) / propellantmdot) + (Thrust * log(HLSremainingmass) / propellantmdot);

		remainingpropellant = remainingpropellant - (propellantmdot * firingtime);

		remainingoxidizer = remainingoxidizer - (oxmdot * firingtime);

		remainingfuel = remainingfuel - (fuelmdot * firingtime);


		cout << "remainingpropellant: " << remainingpropellant << endl;
		cout << "remainingoxidizer: " << remainingoxidizer << endl;
		cout << "remainingfuel: " << remainingfuel << endl;
	};
	virtual void update(double dt_seconds) override
	{
		//cout << "PropulsionModel dt: " << dt_seconds << endl;
	};
};


class HeatTransferModel : public Model
{
public:
	HeatTransferModel(shared_ptr<Entity> _en) : Model(_en) {};
	virtual void init() override
	{

	};
	virtual void update(double dt_seconds) override
	{
		//cout << "HeatTransferModel dt: " << dt_seconds << endl;
	};
};