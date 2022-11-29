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
//private:
public:
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
	// Constants
	/*Single Engine specs*/
	double Isp;
	double g0;
	double maxthrust;
	double nmaxengines;
	double minthrottling;
	double maxmdot;

	/*HLS specs*/
	double oxidizerfullmass;
	double fuelfullmass;
	double mixtureratio;
	double propellantfullmass;
	double HLSfullmass;
	double HLSemptymass;

	// Variables that really should be on the entity but aren't yet
	double remainingfuel;
	double remainingoxidizer;


public:
	PropulsionModel(shared_ptr<Entity> _en) : Model(_en) {};
	virtual void init() override
	{
		// Constants
		/*Single Engine specs*/
		Isp = 363;
		g0 = 9.80665;
		maxthrust = 606994;
		nmaxengines = 8;
		minthrottling = 0.40;
		maxmdot = 1 / (Isp * g0 / maxthrust);


		/*HLS specs*/
		oxidizerfullmass = 92550.4;
		fuelfullmass = 26104.0;
		mixtureratio = oxidizerfullmass / fuelfullmass;
		propellantfullmass = oxidizerfullmass + fuelfullmass;
		HLSfullmass = 166429.00;
		HLSemptymass = HLSfullmass - (propellantfullmass);

		/*remainingfuel = input('Input remaining fuel mass') This line is used to input remaining fuel mass prior to firing*/
		remainingfuel = fuelfullmass;

		/*remainingoxidizer = input('Input remaining oxidizer mass')  This line is used to input remaining oxidizer mass prior to firing*/
		remainingoxidizer = oxidizerfullmass;


	};
	virtual void update(double dt_seconds) override
	{
		//cout << "PropulsionModel dt: " << dt_seconds << endl;

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
		double firingtime = dt_seconds;

		//Connor: Might be some odd integration method for computing delta V (could use momentum calculations and not require logs?)
		double deltav = (-1 * Thrust * log((HLSremainingmass - (propellantmdot * firingtime))) / propellantmdot) + (Thrust * log(HLSremainingmass) / propellantmdot);

		//Connor: simplified modification of velocity
		auto vel = en->GetVelocity();
		vel.x() += deltav;
		en->SetVelocity(vel);

		remainingpropellant = remainingpropellant - (propellantmdot * firingtime);

		remainingoxidizer = remainingoxidizer - (oxmdot * firingtime);

		remainingfuel = remainingfuel - (fuelmdot * firingtime);


		cout << "---------------------------------------------------" << endl;
		//cout << "remainingpropellant: " << remainingpropellant << endl;
		cout << "remainingoxidizer: " << remainingoxidizer << endl;
		cout << "remainingfuel: " << remainingfuel << endl;
		cout << "deltav: " << deltav << endl;
		cout << "velocity: " << vel.x() << endl;
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