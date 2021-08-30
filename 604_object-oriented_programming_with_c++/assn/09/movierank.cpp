/*
 * movierank.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 9 Assignment #1
 *
 * This file contains the implementation for the MovieRank class
 *
 */

#include "movierank.hpp"

#include <iostream>

/*
 * Default destructor
 *
 */
MovieRank::~MovieRank() {

    movies_.resize(0);
}

/*
 * Loop through the movies list to display each of the elements along with their
 * ranks
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
void MovieRank::display_movies_list() {
    int rank = 0;
    for (std::string& movie : movies_) {
        rank++;
        std::cout << rank << ' ' << movie << '\n';
    }
}

/*
 * Add movie to movies list
 *
 * Params:
 *  movie <std::string&>: movie to add to list
 *
 * Returns:
 *  None
 *
 */
void MovieRank::add_movie(std::string& movie) {
    movies_.push_back(movie);
}

/*
 * Swap ranks of a movie by moving it forward or backward 1 index in the movies
 * list
 *
 * Params:
 *  rank <unsigned int>: the current rank of the movie to swap
 *  down <bool>:    flag to swap rank down or up - false for moving rank of the
 *                  movie up, and true for moving it down
 *
 * Returns:
 *  None
 *
 */
void MovieRank::move_rank(unsigned int rank, bool down) {
    // get iterator to movie at rank
    auto source = find_at_rank(rank);

    // to swap rank down
    if (down) {
        if (rank < movies_.size() - 1) {
            // move it forward 2 ranks
            auto destination = find_at_rank(rank + 2);
            movies_.splice(destination, movies_, source);
        }
    } else {
        if (rank > 0) {
            // move it backward 1 rank
            auto destination = find_at_rank(rank - 1);
            movies_.splice(destination, movies_, source);
        }
    }
}

/*
 * Find movie at given rank
 *
 * Params:
 *  rank <const unsigned int>: index at which to locate the movie
 *
 * Returns:
 *  <std::list<std::string>::iterator>: iterator to movie at rank
 *
 */
str_list::iterator MovieRank::find_at_rank(const int rank) {
    int iterations = 0;
    auto first = movies_.begin();
    while (iterations != rank) {
        iterations++;
        ++first;
    }
    return first;
}

/*
 * Prints a menu to stdout displaying user options
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
void MovieRank::display_choice_menu() {
    std::cout << std::string(40, '-') << '\n';
    std::cout << "\nPick an option from the menu below: \n\n";
    std::cout << std::string(40, '-') << "\n\n";
    std::cout << "1: Display current list of movies\n";
    std::cout << "2: Enter a new movie list\n";
    std::cout << "3: Change ranking of a movie\n";
    std::cout << "4: Exit\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << "Your choice: ";
}

/*
 * Initializes the member VendingMachine object by prefilling it with item
 * names, prices, and quantities. The item names are provided by a prefilled
 * array of strings and the prices are generated randomly.
 *
 * Params:
 *  choice <int>: user option. This function does NOT handle invalid data types
 *                 for user choice.
 *
 * Returns:
 *  None
 *
 */
void MovieRank::parse_choice(int choice) {

    switch (choice) {
        // displays the movie rank menu
        case 1: {
            if (!movies_.empty()) {
                display_movies_list();
            } else {
                std::cout << "No movies added yet!\n";
            }
            break;
        }

        // prompt user to generate a new movie list
        case 2: {
            movies_.clear();
            std::string movie_title;
            for (int i = 0; i < 5; i++) {
                std::cout << "Add movie title for rank " << i + 1 << ": ";
                std::getline(std::cin >> std::ws, movie_title);
                add_movie(movie_title);
            }
            std::cout << "Movies added to list!\n";
            break;
        }

        // prompts user to move the rank of a movie up or down
        case 3: {
            if (!movies_.empty()) {
                unsigned int rank, down;
                std::cout << "Pick rank to swap from: ";
                std::cin >> rank;
                std::cout << "0 for up, 1 for down: ";
                std::cin >> down;
                move_rank(rank - 1, down);
                std::cout << "Rank: " << rank << " moved "
                          << (down ? "down\n" : "up\n");
                display_movies_list();
            } else {
                std::cout << "No movies added yet!\n";
            }
            break;
        }

        // exit
        case 4: {
            std::cout << "Goodbye!\n";
            return;
        }

        default: {
            std::cout << "Please select a valid option\n";
            break;
        }
    }
    display_choice_menu();
}

/*
 * Loops options continuously to user for prompts
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void MovieRank::loop() {

    // main loop to prompt for user choices
    int choice = 0;
    display_choice_menu();
    while (choice != 4) {
        std::cin >> choice;
        parse_choice(choice);
    }
}
