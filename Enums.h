#pragma once

enum class SeatClass {
    ECONOMY,
    BUSINESS,
    FIRST_CLASS
};

enum class SortCriteria {
    BY_MAX_SEATS,
    BY_DURATION,
    BY_DESTINATION
};

enum class SearchCriteria {
    BY_ORIGIN,
    BY_DESTINATION,
    BY_BOTH 
};