#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const string coursenames[10] = {"Biology", "English", "History", "Sports", "Math", "Chemistry", "Computer Science", "Spanish", "Music", "Art"};
const string coursenums[4] = {"I", "II", "III", "IV"};
const string firstnames[40] = {"James", "John", "Robert", "Michael", "William", "David", "Richard", "Joseph", "Charles", "Thomas", "Christopher", "Daniel", "Matthew", "Austin", "Anthony", "Mark", "Paul", "Steven", "George", "Kenneth", "Mary", "Patricia", "Jennifer", "Elizabeth", "Linda", "Barbara", "Susan", "Margaret", "Jessica", "Sarah", "Dorothy", "Karen", "Nancy", "Betty", "Lisa", "Sandra", "Ashley", "Kimberly", "Donna", "Helen"};

const string lastnames[40] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Miller", "Davis", "Garcia", "Rodriguez", "Childress", "Martinez", "Anderson", "Taylor", "Thomas", "Hernandez", "Moore", "Martin", "Jackson", "Thompson", "White", "Lopez", "Lee", "Gonzalez", "Harris", "Clark", "Lewis", "Robinson", "Walker", "Perez", "Hall", "Young", "Allen", "Sanchez", "Wright", "King", "Scott", "Green", "Baker", "Adams", "Nelson"};
const string schoolfirst[5] = {"Austin", "Hogwarts", "Elkins", "Public High", "United School of"};
const string schoolsecond[2] = {"High School", "Consolidated"};
const int MAX_STUDENTS = 100;

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

struct school {
	string name;
	student students[100]; 
};


int random(int l, int h);
void gen_schedule(course *gschedule);
void gen_school(school &gschool);
void gen_student(student &gstudent);


int main() {
	srand(time(NULL));
	school hs;
	gen_school(hs);
	cout << '\n';
	for(int i = 0; i < MAX_STUDENTS; i++) {
		cout << '\n' << hs.students[i].name;
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
		temp = coursenames[random(0, 10)] + ' ' + coursenums[random(0, 4)]; //Nasty hack to randomize 3 times
		temp = coursenames[random(0, 10)] + ' ' + coursenums[random(0, 4)];
		temp = coursenames[random(0, 10)] + ' ' + coursenums[random(0, 4)];
		tc.name = temp;
		gschedule[i] = tc;
	}
}

void gen_school(school &gschool) {
	gschool.name = schoolfirst[random(0, 5)] + ' ' + schoolsecond[random(0, 5)];
	for(int i = 0; i < MAX_STUDENTS; i++) {
		gen_student(gschool.students[i]);
	}
}

void gen_student(student &gstudent) {
	gstudent.name = firstnames[random(0, 40)] + ' ' + lastnames[random(0, 40)];
	gstudent.pop = random(0, 100);
	gstudent.intel = random(0, 100);
	gen_schedule(gstudent.schedule);
}
