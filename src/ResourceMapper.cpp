#include "ResourceMapper.h"

#include<assert.h>
template<typename Resource, typename Identifier>
ResourceMapper<Resource, Identifier>::ResourceMapper()
{
    //ctor
}

template<typename Resource, typename Identifier>
ResourceMapper<Resource, Identifier>::~ResourceMapper()
{
    //dtor
}


template<typename Resource, typename Identifier>
void ResourceMapper<Resource, Identifier>::Load(Identifier id,const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());

    if(! resource->loadFromFile(filename))
     {
       throw std::runtime_error("Resource::Load - failed to load " + filename);
     }

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}


template<typename Resource, typename Identifier>
 Resource& ResourceMapper<Resource, Identifier>::Get(Identifier id)
 {
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
 }

 template<typename Resource, typename Identifier>
 const Resource& ResourceMapper<Resource, Identifier>::Get(Identifier id) const
 {
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
 }




