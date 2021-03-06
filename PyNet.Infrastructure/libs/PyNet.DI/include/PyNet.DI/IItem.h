#pragma once
 #include <memory>
 #include <any>

 using namespace std;

 class IItem {
 public:
 	virtual void Reset() = 0;
	virtual void* GetInstance(any& context) = 0;
	virtual bool HasInstance() = 0;
    virtual void MakeReferenceWeak() = 0;
	bool Marker = false;
	virtual ~IItem() = default;
 };