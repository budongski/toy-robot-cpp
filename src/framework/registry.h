#pragma once

#include <map>
#include <string>
#include <functional>
#include "command.h"
#include "utils.h"

namespace toyrobot
{
    class Registry 
	{
    public:
        using CreatorCallback = std::function<std::unique_ptr<Command> (const std::string& src)>;

        Registry() = default;
        Registry(const Registry&) = delete;
        Registry& operator=(const Registry&) = delete;

        std::unique_ptr<Command> makeCommand(const std::string& id, const std::string& src) 
		{
            if(auto it = mCallbacks.find(id);
                it != mCallbacks.end()) 
			{
                return (it->second)(src);
            }
            else if(mUnknownCreator)
            {
                return mUnknownCreator(id);
            }

            return nullptr;
        }

        bool addCreator(const std::string& id, CreatorCallback creator) 
		{
            return mCallbacks.insert(CallbackMap::value_type(id, creator)).second;
        }

        bool addUnknownCreator(CreatorCallback creator)
        {
            mUnknownCreator = creator;
            return true;
        }

        bool removeCreator(const std::string& id)
		{
            return mCallbacks.erase(id) == 1;
        }

    private:
        using CallbackMap = std::map<std::string, CreatorCallback>;
        CallbackMap mCallbacks;

        // special callback to handle unknown tokens
        CreatorCallback mUnknownCreator;
    };
}
