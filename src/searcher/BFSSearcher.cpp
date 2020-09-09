#include "BFSSearcher.hpp"


namespace searcher{

    

    template <typename ElementType>
    std::vector<std::string> BFSSearcher::search(const Searchable<ElementType>& searchable) const{
        return recursiveSearch(searchable, searchable.getStartElement(), searchable.getEndElement());
    }

    template <typename ElementType>
     std::vector<std::string> BFSSearcher::recursiveSearch(const Searchable<ElementType>& searchable, const ElementType& elm, const ElementType& target){
         if(elm.getValue() == target.getValue())
            return "";
        
        for(Element<IdentifierType, ValueType> next : searchable.getAllReachableElements(elm)){
            return ""
        }
     }


}