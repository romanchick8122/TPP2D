#pragma once
#include "gameObject.h"
namespace engine {
    class gameplayClickableGameObject : public engine::gameObject {
    public:
        static gameplayClickableGameObject* previousClick;
        virtual void doOnClick() = 0;
    };
}