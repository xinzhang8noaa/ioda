#include <string>
#include <iostream>

#include "netcdf_io.h"
#include "odb.h"

using namespace ioda;

int main()
{
    // Open the file for read access
    NcFile dataFile("diag_t_01_wprofiles.nc4", NcFile::read);

    OdbContainer<double> odb;

    // Initial the io
    NetCDF_IO io;
    io.getVar(dataFile, "Latitude"); 
    std::unique_ptr<double[]> lat = io.getData<double>();
    odb.DataContainer.insert({"Radiosonde", "4DLocation", "Latitude", lat});

    io.getVar(dataFile, "Observation"); 
    std::unique_ptr<double[]> v = io.getData<double>();
    odb.DataContainer.insert({"Radiosonde", "ObsValue", "V", v});
    //odb.DataContainer.insert({"GPS", "ObsValue", "U", u});
    //odb.DataContainer.insert({"Aircraft", "ObsValue", "T", t});
    //odb.DataContainer.insert({"Profiler", "ObsErr", "T", toe});
    //odb.DataContainer.insert({"Surface", "OminusA", "Q", q});  
    std::cout << odb.DataContainer.count("Radiosonde") << '\n'; 
    std::cout << "What it is ? : " << odb << std::endl;
    std::cout << "Hello ! " << io << std::endl;
    std::cout << "\nAll records:\n----------------------------------------------------------------------\n";
    for (auto & v : odb.DataContainer)
        std::cout << v << "\n";   

    std::cout << "\nAll records with ObsValue:\n----------------------------------------------------------------------\n";
    const auto & entity_index = odb.DataContainer.get<2>();
    std::cout << entity_index.count("ObsValue") << '\n';
    auto entity_range = entity_index.equal_range("ObsValue");
    for (auto const& r : boost::make_iterator_range(entity_range.first, entity_range.second)){
        std::cout << r << std::endl;
    }

    std::cout << "\nAll records with (first, second, thrid) == (Radiosonde,ObsValue,V):\n----------------------------------------------------------------------\n";
    const auto& index = odb.DataContainer.get<0>();
    auto range = index.equal_range(boost::make_tuple("Radiosonde","ObsValue","V"));
    for (auto const& r : boost::make_iterator_range(range.first, range.second)){
        std::cout << r << "\n";
    }

    return 0;
}
