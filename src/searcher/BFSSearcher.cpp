#include "BFSSearcher.hpp"


namespace searcher{

    

    template <typename IdentifierType, typename ValueType>
    std::vector<std::string> BFSSearcher::search(const Searchable<IdentifierType, ValueType>& searchable) const{
        return recursiveSearch(searchable, searchable.getStartElement(), searchable.getEndElement());
    }

    template <typename IdentifierType, typename ValueType>
     std::vector<std::string> BFSSearcher::recursiveSearch(const Searchable<IdentifierType, ValueType>& searchable, const Element<IdentifierType, ValueType>& elm, const Element<IdentifierType, ValueType>& target){
         if(elm.getValue() == target.getValue())
            return "";
        
        for(Element<IdentifierType, ValueType> next : searchable.getAllReachableElements(elm)){
            return ""
        }
     }


}