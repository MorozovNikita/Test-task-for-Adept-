# Тестовое задание компании "Адепт"

**Список файлов**:
- /Sourses/
    - /Controller.h - Класс, использующий интерфейс ListObjectWorker
    - /listobjectsworker.h 
    - /listobjectsworker.cpp
    - /main.cpp
- /Application/
    -  /test_adept.exe - Консольное приложение 
    -  /data.txt - Файл для заполнения 
    -  /data2.txt - Файл для заполнения

**Заполнение**
    Можно добавить записи из нескольких файлов и отсортировав, сохранить в новый файл. 
    Для этого используются методы:
    - ListObjectWorker::AddAllObjects() //Добавить все объекты из файла
    - ListObjectsWorker::AddObject(size_t idx) //Добавить объект по его индексу
    - ListObjectsWorker::GroupByDistance(std::ostream &out) //Группировать по расстоянию
    - ListObjectsWorker::GroupByName(std::ostream &out) //группировать по имени
    - ListObjectsWorker::GroupByType(std::ostream &out, int min_count) //Группировать по типу
    - ListObjectsWorker::GroupByTime(std::ostream &out) //Группировать по времени создания
    
---
# Object
```C++
struct Object
{
    std::string name;
    double first_coord;
    double second_coord;
    std::string type;
    time_t time;

    double GetDistance() const;
};
```    