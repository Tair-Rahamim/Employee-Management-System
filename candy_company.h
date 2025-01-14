/**************************
 * Name: Tair Rahamim
 * Assignment: Ex_5
 **************************/


 #define MAX_WORKERS 50
#define MAX_PROJECTS 100
#define FIRST_CHOICE 1
#define SECOND_CHOICE 2
#define THIRD_CHOICE 3
#define FOURTH_CHOICE 4
#define FIFTH_CHOICE 5
#define SIXTH_CHOICE 6
#define SEVENTH_CHOICE 7
#define EXIT_CHOICE 8
#define ZERO 0
#define ONE 1
#define FALSE 0
#define TRUE 1
#define MAX_WORKERS_IN_PROJECT 4
#define MAX_USER_CHOICE 10
#define REMOVE_OPTION "remove"
#define ADD_OPTION "add"
#define EXIT_FAIL 1

typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;

struct Worker
{
    char *name;
    Project **projects;
    int projectCount;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};

void menu(void);
char *getChars(int * strLen);
void clearInputBuffer(void);
int isWorkerNameExists(Worker *workers[], int workerCount, const char *name);
int isProjectNameExists(Project *projects[], int projectCount, const char *name);
int isFeatureExists(FeatureNode *head, const char *featureName);
void joinCompany(Worker *workers[], int *workerCount);
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount);
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void addWorkerToProject(Worker *worker, Project *project);
void displayWorkers(Worker *workers[], int workerCount);
void displayProjects(Project *projects[], int projectCount);
void displayAllProjects(Project *projects[], int projectCount);
void displayAllWorkers(Worker *workers[], int workerCount);
void workOnProject(Worker *workers[], int workerCount, int *projectCount);
void addFeatureToProject(Project *project);
void removeFeatureFromProject(Project *project);
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount);
void freeProject(Project *project);
void freeFeatures(FeatureNode *head);
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount);
