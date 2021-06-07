#include "date.cpp"

int main() {
    Date date1(2021, 6, 7);
    std::cout << date1.get_month_name() << '\n';
    date1.print_date();

    Date date2;

    date2.set_year(2021);
    date2.set_month(2);
    date2.set_day(28);
    std::cout << date2.get_month_name() << '\n';
    date2.print_date();
}
