#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "university.h"

typedef
enum {
   ADD_COLLEGE,
   ADD_DEPT,
   COUNT,
   ENROLLMENT,
   PRINT_COLLEGE,
   PRINT,
   ADD_COLLEGE_ORDERED,
   ADD_DEPT_ORDERED,
   REMOVE_DEPT,
   REMOVE_COLLEGE,
   HELP,
   QUIT,
   INVALID
}
Option;

char *actions[12] = {
   "addCollege",
   "addDept",
   "count",
   "enrollment",
   "printCollege",
   "print",
   "addCollegeOrdered",
   "addDeptOrdered",
   "removeDept",
   "removeCollege",
   "help",
   "quit"
};

int getActionID(char action[])
{
	int i;
	for (i=0; i<12; i++) {
		if (strcmp(action, actions[i])==0) return i;
	}
	return i; // 12 for invalid action
}

void printHelp(void) {
   printf("\nThe valid commands:\n\n");
   printf("\taddCollege name\n");
   printf("\t*** Add a college (add-at-front)\n");
   printf("\taddDept collegename deptname enrollment\n");
   printf("\t*** Add a dept to an existing college (add-at-end)\n");
   printf("\tcount\n");
   printf("\t*** Print the number of colleges\n");
   printf("\enrollment collegename\n");
   printf("\t*** Print the total number of students enrolled in a college\n");
   printf("\tprintCollege name\n");
   printf("\t*** Print a college and its depts\n");
   printf("\tprint\n");
   printf("\t*** Print all colleges\n");
   printf("\taddCollegeOrdered name\n");
   printf("\t*** Add a college (in alphabetical order)\n");
   printf("\taddDeptOrdered collegename deptname enrollment\n");
   printf("\t*** Add a dept by enrollment (desc) then name (alphabetically) to an existing college\n");
   printf("\tremoveDept collegename deptname\n");
   printf("\t*** Remove a dept from a college\n");
   printf("\tremoveCollege collegename\n");
   printf("\t*** Remove a college\n");
   printf("\thelp\n");
   printf("\t*** Display this list\n");
   printf("\tquit\n");
   printf("\t*** Exit the program\n");
}

int main(int argc, char* argv[])
{
	char action[100];
	char collegeName[100];
	char deptName[100];
	int enroll;
	char rest[300];

	College *university = NULL;

	while (1) {
		printf("\nEnter a command: ");
      scanf("%s", action);
		int action_id = getActionID(action);
		if (action_id == QUIT) break;
		switch (action_id) {
			case ADD_COLLEGE:
				scanf("%s", collegeName);
				university = addCollege(university, collegeName);
				break;
			case ADD_DEPT:
				scanf("%s", collegeName);
				scanf("%s", deptName);
				scanf("%d", &enroll);
				addDept(university, collegeName, deptName, enroll);
				break;
			case COUNT:
				printf("\nThere are %d college(s)\n", count(university));
				break;
			case ENROLLMENT:
			   scanf("%s", collegeName);
			   enroll = enrollment(university, collegeName);
			   if (enroll == -1)
			      printf("\nError: college \"%s\" does not exist.\n", collegeName);
			   else
				   printf("\nThere are %d student(s) in %s\n", enroll, collegeName);
				break;
			case PRINT_COLLEGE:
				scanf("%s", collegeName);
				printCollege(university, collegeName);
				break;
			case PRINT:
				print(university);
				break;
			case ADD_COLLEGE_ORDERED:
				scanf("%s", collegeName);
				university = addCollegeOrdered(university, collegeName);
				break;
			case ADD_DEPT_ORDERED:
				scanf("%s", collegeName);
				scanf("%s", deptName);
				scanf("%d", &enroll);
				addDeptOrdered(university, collegeName, deptName, enroll);
				break;
			case REMOVE_DEPT:
				scanf("%s", collegeName);
				scanf("%s", deptName);
				removeDept(university, collegeName, deptName);
				break;
			case REMOVE_COLLEGE:
				scanf("%s", collegeName);
				university = removeCollege(university, collegeName);
				break;
			case HELP:
				printHelp();
				break;
			case INVALID:
            	printf("\n%s: invalid action. Type help for help.\n", action);
            	fgets(rest, 300, stdin); // skip the rest of line
				break;
		}

	}
	return 0;
}
