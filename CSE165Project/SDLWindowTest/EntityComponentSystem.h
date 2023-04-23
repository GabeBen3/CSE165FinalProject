//Header file to manage Entities in the game and the components each entity will have.
//Contains components class that can be derived into sepcific components (Position, life, physics, collisions)
//Contains Entity class to hold information about specific entities in the game, each entity will have its own array of components that it will use and can access/manipulate
#ifndef ENTITYCOMPONENTSYSTEM_H
#define ENTITYCOMPONENTSYSTEM_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

//Declare IDs for components we will use in game 
using ComponentID = std::size_t;

//ID correlating to a game component (postion, physics, input handling)
inline ComponentID getComponentTypeID() {

	static ComponentID lastID = 0;
	return lastID++;
}

//Return the component ID of Given component
template <typename T> inline ComponentID getComponentTypeID() noexcept{

	static ComponentID typeID = getComponentTypeID();
	return typeID;
}


//declare/define new variable types to use in our Entity and Component functions

//Determine if Etity has a component
constexpr std::size_t maxComponents = 32;

//True/False whether certain component exists in an entity
using ComponentBitSet = std::bitset<maxComponents>;

//Store Components in entity
using ComponentArray = std::array<Component*, maxComponents>;

//Base class for components
class Component {
public:
	//Ptr to an entity obj
	Entity* entity;


	//entity functions to override on specific entity types
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Component() {} ;
};

class Entity {
public:

	//Entity loops through components and runs update/draw for each through Component
	void update() {
		for (auto& c : components) {
			c->update();
		}
	}

	//Render entity through component function
	void draw() {
		for (auto& c : components) {
			c->draw();
		}
	}

	void deactivate() {
		active = false;
	}

	void activate() {
		active = true;
	}

	//check if should be destroyed 
	bool isActive() const {
		return active;
	}

	//Initiate entity destruction
	void destroy() {
		active = false;
	}

	//Function to check if entity contains certain component
	template <typename T> bool hasComponent() const {
		//return bool value if entity contains the component
		return compBitSet[getComponentTypeID<T>()];
	}


	//Function to add component to entity
	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;	//Create new entity

		//Determine component to be added
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		//Update Component variables in entity
		//Add component to correct position in compArray (same index between all entities)
		compArray[getComponentTypeID<T>()] = c;
		compBitSet[getComponentTypeID<T>()] = true;

		//Initialize new component
		c->init();
		return *c;
	}

	//Get component function to perform operations on it
	template <typename T> T& getComponent() const {
		auto ptr(compArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	// HOW TO USE THESE FUNCTIONS: 
	//	gameobject.getComponent<PositionComponent>().setXpos(25);
			//reference to game objs
				//use get component function to open and make edits to a certain component on the entity
					//Make alterations to the component accordingly




private:
	//Should entity stay in game (is enemy alive?)
	bool active = true;

	//Vector to hold component objs of an entity
	std::vector<std::unique_ptr<Component>> components;

	//Declare Comp. variables
	ComponentArray compArray;
	ComponentBitSet compBitSet;
};


//Manager class to keep track of all entites in world

class Manager {
public:

	//Function to update list of entities and their components (update funtion from Entity class)->(virtual update function in components)
	void update() {
		for (auto& entity : entities) {
			entity->update();
		}
	}

	//Function to render entity in vector (draw function in Entity Class)->(virtual draw function in components)
	void draw() {
		for (auto& entity : entities) {
			entity->draw();
		}
	}

	//Remove entities no longer in vector
	void refresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity){

			return !mEntity->isActive();
				
		}),
			std::end(entities));
	}

	//Function to add an entity to vector of entities
	Entity& addEntity() {
		Entity* entity = new Entity(); //Create new entity
		std::unique_ptr<Entity> uPtr{ entity };	//Create smart ptr to new Entity
		entities.emplace_back(std::move(uPtr));	//Move ptr to entity to entities vect
		return *entity;		//return ptr to entity
	}

private:
	//Vector of smart ptrs to entites
	std::vector<std::unique_ptr<Entity>> entities;
};


#endif // !ENTITYCOMPONENTSYSTEM_H