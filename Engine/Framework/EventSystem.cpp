#include"EventSystem.h"
#include"Object/Object.h"


namespace nc
{
    void EventSystem::Unsubscribe(const std::string& name, Object* reveiver)
    {
        auto& eventObservers = observers[name];
        for (auto iter = eventObservers.begin(); iter != eventObservers.end();)
        {
            if (iter->reveiver == reveiver)
            {
                iter = eventObservers.erase(iter);

            }
            else
            {
                iter++;
            }
        }
    }
    void EventSystem::Startup()
    {

    }

    void EventSystem::Shutdown()
    {

    }

    void EventSystem::Update(float dt)
    {

    }

    void EventSystem::Subscribe(const std::string& name, function_t function,Object* reveiver)
    {
        Observer observer;
        observer.function = function;
        observer.reveiver = reveiver;

        observers[name].push_back(observer);
    }

    void EventSystem::Notify(const Event& event)
    {
        auto& eventObservers = observers[event.name];
        for (auto& observer : eventObservers)
        {
            if (event.receiver == nullptr || event.receiver == observer.reveiver)
            {
                observer.function(event);
            }
        }
    }
}