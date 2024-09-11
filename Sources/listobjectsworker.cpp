#include "listobjectsworker.h"

#include <algorithm>
#include <iostream>
#include <map>

ListObjectsWorker::ListObjectsWorker() {}

void ListObjectsWorker::ReadObjects(std::istream &in)
{
    current_list_.clear();
    std::string obj;

    size_t i = 1;
    while( std::getline(in, obj) ){
        if( obj.empty() )
            continue;
        std::cout << i << '.' << obj << std::endl;
        current_list_.push_back(std::move(obj));
        ++i;
    }
}

void ListObjectsWorker::AddObject(size_t idx)
{
    temp_storage_.push_back( ParseStrToObj(current_list_[idx + 1]) );
}

void ListObjectsWorker::AddAllObjects()
{
    for( const auto& obj : current_list_ ){
        temp_storage_.push_back( ParseStrToObj(obj) );
    }
}

void ListObjectsWorker::SaveResultInFile(std::ostream &out)
{
    for( const auto& obj : temp_storage_ ){
        out << obj << std::endl;
    }
}

void ListObjectsWorker::GroupByDistance(std::ostream &out)
{
    std::sort(temp_storage_.begin(), temp_storage_.end(),
              [](const Object &lhs, const Object &rhs ){
                  return lhs.GetDistance() < rhs.GetDistance();
              });

    out << "Up to 100 units:\n";
    for( const auto& obj : temp_storage_ ){
        if( obj.GetDistance() < 100 )
            out << obj << std::endl;
    }

    out << "Up to 1000 units:\n";
    for( const auto& obj : temp_storage_ ){
        double distance = obj.GetDistance();
        if( distance > 100 && distance < 1000 )
            out << obj << std::endl;
    }

    out << "Up to 10000 units:\n";
    for( const auto& obj : temp_storage_ ){
        double distance = obj.GetDistance();
        if( distance > 1000 && distance < 10000 )
            out << obj << std::endl;
    }

    out << "Too far\n";
    for( const auto& obj : temp_storage_ ){
        double distance = obj.GetDistance();
        if( distance > 10000 )
            out << obj << std::endl;
    }
}

void ListObjectsWorker::GroupByName(std::ostream &out)
{
    std::map<char, std::vector<Object>> groupps;

    for( const auto &obj : temp_storage_ ){
        char key = obj.name[0];
        groupps[key].push_back(obj);
    }

    for( auto &[key, value] : groupps ){
        out << key << std::endl;
        std::sort(value.begin(), value.end(),
                  [](const Object &lhs, const Object &rhs ){
                      return lhs.name < rhs.name;
                  });
        for( const auto &obj : value ){
            out << obj << std::endl;
        }
        out << std::endl;
    }
}

void ListObjectsWorker::GroupByType(std::ostream &out, int min_count)
{
    std::map<std::string_view, std::vector<Object>> groupps;

    for( const auto &obj : temp_storage_ ){
        if( std::count_if(temp_storage_.begin(), temp_storage_.end(),
                          [obj](const auto &obj2){
                              return obj.type == obj2.type;
                          }) >= min_count ){
            groupps[obj.type].push_back(obj);
        }else{
            groupps["miscellaneous"].push_back(obj);
        }
    }

    for( auto &[key, value] : groupps ){
        out << key << std::endl;
        std::sort(value.begin(), value.end(),
                  [](const Object &lhs, const Object &rhs ){
                      return lhs.name < rhs.name;
                  });
        for( const auto &obj : value ){
            out << obj << std::endl;
        }
        out << std::endl;
    }
}

void ListObjectsWorker::GroupByTime(std::ostream &out)
{
    time_t now = time(NULL);

    out << "Previously created" << std::endl;
    for( const auto& obj : temp_storage_ ){
        if( obj.time - now < 0 )
            out << obj << std::endl;
    }

    out << "Created today" << std::endl;
    for( const auto& obj : temp_storage_ ){
        if( obj.time - now > 0 && (obj.time - now)/(3600*24) < 1 )
            out << obj << std::endl;
    }

    out << "Will be created later" << std::endl;
    for( const auto& obj : temp_storage_ ){
        if( (obj.time - now)/(3600*24) > 1 )
            out << obj << std::endl;
    }
}

bool ListObjectsWorker::CurrentListIsEmpty()
{
    return current_list_.empty();
}

Object ListObjectsWorker::ParseStrToObj(const std::string &str) const
{
    auto first_it = std::find(str.begin(), str.end(),  ' ');
    std::string name(str.begin(), first_it);

    auto second_it = std::find(first_it + 1, str.end(), ' ');
    std::string lat(first_it, second_it);

    auto third_it = std::find(second_it + 1, str.end(), ' ');
    std::string lng(second_it, third_it);

    auto fourth_it = std::find(third_it + 1, str.end(), ' ');
    std::string type(third_it + 1, fourth_it);

    std::string time(fourth_it, str.end());

    return {name, std::stod(lat), std::stod(lng), type, static_cast<time_t>(std::stoi(time))};
}

double Object::GetDistance() const
{
    return std::abs(first_coord - second_coord);
}

std::ostream &operator<<(std::ostream &out, const Object &obj)
{
    out << obj.name
        << ' ' << obj.first_coord
        << ' ' << obj.second_coord
        << ' ' << obj.type
        << ' ' << obj.time;
    return out;
}
