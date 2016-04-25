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
	int prep; //Preparedness for next whatever(quiz, test)
	int nh, nq, nt, grade; //Next homework, quiz, test, and grade
	int nhw, ntw, nqw;
	int hwgrades[25];
	int qgrades[10];
	int tgrades[4];
	void calc_grade();
};

struct student {
	string name;
	int pop;
	int intel;
	int energy;
	bool asleep;
	bool player;
	course schedule[7];
	void prep_class();
	void process_block(int block);
	void study(int ncourse);
	void sleep(int ncourse);
	void dohw(int ncourse);
	void learn(int ncourse);
	void earnpop(int ncourse);
	void print_report();
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
	int day = 1;
	school highschool;
	gen_school(highschool);
	cblock = 1;
	while(day < 10) {
		cblock = 1;
	while(cblock < 17) { //Main game loop
		for(int i = 0; i < MAX_STUDENTS; i++) {
			highschool.students[i].prep_class();
		}
		for(int i = 1; i < MAX_STUDENTS; i++) {
			highschool.students[i].process_block(cblock);
		}
		for(int i = 1; i < MAX_STUDENTS; i++) {
			highschool.students[i].print_report();
		}
		
		cblock++;
		qcheck++;
	}
		day++;
	}
	return 0;
}

void course::calc_grade() {
	float qgrade, tgrade, hgrade;
	hgrade = 0;
	qgrade = 0;
	tgrade = 0;
	for(int i = 0; i < 25; i++)
		hgrade = hgrade + hwgrades[i];
	for(int i = 0; i < 10; i++)
		qgrade = qgrade + qgrades[i];
	for(int i = 0; i < 4; i++)
		tgrade = tgrade + tgrades[i];
	hgrade = (hgrade/25);
	qgrade = (qgrade/10);
	tgrade = (tgrade/4);
	grade = (hgrade + tgrade + qgrade)/3;

}

int get_input() {
	int n;
	cout << "\n\n > ";
	cin >> n;
	return n;
}

void student::print_report() {
	cout << "\nBEGIN REPORT FOR " << name << "\n";
	for(int i = 0; i < 7; i++) {
		cout << "\nCourse: " << schedule[i].name << "\n\nPrep: " << schedule[i].prep << "\nGrade: " << schedule[i].grade;
		cout << "\nNext HW: " << schedule[i].nh << "\nNext quiz: " << schedule[i].nq << "\nNext test: " << schedule[i].nt;
		cout << "\nHomework done: " << schedule[i].hwdone << "\nEnd class report";
	}
	cout << "\nEND REPORT\n";
}

void student::study(int ncourse) {
	float prep = random(1, 10);
	schedule[ncourse].prep = schedule[ncourse].prep + prep;
	if(energy > 0) {
		if(pop > 0)
			pop = pop - random(0,5);
		if(player)
			cout << "\nYou studied " << schedule[ncourse].name << " for 1 block and made " << prep << "% progress in your studies, but you lost a tiny bit of popularity.";
		energy--;
	} else {
		if(player)
			cout << "\nYou try to study, but are too tired, get some sleep!";
	}
}

void student::sleep(int ncourse) {
	if(cblock < 10 && cblock > 2) { //School
		energy++;
		pop = pop + random(1, 5);
		schedule[ncourse].prep = schedule[ncourse].prep - random(1, 5);
		if(player)
			cout << "\nYou slept through class! Since sleeping in class is cool, you gained popularity, but also lost some preparedness.";
	} else if(cblock > 9) { //After school
		asleep = true;
		energy = energy + (17-cblock);
		if(player)
			cout << "\nYou slept for " << 17-cblock << " blocks. It is now morning.";
	} else if(cblock < 3) {
		energy++;
		if(player)
			cout << "\nYou slept for 1 block, was it worth it? School is starting soon.";
	}
}

void student::dohw(int ncourse) {
	if(schedule[ncourse].nh != 0) {
		schedule[ncourse].hwdone = true;
		schedule[ncourse].prep = schedule[ncourse].prep + random(1,5);
		if(player)
			cout << "\nYou do your homework. This should help prepare you.";
	} else { 
		schedule[ncourse].prep = schedule[ncourse].prep + random(1, 5);
		if(player)
			cout << "\nYou actually don't have any homework, so you study instead.";
	}
}

void student::learn(int ncourse) {
	schedule[ncourse].prep = schedule[ncourse].prep + random(10, 20);
	pop = pop - random(1, 20);
	if(player)
		cout << "\nYou actually pay attention in class and learn something. This is not considered cool, but oh well. (Lost popularity)";
}

void student::earnpop(int ncourse) {
	pop = pop + random(1, 20);
	schedule[ncourse].prep = schedule[ncourse].prep - random(1, 10);
	if(player)
		cout << "\nYou mess around in class, very cool! (Gained popularity)";
}


void student::process_block(int block) {
	int command = random(1, 3);
	if(block > 2 && block < 10) { //School block
		switch(command) {
			case 1 :
				learn(cblock-2);
				break;
			case 2 :
				earnpop(cblock-2);
				break;
			case 3 :
				sleep(cblock-2);
				break;
		}
	} else if(block < 2) { //Morning block
		switch(command) {
			case 1 :
				study(random(1, 7));
				break;
			case 2 :
				dohw(random(1, 7));
				break;
			case 3 :
				sleep(cblock);
				break;
		}
	} else if(block > 9) { //After school block
		switch(command) {
			case 1 :
				study(random(1, 7));
				break;
			case 2 :
				dohw(random(1, 7));
				break;
			case 3 :
				sleep(cblock);
				break;
		}
	}
}

void student::prep_class() {
	for(int i = 0; i < 7; i++) {
		if(schedule[i].nh == 0) { //No homework assigned
			if(schedule[i].hwdone)
				schedule[i].hwgrades[schedule[i].nhw] = random(80, 100);
			else
				schedule[i].hwgrades[schedule[i].nhw] = random(0, 79);
			schedule[i].nh = 4;
			schedule[i].hwdone = false;
			schedule[i].nhw++;
		} else {
			schedule[i].nh = schedule[i].nh - 1;
		}
		
		if(schedule[i].nq == 0) { //No quiz
			schedule[i].qgrades[schedule[i].nqw] = random(1, 50) + (schedule[i].prep % 50);
			schedule[i].nq = 10;
			schedule[i].prep = schedule[i].prep - random(1, 100);
			schedule[i].nqw++;
		} else {
			schedule[i].nq = schedule[i].nq - 1;
		}

		if(schedule[i].nt == 0) { //No test
			schedule[i].tgrades[schedule[i].ntw] = random(1, 50) + (schedule[i].prep % 50);
			schedule[i].nt = schedule[i].nq + 25;
			schedule[i].prep = schedule[i].prep - random(50, 200);
			schedule[i].ntw++;
		} else {
			schedule[i].nt = schedule[i].nt - 1;
		}
	}
}

int random(int l, int h) {
	int r = ((rand() % h) + l);
	return r;
}

void gen_schedule(course *gschedule) {
	course tc = {"Test", 0, 0, 0, 0, 0, 0};
	tc.nq = 0;
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
	gstudent.asleep = false;
	gen_schedule(gstudent.schedule);
}
