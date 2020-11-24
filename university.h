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
