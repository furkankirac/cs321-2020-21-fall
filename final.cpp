// StudentID: xxxxxxxx, Name: AAA BBB CCC

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <tuple>

// printer for a tuple of 4 int dimensions. you will need this in Q4 for easily sending tuples to the console.
// this must be defined before including range lib here to make it compatible with clang.
std::ostream& operator<<(std::ostream& str, const std::tuple<int, int, int, int>& tpl)
{
    auto [v1, v2, v3, v4] = tpl;
    str << " d" << v1 << "w" << v2 << "=" << v3 << "/" << v4;
    return str;
}

#include <range/v3/all.hpp>

using std::vector;
using std::array;
using std::string;
using std::cout;
using std::endl;

namespace views = ranges::views; // instead of ranges::views::*, directly use views::*
namespace actions = ranges::actions; // instead of ranges::views::*, directly use views::*
using namespace ranges; // instead of ranges::*, directly use *

enum DayOfWeek { Mon, Tue, Wed, Thu, Fri, Sat, Sun };
auto day_names = array<string, 7>{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
auto month_days = array<int, 12>{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void print_calendar(int year, DayOfWeek first_day)
{
    // calculate how many days are there in February
    month_days[1] = 28 + (int)(year % 4 == 0); // you can use this trick to add 1 or 0 conditionally without using if statement

    cout << "Calendar Year is " << year << "." << endl;
    cout << "First day of the year is " << day_names[first_day] << "." << endl;

    cout << "Q1) (10 pts) Day boundaries of a new month are:" << endl;
    auto print = [](const auto& container) { cout << (container | views::all) << endl; };
    auto day_bounds = views::concat(views::single(0), month_days) | views::partial_sum(std::plus<>()) | to<vector<int>>;
    print(day_bounds);

    cout << "Q2) (5 pts) Total days in " << year << " is " << endl;
    auto num_days_in_year = *begin(day_bounds | views::reverse);
    cout << num_days_in_year << endl;

    cout << "Q3) (15 pts) Month of Day Sequence" << endl;
    auto all_days_view = [=] { return views::iota(1, num_days_in_year+1); };
    auto month_of_day = [&day_bounds](int day) {
        auto iter = find_if(day_bounds, [=](int bound) { return bound >= day; });
        return iter - begin(day_bounds);
    };
    auto month_of_day_seq = all_days_view() | views::transform(month_of_day) | to<vector<int>>;
    print(month_of_day_seq);

    cout << "Q4a) (10 pts) Week of Day Sequence" << endl;
    auto day_to_week = [=](int day) { return (day-1+first_day)/7+1; };
    auto week_of_day_view = all_days_view() | views::transform(day_to_week) | views::take(num_days_in_year);
    auto week_of_day_seq = week_of_day_view | to<vector<int>>;
    print(week_of_day_seq);

    cout << "Q4b) (10 pts) Month Offsets as Days" << endl;
    auto month_offset_view = all_days_view() | views::transform([&](int day) { return day_bounds[month_of_day_seq[day-1]-1]; });
    auto month_offset_seq = month_offset_view | to<vector<int>>;
    print(month_offset_seq);

    cout << "Q4c) (10 pts) Day of Month Sequence" << endl;
    auto day_of_month_view = all_days_view() | views::transform([&](int day) { return day - month_offset_seq[day-1]; });
    auto day_of_month_seq = day_of_month_view | to<vector<int>>;
    print(day_of_month_seq);

    cout << "Q4d) (15 pts) Days in Same Week and Month" << endl;
    auto same_month = [&](int day1, int day2) { return month_of_day_seq[day1-1] == month_of_day_seq[day2-1]; };
    auto same_week = [&](int day1, int day2) { return day_to_week(day1) == day_to_week(day2); };
    auto same_week_and_month = [&](int day1, int day2) { return same_week(day1, day2) && same_month(day1, day2); };
    cout << (all_days_view() | views::group_by(same_week_and_month)) << endl;

    cout << "Q4_full) (70 pts) range of (Day, Week, DayOfMonth, Month) tuples:" << endl;
    auto tuple_same_week_month = [](auto tpl1, auto tpl2) {
        return std::get<1>(tpl1) == std::get<1>(tpl2) && std::get<3>(tpl1) == std::get<3>(tpl2); // same week and month
    };
    auto rng = views::zip(all_days_view(), week_of_day_seq, day_of_month_seq, month_of_day_seq) | views::group_by(tuple_same_week_month);
    cout << rng << endl;
}

int main()
{
    print_calendar(2020, Wed); // 2020 starts with Wednesday
//    print_calendar(2021, Fri); // 2021 starts with Friday

    return 0;
}
