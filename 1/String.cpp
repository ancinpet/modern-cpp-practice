#include <cstring>
#include "String.h"

class String::Impl {
public:
    //Default ctor
    Impl(const char* arg): data_(new char[strlen(arg) + 1]) { strcpy(data_, arg); }
    //Copy ctor using default ctor
    Impl(const Impl & arg): Impl(arg.data_) {}
    //Move ctor using nulling of argument
    Impl(Impl && arg) noexcept { data_ = arg.data_; arg.data_ = nullptr; }
    Impl& operator=(const Impl&) = delete;
    ~Impl() { delete[] data_; }
    const char* data() const { return data_; }
    void swap(Impl & arg) {
        char * tmp = arg.data_;
        arg.data_ = data_;
        data_ = tmp;
    }

    char* data_;
};

String::String(const char* arg): pimpl_(new Impl(arg)) {}
String::String(const String & arg): pimpl_(new Impl(*(arg.pimpl_))) {}
String::~String() { delete pimpl_; }
const char* String::data() const { return pimpl_->data(); }

String::String(String && arg) noexcept {
    //Call move ctor
    pimpl_ = new Impl(std::move(*(arg.pimpl_)));
}

String& String::operator=(const String & arg) {
    //Copy and swap - copy String and swap Impl, tmp with old data_ destructs and calls Impl destructor
    String tmp(arg);
    pimpl_->swap(*(tmp.pimpl_));
    return *this;
}

String& String::operator=(String && arg) noexcept {
    String tmp(std::move(arg));
    pimpl_->swap(*(tmp.pimpl_));
    return *this; 
}

void String::swap(String & arg) noexcept {
    pimpl_->swap(*(arg.pimpl_));
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    return os << s.data();
}

void swap(String & lhs, String & rhs) noexcept {
    lhs.swap(rhs);
}