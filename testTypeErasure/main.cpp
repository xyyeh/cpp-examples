// typeErasure.cpp

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Object {  // (2)

public:
  template <typename T>  // (3)
  Object(T&& obj) : object(std::make_shared<Model<T>>(std::forward<T>(obj))) {}

  std::string getName() const {  // (4)
    return object->getName();
  }

  struct Concept {  // (5) The concept, everything here must be pure virtual
    virtual ~Concept() {}
    virtual std::string getName() const = 0;
  };

  template <typename T>  // (6) The model is an instantiation of the concept
  struct Model : Concept {
    Model(const T& t) : object(t) {}
    std::string getName() const override { return object.getName(); }

  private:
    T object;
  };

  std::shared_ptr<const Concept> object;
};

void printName(std::vector<Object> vec) {  // (7)
  for (auto v : vec) std::cout << v.getName() << '\n';
}

struct Bar {
  std::string getName() const {  // (8)
    return "Bar";
  }
};

struct Foo {
  std::string getName() const {  // (8)
    return "Foo";
  }
};

int main() {
  std::vector<Object> vec{Object(Foo()), Object(Bar())};  // (1)
  printName(vec);
}