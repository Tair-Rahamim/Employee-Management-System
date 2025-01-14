/**************************
 * Name: Tair Rahamim
 * Assignment: Ex_5
 **************************/


#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    int userChoice = 0;
    Worker *workers[MAX_WORKERS] = {0};
    Project *projects[MAX_PROJECTS] = {0};
    int workerCount = 0;
    int projectCount = 0;
    while (userChoice != EXIT_CHOICE)
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &userChoice);
        clearInputBuffer();
        switch (userChoice)
        {
            case FIRST_CHOICE:
                joinCompany(workers, &workerCount);
                break;
            case SECOND_CHOICE:
                openNewProject(workers, workerCount, projects, &projectCount);
                break;
            case THIRD_CHOICE:
                workerJoinsProject(workers, workerCount, projects, projectCount);
                break;
            case FOURTH_CHOICE:
                displayAllProjects(projects, projectCount);
                break;
            case FIFTH_CHOICE:
                displayAllWorkers(workers, workerCount);
                break;
            case SIXTH_CHOICE:
                workOnProject(workers, workerCount, &projectCount);
                break;
            case SEVENTH_CHOICE:
                leaveCompany(workers, &workerCount, projects, &projectCount);
                break;
            case EXIT_CHOICE:
                printf("Exiting...");
                freeAllAllocations(workers, workerCount, projects, projectCount);
                break;
            default:
                //Invalid option input
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}


/*
 * The function checks whether the name of feature already exists in the project:
 * If the feature already exists, the function returns 1 (TRUE)
 * and if not, then the function returns 0 (FALSE)
 */
int isFeatureExists(FeatureNode *head, const char *featureName)
{
    //There are no features for the project
    if (head == NULL)
    {
        return FALSE;
    }
    //Going over all the features in the list, and comparing the names of the features
    FeatureNode *current = head;
    while (current != NULL)
    {
        //The names of the features are equal
        if (strcmp(current->feature, featureName) == ZERO)
        {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

/*
 * The function free the memory of all the features of a project:
 * The features are arranged in a linked list,
 * so always keep the pointer to the next feature
 * and free the current feature you are standing on
 */
void freeFeatures(FeatureNode *head)
{
    //Setting a temporary pointer to iterate through the linked list
    FeatureNode *current = head;
    while (current != NULL)
    {
        // Set the current node in a temporary pointer
        FeatureNode *temp = current;
        // Move to the next node in the linked list
        current = current->next;

        // Free the memory allocated for the current feature
        free(temp->feature);
        free(temp);
    }
}


/*
 * The function performs a project memory release:
 * Free the memory of the features that exist in the project
 * Free the memory allocated for the project name
 * Free the pointer to the array of workers working on the project
 * and Free the pointer to the project
 */
void freeProject(Project *project)
{
    freeFeatures(project->features);
    free(project->name);
    free(project->workers);
    free(project);
}

/*
 * The function is responsible for freeing all dynamically allocated memory throughout the program
 */
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount)
{
    //Free the memory of all the projects opened in the program
    for (int i = 0; i < projectCount; i++)
    {
        freeProject(projects[i]);
    }

    //Free the memory of all workers created in the program
    for (int i = 0; i < workerCount; i++)
    {
        //free the worker name and the pointer of worker's projects list
        free(workers[i]->name);
        if (workers[i]->projects != NULL)
            free(workers[i]->projects);
        free(workers[i]);
    }
}
/*
 * The function deletes an employee from the company:
 * First, the function deletes the worker from all the projects in which he is:
 *      1. If the worker is the only one in the project - the function also deletes the project from the company
 *      2. If there are more workers in the project - the function will delete the specific worker,
 *          and move all the workers after him in the list, one index back
 * Second, the function deletes the worker from the list of all workers in the company
 * and moves all the workers after him in the list, one index back
 */
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount)
{
    //There are no workers in the company
    if (*workerCount == ZERO)
    {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    int workerNumToRemove;
    printf("Select a worker to leave the company:\n");
    displayWorkers(workers, (*workerCount));
    printf("Enter the worker's number: ");
    scanf("%d", &workerNumToRemove);
    clearInputBuffer();
    //The worker number out of range
    if (workerNumToRemove < ONE || workerNumToRemove > *workerCount)
    {
        printf("Invalid worker selection.\n");
        return;
    }

    int workerIndex = workerNumToRemove - ONE; //Because the first index is zero

    //Deleting the worker from all the projects he worked on
    for (int i = 0; i < workers[workerIndex]->projectCount; i++)
    {
        Project *project = workers[workerIndex]->projects[i];
        // Removing the worker from the project's workers list
        for (int j = 0; j < project->workerCount; j++)
        {
            //Finding the worker in the list of workers
            if (project->workers[j] == workers[workerIndex])
            {
                //If there is only one worker in the project, then we will delete the entire project from the list of projects in the company
                if (project->workerCount == ONE)
                {
                    for (int k = 0; k < *projectCount; k++)
                    {
                        if (projects[k] == project)
                        {
                            //free the project details memory
                            freeFeatures(project->features);
                            free(project->name);
                            free(project->workers);
                            free(project);
                            //Move all projects one step back in the projects list
                            for (int z = k; z < *projectCount - ONE; z++)
                            {
                                projects[z] = projects[z + ONE];
                            }
                            //We deleted a project, therefore we will subtract 1 from the number of projects
                            (*projectCount)--;
                            break;
                        }
                    }
                }
                /*If there is more than one worker in the project,
                 * then we will delete only the specific worker from
                 * the list of workers in the project*/
                else
                {
                    for (int k = j; k < project->workerCount - ONE; k++)
                    {
                        project->workers[k] = project->workers[k + ONE];
                    }
                    //We deleted a worker, therefore we will subtract 1 from the number of workers in the project
                    project->workerCount--;
                }
                break;
            }
        }
    }

    // Deleting the worker from the array of all workers in the company,
    // free his name and the pointer to the list of projects in which he worked
    free(workers[workerIndex]->name);
    if (workers[workerIndex]->projects != NULL)
        free(workers[workerIndex]->projects);
    free(workers[workerIndex]);

    //Move all workers one step back in the workers list
    for (int i = workerIndex; i < *workerCount - ONE; i++)
    {
        workers[i] = workers[i + ONE];
    }
    //We deleted a worker, therefore we will subtract 1 from the number of workers
    (*workerCount)--;
}


/*
 * The function deletes feature from the linked list:
 * There are 2 situations:
 * 1. Deleting the first feature
 * 2. Deleting the feature from the middle of the list
 */
void removeFeatureFromProject(Project *project)
{
    int featureNum;
    //There are no features for the project
    if (project->features == NULL)
    {
        printf("There are no features to remove.\n");
        return;
    }

    printf("Select a feature to remove:\n");

    //Printing the features in the project
    int featuresCounter = 0;
    FeatureNode *current = project->features;
    while (current != NULL)
    {
        printf("%d. %s\n", featuresCounter + ONE, current->feature);
        current = current->next;
        featuresCounter++;
    }
    printf("Enter your choice: ");
    scanf("%d", &featureNum);
    clearInputBuffer();

    //The feature number is out of range
    if (featureNum < ONE || featureNum > featuresCounter)
    {
        printf("Invalid selection.\n");
        return;
    }

    // remove the first node in the linked list
    if (featureNum == ONE)
    {
        FeatureNode *temp = project->features; //save the first feature in temp
        project->features = project->features->next; //move to the next feature in the list
        free(temp->feature); //free the feature name
        free(temp); //free the first feature
    }
    //Deleting a feature from the middle of the linked list
    else
    {
        FeatureNode *currentNode = project->features;
        FeatureNode *prev = NULL;
        int count = 1;

        // Search the feature that needs to be deleted in the linked list
        while (currentNode != NULL && count < featureNum)
        {
            prev = currentNode; //Saving the link that needs to be deleted in prev
            currentNode = currentNode->next; //move to the next feature in the list
            count++;
        }

        //free the memory feature
        prev->next = currentNode->next;
        free(currentNode->feature);
        free(currentNode);
    }
}

/*
* The function adds feature to the linked list:
* There are 2 modes:
* 1. Added feature for the first time, so it is the first in the list
* 2. There are already features in the list, so we will add the new feature to the end of the list
*/
void addFeatureToProject(Project *project)
{
    int featureNameLen = 0;
    printf("Enter the new feature: ");
    char *featureName = getChars(&featureNameLen);
    //check if the feature name already exists in the features list
    if (isFeatureExists(project->features, featureName))
    {
        printf("This feature already exists in the project.\n");
        free(featureName);
        return;
    }

    //create new FeatureNode and initializing it with its name
    FeatureNode *newFeature = (FeatureNode *) malloc(sizeof(FeatureNode));
    if (newFeature == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAIL);
    }
    newFeature->feature = featureName;
    newFeature->next = NULL;

    //There are no features in the list, meaning the new feature is the first in the list
    if (project->features == NULL)
    {
        project->features = newFeature;
    }
        //There are features in the list, which means we will add the new feature to the end of the list
    else
    {
        FeatureNode *current = project->features;
        // Finding the last feature in the list
        while (current->next != NULL)
        {
            current = current->next;
        }
        // Add the new feature to the end of the list
        current->next = newFeature;
    }
}


/*
 * First the function checks if the employee has projects.
 * The employee chooses a project he wants to work on.
 * The function receives from him what action he wants to perform,
 * add/remove a feature in the project and sends it to the appropriate function
 */
void workOnProject(Worker *workers[], int workerCount, int *projectCount)
{
    int workerNum;
    int projectNum;
    char userChoice[MAX_USER_CHOICE] = {0};

    //There are no workers in the company
    if (workerCount == ZERO)
    {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
        //There are no projects in the company
    else if ((*projectCount) == ZERO)
    {
        printf("There are no projects in the company yet, please create a project first.\n");
        return;
    }

    printf("Select a worker:\n");
    displayWorkers(workers, workerCount);
    printf("Enter the worker's number: ");
    scanf("%d", &workerNum);
    clearInputBuffer();
    //The worker number out of range
    if (workerNum > workerCount || workerNum < ONE)
    {
        printf("Invalid worker selection.\n");
        return;
    }
    //The worker has no projects
    else if (workers[workerNum - ONE]->projectCount == ZERO)
    {
        printf("This worker is not involved in any projects.\n");
        return;
    }
    //Printing the worker's projects
    printf("Select a project:\n");
    for (int i = 0; i < workers[workerNum - ONE]->projectCount; i++)
        printf("%d. %s\n", i + ONE, workers[workerNum - ONE]->projects[i]->name);

    printf("Enter the project number: ");
    scanf("%d", &projectNum);
    clearInputBuffer();
    //The project number out of range
    if (projectNum < ONE || projectNum > workers[workerNum - ONE]->projectCount)
    {
        printf("Invalid project selection.\n");
        return;
    }
    printf("Do you want to add or remove a feature? (add/remove): ");
    scanf(" %s", userChoice);
    clearInputBuffer();
    //remove feature
    if (strcmp(userChoice, REMOVE_OPTION) == ZERO)
    {
        removeFeatureFromProject(workers[workerNum - ONE]->projects[projectNum - ONE]);
    }
    //add feature
    else if (strcmp(userChoice, ADD_OPTION) == ZERO)
    {
        addFeatureToProject(workers[workerNum - ONE]->projects[projectNum - ONE]);
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

/*
 * The function is responsible for receiving a string from the user and allocating the memory dynamically
 * The function returns a pointer to the address where the string entered by the user is stored
 */
char *getChars(int *strLen)
{
    char *name = (char *) malloc(sizeof(char));
    char c;
    // Accepting characters from the user up to the character \n, \r
    while (scanf("%c", &c) == ONE && c != '\n' && c != '\r')
    {
        // Increasing the memory of the name by 1 every time you get a new character
        name = realloc(name, (*strLen + ONE) * sizeof(char));
        if (name == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAIL);
        }

        // Added the character to the name
        name[*strLen] = c;
        // Update the length of the name
        (*strLen)++;
    }
    // adding a NULL byte to the end of the string
    name = realloc(name, (*strLen + ONE) * sizeof(char));
    name[*strLen] = '\0';
    return name;
}

/*
 * The function is responsible for clearing the buffer of the program
 * scanf with "%*[^\n]" to pick up all characters up to the newline character
 * scanf with "%*c" to catch the newline character
 */
void clearInputBuffer(void)
{
    scanf("%*[^\n]");
    scanf("%*c");
}

/*
 * The function prints the details of each worker (if workers exist):
 * Employee's name
 * The list of projects the worker is working on (if projects exist)
 */
void displayAllWorkers(Worker *workers[], int workerCount)
{
    //There are no workers in the company
    if (workerCount == ZERO)
    {
        printf("There are no workers to display.\n");
        return;
    }

    for (int i = 0; i < workerCount; i++)
    {
        printf("Worker: %s\n", workers[i]->name);
        //The worker does not work on any project
        if (workers[i]->projectCount == ZERO)
        {
            printf("  Not involved in any projects.\n");
        }
        else
        {
            //Printing all the projects the worker is working on
            printf("  Projects this worker is involved in:\n");
            for (int j = 0; j < workers[i]->projectCount; j++)
            {
                printf("    - %s\n", workers[i]->projects[j]->name);
            }
            printf("\n");
        }
    }
}


/*
 * The function prints the details of each project (if projects exist):
 * the project's name
 * The list of workers working on the project
 * The list of features that exist in the project (if any)
 */
void displayAllProjects(Project *projects[], int projectCount)
{
    //There are no projects in the company
    if (projectCount == ZERO)
    {
        printf("There are no projects to display.\n");
        return;
    }
    //print all the projects at work, and the workers who work on it
    for (int i = 0; i < projectCount; i++)
    {
        printf("Project: %s\n", projects[i]->name);

        //Printing the names of the workers in the project
        printf("  Workers in this project:\n");
        for (int j = 0; j < projects[i]->workerCount; j++)
        {
            printf("  - %s\n", projects[i]->workers[j]->name);
        }

        //Printing the names of the features in the project
        printf("  Features of the project:\n");
        if (projects[i]->features == NULL)
            printf("    No features\n");
        else
        {
            //Going through the list of features (linked list) and printing their names
            FeatureNode *current = projects[i]->features;
            while (current != NULL)
            {
                printf("    - %s\n", current->feature);
                current = current->next;
            }
        }
        printf("\n");
    }
}


/*
 * The function adds a worker to the project:
 * 1. First, she adds the employee to the list of workers working on the project
 * (there are a maximum of 4 workers in each project)
 * 2. Second, she adds the project to the list of the worker's projects
 * (the list contains all the projects the worker is on)
 */
void addWorkerToProject(Worker *worker, Project *project)
{
    //check if the worker already exists in the project
    for (int i = 0; i < project->workerCount; i++)
    {
        if (project->workers[i] == worker)
        {
            printf("This worker is already part of the project %s.\n", project->name);
            return;
        }
    }

    //check if there are 4 workers in the project
    if (project->workerCount == MAX_WORKERS_IN_PROJECT)
    {
        printf("Project is full.\n");
        return;
    }
    //Adding the worker to the list of workers belonging to the project
    //Increasing the number of workers in the project by 1
    project->workers[project->workerCount] = worker;
    project->workerCount++;

    //The worker's first project
    if (worker->projectCount == ZERO)
    {
        //Allocation of memory to first worker project
        worker->projects = (Project **) malloc(ONE * sizeof(Project *));
        if (worker->projects == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAIL);
        }
    }
    else
    {
        //Allocation of memory to additional worker project
        worker->projects = (Project **) realloc(worker->projects,
                                                (worker->projectCount + ONE) * sizeof(Project *));
        if (worker->projects == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAIL);
        }
    }
    //add the project to worker's projects list
    worker->projects[worker->projectCount++] = project;
}

/*
 * The function receives the worker and project details from the user
 * (checks the correctness of the input)
 * and calls the function to add the selected worker to the selected project
 */
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount)
{
    //There are no workers in the company
    if (workerCount == ZERO)
    {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
        //There are no projects in the company
    else if (projectCount == ZERO)
    {
        printf("There are no projects in the company yet, please create one first.\n");
        return;
    }
    int workerNum;
    int projectNum;
    printf("Select a worker to join a project:\n");
    displayWorkers(workers, workerCount);
    printf("Enter the worker's number: ");
    scanf("%d", &workerNum);
    clearInputBuffer();

    //The worker number out of range
    if (workerNum > workerCount || workerNum < ONE)
    {
        printf("Invalid worker selection.\n");
        return;
    }

    printf("Select a project to join:\n");
    displayProjects(projects, projectCount);
    printf("Enter the project's number: ");
    scanf("%d", &projectNum);
    clearInputBuffer();

    //The project number out of range
    if (projectNum > projectCount || projectNum < ONE)
    {
        printf("Invalid project selection.");
        return;
    }
    //A call to a function that will add the selected worker to the selected project
    addWorkerToProject(workers[workerNum - ONE], projects[projectNum - ONE]);
}
/*
 * The function opens a new project in the company:
 * 1. First she links the project to the worker who open the project
 * 2. Second, the function adds the new project to the list of all the projects in the company
 */
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount)
{
    if(*projectCount ==MAX_PROJECTS)
    {
        printf("Maximum number of projects reached.\n");
        return;
    }
    //There are no workers in the company
    if (workerCount == ZERO)
    {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    int userChoice = 0;
    printf("Who are you? Choose a number:\n");
    displayWorkers(workers, workerCount);
    printf("Enter your choice: ");
    scanf("%d", &userChoice);
    clearInputBuffer();

    //The worker number out of range
    if (userChoice > workerCount || userChoice < ONE)
    {
        printf("Invalid selection.\n");
        return;
    }

    printf("Enter the name of the new project: ");
    Project *newProject = (Project *) malloc(sizeof(Project));
    if (newProject == NULL)
        exit(EXIT_FAIL);

    //Initialize the values of the new project
    newProject->name = NULL;
    int projectNameLen = 0;

    //Receiving a project name from the user
    newProject->name = getChars(&projectNameLen);
    if (projectNameLen > ZERO)
    {
        if (isProjectNameExists(projects, (*projectCount), newProject->name) == TRUE)
        {
            printf("A project with this name already exists.\nBetter be more creative\n");
            free(newProject->name);
            free(newProject);
            return;
        }
        else
        {
            newProject->features = NULL;
            newProject->workers = (Worker **) malloc(MAX_WORKERS_IN_PROJECT * sizeof(Worker *));
            if (newProject->workers == NULL)
            {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAIL);
            }
            //The first project of the worker therefore we will create an array of pointers to the projects of the worker
            if (workers[userChoice - ONE]->projectCount == ZERO)
            {
                workers[userChoice - ONE]->projects = (Project **) malloc(ONE * sizeof(Project *));
                if (workers[userChoice - ONE]->projects == NULL)
                {
                    printf("Memory allocation failed.\n");
                    exit(EXIT_FAIL);
                }
            }
            //The employee already has projects, so we will add the new project at the end of array
            else
            {
                workers[userChoice - ONE]->projects = (Project **) realloc(
                        workers[userChoice - ONE]->projects,
                        (workers[userChoice - ONE]->projectCount + ONE) * sizeof(Project *));
                if (workers[userChoice - ONE]->projects == NULL)
                {
                    printf("Memory allocation failed.\n");
                    exit(EXIT_FAIL);
                }
            }
            //Adding the project to the worker's projects list and updating the number of projects of the worker
            workers[userChoice - ONE]->projects[workers[userChoice - ONE]->projectCount++] = newProject;
            //Adding a project to the list of projects that exist in the company and updating the number of projects in the company
            projects[(*projectCount)++] = newProject;

            //Updating the number of workers in the new project
            newProject->workerCount = ONE;
            //Updating the first worker in the new project
            newProject->workers[ZERO] = workers[userChoice - ONE];
        }
    }
    //empty name
    else
    {
        printf("Invalid name\n");
        return;
    }
}

/*
 * The function receives a list of projects, and the name of a new project.
 * The function will check if the name of the new project already exists in the list of projects.
 * If it already exists, the function will return 1(TRUE)
 * If it does not exist, the function will return 0 (FALSE)
 */
int isProjectNameExists(Project *projects[], int projectCount, const char *name)
{
    for (int i = 0; i < projectCount; i++)
    {
        //The names are equal
        if (strcmp(projects[i]->name, name) == ZERO)
            return TRUE;
    }
    return FALSE;
}


/*
 * The function receives a list of workers, and the name of a new worker.
 * The function will check if the name of the new worker already exists in the list of workers.
 * If it already exists, the function will return 1(TRUE)
 * If it does not exist, the function will return 0 (FALSE)
 */
int isWorkerNameExists(Worker *workers[], int workerCount, const char *name)
{
    for (int i = 0; i < workerCount; i++)
    {
        //The names are equal
        if (strcmp(workers[i]->name, name) == ZERO)
            return TRUE;
    }
    return FALSE;
}


/*
 * The function receives a list of workers in the company and prints their names
 */
void displayWorkers(Worker *workers[], int workerCount)
{
    for (int i = 0; i < workerCount; i++)
    {
        printf("%d. %s\n", i + ONE, workers[i]->name);
    }
}

/*
 * The function receives a list of projects in the company and prints their names,
 * and the number of workers in the project
 */
void displayProjects(Project *projects[], int projectCount)
{
    for (int i = 0; i < projectCount; i++)
    {
        printf("%d. %s (Workers: %d)\n", i + ONE, projects[i]->name, projects[i]->workerCount);
    }
}

/*
 * The function collect a name of worker, if the name is empty it prints an error message.
 * If the name is correct, the function checks if such a name already exists in the company
 * If it already exists - prints a message that it is not possible to join the company
 * If it does not exist - it creates a new worker and adds it to the list of workers
 */
void joinCompany(Worker *workers[], int *workerCount)
{
    if(*workerCount == MAX_WORKERS)
    {
        printf("The company is at full capacity.\n");
        return;
    }
    printf("Enter the name of the new worker: ");
    Worker *newWorker = (Worker *) malloc((sizeof(Worker)));
    if (newWorker == NULL)
        exit(EXIT_FAIL);

    //Initialize the values of the new worker
    newWorker->name = NULL;
    newWorker->projectCount = 0;
    newWorker->projects = NULL;
    int nameLen = 0;

    //Receiving a name from the user
    newWorker->name = getChars(&nameLen);

    if (nameLen > ZERO)
    {
        if (isWorkerNameExists(workers, (*workerCount), newWorker->name) == TRUE)
        {
            printf("A worker with this name already exists.\n"
                   "There is not enough space in this company for both of us\n");
            free(newWorker->name);
            free(newWorker);
            return;
        }
        else
        {
            //Adding the new worker to the list of workers
            workers[(*workerCount)] = newWorker;
            workers[(*workerCount)]->projectCount = 0;
            // A new worker joined, add one to the number of workers in the company
            (*workerCount)++;
        }
    }
        //Empty name
    else
    {
        printf("Invalid name\n");
        return;
    }
}

/*
 * The function prints the menu of the program
 */
void menu(void)
{
    printf("Welcome!\n"
           "Please select the desired option:\n"
           "1. Join the company\n"
           "2. Open a new project\n"
           "3. Join an existing project\n"
           "4. See what projects are in work\n"
           "5. See which people are in what projects\n"
           "6. Work on existing project\n"
           "7. Leave the company\n"
           "8. Exit\n");
}
