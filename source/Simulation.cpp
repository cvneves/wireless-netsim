#include "../include/Simulation.h"

void Simulation::update()
{


	time++;
}

void Simulation::log_curr_state()
{

}

void Simulation::read_data(std::string file_name)
{
	std::ifstream file;

	file.open(file_name);

	std::string line;
	int i = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::stringstream s(line);
			std::string temp;
			double x, y, reach;
			Router *router = new Router(x, y, reach, i);
			entities.push_back(router);
			i++;
		}
		file.close();
	}
}
