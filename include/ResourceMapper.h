#ifndef RESOURCEMAPPER_H
#define RESOURCEMAPPER_H

#include <map>
#include <memory>
#include<string>

#include <SFML/Graphics.hpp>

template<typename Resource, typename Identifier>
class ResourceMapper
{
    public:
        ResourceMapper();
        ~ResourceMapper();

        void Load(Identifier id,const std::string& filename);
        Resource& Get(Identifier id);
        const Resource& Get(Identifier id) const;

    private:
      std::map<Identifier,std::unique_ptr<Resource>> mResourceMap;
};

#endif // RESOURCEMAPPER_H
