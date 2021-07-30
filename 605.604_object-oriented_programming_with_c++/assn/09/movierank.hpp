/*
 * movierank.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 9 Assignment #1
 *
 * This file contains the declarations for the MovieRank class
 *
 */

#include <list>
#include <string>

using str_list = std::list<std::string>;

class MovieRank {
public:
    /* ------------------------ DESTRUCTORS ------------------------ */
    ~MovieRank();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void display_choice_menu();

    void parse_choice(int);

    void loop();

    void display_movies_list();

    void add_movie(std::string&);

    void move_rank(unsigned int, bool);

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    str_list movies_;

    /* ------------------------ PRIVATE METHODS ------------------------ */
    str_list::iterator find_at_rank(const int);
};
