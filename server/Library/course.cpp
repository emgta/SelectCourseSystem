#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <numeric>
#include <cmath>
#include <algorithm>

#include "course.hpp"
#include "system.hpp"
#include "../Shared/global.hpp"

using std::string;
using std::istream;
using std::pair;

istream& operator>>(istream &is, Course &c) {
    using seq = Course::seq;
    using score = Course::score;

    is >> c.id >> c.name >> c.credit >> c.remain_amount >> c.teacher;
    is.ignore();            //ignore '\n'

    string s;
    getline(is, s);
    std::stringstream record(s);
    while (!record.eof()) {
        Shared::Person x;
        score y;
        record >> x >> y;
        c.studentScore.insert(std::make_pair(x, y));
    }

    return is;
}

Require_course::~Require_course() {
    using std::endl;

    if (id != 0) {
        static std::ofstream out_file("require_course.txt");
        out_file << id << ' ' << name << ' ' << credit << ' ' << remain_amount << ' ' << teacher << endl;
        for (auto i = studentScore.begin(); i != studentScore.end(); i++)
            out_file << i->first << " " << i->second << " ";
        out_file << endl;
    }
    studentScore.clear();
}

Elective_course::~Elective_course() {
    using std::endl;

    if (id != 0) {
        static std::ofstream out_file("elective_course.txt");
        out_file << id << ' ' << name << ' ' << credit << ' ' << remain_amount << ' ' << teacher << endl;
        for (auto i = studentScore.begin(); i != studentScore.end(); i++)
            out_file << i->first << " " << i->second << " ";
        out_file << endl;
    }
    studentScore.clear();
}

bool Require_course::display(std::ostream &os, const int &x) const {
    using std::endl;
    Result_system &system = Result_system::get_instance();

    if (x == NO_REQUIRED)
        return WRONG;
    else {
        os << get_id() << ' ' << get_name() << " Required " << get_remain_amount() << ' ' << system.get_person(get_teacher())->get_name() << ' ' << get_credit();
        return RIGHT;
    }
}

bool Elective_course::display(std::ostream &os, const int &x) const {
    using std::endl;
    Result_system &system = Result_system::get_instance();

    os << get_id() << ' ' << get_name() << " Elective " << get_remain_amount() << ' ' <<system.get_person(get_teacher())->get_name() << ' ' << get_credit();
    return RIGHT;
}

inline void Require_course::throw_student(const Shared::Person &x) {
    throw std::invalid_argument("You must attend a REQUIRED course.");
}

inline void Elective_course::throw_student(const Shared::Person &x) {
    auto stu_it = studentScore.find(x);
    if (stu_it == studentScore.end())
        throw std::invalid_argument("You are not in this class.");
    studentScore.erase(stu_it);
    remain_amount++;
    std::cout << "remian_count ++" << std::endl;
}

inline void Require_course::enroll_student(const Shared::Person &x) {
    throw std::invalid_argument("You cannot choose a REQUIRED course.");
}

inline void Elective_course::enroll_student(const Shared::Person &x) {
    auto stu_it = studentScore.find(x);
    if (stu_it != studentScore.end())
        throw std::invalid_argument("You have already been in this class.");

    if (remain_amount > 0) {
        remain_amount -= 1;
        studentScore.insert(std::make_pair(x, ALL));
    } else {
        throw std::invalid_argument("You have no room for this course.");
    }
}

void Course::print_score_table(std::ostream &os, const Score_mode &mode) const {
    Result_system &system = Result_system::get_instance();
    std::vector <pair<seq, score> > myScore(studentScore.begin(), studentScore.end());

    if (mode == INCREASE_BY_SCORE)
        sort(myScore.begin(), myScore.end(), [](const pair<seq, score> &a, const pair<seq, score> &b) {
        return a.second < b.second;
    });
    else
        sort(myScore.begin(), myScore.end(), [](const pair<seq, score> &a, const pair<seq, score> &b) {
        return a.second > b.second;
    });
    for (auto u : myScore) {
        Person_ptr p = system.get_person(u.first);
        Student_ptr s = std::dynamic_pointer_cast<Student>(p);
        os << *s << u.second << std::endl;
    }
}
