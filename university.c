#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "university.h"
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
