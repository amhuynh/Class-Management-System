/**
* @file project1.cpp
* @author Amanda Huynh
* @brief project 1 
* @date 2024-04-14
*
* @copyright Copyright (c) 2024
*
*/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student
{
private:
    int id;
    string name;
    int score;
public:
    // Constructors
    Student();
    Student(int tid, string tname, int tscore);
    // Deconstructor
    ~Student() {}
    // Setters
    void setID(int tid);
    void setName(string tname);
    void setScore(int tscore);
    // Getters
    int getID() const;
    string getName() const;
    int getScore() const;
};

// Constructors
Student::Student() {
    id = 0;
    name = "null";
    score = 0;
}
Student::Student(int tid, string tname, int tscore) {
    id = tid;
    name = tname;
    score = tscore;
}

// Setters
void Student::setID(int tid) { id = tid; }
void Student::setName(string tname) { name = tname; }
void Student::setScore(int tscore) { score = tscore; }

// Getters
int Student::getID() const { return id; }
string Student::getName() const { return name; }
int Student::getScore() const{ return score; }

struct Course
{
    string title;
    int number_of_students;
    Student* list;
};

void file(string fileName, Course& tcourse);
void menu1(Course courses[]);
void menu2(Course courses[]);
void menu3(Course courses[]);
void menu4(Course courses[]);

int main() {
    // Declare variables.
    Course courses[3];
    string file1, file2, file3;
    int selection;

    // Prompt user for file names and store in variables.
    cout << "Enter filename #1 : ";
    cin >> file1; 
    cout << "Enter filename #2 : ";
    cin >> file2; 
    cout << "Enter filename #3 : ";
    cin >> file3; 

    // Call function to read data from files and store in array.
    file(file1, courses[0]);
    file(file2, courses[1]);
    file(file3, courses[2]);

    // Output menu and complete selected menu until user selects menu 5 (exit).
    do {
        // Output menu.
        cout << "\n\n==================== Menu ====================";
        cout << "\n 1. Show all course lists (sorting)";
        cout << "\n 2. List of students who take all courses";
        cout << "\n 3. List of students who take two courses";
        cout << "\n 4. Print out top three scores for each course";
        cout << "\n 5. Exit";

        // Prompt user for menu selection and store in answer in variable.
        cout << "\n---- > Select : ";
        cin >> selection;

        // Call menu function or output exiting message based on user answer.
        if (selection == 1) {
            menu1(courses);
        } else if (selection == 2) {
            menu2(courses);
        } else if (selection == 3) {
            menu3(courses);
        } else if (selection == 4) {
            menu4(courses);
        } else if (selection == 5) {
            cout << "\n Exiting . . .";
        }
    } while (selection != 5);

    // Delete.
    for (int i = 0; i < 3; ++i) {
        delete[] courses[i].list;
    }

    return 0;
}

// This function opens the file and stores data from the file into an array.
void file(string fileName, Course& tcourse) {
    // Declare variables.
    string title;
    int numStudents;

    // Open file and check if the file has failed to open.
    ifstream infile;
    infile.open(fileName);
    if (infile.fail()) {
        cout << "Input file opening failed." << endl;
        exit(1);
    }

    // Store information from file into variables.
    infile >> title >> numStudents;
    tcourse.title = title;
    tcourse.number_of_students = numStudents;

    // Create array dynamically and store information from file.
    tcourse.list = new Student[numStudents];
    for (int i = 0; i < numStudents; i++) {
        int id, score;
        string name;
        infile >> id >> name >> score;
        tcourse.list[i].setID(id);
        tcourse.list[i].setName(name);
        tcourse.list[i].setScore(score);
    }

    // Close file.
    infile.close();
}

// This function outputs all the course lists in ascending order of id.
void menu1(Course courses[]) {
    // Use for loop to output all three course lists in ascending order of id.
    for (int i = 0; i < 3; i++) {
        // Outputs course title.
        cout << "\n==========  " << courses[i].title << "  ==========\n\n";

        // Sort students by ID number.
        for (int j = 0; j < courses[i].number_of_students - 1; j++) {
            for (int k = 0; k < courses[i].number_of_students - j - 1; k++) {
                if (courses[i].list[k].getID() > courses[i].list[k + 1].getID()) {
                    Student temp = courses[i].list[k];
                    courses[i].list[k] = courses[i].list[k + 1];
                    courses[i].list[k + 1] = temp;
                }
            }
        }

        // Print list of sorted students.
        for (int a = 0; a < courses[i].number_of_students; a++) {
            cout << setw(10) << courses[i].list[a].getID() << setw(10) << courses[i].list[a].getName() << setw(5) << courses[i].list[a].getScore() << endl;
        }
        cout << endl;
    }
}

// This function outputs the list of students who take all courses, in ascending order of id.
void menu2(Course courses[]) {
    // Declare variables and dynamic arrays.
    int count = 0;
    int** scores = new int*[courses[0].number_of_students];
    bool* enrolled = new bool[courses[0].number_of_students];

    // Loop through the first course's students.
    for (int i = 0; i < courses[0].number_of_students; i++) {
        int studentID = courses[0].list[i].getID();
        enrolled[i] = true;

        // Check if the student exists in the other courses.
        for (int j = 1; j < 3; j++) {
            bool found = false;
            for (int k = 0; k < courses[j].number_of_students; k++) {
                if (courses[j].list[k].getID() == studentID) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                enrolled[i] = false;
                break;
            }
        }
        // If the student is enrolled in all courses, increment count and store their scores.
        if (enrolled[i]) {
            count++;
            scores[i] = new int[3];
            for (int l = 0; l < 3; l++) {
                for (int m = 0; m < courses[l].number_of_students; m++) {
                    if (courses[l].list[m].getID() == studentID) {
                        scores[i][l] = courses[l].list[m].getScore();
                        break;
                    }
                }
            }
        }
    }

    // Sort enrolled students by ID.
    for (int n = 0; n < courses[0].number_of_students - 1; n++) {
        for (int o = 0; o < courses[0].number_of_students - n - 1; o++) {
            if (enrolled[o] && enrolled[o + 1] && courses[0].list[o].getID() > courses[0].list[o + 1].getID()) {
                // Swap students
                Student temp = courses[0].list[o];
                courses[0].list[o] = courses[0].list[o + 1];
                courses[0].list[o + 1] = temp;

                // Swap scores
                int* tempScores = scores[o];
                scores[o] = scores[o + 1];
                scores[o + 1] = tempScores;
            }
        }
    }

    // Output the count and list of students taking all courses.
    cout << "\n    There are " << count << " students who take all courses:" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int a = 0; a < courses[0].number_of_students; a++) {
        if (enrolled[a]) {
            cout << setw(8) << courses[0].list[a].getID() << setw(10) << courses[0].list[a].getName();
            for (int b = 0; b < 3; b++) {
                cout << setw(5) << courses[b].title << "(" << scores[a][b] << ") ";
            }
            cout << endl;
        }
    }

    // Delete.
    for (int z = 0; z < courses[0].number_of_students; z++) {
        delete[] scores[z];
    }
    delete[] scores;
    delete[] enrolled;
}

// This function outputs the list of students who take two courses, in ascending order of id.  It does not include the students who take all three courses.
void menu3(Course courses[]) {
    // Declare variables and dynamic arrays.
    int count1 = 0, count2 = 0, count3 = 0;
    int* ID1 = new int[courses[0].number_of_students], * ID2 = new int[courses[0].number_of_students], * ID3 = new int[courses[1].number_of_students];
    int** scores1 = new int*[courses[0].number_of_students], ** scores2 = new int*[courses[0].number_of_students], ** scores3 = new int*[courses[1].number_of_students];
    for (int i = 0; i < courses[0].number_of_students; ++i) {
        scores1[i] = new int[2];
    }
    for (int i = 0; i < courses[0].number_of_students; ++i) {
        scores2[i] = new int[2];
    }
    for (int i = 0; i < courses[1].number_of_students; ++i) {
        scores3[i] = new int[2];
    }
    string* name1 = new string[courses[0].number_of_students], * name2 = new string[courses[0].number_of_students], * name3 = new string[courses[1].number_of_students];

    // Determine students who take both course 1 and course 2, but not course 3, and store their information into dynamic arrays.
    for (int i = 0; i < courses[0].number_of_students; i++) {
        int studentID = courses[0].list[i].getID();
        bool enrolled_in_both = false;

        // Check if student is enrolled in both course 1 and course 2, but not course 3.
        for (int j = 0; j < courses[1].number_of_students; j++) {
            if (studentID == courses[1].list[j].getID()) {
                enrolled_in_both = true;
                // Assign score of course 2
                scores1[count1][1] = courses[1].list[j].getScore();
                break;
            }
        }
        // Check if student is enrolled in course 1 and course 2, and not in course 3
        if (enrolled_in_both) {
            for (int k = 0; k < courses[2].number_of_students; k++) {
                if (studentID == courses[2].list[k].getID()) {
                    enrolled_in_both = false;
                    break;
                }
            }
        }

        // If the student is enrolled in both course 1 and course 2, but not course 3, add the student's information to the array.
        if (enrolled_in_both) {
            scores1[count1][0] = courses[0].list[i].getScore();
            ID1[count1] = studentID;
            name1[count1] = courses[0].list[i].getName();
            count1++;
        }
    }

    // Determine students who take both course 1 and course 3, but not course 2, and store their information into dynamic arrays.
    for (int i = 0; i < courses[0].number_of_students; i++) {
        int studentID = courses[0].list[i].getID();
        bool enrolled_in_both = false;

        // Check if student is enrolled in both course 1 and course 3, but not course 2.
        for (int j = 0; j < courses[2].number_of_students; j++) {
            if (studentID == courses[2].list[j].getID()) {
                enrolled_in_both = true;
                // Assign score of course 2
                scores2[count2][1] = courses[2].list[j].getScore();
                break;
            }
        }
        // Check if student is enrolled in course 1 and course 3, and not in course 2
        if (enrolled_in_both) {
            for (int k = 0; k < courses[1].number_of_students; k++) {
                if (studentID == courses[1].list[k].getID()) {
                    enrolled_in_both = false;
                    break;
                }
            }
        }

        // If the student is enrolled in both course 1 and course 3, but not course 2, add the student's information to the array.
        if (enrolled_in_both) {
            scores2[count2][0] = courses[0].list[i].getScore();
            ID2[count2] = studentID;
            name2[count2] = courses[0].list[i].getName();
            count2++;
        }
    }

    // Determine students who take both course 2 and course 3, but not course 1, and store their information into dynamic arrays.
    for (int i = 0; i < courses[1].number_of_students; i++) {
        int studentID = courses[1].list[i].getID();
        bool enrolled_in_both = false;

        // Check if student is enrolled in both course 2 and course 3, but not course 1.
        for (int j = 0; j < courses[2].number_of_students; j++) {
            if (studentID == courses[2].list[j].getID()) {
                enrolled_in_both = true;
                // Assign score of course 3
                scores3[count3][1] = courses[2].list[j].getScore();
                break;
            }
        }
        // Check if student is enrolled in course 2 and course 3, and not in course 1
        if (enrolled_in_both) {
            for (int k = 0; k < courses[0].number_of_students; k++) {
                if (studentID == courses[0].list[k].getID()) {
                    enrolled_in_both = false;
                    break;
                }
            }
        }

        // If the student is enrolled in both course 2 and course 3, but not course 1, add the student's information to the array.
        if (enrolled_in_both) {
            scores3[count3][0] = courses[1].list[i].getScore();
            ID3[count3] = studentID;
            name3[count3] = courses[1].list[i].getName();
            count3++;
        }
    }

    // Sort arrays in ascending order of student IDs.
    for (int l = 0; l < count1 - 1; ++l) {
        for (int m = 0; m < count1 - l - 1; ++m) {
            if (ID1[m] > ID1[m + 1]) {
                // Swap IDs
                int tempID = ID1[m];
                ID1[m] = ID1[m + 1];
                ID1[m + 1] = tempID;
                // Swap names
                string tempName = name1[m];
                name1[m] = name1[m + 1];
                name1[m + 1] = tempName;
                // Swap scores
                int tempScore1 = scores1[m][0];
                int tempScore2 = scores1[m][1];
                scores1[m][0] = scores1[m + 1][0];
                scores1[m][1] = scores1[m + 1][1];
                scores1[m + 1][0] = tempScore1;
                scores1[m + 1][1] = tempScore2;
            }
        }
    }
    for (int l = 0; l < count2 - 1; ++l) {
        for (int m = 0; m < count2 - l - 1; ++m) {
            if (ID2[m] > ID2[m + 1]) {
                // Swap IDs
                int tempID = ID2[m];
                ID2[m] = ID2[m + 1];
                ID2[m + 1] = tempID;
                // Swap names
                string tempName = name2[m];
                name2[m] = name2[m + 1];
                name2[m + 1] = tempName;
                // Swap scores
                int tempScore1 = scores2[m][0];
                int tempScore2 = scores2[m][1];
                scores2[m][0] = scores2[m + 1][0];
                scores2[m][1] = scores2[m + 1][1];
                scores2[m + 1][0] = tempScore1;
                scores2[m + 1][1] = tempScore2;
            }
        }
    }
    for (int l = 0; l < count3 - 1; ++l) {
        for (int m = 0; m < count3 - l - 1; ++m) {
            if (ID3[m] > ID3[m + 1]) {
                // Swap IDs
                int tempID = ID3[m];
                ID3[m] = ID3[m + 1];
                ID3[m + 1] = tempID;
                // Swap names
                string tempName = name3[m];
                name3[m] = name3[m + 1];
                name3[m + 1] = tempName;
                // Swap scores
                int tempScore1 = scores3[m][0];
                int tempScore2 = scores3[m][1];
                scores3[m][0] = scores3[m + 1][0];
                scores3[m][1] = scores3[m + 1][1];
                scores3[m + 1][0] = tempScore1;
                scores3[m + 1][1] = tempScore2;
            }
        }
    }

    // Output students enrolled in course 1 and 2.
    cout << "\n   There are " << count1 << " students who take " << courses[0].title << " and " << courses[1].title << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < count1; ++i) {
        cout << setw(10) << ID1[i] << setw(10) << name1[i];
        cout << setw(5) << courses[0].title << "(" << scores1[i][0] << ") ";
        cout << setw(5) << courses[1].title << "(" << scores1[i][1] << ") " << endl;
    }

    // Output students enrolled in course 1 and 3.
    cout << "\n   There are " << count2 << " students who take " << courses[0].title << " and " << courses[2].title << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < count2; ++i) {
        cout << setw(10) << ID2[i] << setw(10) << name2[i];
        cout << setw(5) << courses[0].title << "(" << scores2[i][0] << ") ";
        cout << setw(5) << courses[2].title << "(" << scores2[i][1] << ") " << endl;
    }

    // Output students enrolled in course 2 and 3.
    cout << "\n   There are " << count3 << " students who take " << courses[1].title << " and " << courses[2].title << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < count3; ++i) {
        cout << setw(10) << ID3[i] << setw(10) << name3[i];
        cout << setw(5) << courses[1].title << "(" << scores3[i][0] << ") ";
        cout << setw(5) << courses[2].title << "(" << scores3[i][1] << ") " << endl;
    }

    // Delete.
    delete[] ID1;
    delete[] ID2;
    delete[] ID3;
    delete[] name1;
    delete[] name2;
    delete[] name3;
    for (int z = 0; z < courses[0].number_of_students; z++) {
        delete[] scores1[z];
    }
    delete[] scores1;
    for (int z = 0; z < courses[0].number_of_students; z++) {
        delete[] scores2[z];
    }
    delete[] scores2;
    for (int z = 0; z < courses[1].number_of_students; z++) {
        delete[] scores3[z];
    }
    delete[] scores3;
}

// This function outputs the top three scores for each course, in order of ascending id.
void menu4(Course courses[]) {
    cout << endl;

    // Loop through each course.
    for (int i = 0; i < 3; i++) {
        cout << "[ " << courses[i].title << " Top Three Scores ]" << endl;

        // Declare variables and dynamic arrays.
        int maxScore = INT_MIN, secondMaxScore = INT_MIN, thirdMaxScore = INT_MIN, maxCount = 0, secondMaxCount = 0, thirdMaxCount = 0;
        Student** maxStudents = new Student*[courses[i].number_of_students];
        Student** secondMaxStudents = new Student*[courses[i].number_of_students];
        Student** thirdMaxStudents = new Student*[courses[i].number_of_students];

        // Iterate through the students in the current course to find the top three scores.
        for (int j = 0; j < courses[i].number_of_students; j++) {
            int score = courses[i].list[j].getScore();

            // Update max score.
            if (score > maxScore) {
                maxScore = score;
            }
        }
        for (int j = 0; j < courses[i].number_of_students; j++) {
            int score = courses[i].list[j].getScore();

            // Update second max score.
            if (score > secondMaxScore && score < maxScore && score > thirdMaxScore) {
                secondMaxScore = score;
            }
        }
        for (int j = 0; j < courses[i].number_of_students; j++) {
            int score = courses[i].list[j].getScore();

            // Update third max score.
            if (score > thirdMaxScore && score < maxScore && score < secondMaxScore) {
                thirdMaxScore = score;
            }
        }

        // Populate arrays with students who achieved the max, second max, and third max scores.
        for (int k = 0; k < courses[i].number_of_students; k++) {
            if (courses[i].list[k].getScore() == maxScore) {
                maxStudents[maxCount] = &courses[i].list[k];
                maxCount++;
            } else if (courses[i].list[k].getScore() == secondMaxScore) {
                secondMaxStudents[secondMaxCount] = &courses[i].list[k];
                secondMaxCount++;
            } else if (courses[i].list[k].getScore() == thirdMaxScore) {
                thirdMaxStudents[thirdMaxCount] = &courses[i].list[k];
                thirdMaxCount++;
            }
        }

        // Sort each array in ascending order of student ID.
        for (int l = 0; l < maxCount - 1; l++) {
            for (int m = 0; m < maxCount - l - 1; ++m) {
                if (maxStudents[m]->getID() > maxStudents[m + 1]->getID()) {
                    Student* temp = maxStudents[m];
                    maxStudents[m] = maxStudents[m + 1];
                    maxStudents[m + 1] = temp;
                }
            }
        }
        for (int l = 0; l < secondMaxCount - 1; l++) {
            for (int m = 0; m < secondMaxCount - l - 1; ++m) {
                if (secondMaxStudents[m]->getID() > secondMaxStudents[m + 1]->getID()) {
                    Student* temp = secondMaxStudents[m];
                    secondMaxStudents[m] = secondMaxStudents[m + 1];
                    secondMaxStudents[m + 1] = temp;
                }
            }
        }
        for (int l = 0; l < thirdMaxCount - 1; l++) {
            for (int m = 0; m < thirdMaxCount - l - 1; ++m) {
                if (thirdMaxStudents[m]->getID() > thirdMaxStudents[m + 1]->getID()) {
                    Student* temp = thirdMaxStudents[m];
                    thirdMaxStudents[m] = thirdMaxStudents[m + 1];
                    thirdMaxStudents[m + 1] = temp;
                }
            }
        }

        // Output the top three scores and corresponding students and their information.
        cout << "1. " << maxScore << endl;
        for (int z = 0; z < maxCount; z++) {
            cout << setw(9) << maxStudents[z]->getID() << setw(10) << maxStudents[z]->getName() << endl;
        }
        cout << "2. " << secondMaxScore << endl;
        for (int z = 0; z < secondMaxCount; z++) {
            cout << setw(9) << secondMaxStudents[z]->getID() << setw(10) << secondMaxStudents[z]->getName() << endl;
        }
        cout << "3. " << thirdMaxScore << endl;
        for (int z = 0; z < thirdMaxCount; z++) {
            cout << setw(9) << thirdMaxStudents[z]->getID() << setw(10) << thirdMaxStudents[z]->getName() << endl;
        }

        cout << endl;

        // Delete.
        delete[] maxStudents;
        delete[] secondMaxStudents;
        delete[] thirdMaxStudents;
    }
}