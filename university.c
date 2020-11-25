/* This include statemnt is here to show that I did break the file into 3 parts(interface2.c, university.c, university.h) originally. I have broken up the post 
so that you can run this directly from this page. */
// Type "help" for a list of commands to enter into the terminal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//
// university.h
//

#ifndef _UNIVERSITY_H_
#define _UNIVERSITY_H_

typedef struct _dept {
	char *name;
	int enrollment;
	struct _dept *next;
} Dept;

typedef struct _college {
	char *name;
	Dept *headDeptList;
	struct _college *next;
} College;

College* addCollege(College *headCollegeList, char collegeName[]);
void addDept(College *headCollegeList, char collegeName[], char deptName[], int enrollment);
int count(College *headCollegeList);
int enrollment(College *headCollegeList, char collegeName[]);
void printCollege(College *headCollegeList, char collegeName[]);
void print(College *headCollegeList);
College *addCollegeOrdered(College *headCollegeList, char collegeName[]);
void addDeptOrdered(College *headCollegeList, char collegeName[], char deptName[], int enrollment);
void removeDept(College *headCollegeList, char collegeName[], char deptName[]);
College *removeCollege(College *headCollegeList, char collegeName[]);

#endif

//
// interface.c
//

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

//
// university.c
//

College* createCollege(char name[], College* next);
Dept* createDept(char name[], int enroll, Dept* next);
int compareCollege(College *pNew, College *pExisting);

/////////////////////////////////////////////////////////////////////////////////////////////
// add a college to the list
//	   1. Make sure a college by that name does not exist
//	   2. Add a new college with that name (add-at-front)
//    Error: If the college already exists, print "Error: college \"%s\" already exists.\n" and do nothing
College* createCollege(char name[], College* next) {
    College *pNew = (College*)malloc(sizeof(College));
    pNew -> name = malloc(strlen(name) + 1);
    strcpy(pNew -> name, name);
    pNew -> next = next;
    return pNew;
}

College* addCollege(College *headCollegeList, char collegeName[]) {
	College* temp = headCollegeList;
	while (temp != NULL) {
        if (strcmp(collegeName, temp -> name) == 0) {
            printf("Error: college \"%s\" already exists.\n", collegeName);
            return headCollegeList;
        }
        temp = temp -> next;
	}
	College* head = NULL;
	if (headCollegeList == NULL) {
		return createCollege(collegeName, NULL); 
	}
	else {
		head = createCollege(collegeName, headCollegeList);
	}
	return head;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// add a dept to the specified college
//   1. Make sure a college by that name exists (so you can add a dept to it).
//   2. If the specifed dept already exists, update the dept's enrollment to the new value
//   3. Otherwise, add the dept to the end of the college's dept list (add-at-end)
//   Error: If the college does not exist, print "Error: college \"%s\" does not exist.\n" and do nothing

Dept* createDept(char name[], int enroll, Dept* next) {
    Dept* pNew = (Dept*)malloc(sizeof(Dept));
    pNew -> name = malloc(strlen(name) + 1);
    strcpy(pNew -> name, name);
	pNew -> enrollment = enroll;
    pNew -> next = next;
    return pNew;
}

void addDept(College *headCollegeList, char collegeName[], char deptName[], int enrollment) {
	bool found = false;
	College* temp = headCollegeList;
	Dept* dTemp = NULL;
	while (temp != NULL) {
        if (strcmp(collegeName, temp -> name) == 0) {
			found = true;
            break;
        }
        temp = temp -> next;
	}
	if (found == false) {
		printf("Error: college \"%s\" does not exist.\n", collegeName);
		return;
	}
	dTemp = temp -> headDeptList;
	while (dTemp != NULL) {
    	if (strcmp(deptName, dTemp -> name) == 0) {
        	dTemp -> enrollment = enrollment;
        	break;
    	}
    	dTemp = dTemp -> next;
	}
	if (dTemp == NULL) {
		Dept* nTemp = createDept(deptName, enrollment, NULL);
		if (temp -> headDeptList == NULL) { 
			temp -> headDeptList = nTemp;
		}
		else {
			Dept* fTemp = temp -> headDeptList;
			while (fTemp -> next != NULL) {
				fTemp = fTemp -> next;
			}
			fTemp  ->next = nTemp;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// return the number of colleges in the list
// Iterate through the college list to count the number of colleges, return that count

int count(College *headCollegeList) {
	College* temp = headCollegeList;
	int count = 0;
	while (temp != NULL) {
		++count;
    	temp = temp -> next;			
	}
	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// return the total number of students enrolled in a college
//	1. Make sure a college with that name exists
//	2. for each dept in the college, sum their enrollment
//	3. Print the total enrollment of the college
// 4. If the college does not exist, return -1

int enrollment(College *headCollegeList, char collegeName[]) {
	College* temp = headCollegeList;
	bool isEnroll = false;
	int enrollNum = 0;
	while (temp != NULL) {
		if (strcmp(collegeName, temp -> name) == 0) {
			isEnroll = true;
			Dept* dTemp = temp -> headDeptList;
    		while (dTemp != NULL) {
				enrollNum += dTemp -> enrollment;
				dTemp = dTemp -> next;
			}
		}
    	temp = temp -> next;
	}
	if (isEnroll == false) {
			return -1;
	}
	return enrollNum;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// print all the depts for a given college
//	1. Make sure a college with that name exists
//	2. Print the name of that college
//	3. Print all the "deptname: enrollment" pairs for that college
// Error: If the college does not exist, print "Error: college \"%s\" does not exist.\n" and do nothing

void printCollege(College *headCollegeList, char collegeName[]) {
	College* temp = headCollegeList;
	bool foundC = false;
	while (temp != NULL) {
      if (strcmp(collegeName, temp -> name) == 0) {
			foundC = true;
			printf("%s\n", collegeName);
			Dept* dTemp = temp -> headDeptList;
        	while (dTemp != NULL) {
				printf("%s: %d\n", dTemp -> name, dTemp -> enrollment);
    			dTemp = dTemp -> next;
			}
		}
      temp = temp -> next;
	}
	if (foundC == false) {
			printf("Error: college \"%s\" does not exist.\n", collegeName);
			return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// print all the colleges
// For each college
//	   a. Print the name of that college
//	   b. Print all the "deptname: enrollment" pairs for that college
// Error: If the college list is empty, print "Error: no colleges.\n" and do nothing

void print(College *headCollegeList) {
	if (headCollegeList == NULL) {
		printf("Error: no colleges.\n");
	}
	College* temp = headCollegeList;
	while (temp != NULL) {
		printf("%s\n", temp -> name);
		Dept* dTemp = temp -> headDeptList;
    	while (dTemp != NULL) {
			printf("\t%s: %d\n", dTemp -> name, dTemp -> enrollment);
			dTemp = dTemp -> next;
		}
    	temp = temp -> next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// add a college (in alphabetical order)
//	1. Make sure a college by that name does not exist
//	2. Add a college with that name (add-in-order)
// Error: if the college already exists, print "Error: college \"%s\" already exists.\n" and do nothing

int compareCollege(College *pNew, College *pExisting) {
    return strcmp(pExisting -> name, pNew -> name);
}

College *addCollegeOrdered(College *headCollegeList, char collegeName[]) {
	College* temp = headCollegeList;
	while (temp != NULL) {
        if (strcmp(collegeName, temp -> name) == 0) {
            printf("Error: college \"%s\" already exists.\n", collegeName);
            return headCollegeList;
        }
        temp = temp -> next;
	}
	College* head = headCollegeList;
	College *newNode = createCollege(collegeName, NULL);
    if (head == NULL) { // empty list
        return newNode; // return the head
    }
    else if (compareCollege(newNode, head) > 0) { // insert front
        newNode -> next = head;
        return newNode;
    }
    else { // insert back and middle
        // find location
        College *prev = head;
        College *cur = head -> next;
        while (cur != NULL) {
            if (compareCollege(newNode, cur) > 0) {
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        // assign the pointers
        newNode->next = cur;
        prev->next = newNode;
        return head;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a dept to the specified college in enrollment (desc) order.
// If enrollment is the same, order the depts with the same enrollment by alphabetically.
//	1. Make sure a college by that name exists (so you can add a dept to the college)
//	2. If the dept already exists, update the enrollment
//	3. Otherwise, add the dept to the college (add-in-order)
// Error: If the college does not exists, print "Error: college \"%s\" does not exist.\n" and do nothing
int compareDept(Dept *pNew, Dept *pExisting) {
	if (pNew -> enrollment < pExisting -> enrollment) {
        return -1;
    }
    else if (pNew -> enrollment > pExisting -> enrollment) {
        return 1;
    }
    else {
        return strcmp(pExisting -> name, pNew -> name);
	}
}

void addDeptOrdered(College *headCollegeList, char collegeName[], char deptName[], int enrollment) {
	bool found = false;
	College* temp = headCollegeList;
	Dept* dTemp = NULL;
	while (temp != NULL) {
        if (strcmp(collegeName, temp -> name) == 0) {
			found = true;
            break;
        }
        temp = temp -> next;
	}
	if (found == false) {
		printf("Error: college \"%s\" does not exist.\n", collegeName);
		return;
	}
	dTemp = temp -> headDeptList;
	while (dTemp != NULL) {
    	if (strcmp(deptName, dTemp -> name) == 0) {
        	dTemp -> enrollment = enrollment;
        	return;
    	}
    	dTemp = dTemp -> next;
	}
	Dept* head = temp -> headDeptList;
	Dept* nHead = createDept(deptName, enrollment, NULL);
	if (head == NULL) {
		temp -> headDeptList = nHead;
		return;
    }
	else if (compareDept(nHead, head) > 0) { // insert front
		nHead -> next = head;
		temp -> headDeptList = nHead;
    }
    else { // insert back and middle
        // find location
        Dept *prev = head;
        Dept *cur = head -> next;
        while (cur != NULL) {
            if (compareDept(nHead, cur) > 0) {
                break;
            }
            prev = cur;
            cur = cur -> next;
        }
        // assign the pointers
		// A:50 B:100 ends up as A:50
        nHead -> next = cur;
        prev -> next = nHead;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a dept from a college
//	1. Make sure a college with that name exists
//	2. Make sure the dept exists in that college
//	3. Remove the dept from that college
// Error: If the college does not exist, print "Error: college \"%s\" does not exist.\n" and do nothing
// Error: If the dept does not exist, print "Error: dept \"%s\" does not exist in college \"%s\".\n" and do nothing

void removeDept(College *headCollegeList, char collegeName[], char deptName[]) {
	bool foundC = false;
	bool foundD = false;
	
	College* temp = headCollegeList;
	
	Dept* dTemp = temp -> headDeptList;
	Dept* prev;
	Dept* cur;
	Dept* next;
	while (temp != NULL) {
        if (strcmp(collegeName, temp -> name) == 0) {
			foundC = true;
			dTemp = temp -> headDeptList;
            break;
        }
        temp = temp -> next;
	}
	if (foundC == false) {
		printf("Error: college \"%s\" does not exist.\n", collegeName);
		return;
	}
	prev = dTemp;
	cur = prev;
	while (cur != NULL) {
    	if (strcmp(deptName, cur -> name) == 0) {
			foundD = true;
        	break;
    	}
		prev = cur;
		cur = prev -> next;
		if(cur != NULL) {
			next = cur -> next;
		}
	}
	if (foundD == false) {
		printf("Error: dept \"%s\" does not exist in college \"%s\".\n", deptName, collegeName);
		return;
	}
	if (strcmp(prev -> name, deptName) == 0) {
		Dept* newHead = dTemp -> next;
        free(dTemp);
		temp -> headDeptList = newHead;
		return;
	}
	else if (strcmp(cur -> name, deptName) == 0) {
		prev -> next = next;
		free(cur);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a college
//	1. Make sure a college with that name exists
//	2. Remove that college and all the depts of that college
// Error: If the college does not exist, print "Error: college \"%s\" does not exist.\n" and do nothing

College *removeCollege(College *headCollegeList, char collegeName[]) {
	bool found = false;
	College* temp = headCollegeList;
	while (temp != NULL) {
        if (strcmp(collegeName, temp -> name) == 0) {
			found = true;
            break;
        }
        temp = temp -> next;
	}
	if (found == false) {
		printf("Error: college \"%s\" does not exist.\n", collegeName);
		return headCollegeList;
	}
	if (strcmp(headCollegeList -> name, collegeName) == 0) {
        College* newHead = headCollegeList -> next;
        free(headCollegeList);
        return newHead;
    }
    else {
        College* prev = headCollegeList;
        while (prev->next != NULL) {
            if (strcmp(prev-> next -> name, collegeName) == 0) {
                break;
            }
            prev = prev->next;
        }
        
        College* toBeDeleted = prev->next;
        prev->next = toBeDeleted->next;
        free(toBeDeleted);

        return headCollegeList;
    }
}
