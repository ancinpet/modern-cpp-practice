#ifndef TED_UNIQUE_PTR_H
#define TED_UNIQUE_PTR_H

#include <memory>
#include <utility>

template <typename T>
class ted_unique_ptr
{
   struct DeleterBase
   {
      virtual void operator()(T *) = 0;
      virtual ~DeleterBase() = default;
   };
   
   template <typename U> 
   struct DeleterDerived : DeleterBase
   {
      U deleter_;
      DeleterDerived(const U& deleter): deleter_(deleter) {}
      virtual void operator()(T * p) override {
         deleter_(p);
      }
   };
   
   T * ptr_;
   DeleterBase * ptr_del_;
   
public:
   ted_unique_ptr() : ptr_(nullptr), ptr_del_(nullptr) { }
   
   template <typename U = std::default_delete<T>>
   ted_unique_ptr(T* ptr, const U& deleter = U{}) : ptr_(ptr)
   {
       ptr_del_ = new DeleterDerived(deleter);
   }
   
   ted_unique_ptr(const ted_unique_ptr&) = delete;
      
   ted_unique_ptr(ted_unique_ptr&& other) : ptr_(other.ptr_), ptr_del_(other.ptr_del_)
   {
      other.ptr_ = nullptr;
      other.ptr_del_ = nullptr;
   }
   
   ted_unique_ptr& operator=(const ted_unique_ptr&) = delete;
   
   ted_unique_ptr& operator=(ted_unique_ptr&& other)
   {
      ted_unique_ptr temp{ std::move(other) };
      std::swap(ptr_, temp.ptr_);
      std::swap(ptr_del_, temp.ptr_del_);
      return *this;
   }
   
   ~ted_unique_ptr()
   {
      (*ptr_del_)(ptr_);
      delete ptr_del_;
   }
};

#endif