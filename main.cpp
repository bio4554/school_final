#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const string coursenames[10] = {"Biology", "English", "History", "Sports", "Math", "Chemistry", "Computer Science", "Spanish", "Music", "Art"};
const string coursenums[4] = {"I", "II", "III", "IV"};

struct school {
	string name;
	int students; 
};

struct course {
	string name;
	bool hwdone; //Homework done
	float prep; //Preparedness for next whatever(quiz, test)
	int nh, nq, nt, grade; //Next homework, quiz, test, and grade
};

struct student {
	string name;
	int pop;
	int intel;
	course schedule[7];
};


int random(int l, int h);
void gen_schedule(course *gschedule);
void gen_school(school &gschool);
void gen_student(student &gstudent);


int main() {
	srand(time(NULL));
	student bob = {"Bob", 0, 0};
	gen_schedule(bob.schedule);
	for(int i = 0; i < 7; i++) {
		cout << '\n' << bob.schedule[i].name;
	}
	cout << '\n';
	return 0;
}

int random(int l, int h) {
	int r = ((rand() % h) + l);
	return r;
}

void gen_schedule(course *gschedule) {
	course tc = {"Test", 0, 0, 0, 0, 0, 0};
	string temp;
	for(int i = 0; i < 7; i++) {
		temp = coursenames[random(0, 9)] + ' ' + coursenums[random(0, 4)];
		tc.name = temp;
		gschedule[i] = tc;
	}
}

void gen_school(school &gschool) {

}

void gen_student(student &gstudent) {

}
