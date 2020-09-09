#include "DFSSearcher.hpp"


namespace searcher{
    
    template <typename ElementType>
    std::vector<std::string> DFSSearcher::search(const Searchable<ElementType>& searchable) const{
        return recursiveSearch(searchable, searchable.getStartElement(), searchable.getEndElement());
    }

    template <typename ElementType>
     std::vector<std::string> DFSSearcher::recursiveSearch(const Searchable<ElementType>& searchable, const ElementType& elm, const ElementType& target){
         if(elm.getValue() == target.getValue())
            return "";
        
        ElementType best = nullptr;
        uint32_t bestPrice = elm.getValue();
        for(auto next : searchable.getAllReachableElements(elm)){
            
        }

     }

}