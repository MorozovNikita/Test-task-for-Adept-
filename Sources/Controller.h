#pragma once

#include <fstream>
#include <iostream>

#include <string>

#include "listobjectsworker.h"

void PrintHeader(){
    std::cout << "Select action:\n"
                 "1 - Read a list of objects from a new file\n"
                 "2 - Add object to the list\n"
                 "3 - Add all objects to the list\n"
                 "4 - Group objects to Distance\n"
                 "5 - Group objects to Name\n"
                 "6 - Group objects to Type\n"
                 "7 - Group objects to Time\n"
                 "8 - Save results to file\n"
                 "0 - Exit"
              << std::endl;
}

void ReadListObjects(ListObjectsWorker &worker){
    std::cout << "Enter file name: ";
    std::string file_path;
    std::cin >> file_path;

    std::ifstream in(file_path);
    if(!in.is_open()){
        std::cout << "File not found." << std::endl;
        return;
    }

    worker.ReadObjects(in);
}

void AddObject(ListObjectsWorker &worker){
    size_t idx;
    std::cout << "Input index: ";
    std::cin >> idx;

    if( worker.CurrentListIsEmpty() ){
        std::cout << "Objects are missing from memory" << std::endl;
        return;
    }

    worker.AddObject(idx);
}

void AddAllObjects(ListObjectsWorker &worker){
    worker.AddAllObjects();
}

void SaveResult(ListObjectsWorker &worker){
    std::string file_path;
    std::cout << "Input file path: ";
    std::cin >> file_path;

    std::ofstream out(file_path);
    worker.SaveResultInFile(out);
    out.close();
}

void SortObjectsD(ListObjectsWorker &worker){
    std::string file_path;
    std::cout << "Input file path: ";
    std::cin >> file_path;

    std::ofstream out(file_path);
    worker.GroupByDistance(out);
    out.close();
}

void SortObjectsN(ListObjectsWorker &worker){
    std::string file_path;
    std::cout << "Input file path: ";
    std::cin >> file_path;

    std::ofstream out(file_path);
    worker.GroupByName(out);
    out.close();
}

void SortObjectsT(ListObjectsWorker &worker){
    std::string file_path;
    std::cout << "Input file path: ";
    std::cin >> file_path;
    int min;
    std::cout << "Enter the minimum quantity to form a group: ";
    std::cin >> min;

    std::ofstream out(file_path);
    worker.GroupByType(out, min);
    out.close();
}

void SortObjectsTime(ListObjectsWorker &worker){
    std::string file_path;
    std::cout << "Input file path: ";
    std::cin >> file_path;

    std::ofstream out(file_path);
    worker.GroupByTime(out);
    out.close();
}

void SelectAction(){
    ListObjectsWorker worker;

    while (1) {
        PrintHeader();
        int control;
        std::cin >> control;
        switch (control) {
        case 1:
            ReadListObjects(worker);
            break;

        case 2:
            AddObject(worker);
            break;

        case 3:
            AddAllObjects(worker);
            break;

        case 4:
            SortObjectsD(worker);
            break;

        case 5:
            SortObjectsN(worker);
            break;

        case 6:
            SortObjectsT(worker);
            break;

        case 7:
            SortObjectsTime(worker);
            break;

        case 8:
            SaveResult(worker);
            break;
        case 0: return;
        default:
            std::cout << "Indefinite action..." << std::endl;
            break;
        }
    }
}
