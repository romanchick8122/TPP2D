#pragma once
#include "iostream"
namespace engine {
    class Action {
      public:
        enum Type {
            None
        };
        virtual void write(const std::ostream&);
        virtual void apply();
        static Action read(const std::istream&);
    };
}