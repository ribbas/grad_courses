/*
 * ui.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the function declarations for a simple user interface
 * class for the Mini-project 1.
 *
 */

#include <list>
#include <string>

using str_list = std::list<std::string>;

class MovieRanker {
public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    MovieRanker();

    /* ------------------------ DESTRUCTORS ------------------------ */
    ~MovieRanker();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void display_choice_menu();

    void parse_choice(int);

    void loop();

    void display_movies_list();

    void add_movie(std::string&);

    int get_size();

    bool is_empty();

    void clear();

    void swap_rank(int, bool);

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    str_list movies_;

    str_list::iterator find_at_rank(const int);
};
