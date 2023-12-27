#pragma once

#define MAX_WORKERS 100

struct Date {
    int day;
    int month;
    int year;
};

struct Worker {
    char surname[50];
    char position[50];
    struct Date contractDate;
    int contractDuration;
    float salary;
};

struct Storage {
    struct Worker workers[MAX_WORKERS];
    int count;
};


void printRecentWorkers(const struct Storage* storage);

void readWorkersFromFile(struct Storage* storage, const char* fileName);


int isLeapYear(int year);


int getDayCount(struct Date date);

