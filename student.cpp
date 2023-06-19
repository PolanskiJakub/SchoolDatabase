#include "subjectStudent.cpp"
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
    int averageYear(){
        bool flag = false;
        std::ifstream avarageGradeFile(_avarageYearGradePath);
        std::vector<std::string> allGrades;
        if(avarageGradeFile.is_open()){
            std::string line;
            while (std::getline(avarageGradeFile, line)){
                allGrades.push_back(line);
                if(line == _name + " " + _surname){
                    //add data with avarage grade to txt file
                }
                else
                    flag = true;
            }
            avarageGradeFile.close();
        }else{
            std::cout<<"Can't open file"<<std::endl;
            return 0;
        }
        std::ofstream avarageGradeFileWrite(_avarageYearGradePath);
        if(flag == true){
            //add function to pass avarage grade
        }

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
private:
    std::string _bestSubject;
};



