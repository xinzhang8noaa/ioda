ecbuild_add_library (   TARGET ioda
                        SOURCES
                            NetCDF_IO.cc
                            NetCDF_IO.h
                            odb.h
                        LIBS ${NETCDF_LIBRARIES}
                        INSTALL_HEADERS LISTED
                        LINKER_LANGUAGE ${IODA_LINKER_LANGUAGE}
)