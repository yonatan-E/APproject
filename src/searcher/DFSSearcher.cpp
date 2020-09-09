#include "DFSSearcher.hpp"
#include "algorithm"


namespace searcher{
    
    template <typename ElementType>
    std::vector<std::string> DFSSearcher::search(const Searchable<ElementType>& searchable) const{
        std::vector<ElementType> visited;
        std::vector<std::string> directions;
        for(searchable.)
        return recursiveSearch(visited, directions, searchable, searchable.getStartElement());
    }

    template <typename ElementType>
     std::vector<std::string> DFSSearcher::recursiveSearch(std::vector<ElementType>& visited, std::vector<std::string>& directions, const Searchable<ElementType>& searchable, const ElementType& elm){
       
        if(std::find(visited.begin(), visited.end(), elm) == visited.end()){

        }

     }

}