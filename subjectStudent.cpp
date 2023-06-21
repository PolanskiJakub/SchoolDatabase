#include <fstream>
#include <iterator>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>


//
// Created by jakup on 13.06.2023.
//
struct Grade{
    int mark;
    int weight;
    std::string note;
};
class subjectStudent{
public:
    std::vector<std::string> subjectName;
    std::map<int,Grade> marks;
    void readSubjectsName(std::string studentFilePath){
        std::fstream file;
        std::string gradeWithWeight;
        file.open(studentFilePath.c_str());
        if(file.is_open()){
            while (file >> gradeWithWeight) {
                if (gradeWithWeight == "Subject"){
                    file >> gradeWithWeight;
                    subjectName.push_back(gradeWithWeight);
                }
            }
        }else
            std::cout<<"This student dont have grades"<<std::endl;
        file.close();
    }
    void insertingDateFromFileForOneSubject(std::string subjectN,std::string studentFilePath){
        std::fstream file;
        std::string gradeWithWeight,mark,weight,id,note,mainSubjectName;
        //studentFile="C:/Users/jakup/Documents/GitHub/SchoolDatabase/student.txt";
        file.open(studentFilePath.c_str());
        int i=0;
        while (file >> gradeWithWeight){
            if (gradeWithWeight == "Subject"){
                file >> gradeWithWeight;
                mainSubjectName = gradeWithWeight;
                continue;
            }
            if(mainSubjectName == subjectN) {
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
    void clearMap(){
        marks.clear();
    }
    void showGrades(){
        if(marks.empty())
            std::cout<<"Student dont have grades";
        else{
            for (const auto& element : marks) {
                int key = element.first;
                Grade grade = element.second;
                std::cout<<"Grade Id: "<< key<<" "<< "Grade: "<<grade.mark<<std::endl;
            }
        }
    }
    void showParticularGrade(int id){
        auto key = marks.find(id);
        if(key !=marks.end())
            std::cout<<"Grade Id: "<<key->first<<" "<<"Grade: "<<key->second.mark<<" "<<"Weight: "<<key->second.weight
            << " "<<"Note: "<<key->second.note<<std::endl;
        else{
            std::cout <<"Grade with id: "<<id<<" don't exist"<<std::endl;
        }
    }
    void allSubjectsDisplay(){
        for(int i=0; i<subjectName.size();i++){
            std::cout<<subjectName[i]<<std::endl;
        }
    }
    float avarageGrade(){
            float devider = 0;
            float GradesAddition =0;
        for (auto& element : marks) {
            Grade grade = element.second;
            GradesAddition+=grade.mark*grade.weight;
            devider +=grade.weight;
        }
        return round(GradesAddition/devider*100)/100;
    }
};
