struct TypeInfo {
	virtual size_t getSize() = 0;
	
	virtual std::string getName() = 0;
	
	struct Member {
		std::string name;
		std::string typeName;
	} members;
	
	const std::vector& getMembers() const {
		return members;
	}
}

template <typename T>
class RegisterTheThing {
	RegisterTheThing() {
		mTypeInfoList.push_back(T::getTypeInfo());
	}
	static RegisterTheThing instance;
}

template <typename T>
class Component : private RegisterTheThing<T>{
	struct T_TypeInfo {
	size_t getSize() {
			return sizeof(T);
		}
	}
	
	template <typename Type>
	void addMembers(const char *name)
	
	
	std::string getName() {
		return 
	}
	
	TypeInfo *getTypeInfo() { static T_TypeInfo type; return &type; }
}

typeInfoList.push_back(PhysicsComponent::getTypeInfo());



class PhysicsComponent : public Component<PhysicsComponent> {
	Physics() : Component<PhysicsComponent>("PhysicsComponent") {
	}
}