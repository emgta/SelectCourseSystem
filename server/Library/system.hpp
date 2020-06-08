#ifndef system_hpp
#define system_hpp

#include <stdio.h>
#include <map>
#include <memory>

#include "person.hpp"
#include "course.hpp"
#include "../Shared/global.hpp"

class Result_system {
private:
    Result_system();
    static std::unique_ptr<Result_system> m_instance;

public:
    ~Result_system();
    static Result_system& get_instance() {
        if (m_instance == nullptr)
            m_instance.reset(new Result_system);

        return *m_instance;
    }

public:
    Person_ptr get_person(const Person::seq &);
    Course_ptr get_course(const Course::seq &);
    void print_available_course(const Student&, std::ostream &);

private:
    std::map <Person::seq, Person_ptr> num_to_person;
    std::map <Course::seq, Course_ptr> num_to_course;
};

#endif /* system_hpp */
