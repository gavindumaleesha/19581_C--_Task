#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string stream;
    std::string className;
    std::string studentID;
    int marks[3]; // Assuming 3 subjects for each student
    int totalMarks;

    bool operator<(const Student& other) const {
        return totalMarks > other.totalMarks; // Sort in descending order
    }
};

void readStudentData(std::vector<Student>& students, const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    while (!file.eof()) {
        Student student;
        file >> student.stream >> student.className >> student.studentID;
        for (int i = 0; i < 3; ++i) {
            file >> student.marks[i];
            student.totalMarks += student.marks[i];
        }
        students.push_back(student);
    }

    file.close();
}

void calculateRanks(std::vector<Student>& students) {
    std::sort(students.begin(), students.end());

    int schoolRank = 1;
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].totalMarks = i == 0 ? students[i].totalMarks : students[i - 1].totalMarks;
        students[i].totalMarks = i == 0 || students[i].totalMarks != students[i - 1].totalMarks ? i + 1 : students[i - 1].totalMarks;
    }
}

void printRanks(const std::vector<Student>& students) {
    for (const auto& student : students) {
        std::cout << "Student ID: " << student.studentID
                  << ", Total Marks: " << student.totalMarks
                  << ", School Rank: " << student.totalMarks << std::endl;
    }
}

void writeRanksToFile(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& student : students) {
        file << "Student ID: " << student.studentID
             << ", Total Marks: " << student.totalMarks
             << ", School Rank: " << student.totalMarks << std::endl;
    }

    file.close();
}

int main() {
    std::vector<Student> students;
    readStudentData(students, "student_data.txt");

    calculateRanks(students);

    std::cout << "School Ranks:" << std::endl;
    printRanks(students);

    writeRanksToFile(students, "rank_output.txt");

    return 0;
}
