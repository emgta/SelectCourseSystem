#ifndef people_hpp
#define people_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "../Shared/global.hpp"
#include "../Shared/network.hpp"

class Student;
class Teacher;

class Person {
public:
    using seq = Shared::Person;
    using cou = Shared::Course;
    Person() { }
    Person(const seq& i, const std::string &n, const std::string &cl, std::vector <cou> &co, const std::string &pa):
        id(i), name(n), college(cl), course(co), password(pa) {};
    virtual ~Person() = default;
    seq get_id() const {
        return id;
    };
    std::string get_name() {
        return name;
    };
    clientType get_user_type() {
        return user_type;
    };
    bool change_passwd(const std::string &cur_pswd, const std::string &new_pswd) {
        if (authorize(cur_pswd)) {
            password = new_pswd;
            return true;
        }

        return false;
    }

    bool authorize(const std::string &);
    virtual const Person &display_info(std::ostream&, const Score_mode& = INCREASE_BY_SCORE) = 0;
protected:
    clientType user_type;
    seq id = 0;
    std::string name, college, password;
    std::vector <Shared::Course> course;
};


class Student: public Person {
    friend std::istream &operator>>(std::istream&, Student&);
    friend std::ostream& operator<<(std::ostream&, const Student&);

public:
    Student() = default;
    virtual ~Student();

    virtual const Person &display_info(std::ostream&, const Score_mode& = INCREASE_BY_SCORE) override final;
    std::string enroll_course(Shared::Course);
    std::string cancel_course(Shared::Course);
    const Person& display_course(std::ostream&) const;
private:
    unsigned int classNum = 0;
};


class Teacher: public Person {
    friend std::istream &operator>>(std::istream&, Teacher&);
    friend std::ostream& operator<<(std::ostream&, const Teacher&);

public:
    Teacher() = default;
    virtual ~Teacher();
    virtual const Person &display_info(std::ostream&, const Score_mode& = INCREASE_BY_SCORE) override final;
    void modify_score(std::ostream&, Shared::Course, seq, Shared::score);
    void check_score(Shared::Course, std::ostream &, const Score_mode&) const;
};

#endif /* people_hpp */


