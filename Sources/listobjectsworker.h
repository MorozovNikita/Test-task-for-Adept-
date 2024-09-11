#pragma once

#include <ctime>
#include <deque>
#include <string>
#include <vector>
#include <iostream>

struct Object
{
    std::string name;
    double first_coord;
    double second_coord;
    std::string type;
    time_t time;

    double GetDistance() const;
};

std::ostream& operator<<(std::ostream &out, const Object&);

class ListObjectsWorker
{
public:

    ListObjectsWorker();

    void ReadObjects(std::istream&);
    void AddObject(size_t);
    void AddAllObjects();
    void SaveResultInFile(std::ostream&);

    void GroupByDistance(std::ostream&);
    void GroupByName(std::ostream&);
    void GroupByType(std::ostream&, int);
    void GroupByTime(std::ostream&);

    bool CurrentListIsEmpty();
private:
    std::vector<std::string> current_list_;
    std::deque<Object> temp_storage_;

    Object ParseStrToObj(const std::string&) const;
};

