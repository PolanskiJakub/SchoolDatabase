#include "subjectTeacher.cpp"
#include <filesystem>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

struct GradeTeacher{
    int mark;
    int weight;
    std::string note;
};

namespace fs = std::filesystem;
class teacher{
public:
    std::map<int,GradeTeacher> marks;
    std::vector<std::string> classes;
    std::vector<std::string> students;
    std::string _name,_surname,_subject,_pathToClassDirectory, _pathToStudent,_pathToClass;
    teacher(std::string name,std::string _surname,std::string subject):_name(name),_surname(_surname),_subject(subject){
        _pathToClassDirectory = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/";
    }
    void showAllClasses(){
        int iteration=0;
        for(auto& className : fs::directory_iterator(_pathToClassDirectory)){
            if(className.is_directory()){
                classes.push_back(className.path().filename().string());
                int positionBegin = className.path().filename().string().find("_");
                std::string classProfileDisplay = className.path().filename().string().substr(0,positionBegin);
                std::string classYearDisplay = className.path().filename().string().substr(positionBegin+1);
                std::cout<<"Class Id: "<<iteration<<" | Class profile : "<<classProfileDisplay<<" | Class Year : "<<
                classYearDisplay<<std::endl;
            }
        }
    }
    void showStudentsInClassById(int iteration){
       std::string classPath = _pathToClassDirectory + classes.at(iteration);
       std::string studentName;
       for(auto& student: fs::directory_iterator(classPath)){
           if(student.is_regular_file()){
               studentName = student.path().filename().string();
               int positionBegin = studentName.find("_");
               std::string name = studentName.substr(0,positionBegin);
               std::string surname = studentName.substr(positionBegin+1);
               int positionEnd = surname.find(".");
               surname = surname.substr(0,positionEnd);
               std::cout<<"Name: "<<name<<" Surname: "<<surname<<std::endl;
           }
       }

    }
    int chooseClassById(int id){
        if(id > classes.size()){
            std::cout<<"This Class don't exist"<<std::endl;
            return 0;
        }
        _pathToClass = _pathToClassDirectory + classes.at(id)+"/";
        return 1;
    }
    int chooseStudent(int id){
        if(id > students.size()){
            std::cout<<"This student dont exist"<< std::endl;
            return 0;
        }
        _pathToStudent = _pathToClass + students.at(id);
        return 1;
    }
    void insertingDateFromFileForOneSubject(){
        std::fstream file;
        std::string gradeWithWeight,mark,weight,id,note,mainSubjectName;
        //studentFile="C:/Users/jakup/Documents/GitHub/SchoolDatabase/student.txt";
        file.open(_pathToStudent.c_str());
        int i=0;
        while (file >> gradeWithWeight){
            if (gradeWithWeight == "Subject"){
                file >> gradeWithWeight;
                mainSubjectName = gradeWithWeight;
                continue;
            }
            if(mainSubjectName == _subject) {
                if (i == 0) {
                    id = gradeWithWeight;
                    i++;
                    continue;
                }
                if (i == 1) {
                    mark = gradeWithWeight;
                    i++;
                    continue;
                }
                if (i == 2) {
                    weight = gradeWithWeight;
                    i++;
                    continue;
                } else {
                    note = gradeWithWeight;
                    marks[stoi(id)] = {stoi(mark), stoi(weight), note};
                    i = 0;
                }
            }
        }
        file.close();
    }
    int addGradeToSubject(std::string grade,std::string weight, std::string note){
        std::ifstream studentFile(_pathToStudent);
        std::vector<std::string> text;
        int numberOfLines=0;
        int placeToAdd=0;
        if(studentFile.is_open()){
            std::string line;
            while (std::getline(studentFile, line)){
                text.push_back(line);
                if (line == "Subject "+_subject){
                    placeToAdd=numberOfLines;
                }
                ++numberOfLines;
            }
            studentFile.close();
        }else{
            std::cout<<"Can't open file"<<std::endl;
            return 0;
        }
        if(placeToAdd == 0){
            std::cout<<"This subject don't exist"<<std::endl;
            return 0;
        }
        auto key = marks.end();
        int iteration = key->first + 1;
        placeToAdd+=iteration;
        std::cout<<placeToAdd<<std::endl;
        std::string iterationString = std::to_string(iteration);
        const std::string gradeToAdd= iterationString + " " +grade + " " + weight + " " + "note";
        text.insert(text.begin()+placeToAdd,gradeToAdd);
        std::ofstream studentFileWrite(_pathToStudent);
        if(studentFileWrite.is_open()){
            for(const std::string& line : text){
                std::cout<<line<<std::endl;
                studentFileWrite << line << std::endl;
            }
            studentFileWrite.close();
        }
        return 0;
    }
};
