#include <string>
#include "subjectStudent.cpp"

class classYear{
public:
    int _class;
    std::string _mainTeacher;
    std::string _profile;
    classYear(int classw, std::string mainTeacher){
        _class = classw;
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
};

class student : public classYear,public subjectStudent{
public:
    std::string _surname;
    student(std::string surname,int classw, std::string mainTeacher) : classYear(classw,mainTeacher),_surname(surname)
    {}
    void showStudent(){
        showMainPreorities();
        std::cout<<_surname<<" "<<_bestSubject<<std::endl;
    }
    void printMainTeacher(){
        std::cout<<_mainTeacher<<std::endl;
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



