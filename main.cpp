#include "student.cpp"
#include "teacher.cpp"

int main(){
    classYear first(2,"dwanascie","adfs");
    student second("Prolanski",5,"Sport","asddas","Kamil");
//    student second("Kania",5,"Sport","asddas","Albert");
//    student second("Marzec",5,"Sport","asddas","Piotr");
//    student second("Kowalski",5,"Sport","asddas","Adam");
    subjectStudent mark;
    teacher jakub("Jakub","Nowak","Polish");
//    mark.readSubjectsName();

//    mark.showGrades();
    //    mark.showParticularGrade(1);
//    mark.addGradeToSubject("1","2","bsd","Polish"); // same as insertingDate
    //    mark.allSubjectsDisplay();
    //    mark.addSubject("Polish");
//    second.addClass();
//    second.bestSubject();
//    second.bestSubjectDisplay();
//    second.addStudentFile();
//    second.displayAllStudentsInClass();
    jakub.showAllClasses();
    jakub.showStudentsInClassById(0);
    second.avarageYearUpdate();
}
