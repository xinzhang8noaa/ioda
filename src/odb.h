#ifndef IODA_ODB_H
#define IODA_ODB_H

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/range/iterator_range.hpp>

#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

#include <string>
#include <iostream>

using namespace boost::multi_index;

namespace ioda {

template<typename Type>
class OdbContainer: public util::Printable {
    public:
        struct Variable{
            std::string obstype;
            std::string group;
            std::string name;
            std::unique_ptr<Type[]> & data;

            // Constructors
            Variable(const std::string & obstype, const std::string & group,
                    const std::string & name, std::unique_ptr<Type[]> & data ):
                obstype(obstype),
                group(group),
                name(name),
                data(data)
            {}

            void setSize( const std::size_t size) {
                totalSize = size;
            }

            const std::size_t getSize() const{
                return totalSize;
            }

            friend std::ostream& operator<<(std::ostream & os, const Variable & v){
                os << v.obstype << ", " << v.group << ", " << v.name << ": { ";
                for (std::size_t i=0; i != 10; ++i){
                    os << v.data[i] << " ";
                }
                os << "}";
                return os;
            }

            private:
                std::size_t totalSize;
        };

        using InnerDataContainer = multi_index_container<
            Variable,
            indexed_by<
                ordered_unique< 
                  composite_key<
                    Variable,
                    member<Variable, std::string, &Variable::obstype>,
                    member<Variable, std::string, &Variable::group>,
                    member<Variable, std::string, &Variable::name>
                  >
                >,
                //non-unique as some subscribers might have more than one number
                ordered_non_unique<
                    member<
                        Variable, std::string, &Variable::obstype
                    >
                >,
                hashed_non_unique<
                    member<
                        Variable, std::string, &Variable::group
                    >
                >,
                ordered_non_unique<
                    member<
                        Variable, std::string, &Variable::name
                    >
                >
            >
        >;

        InnerDataContainer DataContainer;

    private:

        void print(std::ostream & os) const {
             os << "Multi.Index Container for IODA";
        }
};

} // namespace ioda

#endif
