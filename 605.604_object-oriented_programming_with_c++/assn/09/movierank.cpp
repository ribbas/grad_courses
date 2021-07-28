/*
 * ui.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the implementation for a simple user interface class for
 * the Mini-project 1.
 *
 */

#include "movierank.hpp"

#include <iostream>

/*
 * Destructor
 *
 */
MovieRanker::~MovieRanker() {

    // free up dynamically allocated variables
    movies_.resize(0);
}

void MovieRanker::display_movies_list() {
    int rank = 0;
    for (std::string& movie : movies_) {
        rank++;
        std::cout << rank << ' ' << movie << '\n';
    }
}

void MovieRanker::add_movie(std::string& movie) {
    movies_.push_back(movie);
}

int MovieRanker::get_size() {
    return movies_.size();
}

bool MovieRanker::is_empty() {
    return movies_.empty();
}

void MovieRanker::clear() {
    movies_.clear();
}

void MovieRanker::swap_rank(int rank, bool down) {
    auto source = find_at_rank(rank);
    if (down) {
        if (rank < get_size() - 1) {
            auto destination = find_at_rank(rank + 2);
            movies_.splice(destination, movies_, source);
        }
    } else {
        if (rank > 0) {
            auto destination = find_at_rank(rank - 1);
            movies_.splice(destination, movies_, source);
        }
    }
}

/*
 * Initializes a VendingMachine object by prefilling it with item names,
 * prices, and quantities. The item names are provided by a prefilled array of
 * strings and the prices are generated randomly.
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */

str_list::iterator MovieRanker::find_at_rank(const int rank) {
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
void MovieRanker::display_choice_menu() {
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
void MovieRanker::parse_choice(int choice) {

    switch (choice) {
        // displays the vending machine menu
        case 1: {
            if (!is_empty()) {
                display_movies_list();
            } else {
                std::cout << "No movies added yet!\n";
            }
            break;
        }

        // displays the balance in the user's wallet
        case 2: {
            clear();
            std::string movie_title;
            for (int i = 0; i < 5; i++) {
                std::cout << "Add movie title for rank " << i + 1 << ": ";
                std::cin >> movie_title;
                add_movie(movie_title);
            }
            std::cout << "Movies added to list!\n";
            break;
        }

        // prompts user for item column and row to display its price
        case 3: {
            if (!is_empty()) {
                int rank, down;
                std::cout << "Pick rank to swap from: ";
                std::cin >> rank;
                std::cout << "0 for up, 1 for down: ";
                std::cin >> down;
                swap_rank(rank - 1, down);
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
void MovieRanker::loop() {

    // main loop to prompt for user choices
    int choice = 0;
    display_choice_menu();
    while (choice != 4) {
        std::cin >> choice;
        parse_choice(choice);
    }
}
