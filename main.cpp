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

int cblock;

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
	int energy;
	bool player;
	course schedule[7];
	void prep_class();
	void process_block(int block);
	void study(int ncourse);
	void sleep(int ncourse);
	void dohw(int ncourse);
	void learn(int ncourse);
	void earnpop(int ncourse);
};

struct school {
	string name;
	student students[100]; 
};


int random(int l, int h);
void gen_schedule(course *gschedule);
void gen_school(school &gschool);
void gen_student(student &gstudent);
int get_input();

/*
 *	Day
 *
 * Morning: 2 blocks
 * School: 7 blocks, one for each class
 * After School: 8, rec sleep for 4
 *
 * Morning: Sleep, Do homework, study
 *
 * School: Learn, Earn pop, Sleep
 *
 * After school: Study, Do homework, Sleep
 */

int main() {
	srand(time(NULL));
	
	int qcheck = 0; //Quit check
	school highschool;
	gen_school(highschool);

	while(qcheck == 0) { //Main game loop
		cblock = 0;
		for(int i = 0; i < MAX_STUDENTS; i++) {
			highschool.students[i].prep_class();
		}
		
		
			
		get_input();
		qcheck = 1;
	}

	return 0;
}

int get_input() {
	int n;
	cout << "\n\n > ";
	cin >> n;
	return n;
}

void student::study(int ncourse) {
	float prep = random(1, 10);
	schedule[ncourse].prep = schedule[ncourse].prep + prep;
	if(pop > 0)
		pop = pop - random(0,5);
	if(player)
		cout << "\nYou studied " << schedule[ncourse].name << " for 1 block and made " << prep << "% progress in your studies, but you lost a tiny bit of popularity.";
}

void student::sleep(int ncourse) {
	
}

void student::dohw(int ncourse) {

}

void student::learn(int ncourse) {

}

void student::earnpop(int ncourse) {

}


void student::process_block(int block) {
	int command = random(1, 3);
	if(block > 2 && block < 10) { //School block
		
	} else if(block < 2) { //Morning block

	} else if(block > 9) { //After school block

	}
}

void student::prep_class() {
	for(int i = 0; i < 7; i++) {
		if(schedule[i].nh == 0) { //No homework assigned
			schedule[i].nh = random(1, 5);
			schedule[i].hwdone = false;
		} else {
			schedule[i].nh = schedule[i].nh - 1;
		}
		
		if(schedule[i].nq == 0) { //No quiz
			schedule[i].nq = random(5, 10);
		} else {
			schedule[i].nq = schedule[i].nq - 1;
		}

		if(schedule[i].nt == 0) { //No test
			schedule[i].nt = schedule[i].nq + random(2, 4);
		} else {
			schedule[i].nt = schedule[i].nt + 1;
		}
	}
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
	gstudent.energy = 100;
	gstudent.player = false;
	gen_schedule(gstudent.schedule);
}
