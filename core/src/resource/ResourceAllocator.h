#ifndef RESOURCEALLOCATOR_H
#define RESOURCEALLOCATOR_H

#include "raylib.h"

namespace elementled {

    struct ResourceSprite{
        Texture2D texture;

        bool LoadFromFile(const std::string &filePath){
            std::string updatedPath = std::filesystem::current_path().string().append(filePath);
            texture = LoadTexture(updatedPath.c_str());
            if(texture.id != 0)
                return  true;

            return false;
        }

        void Unload(){
            UnloadTexture(texture);
        }
    };


    template<typename T>
    class ResourceAllocator
    {
    private:
        unsigned int currentID;
        std::map<std::string, std::pair<unsigned int, std::shared_ptr<T>>> m_resources;
    public:
        ResourceAllocator(){
            currentID = 1;
        };

        // TODO : REMOVE RESOURECS AFTER USE!!!
        ~ResourceAllocator(){

            // std::map<std::string, std::pair<unsigned int, std::shared_ptr<T>>> m;
            // for(){
            //     // item.
            // }
        }

        // look for id and return it, otherwise it will create a new id
        unsigned int Add(const std::string &filePath, const std::string &name){
            // auto it = m_resources.find(filePath);
            // if(it != m_resources.end()){
            //     return it->second.first;
            // }

            std::shared_ptr<T> resource = std::make_shared<T>();
            if(!resource->LoadFromFile(filePath.c_str())){
                return 0;
            }

            m_resources.insert(std::make_pair(name, std::make_pair(currentID, resource)));
            return currentID++;
        }

        void RemoveByName(const std::string &name){
            auto it = m_resources.find(name);

            if (it != m_resources.end()){
                m_resources.erase(name);
            }
        }

        void Remove(unsigned int id)
        {
            for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
            {
                if (it->second.first == id)
                {
                    m_resources.erase(it->first);
                }
            }
        }

        std::shared_ptr<T> GetByName(const std::string &name){
            auto it = m_resources.find(name);

            if (it != m_resources.end()){
                return m_resources.at(name).second;
            }

            return nullptr;
        }


        std::shared_ptr<T> Get(unsigned int id)
        {
            for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
            {
                if (it->second.first == id)
                {
                    return std::static_pointer_cast<T>(it->second.second);
                }
            }
            return nullptr;
        }

        T* GetPointer(unsigned int id){
            for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
            {
                if (it->second.first == id)
                {
                    return it->second.second.get();
                }
            }
            return nullptr;
        }

        bool Has(unsigned int id)
        {
            return (Get(id) != nullptr);
        }
    };
}

#endif // RESOURCEALLOCATOR_H
