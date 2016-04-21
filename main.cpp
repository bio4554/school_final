#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

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
void gen_schedule(course *gschedule[]);
void gen_school(school &gschool);
void gen_student(student &gstudent);
void gen_class(course &gclass);


int main() {
	
	return 0;
}

int random(int l, int h) {
	int r = ((rand() % h) + l);
	return r;
}

void gen_schedule(course *gschedule[]) {

}

void gen_school(school &gschool) {

}

void gen_student(student &gstudent) {

}

void gen_class(course &gclass) {

}
