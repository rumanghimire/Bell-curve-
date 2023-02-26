#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Student {
  string name;
  double average;
  char grade;
};

// bool compare_students(const Student &a, const Student &b) {
//   return a.average < b.average;
// }

int main() {
  // Open the input file
  ifstream input_file("ruman.txt");

  // Read the number of students from the first line of the input file
  int num_students;
  input_file >> num_students;

  // Read the students' names and grades from the input file
  vector<Student> students;
  vector<int> student_ids(num_students);
  for (int i = 0; i < num_students; i++) {
    string name;
    string fname;
    string lname;
    double grade1, grade2, grade3, grade4;
    input_file >> fname >> lname >> grade1 >> grade2 >> grade3 >> grade4;
    name = fname + " " + lname;

    double average = (grade1 + grade2 + grade3 + grade4) / 4.0;
    students.push_back({name, average});
    student_ids[i] = i;
  }

  // Sort the students by score
  // sort(students.begin(), students.end(), compare_students);
  sort(student_ids.begin(), student_ids.end(),
       [students](int id_left, int id_right) {
         return students[id_left].average < students[id_right].average;
       });

  // Calculate the grade boundaries for the bell curve
  int num_f = ceil(num_students * 0.1);
  int num_d = ceil(num_students * 0.2);
  int num_c = ceil(num_students * 0.4);
  int num_b = ceil(num_students * 0.2);

  // Determine the letter grade for each student based on their position in the
  // bell curve
  for (int i = 0; i < num_students; i++) {
    char grade;
    if (i < num_f) {
      grade = 'F';
    } else if (i < num_f + num_d) {
      grade = 'D';
    } else if (i < num_f + num_d + num_c) {
      grade = 'C';
    } else if (i < num_f + num_d + num_c + num_b) {
      grade = 'B';
    } else {
      grade = 'A';
    }
    int student_id = student_ids[i];
    students[student_id].grade = grade;
    // cout << students[student_id].name << " - " << grade << endl;
  }

  // finally, print grades
  for (int i = 0; i < num_students; i++) {
    cout << students[i].name << " - " << students[i].grade << endl;
  }

  // Close the input file
  input_file.close();

  return 0;
}
