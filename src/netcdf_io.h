#ifndef IODA_NETCDF_IO_H
#define IODA_NETCDF_IO_H

#include <netcdf>
#include <memory>
#include <string>

#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

using namespace netCDF;

namespace ioda {

static const int NC_ERR = 2;

class NetCDF_IO : public util::Printable {

    public:
        static const std::string classname() {return "ioda::NetCDF_IO";}

        /// Access
        void getVar(const NcFile & dataFile, const std::string & varName);
            
        /* The compiler must be able to see the implementation in order to generate code 
           for all specializations */
        template <typename Type>
        std::unique_ptr<Type[]> getData() {
             // Allocate the dynamic array
             std::unique_ptr<Type[]> p(new Type[size_]);
             // Retrive the data
             var_.getVar(p.get());
             // Return the smart pointer
             return p;
        }

        std::size_t getSize();

        std::string getType();

    private:

        void print(std::ostream & os) const;
        NcVar var_;
        NcType type_;
        std::size_t size_;
};

} // namespace ioda

#endif
