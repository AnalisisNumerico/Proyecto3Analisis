#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include "Aplication.hpp"
#include "Spline.hpp"


namespace {
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
} // namespace

int main(int argc, char* argv[]) {

  anpi::heat<double>();

  int plateBorderSize = 3;
  std::vector<float> temperatures = {50,1000,0,100,2000,28};
  anpi::interpolate<float>(plateBorderSize, temperatures);

  try  {

    int top     = -1;
    int bottom  = -1;
    int left    = -1;
    int right   = -1;

    std::vector<char> isolated;
    std::string path;

    int horizontal;
    int vertical;

    int grid = 0;

    // Define and parse the program options
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
        ("help", "produce help message")
        (",t", po::value<int>(&top), "Top border temperature")
        (",b", po::value<int>(&bottom), "Bottom border temperature")
        (",l", po::value<int>(&left), "Left border temperature")
        (",r", po::value<int>(&right), "Right border temperature")
        (",i", po::value<std::vector<char> >(&isolated),"Isolates the given borders")
        (",p", po::value<std::string>(&path)->required(), "Path of the thermic profile txt")
        (",h", po::value<int>(&horizontal)->required(), "Number of horizontal pixels of the solution")
        (",v", po::value<int>(&vertical)->required(), "Number of vertical pixels of the solution")
        (",q", "Deacivates the graphing of the solution")
        (",f", po::value<int>(&grid), "If specified enable heat flow visualization and especifies the grid size")
     ;

    po::variables_map vm;

    try {
      po::store(po::parse_command_line(argc, argv, desc),
                vm); // can throw 

      // --help option

      if ( vm.count("help") ) {
        std::cout << "Basic Command Line Parameter App" << std::endl
                  << desc << std::endl;
        return SUCCESS;
      }

      po::notify(vm); // throws on error, so do after help in case 
      // there are any problems
    }
    catch(po::error& e) {
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
      std::cerr << desc << std::endl;
      return ERROR_IN_COMMAND_LINE;
    }

    std::cout << top <<  " " << bottom << " " << left << " " << right << "\n";
    for(int i = 0; i < isolated.size(); i++) {
      std::cout << isolated[i] <<  " ";
    }
    std::cout << "\n";
    std::cout << path << " " <<vertical <<  " " << horizontal << "\n";

    if ( vm.count("-q") ) {
      std::cout << "graphing deactivated" << std::endl;
    }

    if ( !vm.count("-q") ) {
      std::cout << "graphing activated" << std::endl;
    }

  }

  catch(std::exception& e) {
    std::cerr << "Unhandled Exception reached the top of main: "
              << e.what() << ", application will now exit" << std::endl;
    return ERROR_UNHANDLED_EXCEPTION;
  }

 return SUCCESS;

} // main 