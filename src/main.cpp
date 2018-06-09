#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include "Aplication.hpp"

namespace {
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
} // namespace

int main(int argc, char* argv[]) {

/*
  double lambda = double(2);

  std::vector <double>    topBorder;
  std::vector <double>   leftBorder;
  std::vector <double>  rightBorder;
  std::vector <double> bottomBorder;

  int plateBorderSize = 100;
  std::vector<double> temperatures = {50,100,0,100,200,28};
  anpi::spline<double>(plateBorderSize, temperatures, topBorder);

  anpi::Matrix<double> plate;

  anpi::heat<double>(plateBorderSize, plateBorderSize, lambda, topBorder, leftBorder, rightBorder, bottomBorder, plate);
  anpi::flow<double>(plateBorderSize, plateBorderSize, topBorder, leftBorder, rightBorder, bottomBorder, plate);
*/
 /*

  std::vector<float> border;

  std::cout << std::endl;

  for(int i = 0; i < border.size(); i++) {
    std::cout << border[i] << " ";
  }

  std::cout << std::endl;
*/

  try  {

    std::vector<double> topBorderTemperature;
    std::vector<double> leftBorderTemperature;
    std::vector<double> rightBorderTemperature;
    std::vector<double> bottomBorderTemperature;

    //std::string path;

    int horizontal;
    int vertical;

    double k;
    int grid;

    bool flow = false;

    bool graphication = true;

    // Define and parse the program options
    namespace po = boost::program_options;
    po::options_description description("Interface");
    description.add_options()
        ("help", "produce help message")
        (",t", po::value<std::vector<double>>(&topBorderTemperature)   -> multitoken(), "Top border temperature(s), if not specified the border is isolated   ")
        (",l", po::value<std::vector<double>>(&leftBorderTemperature)  -> multitoken(), "Left border temperature(s), if not specified the border is isolated  ")
        (",r", po::value<std::vector<double>>(&rightBorderTemperature) -> multitoken(), "Right border temperature(s), if not specified the border is isolated ")
        (",b", po::value<std::vector<double>>(&bottomBorderTemperature)-> multitoken(), "Bottom border temperature(s), if not specified the border is isolated")
        //(",p", po::value<std::string>(&path), "Path of the thermic profile txt") // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<ver lo del archivo
        (",h", po::value<int>(&horizontal) -> required(),   "Number of horizontal pixels of the solution")
        (",v", po::value<int>(&vertical)   -> required(),   "Number of vertical pixels of the solution")
        (",k", po::value<double>(&k), "Termic difusive coeficient, if specified enable heat flow calculation")
        (",g", po::value<int>(&grid) -> default_value(5), "Specifies the grid size of the heat visualization")
        (",q", "Deacivates the graphing of the solution")
    ;

    po::variables_map vm;

    try {
      po::store(po::parse_command_line(argc, argv, description), vm); // can throw

      if ( vm.count("help") ) {
        std::cout << "Basic Command Line Parameter App" << std::endl
                  << description << std::endl;
        return SUCCESS;
      }

      po::notify(vm); // throws on error, so do after help in case 
      // there are any problems
    }
    catch(po::error& e) {
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
      std::cerr << description << std::endl;
      return ERROR_IN_COMMAND_LINE;
    }

    if ( vm.count("-q") ) {
      graphication = false;
      std::cout << "graphing deactivated" << std::endl;
    }

    if ( vm.count("-k") ) {
      flow = true;
    }

    anpi::aplication<double>(horizontal, vertical,
                             topBorderTemperature, leftBorderTemperature, rightBorderTemperature, bottomBorderTemperature,
                             flow, k, grid,
                             graphication);

  }

  catch(std::exception& e) {
    std::cerr << "Unhandled Exception reached the top of main: "
              << e.what() << ", application will now exit" << std::endl;
    return ERROR_UNHANDLED_EXCEPTION;
  }

 return SUCCESS;

} // main