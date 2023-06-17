#include <string>
#include <filesystem>
#include <fstream>
#include "subjectStudent.cpp"

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
};

class student : public classYear,public subjectStudent{
public:
    std::string _surname;
    std::string _name;
    student(std::string surname,int studentClassYear,std::string classProfile,std::string mainTeacher,std::string name)
    : classYear(studentClassYear,classProfile,mainTeacher),_surname(surname),_name(name)
    {}
    void showStudent(){
        showMainPreorities();
        std::cout<<_surname<<" "<<_bestSubject<<std::endl;
    }
    void printMainTeacher(){
        std::cout<<_mainTeacher<<std::endl;
    }
    void addStudentFile(){
        bool flag;
        std::vector<std::string> filenames;
        std::string pathToFolder = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/"+_profile+"_"+std::to_string(_class)+"/";
        std::string studentFilePath = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/"+_profile+"_"+std::to_string(_class)+"/"+ _name + "_" + _surname + ".txt";
        for (const auto& entry : fs::directory_iterator(pathToFolder)) {
            if (entry.is_regular_file())
                filenames.push_back(entry.path().string());
        }
        for(auto& element: filenames){
            if(element == studentFilePath)
                flag = true;
        }
        if(flag == true )
            std::cout<< "This student already exist in database"<<std::endl;
        else{
            std::cout<<"Student added"<<std::endl;
            std::ofstream student(studentFilePath);
        }
    }
    void bestSubject(){
        readSubjectsName();
        int iteration=0;
        if (subjectName.empty())
            std::cout<<"Student dont have grades"<<std::endl;
        else {
            float *allAvarageSubjects = new float[subjectName.size()];
            for (auto part: subjectName) {
                insertingDateFromFileForOneSubject(part);
                allAvarageSubjects[iteration] = avarageGrade();
                clearMap();
                ++iteration;
            }
            std::string bestSubject;
            for (int i = 0; i < subjectName.size(); i++) {
                if (i == 0) {
                    bestSubject = subjectName.at(i);
                    continue;
                }
                if (allAvarageSubjects[i] > allAvarageSubjects[i - 1])
                    bestSubject = subjectName.at(i);
            }
            _bestSubject = bestSubject;
            delete[] allAvarageSubjects;
        }
    }
    void bestSubjectDisplay(){
        std::cout<<_bestSubject<<std::endl;
    }
private:
    std::string _bestSubject;
};



