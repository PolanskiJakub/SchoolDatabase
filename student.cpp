#include "subjectStudent.cpp"
#include "classYear.cpp"
#include <filesystem>
#include <bits/stdc++.h>
#include <vector>
namespace fs = std::filesystem;

class student : public classYear,public subjectStudent{
public:

    std::string _pathToDirectory;
    std::string _studentFilePath;
    std::string _surname;
    std::string _name;
    std::string _avarageYearGradePath;
    student(std::string surname,int studentClassYear,std::string classProfile,std::string mainTeacher,std::string name)
    : classYear(studentClassYear,classProfile,mainTeacher),_surname(surname),_name(name)
    {
        _studentFilePath = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/"+_profile+"_"+std::to_string(_class)+"/"+ _name + "_" + _surname + ".txt";
        _pathToDirectory = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/"+_profile+"_"+std::to_string(_class)+"/";
        _avarageYearGradePath = "C:/Users/jakup/Documents/GitHub/SchoolDatabase/Classes/" + _profile+"_"+std::to_string(_class)+"/" + "avarageGrade.txt";
    }
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
        for (const auto& entry : fs::directory_iterator(_pathToDirectory)) {
            if (entry.is_regular_file())
                filenames.push_back(entry.path().string());
        }
        for(auto& element: filenames){
            if(element == _studentFilePath)
                flag = true;
        }
        if(flag == true )
            std::cout<< "This student already exist in database"<<std::endl;
        else{
            std::cout<<"Student added"<<std::endl;
            std::ofstream student(_studentFilePath);
        }
    }
    void bestSubject(){
        readSubjectsName(_studentFilePath);
        int iteration=0;
        if (subjectName.empty())
            std::cout<<"Student dont have grades"<<std::endl;
        else {
            float *allAvarageSubjects = new float[subjectName.size()];
            for (auto part: subjectName) {
                insertingDateFromFileForOneSubject(part,_studentFilePath);
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
    int avarageYearUpdate(){
        bool flag = false;
        int trueAvarageGradeLine=0;
        int iteration = 0;
        std::ifstream avarageGradeFile(_avarageYearGradePath);
        std::vector<std::string> allGrades;
        if(avarageGradeFile.is_open()){
            std::string line;
            while (avarageGradeFile>>line){
                allGrades.push_back(line);
                if(line == _name + "_" + _surname){
                    avarageGradeFile>>line;
                    std::cout<<std::to_string(yearAvarageGrade())<<std::endl;
                    if(std::stof(line) == yearAvarageGrade()){
                        std::cout<<"Grade is up to data"<<std::endl;
                        return 0;
                    }else
                        trueAvarageGradeLine = iteration +1;
                }else
                    flag = true;
                iteration++;
            }
            avarageGradeFile.close();
        }else{
            std::cout<<"File created"<<std::endl;
            std::ofstream avarageGradeFileCreate(_avarageYearGradePath);
            avarageGradeFileCreate<<_name<<"_"<<_surname<<std::endl;
            avarageGradeFileCreate<<yearAvarageGrade()<<std::endl;
            avarageGradeFileCreate.close();
            return 0;
        }
        if(flag == true){
            std::ofstream avarageGradeFileWrite(_avarageYearGradePath,std::ios::app);
            avarageGradeFileWrite <<_name<<"_"<<_surname<<std::endl;
            avarageGradeFileWrite<<yearAvarageGrade()<<std::endl;
            avarageGradeFileWrite.close();
            std::cout<<"Data Added"<<std::endl;
        }
        else{
            std::ofstream avarageGradeFileWrite(_avarageYearGradePath);
            for(int i=0;i<allGrades.size()+1;i++)
            {
                if(i == trueAvarageGradeLine){
                    avarageGradeFileWrite << yearAvarageGrade()<<std::endl;
                    continue;
                }
                avarageGradeFileWrite << allGrades.at(i)<<std::endl;
            }
            avarageGradeFileWrite.close();
            std::cout<<"Data updated"<<std::endl;
        }
        return 0;
    }

    float avarageGrade(){
        float devider = 0;
        float GradesAddition =0;
        for (const auto& element : marks) {
            Grade grade = element.second;
            GradesAddition+=grade.mark*grade.weight;
            devider +=grade.weight;
        }
        float avarageValue = GradesAddition/devider;
        return avarageValue;
    }
    float yearAvarageGrade(){
        float avarageSubjectGrade=0;
        readSubjectsName(_studentFilePath);
        if(subjectName.size() == 0){
            std::cout<<"This student don't attend to any subject"<<std::endl;
            return 0;
        }
        for(int i =0;i<subjectName.size();i++){
            insertingDateFromFileForOneSubject(subjectName.at(i),_studentFilePath);
            avarageSubjectGrade+=avarageGrade();
            clearMap();
        }
        return round(avarageSubjectGrade/subjectName.size()*100)/100;
    }
private:
    std::string _bestSubject;
};



