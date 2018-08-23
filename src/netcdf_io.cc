#include "netcdf_io.h"

namespace ioda {

// -----------------------------------------------------------------------------

void NetCDF_IO::getVar(const NcFile & dataFile, const std::string & varName) {
    
    // Get the handler of the variable
    var_ = dataFile.getVar( varName);
    if(var_.isNull()) {
        std::cerr << "Not Found " << varName << std::endl;
    }
    // Calculate the total size
    size_ = 1;
    for (const auto d : var_.getDims()) {
        //std::cout << "Dimension name :" << d.getName() << "; Dimension size :" << d.getSize() << std::endl;
        size_ *= d.getSize();
    }
}

// -----------------------------------------------------------------------------

std::size_t NetCDF_IO::getSize() {
    return size_;
}

// -----------------------------------------------------------------------------

std::string NetCDF_IO::getType() {
    if (var_.getType().getTypeClassName() == "nc_DOUBLE")
        return "double";
    else if  (var_.getType().getTypeClassName() == "nc_FLOAT")
        return "float";
    else if  (var_.getType().getTypeClassName() == "nc_INT")
        return "int";
    else
        std::cerr << "Not implemented for type : " << var_.getType().getTypeClassName() << " at File " << __FILE__ << std::endl;
}

// -----------------------------------------------------------------------------

void NetCDF_IO::print(std::ostream & os) const {
    os << "In " << __FILE__ << " @ " << __LINE__;
}

// -----------------------------------------------------------------------------

} // namespace ioda
