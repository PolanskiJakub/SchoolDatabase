#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
class classYear{
public:
    int _class;
    std::string _mainTeacher;
    std::string _profile;
    classYear(int studentClassYear,std::string classProfile, std::string mainTeacher){
        _class = studentClassYear;
        _profile = classProfile;
        _mainTeacher = mainTeacher;
    }
    virtual ~classYear(){};
    virtual int printClass(){
        return _class;
    }
    virtual void printMainTeacher(){
        std::cerr<<"This student don't have main Teacher"<<std::endl;
    }
    void showMainPreorities(){
        std::cout<<"Class "<<_class<<"mainTeacher "<<_mainTeacher<<std::endl;
    }
    void addClass(){
        std::string pathToFolder = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/"+_profile+"_"+std::to_string(_class);
        if(!fs::exists(pathToFolder)){
            if(fs::create_directory(pathToFolder))
                std::cout << "Directory Created succesfuly"<<std::endl;
            else
                std::cout << "Can't create directory" << std::endl;
        }   else{
            std::cout << "This directory already exist" << std::endl;
        }
    }
    void displayAllStudentsInClass
            (){
        std::string pathToFolder = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/"+_profile+"_"+std::to_string(_class)+"/";
        for(auto& student : fs::directory_iterator(pathToFolder)){
            std::string studentName;
            if(student.is_regular_file()){
                studentName=student.path().filename().string();
                int positionBegin = studentName.find("_");
                std::string name = studentName.substr(0,positionBegin);
                std::string surname = studentName.substr(positionBegin+1);
                int positionEnd = surname.find(".");
                surname = surname.substr(0,positionEnd);
                std::cout<<"Name: "<<name<<" Surname: "<<surname<<std::endl;
            }

        }
    }
};