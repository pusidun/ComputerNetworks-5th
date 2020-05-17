//
// Created by pusid on 2019/10/20.
//
#include<iostream>
#include<memory>
#include<stdexcept>

class StrBlob {
public:
    typedef std::string::size_type size_type;

    StrBlob(): data(make_shared<std::vector<std::string>>()) {};
    StrBlob(std::initializer_list<std::string> li): data(make_shared<std::vector<std::string>>(li)) {}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string s) { data->push_back(s); }
    void pop_back();
    std::string front();
    const std::string front() const;
    std::string back();
    const std::string back() const;

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& mesg) const;
};

void StrBlob::check(std::string::size_type i, const std::string &mesg) const {
    if( i>= data->size() )
        throw out_of_range(mesg);
}

void StrBlob::pop_back() {
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

std::string StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string StrBlob::front() const{
    check(0, "front back on empty StrBlob");
    return data->front();
}

std::string StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string StrBlob::back() const{
    check(0, "back on empty StrBlob");
    return data->back();
}

int main() {
    StrBlob b2;{
        StrBlob b1 = {"a", "an", "the"};
        b2 = b1;
        b2.push_back("about");
        std::cout<<b2.size()<<std::endl<<b1.size();
    }

}