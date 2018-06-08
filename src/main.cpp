#include <boost/program_options.hpp>
#include <Matrix.hpp>
#include "PlotPyTNSHA.hpp"
namespace {
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
} // namespace

int main() {

    anpi::PlotTNSHA<float> plotTNSHA;
    plotTNSHA.initialize();
    std::vector<float> lol {1,2,3,4,5,6,7,8,9};
    anpi::Matrix<float> lel {{1,2,3,6,7},{4,5,6,12,3},{7,8,9,3,4},{17,2,2,4,3},{7,8,2,2,1}};
    plotTNSHA.imgshow(lel);
    //plotTNSHA.quiver(lol,lol,lol,lol);
    plotTNSHA.show();

} // main
