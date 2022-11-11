//
#include <eigen/Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>

#include "model.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<Model*> models;

	models.push_back(new PropulsionModel());
	models.push_back(new HeatTransferModel());

	

	std::cout << "Closing program." << std::endl;
	return 0;
}
