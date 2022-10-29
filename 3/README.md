#Assignment

A.
Create a smart pointer deep_ptr<T>, which will support copy semantics.
Copying of this "deep pointer" dp1 of type deep_ptr<T>, which owns object "a" of type "T" results in a copy dp2 which will own object of type "T", that will be created as a copy of object "a"
deep_ptr<T> px1{ new T{} }; // px1.get() points to "a"
deep_ptr<T> px2{ px1 };     // px2.get() points to copy of "a"

Also implement function make_deep, which will have same the same semantic for deep_ptr as functions std::make_unique and std::make_shared do for smart pointers std::unique_ptr and std::shared_ptr
auto px1 = make_deep<T>(arg1, arg2, arg3); // args will be perfect-forwarded to the constructor of T

B.
Implement a smart pointer ted_unique_ptr which should be similar to std::unique_ptr with so called type-erased deleter.
Type-erased deleter is a functor which is passed to the smart pointer in constructor as a second argument.
Smart pointer saves a copy of this functor and at the end of its lifetime it applies it to the owned object (the pointer to this object)
{
  auto custom_deleter = [](auto* raw_ptr){ delete raw_ptr; };
  ted_unique_ptr<T> pt{ new T{}, custom_deleter }; // creates an object of type T
} // automatic release of that object, effectively equivalent with custom_deleter(pt.get());
