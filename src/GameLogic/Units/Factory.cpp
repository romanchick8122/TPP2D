#include "GameLogic/Units/Factory.h"

Factory::Factory(const std::string& name_, float cost_, const engine::config::Facade::Texture*& texture_) :
name(name_), cost(cost_), texture(texture_) {}
